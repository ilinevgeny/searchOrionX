#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include "appsettings.h"
#include <dborionengine.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    AppSettings *dbSettings = new AppSettings();
    DBOrionEngine *db = new DBOrionEngine("QPSQL", "localhost", "orionconcept", 5432, "postgres", "ossrion");
    db->Connect();
    QString statusDb[2];
    statusDb[0] = (db->statusConnect) ? "Подключение успешно" : "Нет подключения";
    statusDb[1] = (db->statusConnect) ? "color: green" : "color: red;";
    statusBar()->showMessage(statusDb[0]);
    statusBar()->setStyleSheet("padding-bottom: 10;" + statusDb[1]);

}


void MainWindow::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text();

    qDebug() << input;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    AppSettings *s = new AppSettings(this);

    s->show();
    //statusBar()->showMessage("Настройки сохранены");
}
