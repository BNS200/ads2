#include <QGraphicsProxyWidget>

#include "TableElementWidget.h"

#include "SceneHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"

SceneHashTableWidget::SceneHashTableWidget(QWidget *parent)
    : BaseHashTableWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_view(new QGraphicsView(this))
    , hashTable(new HashTable<QString>(ui->spinBox_size->value(), new HashFunction1(1), 1))
{
    m_view->setScene(m_scene);
    ui->verticalLayout->insertWidget(0, m_view);
    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::addKeyValue()
{
    // TODO: проверка на повтор ключа
    // TODO: заменить определение строки, столбца, коллизий
    if (hashTable->contains(ui->spinBox_key->value())) {
        return;
    }

    size_t row = hashTable->currentFunction->hashFunction(ui->spinBox_key->value(), m_rows.size());

    int column = 0;
    if (!m_rows[row][column].widget->isEmpty())
    {
        column = m_rows[row].size();
        addBlankElement(row, column);
    }

    m_rows[row][column].widget->setKey(ui->spinBox_key->value());
    m_rows[row][column].widget->setValue(ui->lineEdit_value->text());


    hashTable->insert(ui->spinBox_key->value(), ui->lineEdit_value->text());
    //item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void SceneHashTableWidget::resizeTable()
{
    // TODO: resize хеш-таблицы
    int oldSize = m_rows.size();
    int newSize = ui->spinBox_size->value();

    hashTable->setTableSize(newSize);

    for (int i = newSize; i < oldSize; ++i)
    {
        for (ElementData& data : m_rows[i])
        {
            m_scene->removeItem(data.proxy);
            data.widget->deleteLater();
        }
    }
    m_rows.resize(newSize);

    for (int i = oldSize; i < newSize; ++i)
    {
        addBlankElement(i, 0);
    }
    for (int i = 0; i < newSize; ++i)
    {
        // TODO: заполнить новыми значениями из хеш-таблицы
        // (добавить/удалить элементы коллизий при необходимости)
        auto& list = hashTable->getHashTable()[i];
        int column = 0;
        for (auto it = list.begin(); it != list.end(); it++) {
            if (column >= m_rows[i].size()) {
                addBlankElement(i, column);
            }
            m_rows[i][column].widget->setKey(it->first);
            m_rows[i][column].widget->setValue(it->second);
            column++;
        }
    }
}

void SceneHashTableWidget::addBlankElement(int row, int column)
{
    //m_tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
    TableElementWidget *item = new TableElementWidget();
    //item->setTextAlignment(Qt::AlignCenter);
    //item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    connect(item, &TableElementWidget::valueChanged, this, &SceneHashTableWidget::onValueChanged);

    QGraphicsProxyWidget* proxy = m_scene->addWidget(item);
    column = m_rows[row].size();
    int x = column * (item->width() + 50);
    int y = row * item->height();
    proxy->setX(x);
    proxy->setY(y);

    if (column)
    {
        int centerY = item->height() / 2;
        auto* line = m_scene->addLine(-50, centerY, 0, centerY);
        line->setParentItem(proxy);
        line = m_scene->addLine(-centerY / 2, centerY / 2, 0, centerY);
        line->setParentItem(proxy);
        line = m_scene->addLine(-centerY / 2, centerY / 2 * 3, 0, centerY);
        line->setParentItem(proxy);
    }

    m_rows[row].append({item, proxy});
}
