#include "BaseHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"


BaseHashTableWidget::BaseHashTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BaseHashTableWidget)
{
    ui->setupUi(this);
    connect(ui->spinBox_size, &QSpinBox::editingFinished, this, &BaseHashTableWidget::resizeTable);
    connect(ui->pushButton_add, &QPushButton::clicked, this, &BaseHashTableWidget::addKeyValue);
}

BaseHashTableWidget::~BaseHashTableWidget()
{
    delete ui;
}

void BaseHashTableWidget::onValueChanged(int key, const QString &value)
{
//    value.toStdString()
    // TODO: записать новое значение в хеш-таблицу

    hashTable->removeByKey(key);
    hashTable->insert(key, value.toStdString());
}
