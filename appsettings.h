#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QWidget>
#include <QDialog>
#include <QSettings>

namespace Ui {
class AppSettings;
}

class AppSettings : public QWidget
{
    Q_OBJECT

public:
    explicit AppSettings(QWidget *parent = nullptr);
    ~AppSettings();
    bool correctSettings;

private slots:
    void on_pushButton_clicked();
    void saveButton();


private:
    Ui::AppSettings *ui;
    QSettings *dbSettings;
};

#endif // APPSETTINGS_H
