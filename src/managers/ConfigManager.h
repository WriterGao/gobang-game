#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QSettings>
#include <QSize>
#include "core/GameEngine.h"
#include "core/ChessBoard.h"

class ConfigManager : public QObject
{
    Q_OBJECT

public:
    static ConfigManager* instance();
    
    // 游戏设置
    GameEngine::GameMode gameMode() const;
    void setGameMode(GameEngine::GameMode mode);
    
    ChessBoard::PieceType firstPlayer() const;
    void setFirstPlayer(ChessBoard::PieceType player);
    
    int aiDifficulty() const;
    void setAIDifficulty(int difficulty);
    
    bool autoSave() const;
    void setAutoSave(bool enabled);
    
    bool showCoordinates() const;
    void setShowCoordinates(bool show);
    
    // 显示设置
    QString backgroundImage() const;
    void setBackgroundImage(const QString& path);
    
    float backgroundOpacity() const;
    void setBackgroundOpacity(float opacity);
    
    QString theme() const;
    void setTheme(const QString& theme);
    
    QString language() const;
    void setLanguage(const QString& language);
    
    QSize windowSize() const;
    void setWindowSize(const QSize& size);
    
    // 音频设置
    QString backgroundMusic() const;
    void setBackgroundMusic(const QString& path);
    
    float volume() const;
    void setVolume(float volume);
    
    float musicVolume() const;
    void setMusicVolume(float volume);
    
    bool soundEffectsEnabled() const;
    void setSoundEffectsEnabled(bool enabled);
    
    // 配置管理
    void saveSettings();
    void loadSettings();
    void resetToDefaults();
    bool isConfigValid() const;

signals:
    void gameModeChanged(GameEngine::GameMode mode);
    void aiDifficultyChanged(int difficulty);
    void showCoordinatesChanged(bool show);
    void backgroundImageChanged(const QString& path);
    void backgroundMusicChanged(const QString& path);
    void volumeChanged(float volume);
    void languageChanged(const QString& language);
    void themeChanged(const QString& theme);

private:
    explicit ConfigManager(QObject *parent = nullptr);
    void initializeDefaults();
    void validateSettings();
    
    QSettings* m_settings;
    static ConfigManager* s_instance;
};

#endif // CONFIGMANAGER_H 