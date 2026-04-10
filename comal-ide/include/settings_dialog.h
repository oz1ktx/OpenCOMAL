#pragma once
#include <QDialog>
#include <QFont>

class QFontComboBox;
class QSpinBox;
class QPushButton;

// Settings dialog for configuring editor/output fonts and sizes.
// Uses QSettings with XDG_CONFIG_HOME support.
class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    QFont editorFont() const;
    QFont outputFont() const;

signals:
    void fontsApplied(const QFont &editorFont, const QFont &outputFont);

private slots:
    void onApply();
    void onOkClicked();
    void onCancelClicked();
    void onResetDefaultsClicked();
    void loadSettings();
    void saveSettings();

private:
    void createWidgets();
    void connectSignals();

    // Editor font settings
    QFontComboBox *editorFontCombo_;
    QSpinBox      *editorFontSizeSpinBox_;
    QFont         editorFont_;

    // Output font settings
    QFontComboBox *outputFontCombo_;
    QSpinBox      *outputFontSizeSpinBox_;
    QFont         outputFont_;

    // Buttons
    QPushButton *okButton_;
    QPushButton *cancelButton_;
    QPushButton *applyButton_;
    QPushButton *resetDefaultsButton_;
};
