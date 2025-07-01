#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMap>

// 音频管理器
class AudioManager : public QObject
{
    Q_OBJECT

public:
    enum SoundEffect {
        PiecePlaced = 0,
        GameWon = 1,
        GameDraw = 2,
        ButtonClick = 3,
        Undo = 4,
        Error = 5
    };
    
    static AudioManager* instance();
    
    // 音效播放
    void playEffect(SoundEffect effect);
    
    // 背景音乐
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();
    
    // 音量控制
    void setMasterVolume(float volume);
    float masterVolume() const { return m_masterVolume; }
    
    // 静音控制
    void setMuted(bool muted);
    bool isMuted() const { return m_muted; }

signals:
    void volumeChanged(float volume);
    void mutedChanged(bool muted);

private:
    explicit AudioManager(QObject *parent = nullptr);
    ~AudioManager();
    void initializeAudio();
    void createDefaultSounds();
    
    float m_masterVolume;
    bool m_muted;
    
    // 音效
    QMap<SoundEffect, QSoundEffect*> m_soundEffects;
    
    // 背景音乐
    QMediaPlayer* m_backgroundMusic;
    QMediaPlaylist* m_backgroundPlaylist;
    
    static AudioManager* s_instance;
};

#endif // AUDIOMANAGER_H 