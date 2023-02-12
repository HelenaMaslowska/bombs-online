/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *addressInput;
    QLineEdit *portInput;
    QPushButton *confirmBtn;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *nickInput;
    QPushButton *startBtn;
    QPushButton *exitBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(305, 266);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(80, 10, 151, 211));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        addressInput = new QLineEdit(verticalLayoutWidget);
        addressInput->setObjectName("addressInput");
        addressInput->setMaxLength(30);
        addressInput->setFrame(true);
        addressInput->setAlignment(Qt::AlignCenter);
        addressInput->setClearButtonEnabled(false);

        verticalLayout_2->addWidget(addressInput);

        portInput = new QLineEdit(verticalLayoutWidget);
        portInput->setObjectName("portInput");
        portInput->setMaxLength(30);
        portInput->setFrame(true);
        portInput->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(portInput);

        confirmBtn = new QPushButton(verticalLayoutWidget);
        confirmBtn->setObjectName("confirmBtn");

        verticalLayout_2->addWidget(confirmBtn);


        verticalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        nickInput = new QLineEdit(verticalLayoutWidget);
        nickInput->setObjectName("nickInput");
        nickInput->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(nickInput);

        startBtn = new QPushButton(verticalLayoutWidget);
        startBtn->setObjectName("startBtn");
        startBtn->setEnabled(false);

        verticalLayout_3->addWidget(startBtn);

        exitBtn = new QPushButton(verticalLayoutWidget);
        exitBtn->setObjectName("exitBtn");

        verticalLayout_3->addWidget(exitBtn);


        verticalLayout->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 305, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Bombs Online", nullptr));
        addressInput->setInputMask(QString());
        addressInput->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        addressInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "IP address", nullptr));
#if QT_CONFIG(tooltip)
        portInput->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        portInput->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        portInput->setText(QCoreApplication::translate("MainWindow", "8080", nullptr));
        portInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        confirmBtn->setText(QCoreApplication::translate("MainWindow", "Set up!", nullptr));
        nickInput->setText(QCoreApplication::translate("MainWindow", "Nickname", nullptr));
        startBtn->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        exitBtn->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
