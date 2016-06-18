#ifndef HOW_H
#define HOW_H

#include <QDialog>
#include <QtCore>
#include <Qtgui>

namespace Ui {
class how;
}

class how : public QDialog
{
    Q_OBJECT

public:
    explicit how(QWidget *parent = 0);
    ~how();

private:
    Ui::how *ui;

private slots:
    void on_pushButton_clicked();

};

#endif // HOW_H
