#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dborionengine.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_action_triggered();

    void on_actionSELECT_triggered();

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QString sqlRequest;

};

#endif // MAINWINDOW_H
