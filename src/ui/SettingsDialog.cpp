#include "SettingsDialog.h"
#include "managers/ConfigManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QStandardPaths>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , m_configManager(ConfigManager::instance())
    , m_settingsChanged(false)
{
    setWindowTitle("设置");
    setModal(true);
    setupUI();
    loadSettings();
}

void SettingsDialog::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    m_tabWidget = new QTabWidget(this);
    
    setupGamePage();
    setupDisplayPage();
    setupAudioPage();
    
    mainLayout->addWidget(m_tabWidget);
    
    // 按钮
    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton("确定", QDialogButtonBox::AcceptRole);
    buttonBox->addButton("应用", QDialogButtonBox::ApplyRole);
    buttonBox->addButton("取消", QDialogButtonBox::RejectRole);
    buttonBox->addButton("重置", QDialogButtonBox::ResetRole);
    
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::onOkClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SettingsDialog::onCancelClicked);
    
    QPushButton* applyButton = buttonBox->button(QDialogButtonBox::Apply);
    if (applyButton) {
        connect(applyButton, &QPushButton::clicked, this, &SettingsDialog::onApplyClicked);
    }
    
    QPushButton* resetButton = buttonBox->button(QDialogButtonBox::Reset);
    if (resetButton) {
        connect(resetButton, &QPushButton::clicked, this, &SettingsDialog::onResetToDefaults);
    }
    
    mainLayout->addWidget(buttonBox);
}

void SettingsDialog::setupGamePage()
{
    QWidget* gamePage = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(gamePage);
    
    // 游戏模式设置
    QGroupBox* gameModeGroup = new QGroupBox("游戏模式");
    QFormLayout* gameModeLayout = new QFormLayout(gameModeGroup);
    
    m_gameModeCombo = new QComboBox();
    m_gameModeCombo->addItem("人人对战", static_cast<int>(GameEngine::PvP));
    m_gameModeCombo->addItem("人机对战", static_cast<int>(GameEngine::PvC));
    gameModeLayout->addRow("默认模式:", m_gameModeCombo);
    
    m_firstPlayerCombo = new QComboBox();
    m_firstPlayerCombo->addItem("黑方", static_cast<int>(ChessBoard::Black));
    m_firstPlayerCombo->addItem("白方", static_cast<int>(ChessBoard::White));
    gameModeLayout->addRow("先手方:", m_firstPlayerCombo);
    
    layout->addWidget(gameModeGroup);
    
    // AI设置
    QGroupBox* aiGroup = new QGroupBox("AI设置");
    QFormLayout* aiLayout = new QFormLayout(aiGroup);
    
    m_aiDifficultySlider = new QSlider(Qt::Horizontal);
    m_aiDifficultySlider->setRange(1, 3);
    m_aiDifficultySlider->setValue(2);
    m_aiDifficultyLabel = new QLabel("中等");
    
    connect(m_aiDifficultySlider, &QSlider::valueChanged, [this](int value) {
        QStringList levels = {"简单", "中等", "困难"};
        m_aiDifficultyLabel->setText(levels[value - 1]);
    });
    
    QHBoxLayout* difficultyLayout = new QHBoxLayout();
    difficultyLayout->addWidget(m_aiDifficultySlider);
    difficultyLayout->addWidget(m_aiDifficultyLabel);
    
    aiLayout->addRow("AI难度:", difficultyLayout);
    layout->addWidget(aiGroup);
    
    // 游戏选项
    QGroupBox* optionsGroup = new QGroupBox("游戏选项");
    QVBoxLayout* optionsLayout = new QVBoxLayout(optionsGroup);
    
    m_autoSaveCheck = new QCheckBox("自动保存游戏");
    m_showCoordinatesCheck = new QCheckBox("显示坐标");
    
    optionsLayout->addWidget(m_autoSaveCheck);
    optionsLayout->addWidget(m_showCoordinatesCheck);
    layout->addWidget(optionsGroup);
    
    layout->addStretch();
    
    m_tabWidget->addTab(gamePage, "游戏");
}

void SettingsDialog::setupDisplayPage()
{
    QWidget* displayPage = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(displayPage);
    
    // 界面设置
    QGroupBox* interfaceGroup = new QGroupBox("界面设置");
    QFormLayout* interfaceLayout = new QFormLayout(interfaceGroup);
    
    m_languageCombo = new QComboBox();
    m_languageCombo->addItem("中文", "zh_CN");
    m_languageCombo->addItem("English", "en_US");
    interfaceLayout->addRow("语言:", m_languageCombo);
    
    layout->addWidget(interfaceGroup);
    
    // 窗口设置
    QGroupBox* windowGroup = new QGroupBox("窗口设置");
    QFormLayout* windowLayout = new QFormLayout(windowGroup);
    
    m_windowWidthSpin = new QSpinBox();
    m_windowWidthSpin->setRange(640, 1920);
    m_windowWidthSpin->setValue(800);
    windowLayout->addRow("窗口宽度:", m_windowWidthSpin);
    
    m_windowHeightSpin = new QSpinBox();
    m_windowHeightSpin->setRange(480, 1080);
    m_windowHeightSpin->setValue(600);
    windowLayout->addRow("窗口高度:", m_windowHeightSpin);
    
    layout->addWidget(windowGroup);
    
    // 背景设置
    QGroupBox* backgroundGroup = new QGroupBox("背景设置");
    QFormLayout* backgroundLayout = new QFormLayout(backgroundGroup);
    
    m_backgroundImageEdit = new QLineEdit();
    m_backgroundImageEdit->setReadOnly(true);
    m_backgroundImageEdit->setPlaceholderText("未选择背景图片");
    
    m_browseBackgroundButton = new QPushButton("浏览...");
    connect(m_browseBackgroundButton, &QPushButton::clicked, this, &SettingsDialog::onBrowseBackgroundImage);
    
    m_clearBackgroundButton = new QPushButton("清除");
    connect(m_clearBackgroundButton, &QPushButton::clicked, this, &SettingsDialog::onClearBackgroundImage);
    
    QHBoxLayout* backgroundButtonLayout = new QHBoxLayout();
    backgroundButtonLayout->addWidget(m_browseBackgroundButton);
    backgroundButtonLayout->addWidget(m_clearBackgroundButton);
    backgroundButtonLayout->addStretch();
    
    backgroundLayout->addRow("背景图片:", m_backgroundImageEdit);
    backgroundLayout->addRow("", backgroundButtonLayout);
    
    m_backgroundOpacitySlider = new QSlider(Qt::Horizontal);
    m_backgroundOpacitySlider->setRange(10, 100);
    m_backgroundOpacitySlider->setValue(30);
    m_backgroundOpacityLabel = new QLabel("30%");
    
    connect(m_backgroundOpacitySlider, &QSlider::valueChanged, [this](int value) {
        m_backgroundOpacityLabel->setText(QString("%1%").arg(value));
    });
    
    QHBoxLayout* opacityLayout = new QHBoxLayout();
    opacityLayout->addWidget(m_backgroundOpacitySlider);
    opacityLayout->addWidget(m_backgroundOpacityLabel);
    
    backgroundLayout->addRow("透明度:", opacityLayout);
    
    layout->addWidget(backgroundGroup);
    layout->addStretch();
    
    m_tabWidget->addTab(displayPage, "显示");
}

void SettingsDialog::setupAudioPage()
{
    QWidget* audioPage = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(audioPage);
    
    // 音频设置
    QGroupBox* audioGroup = new QGroupBox("音频设置");
    QFormLayout* audioLayout = new QFormLayout(audioGroup);
    
    m_volumeSlider = new QSlider(Qt::Horizontal);
    m_volumeSlider->setRange(0, 100);
    m_volumeSlider->setValue(70);
    m_volumeLabel = new QLabel("70%");
    
    connect(m_volumeSlider, &QSlider::valueChanged, [this](int value) {
        m_volumeLabel->setText(QString("%1%").arg(value));
    });
    
    QHBoxLayout* volumeLayout = new QHBoxLayout();
    volumeLayout->addWidget(m_volumeSlider);
    volumeLayout->addWidget(m_volumeLabel);
    
    audioLayout->addRow("音量:", volumeLayout);
    
    m_soundEffectsCheck = new QCheckBox("启用音效");
    audioLayout->addRow("", m_soundEffectsCheck);
    
    layout->addWidget(audioGroup);
    
    // 背景音乐设置
    QGroupBox* musicGroup = new QGroupBox("背景音乐");
    QFormLayout* musicLayout = new QFormLayout(musicGroup);
    
    m_backgroundMusicEdit = new QLineEdit();
    m_backgroundMusicEdit->setReadOnly(true);
    m_backgroundMusicEdit->setPlaceholderText("未选择背景音乐");
    
    m_browseMusicButton = new QPushButton("浏览...");
    connect(m_browseMusicButton, &QPushButton::clicked, this, &SettingsDialog::onBrowseBackgroundMusic);
    
    m_clearMusicButton = new QPushButton("清除");
    connect(m_clearMusicButton, &QPushButton::clicked, this, &SettingsDialog::onClearBackgroundMusic);
    
    QHBoxLayout* musicButtonLayout = new QHBoxLayout();
    musicButtonLayout->addWidget(m_browseMusicButton);
    musicButtonLayout->addWidget(m_clearMusicButton);
    musicButtonLayout->addStretch();
    
    musicLayout->addRow("音乐文件:", m_backgroundMusicEdit);
    musicLayout->addRow("", musicButtonLayout);
    
    m_musicVolumeSlider = new QSlider(Qt::Horizontal);
    m_musicVolumeSlider->setRange(0, 100);
    m_musicVolumeSlider->setValue(30);
    m_musicVolumeLabel = new QLabel("30%");
    
    connect(m_musicVolumeSlider, &QSlider::valueChanged, [this](int value) {
        m_musicVolumeLabel->setText(QString("%1%").arg(value));
    });
    
    QHBoxLayout* musicVolumeLayout = new QHBoxLayout();
    musicVolumeLayout->addWidget(m_musicVolumeSlider);
    musicVolumeLayout->addWidget(m_musicVolumeLabel);
    
    musicLayout->addRow("音乐音量:", musicVolumeLayout);
    
    layout->addWidget(musicGroup);
    layout->addStretch();
    
    m_tabWidget->addTab(audioPage, "音频");
}

void SettingsDialog::loadSettings()
{
    // 加载游戏设置
    int gameMode = static_cast<int>(m_configManager->gameMode());
    m_gameModeCombo->setCurrentIndex(m_gameModeCombo->findData(gameMode));
    
    int firstPlayer = static_cast<int>(m_configManager->firstPlayer());
    m_firstPlayerCombo->setCurrentIndex(m_firstPlayerCombo->findData(firstPlayer));
    
    m_aiDifficultySlider->setValue(m_configManager->aiDifficulty());
    m_autoSaveCheck->setChecked(m_configManager->autoSave());
    m_showCoordinatesCheck->setChecked(m_configManager->showCoordinates());
    
    // 加载显示设置
    QString language = m_configManager->language();
    m_languageCombo->setCurrentIndex(m_languageCombo->findData(language));
    
    QSize windowSize = m_configManager->windowSize();
    m_windowWidthSpin->setValue(windowSize.width());
    m_windowHeightSpin->setValue(windowSize.height());
    
    // 加载背景设置
    QString backgroundImage = m_configManager->backgroundImage();
    m_backgroundImageEdit->setText(backgroundImage);
    
    float backgroundOpacity = m_configManager->backgroundOpacity();
    int opacityPercent = static_cast<int>(backgroundOpacity * 100);
    m_backgroundOpacitySlider->setValue(opacityPercent);
    m_backgroundOpacityLabel->setText(QString("%1%").arg(opacityPercent));
    
    // 加载音频设置
    int volume = static_cast<int>(m_configManager->volume() * 100);
    m_volumeSlider->setValue(volume);
    m_soundEffectsCheck->setChecked(m_configManager->soundEffectsEnabled());
    
    // 加载背景音乐设置
    QString backgroundMusic = m_configManager->backgroundMusic();
    m_backgroundMusicEdit->setText(backgroundMusic);
    
    int musicVolume = static_cast<int>(m_configManager->musicVolume() * 100);
    m_musicVolumeSlider->setValue(musicVolume);
    m_musicVolumeLabel->setText(QString("%1%").arg(musicVolume));
}

void SettingsDialog::applySettings()
{
    // 应用游戏设置
    GameEngine::GameMode gameMode = static_cast<GameEngine::GameMode>(
        m_gameModeCombo->currentData().toInt());
    m_configManager->setGameMode(gameMode);
    
    ChessBoard::PieceType firstPlayer = static_cast<ChessBoard::PieceType>(
        m_firstPlayerCombo->currentData().toInt());
    m_configManager->setFirstPlayer(firstPlayer);
    
    m_configManager->setAIDifficulty(m_aiDifficultySlider->value());
    m_configManager->setAutoSave(m_autoSaveCheck->isChecked());
    m_configManager->setShowCoordinates(m_showCoordinatesCheck->isChecked());
    
    // 应用显示设置
    QString language = m_languageCombo->currentData().toString();
    m_configManager->setLanguage(language);
    
    QSize windowSize(m_windowWidthSpin->value(), m_windowHeightSpin->value());
    m_configManager->setWindowSize(windowSize);
    
    // 应用背景设置
    QString backgroundImage = m_backgroundImageEdit->text();
    m_configManager->setBackgroundImage(backgroundImage);
    
    float backgroundOpacity = m_backgroundOpacitySlider->value() / 100.0f;
    m_configManager->setBackgroundOpacity(backgroundOpacity);
    
    // 应用音频设置
    float volume = m_volumeSlider->value() / 100.0f;
    m_configManager->setVolume(volume);
    m_configManager->setSoundEffectsEnabled(m_soundEffectsCheck->isChecked());
    
    // 应用背景音乐设置
    QString backgroundMusic = m_backgroundMusicEdit->text();
    m_configManager->setBackgroundMusic(backgroundMusic);
    
    float musicVolume = m_musicVolumeSlider->value() / 100.0f;
    m_configManager->setMusicVolume(musicVolume);
    
    m_configManager->saveSettings();
    m_settingsChanged = false;
}

void SettingsDialog::onOkClicked()
{
    applySettings();
    accept();
}

void SettingsDialog::onApplyClicked()
{
    applySettings();
}

void SettingsDialog::onCancelClicked()
{
    reject();
}

void SettingsDialog::onResetToDefaults()
{
    m_configManager->resetToDefaults();
    loadSettings();
}

void SettingsDialog::onBrowseBackgroundImage()
{
    QString imageFilter = "图片文件 (*.png *.jpg *.jpeg *.bmp *.gif);;所有文件 (*.*)";
    QString filename = QFileDialog::getOpenFileName(
        this,
        "选择背景图片",
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        imageFilter
    );
    
    if (!filename.isEmpty()) {
        m_backgroundImageEdit->setText(filename);
    }
}

void SettingsDialog::onClearBackgroundImage()
{
    m_backgroundImageEdit->clear();
}

void SettingsDialog::onBrowseBackgroundMusic()
{
    QString musicFilter = "音乐文件 (*.mp3 *.wav *.m4a *.aac *.ogg *.flac);;所有文件 (*.*)";
    QString filename = QFileDialog::getOpenFileName(
        this,
        "选择背景音乐",
        QStandardPaths::writableLocation(QStandardPaths::MusicLocation),
        musicFilter
    );
    
    if (!filename.isEmpty()) {
        m_backgroundMusicEdit->setText(filename);
    }
}

void SettingsDialog::onClearBackgroundMusic()
{
    m_backgroundMusicEdit->clear();
} 