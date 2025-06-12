#include "BaseHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"


BaseHashTableWidget::BaseHashTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BaseHashTableWidget)
{
    ui->setupUi(this);
    connect(ui->spinBox_size, &QSpinBox::editingFinished, this, &BaseHashTableWidget::resizeTable);
    connect(ui->pushButton_add, &QPushButton::clicked, this, &BaseHashTableWidget::addKeyValue);
    connect(ui->pushButton_find, &QPushButton::clicked, this, &BaseHashTableWidget::find);
    connect(ui->pushButton_remove, &QPushButton::clicked, this, &BaseHashTableWidget::deleteByKey);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BaseHashTableWidget::changeHashFunction);

}

BaseHashTableWidget::~BaseHashTableWidget()
{
    delete ui;
}

void BaseHashTableWidget::onValueChanged(int key, const QString &value)
{
    hashTable.setValue(key, value);
//    value.toStdString()
    // TODO: записать новое значение в хеш-таблицу

}
