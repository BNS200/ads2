#include <QGraphicsProxyWidget>

#include "TableElementWidget.h"

#include "SceneHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"

SceneHashTableWidget::SceneHashTableWidget(QWidget *parent)
    : BaseHashTableWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_view(new QGraphicsView(this))
{
    m_view->setScene(m_scene);
    ui->verticalLayout->insertWidget(0, m_view);
    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::changeHashFunction(int index){
    switch (index) {
    case 0:
        hashTable.setHashFunction(new HashFunction1());
        break;
    case 1:
        hashTable.setHashFunction(new HashFunction2());
        break;
    case 2:
        hashTable.setHashFunction(new HashFunction3());
        break;
    default:
        break;
    }

    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::addKeyValue()
{
    if (hashTable.contains(ui->spinBox_key->value())) {
        return;
    }
    size_t row = hashTable.getCurrentFunction()->hashFunction(ui->spinBox_key->value(), m_rows.size());

    if (row >= m_rows.size()) {
        return;
    }
    int column = 0;
    while (column < m_rows[row].size() && !m_rows[row][column].widget->isEmpty()) {
        column++;
    }

    if (column >= m_rows[row].size()) {
        addBlankElement(row, column);
    }
    m_rows[row][column].widget->setKey(ui->spinBox_key->value());
    m_rows[row][column].widget->setValue(ui->lineEdit_value->text());
    m_rows[row][column].widget->itemEditable();
    hashTable.insert(ui->spinBox_key->value(), ui->lineEdit_value->text());
}

void SceneHashTableWidget::deleteByKey()
{
    int key = ui->spinBox_key->value();
    if (!hashTable.contains(key)) {
        return;
    }

    hashTable.removeByKey(key);
    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::find()
{
    int key = ui->spinBox_key->value();
    if (!hashTable.contains(key)) {
        return;
    }

    size_t row = hashTable.getCurrentFunction()->hashFunction(key, m_rows.size());
    auto list = hashTable.getHashTable()[row];

    for (int i = 0; i < m_rows[row].size(); i++) {
        if (!m_rows[row][i].widget->isEmpty() && m_rows[row][i].widget->key() == key) {
            m_rows[row][i].widget->setColor(Qt::red);
            break;
        }
    }
}
void SceneHashTableWidget::resizeTable()
{
    int newSize = ui->spinBox_size->value();
    hashTable.setTableSize(newSize);


    m_scene->clear();
    m_rows.clear();
    m_rows.resize(newSize);

    for (int row = 0; row < newSize; ++row) {

        addBlankElement(row, 0);

        auto list = hashTable.getHashTable()[row];
        for (size_t col = 1; col < list.size(); ++col) {
            addBlankElement(row, col);
        }
    }


    for (int row = 0; row < newSize; row++) {
        auto list = hashTable.getHashTable()[row];
        int col = 0;
        for (auto it = list.begin(); it != list.end(); it++) {
            if (col >= m_rows[row].size()) {
                addBlankElement(row, col);
            }
            m_rows[row][col].widget->setKey(it->first);
            m_rows[row][col].widget->setValue(it->second);
            m_rows[row][col].widget->itemEditable();
            col++;
        }
    }
}

void SceneHashTableWidget::addBlankElement(int row, int column)
{
    //m_tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
    TableElementWidget *item = new TableElementWidget();
    item->itemNotEditable();
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
