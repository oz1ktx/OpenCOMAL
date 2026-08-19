#include "settings_dialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFontComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QStandardPaths>
#include <QSettings>
#include <QApplication>

namespace {
constexpr const char *kDefaultFontFamily = "Monospace";
constexpr int kDefaultFontSize = 11;
constexpr const char *kCpmDrivePathKey = "CpmDrive/HostPath";
}

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Settings"));
    setModal(true);
    resize(560, 380);

    createWidgets();
    connectSignals();
    loadSettings();
}

void SettingsDialog::createWidgets()
{
    auto *mainLayout = new QVBoxLayout(this);

    // ── Editor Font Group ────────────────────────────────────────────
    auto *editorGroup = new QGroupBox(tr("Editor Font"), this);
    auto *editorLayout = new QGridLayout(editorGroup);

    auto *editorFontLabel = new QLabel(tr("Font:"), this);
    editorFontCombo_ = new QFontComboBox(this);
    editorLayout->addWidget(editorFontLabel, 0, 0);
    editorLayout->addWidget(editorFontCombo_, 0, 1);

    auto *editorSizeLabel = new QLabel(tr("Size:"), this);
    editorFontSizeSpinBox_ = new QSpinBox(this);
    editorFontSizeSpinBox_->setMinimum(6);
    editorFontSizeSpinBox_->setMaximum(32);
    editorFontSizeSpinBox_->setValue(11);
    editorFontSizeSpinBox_->setSuffix(tr(" pt"));
    editorLayout->addWidget(editorSizeLabel, 1, 0);
    editorLayout->addWidget(editorFontSizeSpinBox_, 1, 1);

    mainLayout->addWidget(editorGroup);

    // ── Output Panel Font Group ──────────────────────────────────────
    auto *outputGroup = new QGroupBox(tr("Output Panel Font"), this);
    auto *outputLayout = new QGridLayout(outputGroup);

    auto *outputFontLabel = new QLabel(tr("Font:"), this);
    outputFontCombo_ = new QFontComboBox(this);
    outputLayout->addWidget(outputFontLabel, 0, 0);
    outputLayout->addWidget(outputFontCombo_, 0, 1);

    auto *outputSizeLabel = new QLabel(tr("Size:"), this);
    outputFontSizeSpinBox_ = new QSpinBox(this);
    outputFontSizeSpinBox_->setMinimum(6);
    outputFontSizeSpinBox_->setMaximum(32);
    outputFontSizeSpinBox_->setValue(11);
    outputFontSizeSpinBox_->setSuffix(tr(" pt"));
    outputLayout->addWidget(outputSizeLabel, 1, 0);
    outputLayout->addWidget(outputFontSizeSpinBox_, 1, 1);

    mainLayout->addWidget(outputGroup);

    // ── CP/M Drive Mapping Group ──────────────────────────────────────
    auto *cpmGroup = new QGroupBox(tr("CP/M Drive Mapping"), this);
    auto *cpmLayout = new QGridLayout(cpmGroup);

    auto *cpmLabel = new QLabel(tr("Host folder:"), this);
    cpmDrivePathEdit_ = new QLineEdit(this);
    cpmDrivePathEdit_->setPlaceholderText(tr("Leave empty to use the program folder"));
    browseCpmDrivePathButton_ = new QPushButton(tr("Browse..."), this);
    cpmLayout->addWidget(cpmLabel, 0, 0);
    cpmLayout->addWidget(cpmDrivePathEdit_, 0, 1);
    cpmLayout->addWidget(browseCpmDrivePathButton_, 0, 2);

    auto *cpmHint = new QLabel(
        tr("Z80/CP-M file operations will read and write files in this folder when set."), this);
    cpmHint->setWordWrap(true);
    cpmLayout->addWidget(cpmHint, 1, 0, 1, 3);

    mainLayout->addWidget(cpmGroup);

    // ── Buttons ──────────────────────────────────────────────────────
    mainLayout->addStretch();

    auto *buttonLayout = new QHBoxLayout;
    okButton_ = new QPushButton(tr("OK"), this);
    cancelButton_ = new QPushButton(tr("Cancel"), this);
    applyButton_ = new QPushButton(tr("Apply"), this);
    resetDefaultsButton_ = new QPushButton(tr("Reset Defaults"), this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(resetDefaultsButton_);
    buttonLayout->addWidget(applyButton_);
    buttonLayout->addWidget(okButton_);
    buttonLayout->addWidget(cancelButton_);

    mainLayout->addLayout(buttonLayout);
}

void SettingsDialog::connectSignals()
{
    connect(okButton_, &QPushButton::clicked, this, &SettingsDialog::onOkClicked);
    connect(cancelButton_, &QPushButton::clicked, this, &SettingsDialog::onCancelClicked);
    connect(applyButton_, &QPushButton::clicked, this, &SettingsDialog::onApply);
    connect(resetDefaultsButton_, &QPushButton::clicked, this, &SettingsDialog::onResetDefaultsClicked);
    connect(browseCpmDrivePathButton_, &QPushButton::clicked, this, &SettingsDialog::onBrowseCpmDrivePath);
}

void SettingsDialog::loadSettings()
{
    // QSettings respects XDG_CONFIG_HOME by default
    // If XDG_CONFIG_HOME is not set, defaults to ~/.config
    QSettings settings("OpenCOMAL", "IDE");

    // Load editor font settings
    QString editorFontFamily = settings.value("EditorFont/Family", kDefaultFontFamily).toString();
    int editorFontSize = settings.value("EditorFont/Size", kDefaultFontSize).toInt();

    editorFontCombo_->setCurrentFont(QFont(editorFontFamily));
    editorFontSizeSpinBox_->setValue(editorFontSize);

    // Load output font settings
    QString outputFontFamily = settings.value("OutputFont/Family", kDefaultFontFamily).toString();
    int outputFontSize = settings.value("OutputFont/Size", kDefaultFontSize).toInt();

    outputFontCombo_->setCurrentFont(QFont(outputFontFamily));
    outputFontSizeSpinBox_->setValue(outputFontSize);

    cpmDrivePathEdit_->setText(settings.value(kCpmDrivePathKey, QString()).toString());
}

void SettingsDialog::saveSettings()
{
    QSettings settings("OpenCOMAL", "IDE");

    // Save editor font settings
    settings.setValue("EditorFont/Family", editorFontCombo_->currentFont().family());
    settings.setValue("EditorFont/Size", editorFontSizeSpinBox_->value());

    // Save output font settings
    settings.setValue("OutputFont/Family", outputFontCombo_->currentFont().family());
    settings.setValue("OutputFont/Size", outputFontSizeSpinBox_->value());
    settings.setValue(kCpmDrivePathKey, cpmDrivePathEdit_->text().trimmed());

    settings.sync();
}

void SettingsDialog::onApply()
{
    saveSettings();
    editorFont_ = QFont(editorFontCombo_->currentFont().family(), editorFontSizeSpinBox_->value());
    outputFont_ = QFont(outputFontCombo_->currentFont().family(), outputFontSizeSpinBox_->value());
    emit fontsApplied(editorFont_, outputFont_);
}

void SettingsDialog::onOkClicked()
{
    onApply();
    accept();
}

void SettingsDialog::onCancelClicked()
{
    reject();
}

void SettingsDialog::onResetDefaultsClicked()
{
    editorFontCombo_->setCurrentFont(QFont(kDefaultFontFamily));
    editorFontSizeSpinBox_->setValue(kDefaultFontSize);
    outputFontCombo_->setCurrentFont(QFont(kDefaultFontFamily));
    outputFontSizeSpinBox_->setValue(kDefaultFontSize);
    cpmDrivePathEdit_->clear();

    // Apply immediately so users can preview defaults without closing the dialog.
    onApply();
}

void SettingsDialog::onBrowseCpmDrivePath()
{
    const QString startDir = cpmDrivePathEdit_->text().trimmed().isEmpty()
        ? QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
        : cpmDrivePathEdit_->text().trimmed();
    const QString folder = QFileDialog::getExistingDirectory(
        this, tr("Select CP/M Drive Folder"), startDir,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!folder.isEmpty()) {
        cpmDrivePathEdit_->setText(folder);
    }
}

QFont SettingsDialog::editorFont() const
{
    return editorFont_;
}

QFont SettingsDialog::outputFont() const
{
    return outputFont_;
}

QString SettingsDialog::cpmDrivePath() const
{
    return cpmDrivePathEdit_->text().trimmed();
}
