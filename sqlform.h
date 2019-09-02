#ifndef SQLFORM_H
#define SQLFORM_H

#include <QWidget>

namespace Ui {
class Sqlform;
}

class Sqlform : public QWidget
{
    Q_OBJECT

public:
    explicit Sqlform(QWidget *parent = nullptr);
    ~Sqlform();

private:
    Ui::Sqlform *ui;
};

#endif // SQLFORM_H
