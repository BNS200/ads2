#pragma once

#include <QWidget>
#include "HashTable.h"


QT_BEGIN_NAMESPACE
namespace Ui { class BaseHashTableWidget; }
QT_END_NAMESPACE

/**
 * @brief Базовый класс виждета хеш-таблицы.
 * Содержит элементы управления (добавление/удаление и т.д.).
 * Наследники класса отвечают за реализацию отображения самой таблицы:
 * - HashTableWidget: метод открытой адресации / метод внутренних цепочек
 * - SceneHashTableWidget: метод внешних цепочек.
 */
class BaseHashTableWidget : public QWidget
{
    Q_OBJECT

public:
    BaseHashTableWidget(QWidget *parent = nullptr);
    ~BaseHashTableWidget() override;

protected slots:
    /**
     * @brief слот, вызывающийся при изменении значения элемента с помощью формы.
     * @param key ключ элемента.
     * @param value новое значение элемента.
     */
    void onValueChanged(int key, const QString &value);

    /**
     * @brief слот, вызывающийся при добавлении элемента в таблицу с помощью формы.
     * Ключ и значение можно получить через указатели `ui->spinBox_key` и `ui->lineEdit_value`
     */
    virtual void addKeyValue() = 0;

    /**
     * @brief слот, вызывающийся при изменении размера таблицы с помощью формы.
     * Новый размер таблицы можно получить через указатель `ui->spinBox_size`.
     */
    virtual void resizeTable() = 0;

protected:
    Ui::BaseHashTableWidget *ui;

    // TODO: добавить поле хеш-таблицы

private:
    HashTable<QString>* hashTable;
};
