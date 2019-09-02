#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include "appsettings.h"
#include <dborionengine.h>
#include <QStandardItemModel>
#include <QMap>
#include <QTime>
#include <sqlform.h>
/*
 * @todo
 * - add widget for running sql
 * - save some sql queries
 *
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* todo:
     * add load or changes settings for connection
     */
    DBOrionEngine *db = new DBOrionEngine("QPSQL", "192.168.201.65", "orionconcept", 5432, "postgres", "orion");
    db->Connect();
    QString statusDb[2];
    statusDb[0] = (db->statusConnect) ? "Подключение успешно" : "Нет подключения";
    statusDb[1] = (db->statusConnect) ? "color: green" : "color: red;";



    QSqlQuery query;
    QString sQuery;
    int countRows = 0;
    sQuery = "SELECT count(*) as countemp FROM \"InstanceX\" WHERE \"IType\" = \'00000000-0000-0000-0000-000000008001\';";

    if (query.exec(sQuery))
    {
        if(query.size() > 0)
        {
            while (query.next()) {
                countRows = query.value("countemp").toInt();
            }
        }
     }




    statusBar()->showMessage(statusDb[0] + ". \n Количество сотрудников в таблице: " + QString::number(countRows));
    statusBar()->setStyleSheet("padding-bottom: 10px; "+statusDb[1]);
}


void MainWindow::on_pushButton_clicked()
{
    ui->statusBar->showMessage("");
    ui->statusBar->setStyleSheet("color: unset");

    QString input = ui->lineEdit->text();

    qDebug() << input;
    QSqlQuery query;
    QString result;
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(5);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Связь ключ-сотрудник")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Тип ключа на сотруднике")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Уровень Доступа и Раздел")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Связь Вход-Раздел")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Входы сотрудника")));

    QString emplName;
    emplName = input;
    QTime myTimer;
    myTimer.start();
    if (query.exec("SELECT \"keys\".\"ISetName\" as keyOfEmployee, 													" \
                   "	\"iKey\".\"IName\" AS nameOfKey, 															" \
                   "	\"sSection\".\"ISetName\" AS nameOfAuthority , 												" \
                   "	\"circuit\".\"ISetName\" AS circuitOfSection, 												" \
                   "	\"circuitName\".\"IName\" as nameOfCircuit    												" \
                   "FROM \"ISetX\" \"keys\" 																		" \
                   "INNER JOIN \"InstanceX\" \"sotr\" 																" \
                   "ON \"keys\".\"ISOWNER\" = \"sotr\".\"IUUID\" ANd \"keys\".\"ISConcept\" = 400200				" \
                   "INNER JOIN \"InstanceX\" \"iKey\"				 												" \
                   "ON \"iKey\".\"IUUID\" = \"keys\".\"ISUUID1\"													" \
                   "INNER JOIN \"ISetX\" \"sSection\" 																" \
                   "ON \"sSection\".\"ISOWNER\" = \"iKey\".\"IUUID1\"  ANd \"sSection\".\"ISConcept\" = 400100		" \
                   "INNER JOIN \"ISetX\" \"circuit\" 																" \
                   "ON \"circuit\".\"ISOWNER\" = \"sSection\".\"ISUUID1\" AND \"circuit\".\"ISConcept\" = 500100	" \
                   "INNER JOIN \"InstanceX\" \"circuitName\" 														" \
                   "ON \"circuitName\".\"IUUID\" = \"circuit\".\"ISUUID1\"											" \
                   "WHERE \"sotr\".\"IName\" like \'%"+emplName+"%\'"))
    {
        if(query.size() > 0){
            model->setRowCount(query.size());
            int row = 0;
            while (query.next()) {
                result = "<b>Связь ключ-сотрудник:</b> " + query.value("keyOfEmployee").toString() + "\n";
                result += "Тип ключа на сотруднике: " + query.value("nameOfKey").toString();
                result += "Связь Уровень Доступа и Раздел: " + query.value("nameOfAuthority").toString();
                result += "Связь Вход-Раздел: " + query.value("circuitOfSection").toString();
                result += "Входы контролируемые сотрудником: " + query.value("circuitOfSection").toString();
                 model->setData(model->index(row, 0), query.value("keyOfEmployee").toString());
                 model->setData(model->index(row, 1), query.value("nameOfKey").toString());
                 model->setData(model->index(row, 2), query.value("nameOfAuthority").toString());
                 model->setData(model->index(row, 3), query.value("circuitOfSection").toString());
                 model->setData(model->index(row, 4), query.value("nameOfCircuit").toString());
                 row++;
            }

            QMap <QString, int> myMap;
            myMap.insert("GG", 166666);
            QString recordsCase = QString::number(query.size());
            recordsCase = "22";
            /* @todo
             * set case of counter from qmap
             */
//            if(recordsCase.rightRef(1).toInt() == 1){
//                qDebug() << "its found";
                //1 .. 21 запись
                // 2,3,4 .. 22, 33, записи
                // 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 .. 20... 35, 36, 37 записей

//            }

            double nMilliseconds = myTimer.elapsed();
            nMilliseconds = nMilliseconds / 1000;
            statusBar()->showMessage("Запрос вернул: " + QString::number(query.size()) + " строк за " + QString::number(nMilliseconds) + " секунд");

        } else {
            ui->statusBar->showMessage("Запрос не вернул результат");
            statusBar()->setStyleSheet("color: red");
        }
    }
    ui->tableView->setModel(model);

    for (int i = 0; i < 5; i++ ) {
         ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui->tableView->setStyleSheet("QHeaderView::section { background-color: #ccc }");


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

void MainWindow::on_actionSELECT_triggered()
{
    Sqlform *sForm = new Sqlform();
    sForm->show();
}

void MainWindow::on_lineEdit_returnPressed()
{
    this->on_pushButton_clicked();
}

