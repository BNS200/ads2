#pragma once

#include <QWidget>
#include "HashTable.h"



QT_BEGIN_NAMESPACE
namespace Ui { class BaseHashTableWidget; }
QT_END_NAMESPACE

class BaseHashTableWidget : public QWidget
{
    Q_OBJECT

public:
    BaseHashTableWidget(QWidget *parent = nullptr);
    ~BaseHashTableWidget() override;

protected slots:
    virtual void addKeyValue() = 0;
    virtual void deleteByKey() = 0;
    virtual void find() = 0;
    virtual void changeHashFunction(int index) = 0;
    virtual void resizeTable() = 0;

    void onValueChanged(int key, const QString &value);


protected:
    Ui::BaseHashTableWidget *ui;

    // TODO: добавить поле хеш-таблицы

    HashTable<QString> hashTable;
};
