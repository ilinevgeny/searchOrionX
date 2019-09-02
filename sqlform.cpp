#include "sqlform.h"
#include "ui_sqlform.h"

Sqlform::Sqlform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sqlform)
{
    ui->setupUi(this);
}

Sqlform::~Sqlform()
{
    delete ui;
}
