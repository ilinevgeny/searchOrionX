#ifndef ORIONSQLQUERY_H
#define ORIONSQLQUERY_H

#include <QSqlQuery>


class OrionSqlQuery : public QSqlQuery
{

public:
    explicit OrionSqlQuery();
    ~OrionSqlQuery();
};

#endif // ORIONSQLQUERY_H
