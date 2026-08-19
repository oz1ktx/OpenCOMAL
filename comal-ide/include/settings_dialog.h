#pragma once
#include <QDialog>
#include <QFont>
#include <QString>

class QFontComboBox;
class QSpinBox;
class QPushButton;
class QLineEdit;

// Settings dialog for configuring editor/output fonts and sizes.
// Uses QSettings with XDG_CONFIG_HOME support.
class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    QFont editorFont() const;
    QFont outputFont() const;
    QString cpmDrivePath() const;

signals:
    void fontsApplied(const QFont &editorFont, const QFont &outputFont);

private slots:
    void onApply();
    void onOkClicked();
    void onCancelClicked();
    void onResetDefaultsClicked();
    void onBrowseCpmDrivePath();
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

    // CP/M drive mapping
    QLineEdit     *cpmDrivePathEdit_;
    QPushButton   *browseCpmDrivePathButton_;

    // Buttons
    QPushButton *okButton_;
    QPushButton *cancelButton_;
    QPushButton *applyButton_;
    QPushButton *resetDefaultsButton_;
};
