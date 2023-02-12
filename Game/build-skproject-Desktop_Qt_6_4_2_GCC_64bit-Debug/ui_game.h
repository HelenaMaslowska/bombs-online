/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Game
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *Players;
    QGroupBox *Player1;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *p1;
    QVBoxLayout *verticalLayout;
    QLabel *label_1;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QLabel *HP_1;
    QLabel *Speed_1;
    QLabel *MaxBombs_1;
    QLabel *StrengthBombs_1;
    QPushButton *rdy_1;
    QGroupBox *Player2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *p1_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_4;
    QLabel *HP_2;
    QLabel *Speed_2;
    QLabel *MaxBombs_2;
    QLabel *StrengthBombs_2;
    QPushButton *rdy_2;
    QGroupBox *Player3;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *p1_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_6;
    QLabel *HP_3;
    QLabel *Speed_3;
    QLabel *MaxBombs_3;
    QLabel *StrengthBombs_3;
    QPushButton *rdy_3;
    QGroupBox *Player4;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *p1_4;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QVBoxLayout *verticalLayout_8;
    QLabel *HP_4;
    QLabel *Speed_4;
    QLabel *MaxBombs_4;
    QLabel *StrengthBombs_4;
    QPushButton *rdy_4;
    QFrame *frame;
    QPushButton *readyBtn;
    QPushButton *readyColor;
    QPushButton *exitBtn;
    QTextEdit *console;

    void setupUi(QFrame *Game)
    {
        if (Game->objectName().isEmpty())
            Game->setObjectName("Game");
        Game->resize(700, 620);
        Game->setMinimumSize(QSize(700, 560));
        verticalLayoutWidget = new QWidget(Game);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(510, 20, 171, 481));
        Players = new QVBoxLayout(verticalLayoutWidget);
        Players->setObjectName("Players");
        Players->setContentsMargins(0, 0, 0, 0);
        Player1 = new QGroupBox(verticalLayoutWidget);
        Player1->setObjectName("Player1");
        horizontalLayoutWidget = new QWidget(Player1);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(11, 29, 151, 90));
        p1 = new QHBoxLayout(horizontalLayoutWidget);
        p1->setSpacing(2);
        p1->setObjectName("p1");
        p1->setSizeConstraint(QLayout::SetMinimumSize);
        p1->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_1 = new QLabel(horizontalLayoutWidget);
        label_1->setObjectName("label_1");

        verticalLayout->addWidget(label_1);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);


        p1->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        HP_1 = new QLabel(horizontalLayoutWidget);
        HP_1->setObjectName("HP_1");

        verticalLayout_2->addWidget(HP_1);

        Speed_1 = new QLabel(horizontalLayoutWidget);
        Speed_1->setObjectName("Speed_1");

        verticalLayout_2->addWidget(Speed_1);

        MaxBombs_1 = new QLabel(horizontalLayoutWidget);
        MaxBombs_1->setObjectName("MaxBombs_1");

        verticalLayout_2->addWidget(MaxBombs_1);

        StrengthBombs_1 = new QLabel(horizontalLayoutWidget);
        StrengthBombs_1->setObjectName("StrengthBombs_1");

        verticalLayout_2->addWidget(StrengthBombs_1);


        p1->addLayout(verticalLayout_2);

        p1->setStretch(0, 6);
        p1->setStretch(1, 2);
        rdy_1 = new QPushButton(Player1);
        rdy_1->setObjectName("rdy_1");
        rdy_1->setEnabled(false);
        rdy_1->setGeometry(QRect(140, 0, 21, 21));

        Players->addWidget(Player1);

        Player2 = new QGroupBox(verticalLayoutWidget);
        Player2->setObjectName("Player2");
        horizontalLayoutWidget_2 = new QWidget(Player2);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 29, 151, 90));
        p1_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        p1_2->setSpacing(2);
        p1_2->setObjectName("p1_2");
        p1_2->setSizeConstraint(QLayout::SetMinimumSize);
        p1_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName("label_5");

        verticalLayout_3->addWidget(label_5);

        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName("label_6");

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(horizontalLayoutWidget_2);
        label_7->setObjectName("label_7");

        verticalLayout_3->addWidget(label_7);


        p1_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        HP_2 = new QLabel(horizontalLayoutWidget_2);
        HP_2->setObjectName("HP_2");

        verticalLayout_4->addWidget(HP_2);

        Speed_2 = new QLabel(horizontalLayoutWidget_2);
        Speed_2->setObjectName("Speed_2");

        verticalLayout_4->addWidget(Speed_2);

        MaxBombs_2 = new QLabel(horizontalLayoutWidget_2);
        MaxBombs_2->setObjectName("MaxBombs_2");

        verticalLayout_4->addWidget(MaxBombs_2);

        StrengthBombs_2 = new QLabel(horizontalLayoutWidget_2);
        StrengthBombs_2->setObjectName("StrengthBombs_2");

        verticalLayout_4->addWidget(StrengthBombs_2);


        p1_2->addLayout(verticalLayout_4);

        p1_2->setStretch(0, 6);
        p1_2->setStretch(1, 2);
        rdy_2 = new QPushButton(Player2);
        rdy_2->setObjectName("rdy_2");
        rdy_2->setEnabled(false);
        rdy_2->setGeometry(QRect(140, 0, 21, 21));

        Players->addWidget(Player2);

        Player3 = new QGroupBox(verticalLayoutWidget);
        Player3->setObjectName("Player3");
        horizontalLayoutWidget_3 = new QWidget(Player3);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(10, 29, 151, 90));
        p1_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        p1_3->setSpacing(2);
        p1_3->setObjectName("p1_3");
        p1_3->setSizeConstraint(QLayout::SetMinimumSize);
        p1_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_8 = new QLabel(horizontalLayoutWidget_3);
        label_8->setObjectName("label_8");

        verticalLayout_5->addWidget(label_8);

        label_9 = new QLabel(horizontalLayoutWidget_3);
        label_9->setObjectName("label_9");

        verticalLayout_5->addWidget(label_9);

        label_10 = new QLabel(horizontalLayoutWidget_3);
        label_10->setObjectName("label_10");

        verticalLayout_5->addWidget(label_10);

        label_11 = new QLabel(horizontalLayoutWidget_3);
        label_11->setObjectName("label_11");

        verticalLayout_5->addWidget(label_11);


        p1_3->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        HP_3 = new QLabel(horizontalLayoutWidget_3);
        HP_3->setObjectName("HP_3");

        verticalLayout_6->addWidget(HP_3);

        Speed_3 = new QLabel(horizontalLayoutWidget_3);
        Speed_3->setObjectName("Speed_3");

        verticalLayout_6->addWidget(Speed_3);

        MaxBombs_3 = new QLabel(horizontalLayoutWidget_3);
        MaxBombs_3->setObjectName("MaxBombs_3");

        verticalLayout_6->addWidget(MaxBombs_3);

        StrengthBombs_3 = new QLabel(horizontalLayoutWidget_3);
        StrengthBombs_3->setObjectName("StrengthBombs_3");

        verticalLayout_6->addWidget(StrengthBombs_3);


        p1_3->addLayout(verticalLayout_6);

        p1_3->setStretch(0, 6);
        p1_3->setStretch(1, 2);
        rdy_3 = new QPushButton(Player3);
        rdy_3->setObjectName("rdy_3");
        rdy_3->setEnabled(false);
        rdy_3->setGeometry(QRect(140, 0, 21, 21));

        Players->addWidget(Player3);

        Player4 = new QGroupBox(verticalLayoutWidget);
        Player4->setObjectName("Player4");
        horizontalLayoutWidget_4 = new QWidget(Player4);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(10, 29, 151, 81));
        p1_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        p1_4->setSpacing(2);
        p1_4->setObjectName("p1_4");
        p1_4->setSizeConstraint(QLayout::SetMinimumSize);
        p1_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_12 = new QLabel(horizontalLayoutWidget_4);
        label_12->setObjectName("label_12");

        verticalLayout_7->addWidget(label_12);

        label_13 = new QLabel(horizontalLayoutWidget_4);
        label_13->setObjectName("label_13");

        verticalLayout_7->addWidget(label_13);

        label_14 = new QLabel(horizontalLayoutWidget_4);
        label_14->setObjectName("label_14");

        verticalLayout_7->addWidget(label_14);

        label_15 = new QLabel(horizontalLayoutWidget_4);
        label_15->setObjectName("label_15");

        verticalLayout_7->addWidget(label_15);


        p1_4->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(3);
        verticalLayout_8->setObjectName("verticalLayout_8");
        HP_4 = new QLabel(horizontalLayoutWidget_4);
        HP_4->setObjectName("HP_4");

        verticalLayout_8->addWidget(HP_4);

        Speed_4 = new QLabel(horizontalLayoutWidget_4);
        Speed_4->setObjectName("Speed_4");

        verticalLayout_8->addWidget(Speed_4);

        MaxBombs_4 = new QLabel(horizontalLayoutWidget_4);
        MaxBombs_4->setObjectName("MaxBombs_4");

        verticalLayout_8->addWidget(MaxBombs_4);

        StrengthBombs_4 = new QLabel(horizontalLayoutWidget_4);
        StrengthBombs_4->setObjectName("StrengthBombs_4");

        verticalLayout_8->addWidget(StrengthBombs_4);


        p1_4->addLayout(verticalLayout_8);

        p1_4->setStretch(0, 6);
        p1_4->setStretch(1, 2);
        rdy_4 = new QPushButton(Player4);
        rdy_4->setObjectName("rdy_4");
        rdy_4->setEnabled(false);
        rdy_4->setGeometry(QRect(140, 0, 21, 21));

        Players->addWidget(Player4);

        frame = new QFrame(Game);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 20, 480, 480));
        frame->setMinimumSize(QSize(480, 480));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        readyBtn = new QPushButton(Game);
        readyBtn->setObjectName("readyBtn");
        readyBtn->setGeometry(QRect(20, 510, 171, 31));
        readyColor = new QPushButton(Game);
        readyColor->setObjectName("readyColor");
        readyColor->setEnabled(false);
        readyColor->setGeometry(QRect(200, 510, 31, 31));
        readyColor->setCheckable(false);
        readyColor->setChecked(false);
        exitBtn = new QPushButton(Game);
        exitBtn->setObjectName("exitBtn");
        exitBtn->setGeometry(QRect(580, 510, 91, 31));
        console = new QTextEdit(Game);
        console->setObjectName("console");
        console->setEnabled(false);
        console->setGeometry(QRect(250, 510, 311, 101));
        console->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        retranslateUi(Game);

        QMetaObject::connectSlotsByName(Game);
    } // setupUi

    void retranslateUi(QFrame *Game)
    {
        Game->setWindowTitle(QCoreApplication::translate("Game", "Bombs online!", nullptr));
        Player1->setTitle(QCoreApplication::translate("Game", "Player 1", nullptr));
        label_1->setText(QCoreApplication::translate("Game", "HP ", nullptr));
        label_3->setText(QCoreApplication::translate("Game", "Bomb strength", nullptr));
        label_2->setText(QCoreApplication::translate("Game", "Speed", nullptr));
        label->setText(QCoreApplication::translate("Game", "Bombs", nullptr));
        HP_1->setText(QCoreApplication::translate("Game", "3", nullptr));
        Speed_1->setText(QCoreApplication::translate("Game", "0", nullptr));
        MaxBombs_1->setText(QCoreApplication::translate("Game", "0", nullptr));
        StrengthBombs_1->setText(QCoreApplication::translate("Game", "0", nullptr));
        rdy_1->setText(QString());
        Player2->setTitle(QCoreApplication::translate("Game", "Player 2", nullptr));
        label_4->setText(QCoreApplication::translate("Game", "HP ", nullptr));
        label_5->setText(QCoreApplication::translate("Game", "Bomb strength", nullptr));
        label_6->setText(QCoreApplication::translate("Game", "Speed", nullptr));
        label_7->setText(QCoreApplication::translate("Game", "Bombs", nullptr));
        HP_2->setText(QCoreApplication::translate("Game", "3", nullptr));
        Speed_2->setText(QCoreApplication::translate("Game", "0", nullptr));
        MaxBombs_2->setText(QCoreApplication::translate("Game", "0", nullptr));
        StrengthBombs_2->setText(QCoreApplication::translate("Game", "0", nullptr));
        rdy_2->setText(QString());
        Player3->setTitle(QCoreApplication::translate("Game", "Player 3", nullptr));
        label_8->setText(QCoreApplication::translate("Game", "HP ", nullptr));
        label_9->setText(QCoreApplication::translate("Game", "Bomb strength", nullptr));
        label_10->setText(QCoreApplication::translate("Game", "Speed", nullptr));
        label_11->setText(QCoreApplication::translate("Game", "Bombs", nullptr));
        HP_3->setText(QCoreApplication::translate("Game", "3", nullptr));
        Speed_3->setText(QCoreApplication::translate("Game", "0", nullptr));
        MaxBombs_3->setText(QCoreApplication::translate("Game", "0", nullptr));
        StrengthBombs_3->setText(QCoreApplication::translate("Game", "0", nullptr));
        rdy_3->setText(QString());
        Player4->setTitle(QCoreApplication::translate("Game", "Player 4", nullptr));
        label_12->setText(QCoreApplication::translate("Game", "HP ", nullptr));
        label_13->setText(QCoreApplication::translate("Game", "Bomb strength", nullptr));
        label_14->setText(QCoreApplication::translate("Game", "Speed", nullptr));
        label_15->setText(QCoreApplication::translate("Game", "Bombs", nullptr));
        HP_4->setText(QCoreApplication::translate("Game", "3", nullptr));
        Speed_4->setText(QCoreApplication::translate("Game", "0", nullptr));
        MaxBombs_4->setText(QCoreApplication::translate("Game", "0", nullptr));
        StrengthBombs_4->setText(QCoreApplication::translate("Game", "0", nullptr));
        rdy_4->setText(QString());
        readyBtn->setText(QCoreApplication::translate("Game", "Not ready", nullptr));
        readyColor->setText(QString());
        exitBtn->setText(QCoreApplication::translate("Game", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Game: public Ui_Game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
