#pragma once

#include <QWidget>
#include "HashTable.h"



namespace Ui {
class TableElementWidget;
}

/**
 * @brief Виджет элемента хеш-таблицы, необходимый для реализации
 * метода внешних цепочек.
 */
class TableElementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableElementWidget(QWidget *parent = nullptr);
    ~TableElementWidget();

    int key() const;
    QString value() const;

    void setKey(int key);
    void setValue(const QString &value);

    /**
     * @brief Возвращает true если у элемента не задан ключ.
     */
    bool isEmpty() const;

    /**
     * @brief Очищает значения полей ключа и значения.
     */
    void clear();

private:
    HashTable<QString>* hashTable;

signals:
    /**
     * @brief Сигнал, вызывающийся при изменении значения элемента таблицы через GUI.
     * @param value новое значение.
     */
    void valueChanged(int key, const QString &value);

private slots:
    void onValueChanged(const QString &value);

private:
    Ui::TableElementWidget *ui;
};

