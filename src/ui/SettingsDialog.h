#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QComboBox>
#include <QSlider>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class ConfigManager;

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    
    void loadSettings();
    void applySettings();

private slots:
    void onOkClicked();
    void onApplyClicked();
    void onCancelClicked();
    void onResetToDefaults();
    void onBrowseBackgroundImage();
    void onClearBackgroundImage();
    void onBrowseBackgroundMusic();
    void onClearBackgroundMusic();

private:
    void setupUI();
    void setupGamePage();
    void setupDisplayPage();
    void setupAudioPage();
    
    // UI组件
    QTabWidget* m_tabWidget;
    
    // 游戏设置
    QComboBox* m_gameModeCombo;
    QComboBox* m_firstPlayerCombo;
    QSlider* m_aiDifficultySlider;
    QLabel* m_aiDifficultyLabel;
    QCheckBox* m_autoSaveCheck;
    QCheckBox* m_showCoordinatesCheck;
    
    // 显示设置
    QComboBox* m_languageCombo;
    QSpinBox* m_windowWidthSpin;
    QSpinBox* m_windowHeightSpin;
    QLineEdit* m_backgroundImageEdit;
    QPushButton* m_browseBackgroundButton;
    QPushButton* m_clearBackgroundButton;
    QSlider* m_backgroundOpacitySlider;
    QLabel* m_backgroundOpacityLabel;
    
    // 音效设置
    QSlider* m_volumeSlider;
    QLabel* m_volumeLabel;
    QCheckBox* m_soundEffectsCheck;
    
    // 背景音乐设置
    QLineEdit* m_backgroundMusicEdit;
    QPushButton* m_browseMusicButton;
    QPushButton* m_clearMusicButton;
    QSlider* m_musicVolumeSlider;
    QLabel* m_musicVolumeLabel;
    
    ConfigManager* m_configManager;
    bool m_settingsChanged;
};

#endif // SETTINGSDIALOG_H 