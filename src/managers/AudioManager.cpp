#include "AudioManager.h"
#include "managers/ConfigManager.h"
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QUrl>
#include <QApplication>
#include <QFileInfo>
#if defined(Q_OS_MAC)
#include <QSound>
#endif

AudioManager* AudioManager::s_instance = nullptr;

AudioManager* AudioManager::instance()
{
    if (!s_instance) {
        s_instance = new AudioManager();
    }
    return s_instance;
}

AudioManager::AudioManager(QObject *parent)
    : QObject(parent)
    , m_masterVolume(0.7f)
    , m_muted(false)
    , m_backgroundMusic(nullptr)
{
    initializeAudio();
}

AudioManager::~AudioManager()
{
    // 确保停止所有音乐播放
    stopBackgroundMusic();
}

void AudioManager::initializeAudio()
{
    // 初始化背景音乐播放器
    m_backgroundMusic = new QMediaPlayer(this);
    m_backgroundPlaylist = new QMediaPlaylist(this);
    m_backgroundMusic->setPlaylist(m_backgroundPlaylist);
    
    // 创建默认音效
    createDefaultSounds();
}

void AudioManager::createDefaultSounds()
{
    // 由于没有实际音频文件，我们创建简单的提示音效
    // 在实际项目中，这里会加载真实的音频文件
    
    for (int i = 0; i < 6; ++i) {
        QSoundEffect* effect = new QSoundEffect(this);
        // 这里应该设置音频文件路径
        // effect->setSource(QUrl::fromLocalFile(":/sounds/effect.wav"));
        effect->setVolume(m_masterVolume);
        m_soundEffects.insert(static_cast<SoundEffect>(i), effect);
    }
}

void AudioManager::playEffect(SoundEffect effect)
{
    if (m_muted) {
        return;
    }
    
    // 输出调试信息（保留原有功能）
    switch (effect) {
        case PiecePlaced:
            qDebug() << "Playing piece placed sound";
            break;
        case GameWon:
            qDebug() << "Playing game won sound";
            break;
        case GameDraw:
            qDebug() << "Playing game draw sound";
            break;
        case ButtonClick:
            qDebug() << "Playing button click sound";
            break;
        case Undo:
            qDebug() << "Playing undo sound";
            break;
        case Error:
            qDebug() << "Playing error sound";
            break;
    }
    
    // 播放系统提示音
    if (!m_muted) {
        // 在macOS上播放系统声音
        #if defined(Q_OS_MAC)
        QString soundFile;
        switch (effect) {
            case PiecePlaced:
                soundFile = "/System/Library/Sounds/Tink.aiff";
                break;
            case GameWon:
                soundFile = "/System/Library/Sounds/Glass.aiff";
                break;
            case GameDraw:
                soundFile = "/System/Library/Sounds/Sosumi.aiff";
                break;
            case ButtonClick:
                soundFile = "/System/Library/Sounds/Pop.aiff";
                break;
            case Undo:
                soundFile = "/System/Library/Sounds/Funk.aiff";
                break;
            case Error:
                soundFile = "/System/Library/Sounds/Basso.aiff";
                break;
        }
        
        if (!soundFile.isEmpty()) {
            QString command = QString("afplay \"%1\" &").arg(soundFile);
            system(command.toUtf8().constData());
        }
        #else
        // 其他平台使用系统提示音
        QApplication::beep();
        #endif
    }
    
    // 播放音效（如果有音频文件的话）
    if (m_soundEffects.contains(effect)) {
        QSoundEffect* soundEffect = m_soundEffects[effect];
        if (soundEffect && soundEffect->isLoaded()) {
            soundEffect->setVolume(m_masterVolume);
            soundEffect->play();
        }
    }
}

void AudioManager::playBackgroundMusic()
{
    if (m_muted || !m_backgroundMusic) {
        return;
    }
    
    ConfigManager* configManager = ConfigManager::instance();
    QString musicPath = configManager->backgroundMusic();
    
    if (!musicPath.isEmpty() && QFileInfo::exists(musicPath)) {
        qDebug() << "Starting background music:" << musicPath;
        
        // 在macOS上使用系统播放器
        #if defined(Q_OS_MAC)
        // 停止当前播放
        stopBackgroundMusic();
        
        // 使用afplay播放背景音乐（循环播放）
        float musicVolume = configManager->musicVolume();
        int volumePercent = static_cast<int>(musicVolume * 100);
        
        // 添加标识符以便于管理进程
        QString command = QString("nohup sh -c 'while true; do afplay -v %1 \"%2\" 2>/dev/null; done' >/dev/null 2>&1 &")
                         .arg(musicVolume)
                         .arg(musicPath);
        system(command.toUtf8().constData());
        
        qDebug() << "Background music started with volume:" << volumePercent << "%";
        #else
        // 其他平台使用Qt播放器
        // 清空播放列表并添加新音乐
        m_backgroundPlaylist->clear();
        m_backgroundPlaylist->addMedia(QUrl::fromLocalFile(musicPath));
        
        // 设置音量（使用音乐专用音量设置）
        float musicVolume = configManager->musicVolume();
        m_backgroundMusic->setVolume(musicVolume * 100); // QMediaPlayer使用0-100范围
        
        m_backgroundPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        m_backgroundMusic->play();
        
        // 添加错误处理
        connect(m_backgroundMusic, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
                [=](QMediaPlayer::Error error) {
                    qDebug() << "Background music error:" << error << m_backgroundMusic->errorString();
                });
        #endif
    } else {
        qDebug() << "No valid background music file configured";
    }
}

void AudioManager::stopBackgroundMusic()
{
    #if defined(Q_OS_MAC)
    // 在macOS上停止afplay进程，包括相关的shell进程
    system("pkill -f \"while true.*afplay\" 2>/dev/null");
    system("killall afplay 2>/dev/null");
    system("pkill -f \"nohup sh.*afplay\" 2>/dev/null");
    qDebug() << "Background music stopped (afplay)";
    #endif
    
    if (m_backgroundMusic) {
        m_backgroundMusic->stop();
        qDebug() << "Background music stopped (Qt)";
    }
}

void AudioManager::pauseBackgroundMusic()
{
    #if defined(Q_OS_MAC)
    system("killall -STOP afplay 2>/dev/null");
    qDebug() << "Background music paused (afplay)";
    #endif
    
    if (m_backgroundMusic) {
        m_backgroundMusic->pause();
        qDebug() << "Background music paused (Qt)";
    }
}

void AudioManager::resumeBackgroundMusic()
{
    #if defined(Q_OS_MAC)
    system("killall -CONT afplay 2>/dev/null");
    qDebug() << "Background music resumed (afplay)";
    #endif
    
    if (m_backgroundMusic) {
        m_backgroundMusic->play();
        qDebug() << "Background music resumed (Qt)";
    }
}

void AudioManager::setMasterVolume(float volume)
{
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 1.0f) volume = 1.0f;
    
    if (m_masterVolume != volume) {
        m_masterVolume = volume;
        
        // 更新所有音效的音量
        for (auto it = m_soundEffects.begin(); it != m_soundEffects.end(); ++it) {
            if (it.value()) {
                it.value()->setVolume(volume);
            }
        }
        
        // 更新背景音乐音量（使用专用的音乐音量设置）
        if (m_backgroundMusic) {
            ConfigManager* configManager = ConfigManager::instance();
            float musicVolume = configManager->musicVolume();
            m_backgroundMusic->setVolume(musicVolume * 100);
        }
        
        emit volumeChanged(volume);
    }
}

void AudioManager::setMuted(bool muted)
{
    if (m_muted != muted) {
        m_muted = muted;
        emit mutedChanged(muted);
    }
} 