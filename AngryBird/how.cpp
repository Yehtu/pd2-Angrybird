#include "how.h"
#include "ui_how.h"

how::how(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::how)
{
    ui->setupUi(this);
}

how::~how()
{
    delete ui;
}

void how::on_pushButton_clicked()
{
    this->close();
}
