/********************************************************************************
** Form generated from reading UI file 'how.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOW_H
#define UI_HOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_how
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *how)
    {
        if (how->objectName().isEmpty())
            how->setObjectName(QStringLiteral("how"));
        how->resize(800, 450);
        label = new QLabel(how);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 800, 450));
        label->setPixmap(QPixmap(QString::fromUtf8(":/image/inform.png")));
        label->setScaledContents(true);
        pushButton = new QPushButton(how);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(660, 400, 101, 41));
        pushButton->setStyleSheet(QStringLiteral("font: 75 24pt \"Comic Sans MS\";"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(30, 30));

        retranslateUi(how);

        QMetaObject::connectSlotsByName(how);
    } // setupUi

    void retranslateUi(QDialog *how)
    {
        how->setWindowTitle(QApplication::translate("how", "Dialog", 0));
        label->setText(QString());
        pushButton->setText(QApplication::translate("how", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class how: public Ui_how {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOW_H
