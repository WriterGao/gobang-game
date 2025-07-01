#include "ConfigManager.h"
#include <QStandardPaths>
#include <QDir>

ConfigManager* ConfigManager::s_instance = nullptr;

ConfigManager* ConfigManager::instance()
{
    if (!s_instance) {
        s_instance = new ConfigManager();
    }
    return s_instance;
}

ConfigManager::ConfigManager(QObject *parent)
    : QObject(parent)
{
    // 使用用户配置目录
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    QDir().mkpath(configPath);
    
    m_settings = new QSettings(configPath + "/gobang.ini", QSettings::IniFormat, this);
    
    loadSettings();
}

GameEngine::GameMode ConfigManager::gameMode() const
{
    return static_cast<GameEngine::GameMode>(m_settings->value("Game/Mode", GameEngine::PvP).toInt());
}

void ConfigManager::setGameMode(GameEngine::GameMode mode)
{
    m_settings->setValue("Game/Mode", static_cast<int>(mode));
    emit gameModeChanged(mode);
}

int ConfigManager::aiDifficulty() const
{
    return m_settings->value("Game/AIDifficulty", 2).toInt();
}

void ConfigManager::setAIDifficulty(int difficulty)
{
    m_settings->setValue("Game/AIDifficulty", difficulty);
    emit aiDifficultyChanged(difficulty);
}

bool ConfigManager::showCoordinates() const
{
    return m_settings->value("Game/ShowCoordinates", true).toBool();
}

void ConfigManager::setShowCoordinates(bool show)
{
    m_settings->setValue("Game/ShowCoordinates", show);
    emit showCoordinatesChanged(show);
}

QSize ConfigManager::windowSize() const
{
    return m_settings->value("Display/WindowSize", QSize(800, 600)).toSize();
}

void ConfigManager::setWindowSize(const QSize& size)
{
    m_settings->setValue("Display/WindowSize", size);
}

void ConfigManager::saveSettings()
{
    m_settings->sync();
}

void ConfigManager::loadSettings()
{
    // 设置已经自动从文件加载
}

ChessBoard::PieceType ConfigManager::firstPlayer() const
{
    return static_cast<ChessBoard::PieceType>(m_settings->value("Game/FirstPlayer", ChessBoard::Black).toInt());
}

void ConfigManager::setFirstPlayer(ChessBoard::PieceType player)
{
    m_settings->setValue("Game/FirstPlayer", static_cast<int>(player));
}

bool ConfigManager::autoSave() const
{
    return m_settings->value("Game/AutoSave", true).toBool();
}

void ConfigManager::setAutoSave(bool enabled)
{
    m_settings->setValue("Game/AutoSave", enabled);
}

QString ConfigManager::backgroundImage() const
{
    return m_settings->value("Display/BackgroundImage", "").toString();
}

void ConfigManager::setBackgroundImage(const QString& path)
{
    m_settings->setValue("Display/BackgroundImage", path);
    emit backgroundImageChanged(path);
}

float ConfigManager::backgroundOpacity() const
{
    return m_settings->value("Display/BackgroundOpacity", 0.3f).toFloat();
}

void ConfigManager::setBackgroundOpacity(float opacity)
{
    m_settings->setValue("Display/BackgroundOpacity", opacity);
}

QString ConfigManager::theme() const
{
    return m_settings->value("Display/Theme", "classic").toString();
}

void ConfigManager::setTheme(const QString& theme)
{
    m_settings->setValue("Display/Theme", theme);
    emit themeChanged(theme);
}

QString ConfigManager::language() const
{
    return m_settings->value("Display/Language", "zh_CN").toString();
}

void ConfigManager::setLanguage(const QString& language)
{
    m_settings->setValue("Display/Language", language);
    emit languageChanged(language);
}

QString ConfigManager::backgroundMusic() const
{
    return m_settings->value("Audio/BackgroundMusic", "").toString();
}

void ConfigManager::setBackgroundMusic(const QString& path)
{
    m_settings->setValue("Audio/BackgroundMusic", path);
    emit backgroundMusicChanged(path);
}

float ConfigManager::volume() const
{
    return m_settings->value("Audio/Volume", 0.7f).toFloat();
}

void ConfigManager::setVolume(float volume)
{
    m_settings->setValue("Audio/Volume", volume);
    emit volumeChanged(volume);
}

float ConfigManager::musicVolume() const
{
    return m_settings->value("Audio/MusicVolume", 0.3f).toFloat();
}

void ConfigManager::setMusicVolume(float volume)
{
    m_settings->setValue("Audio/MusicVolume", volume);
}

bool ConfigManager::soundEffectsEnabled() const
{
    return m_settings->value("Audio/SoundEffects", true).toBool();
}

void ConfigManager::setSoundEffectsEnabled(bool enabled)
{
    m_settings->setValue("Audio/SoundEffects", enabled);
}

void ConfigManager::resetToDefaults()
{
    m_settings->clear();
    saveSettings();
}

bool ConfigManager::isConfigValid() const
{
    return true;
} 