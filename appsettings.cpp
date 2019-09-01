#include "appsettings.h"
#include "ui_appsettings.h"
#include <QString>
#include <QDebug>
AppSettings::AppSettings(QWidget *parent) :
    QWidget (parent),
    ui(new Ui::AppSettings)
{


    this->dbSettings = new QSettings("BOLID", "searchApp");

//    QSettings dbSettings("BOLID", "searchApp");
     this->dbSettings->setValue("DB/Driver", "QPSQL");
     this->dbSettings->setValue("DB/Server", "localhost");
     this->dbSettings->setValue("DB/DBName", "orionconcept");
     this->dbSettings->setValue("DB/Port", "5432");
     this->dbSettings->setValue("DB/User", "postgres");
     this->dbSettings->setValue("DB/Password", "orion");

    ui->setupUi(this);
    ui->LineEdit->setText(this->dbSettings->value("DB/Driver").toString());
//    ui->LineEdit_2->setText(this->dbSettings->value("DB/Server").toString());

    this->correctSettings = false;
    this->setWindowFlags(Qt::Window);

    QObject::connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(saveButton()));
}

AppSettings::~AppSettings()
{
    delete ui;
}

void AppSettings::on_pushButton_clicked()
{
    this->close();
}

void AppSettings::saveButton()
{

    this->dbSettings->setValue("DB/Driver", ui->LineEdit->text());
//    this->correctSettings = true;
   if(!this->correctSettings) {
        ui->textBrowser->setHtml("<b style=\"color: red\">Заданы неправильные параметры</b>");
    }


}


