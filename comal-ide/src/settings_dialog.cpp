#include "settings_dialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFontComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QSettings>
#include <QApplication>

namespace {
constexpr const char *kDefaultFontFamily = "Monospace";
constexpr int kDefaultFontSize = 11;
}

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Settings"));
    setModal(true);
    resize(500, 300);

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

    // Apply immediately so users can preview defaults without closing the dialog.
    onApply();
}

QFont SettingsDialog::editorFont() const
{
    return editorFont_;
}

QFont SettingsDialog::outputFont() const
{
    return outputFont_;
}
