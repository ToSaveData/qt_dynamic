#ifndef PERSONALMODEL_H
#define PERSONALMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "person.h"

class PersonalModel : public QAbstractListModel
{
public:
    explicit PersonalModel(QObject *parent = nullptr);
    ~PersonalModel() override;

    //QAbstractItemModel inerface
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<Person*> persons;
};

#endif // PERSONALMODEL_H
