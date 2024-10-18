/********************************************************************************
** Form generated from reading UI file 'httpdnsdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTTPDNSDEMO_H
#define UI_HTTPDNSDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_httpdnsdemo
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *httpdnsdemo)
    {
        if (httpdnsdemo->objectName().isEmpty())
            httpdnsdemo->setObjectName(QString::fromUtf8("httpdnsdemo"));
        httpdnsdemo->resize(600, 400);
        centralWidget = new QWidget(httpdnsdemo);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 20, 471, 21));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 60, 571, 291));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(510, 20, 75, 23));
        httpdnsdemo->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(httpdnsdemo);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        httpdnsdemo->setMenuBar(menuBar);
        mainToolBar = new QToolBar(httpdnsdemo);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        httpdnsdemo->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(httpdnsdemo);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        httpdnsdemo->setStatusBar(statusBar);

        retranslateUi(httpdnsdemo);

        QMetaObject::connectSlotsByName(httpdnsdemo);
    } // setupUi

    void retranslateUi(QMainWindow *httpdnsdemo)
    {
        httpdnsdemo->setWindowTitle(QCoreApplication::translate("httpdnsdemo", "httpdnsdemo", nullptr));
        pushButton->setText(QCoreApplication::translate("httpdnsdemo", "\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class httpdnsdemo: public Ui_httpdnsdemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTTPDNSDEMO_H
