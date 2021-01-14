/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *spd;
    QTextEdit *rad;
    QTextEdit *wid;
    // QTextEdit *col;
    QTextEdit *asteroids;
    QLabel *label;
    QLabel *label1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    // QLabel *label_6;
    QLabel *label_5;
    QLabel *label_12;
    QCheckBox *blight;
    QLabel *label_13;
    QCheckBox *btextures;
    QLabel *label_14;
    QCheckBox *bobstacles;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(500, 200);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(380, 70, 81, 80));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        spd = new QTextEdit(Dialog);
        spd->setObjectName(QStringLiteral("spd"));
        spd->setGeometry(QRect(70, 40, 121, 21));
        rad = new QTextEdit(Dialog);
        rad->setObjectName(QStringLiteral("rad"));
        rad->setGeometry(QRect(70, 80, 121, 21));
        wid = new QTextEdit(Dialog);
        wid->setObjectName(QStringLiteral("wid"));
        wid->setGeometry(QRect(70, 120, 121, 21));
        // col = new QTextEdit(Dialog);
        // col->setObjectName(QStringLiteral("col"));
        // col->setGeometry(QRect(70, 160, 121, 21));
        asteroids = new QTextEdit(Dialog);
        asteroids->setObjectName(QStringLiteral("asteroids"));
        asteroids->setGeometry(QRect(280, 160, 71, 21));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 20, 71, 16));
        label1 = new QLabel(Dialog);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setGeometry(QRect(200, 20, 71, 16));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 58, 16));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 80, 58, 16));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 120, 58, 16));
        // label_6 = new QLabel(Dialog);
        // label_6->setObjectName(QStringLiteral("label_6"));
        // label_6->setGeometry(QRect(10, 160, 58, 16));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(200, 160, 78, 16));
        label_12 = new QLabel(Dialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(200, 40, 120, 16));
        blight = new QCheckBox(Dialog);
        blight->setObjectName(QStringLiteral("blight"));
        blight->setGeometry(QRect(330, 40, 20, 20));
        blight->setChecked(true);
        label_13 = new QLabel(Dialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(200, 80, 120, 16));
        btextures = new QCheckBox(Dialog);
        btextures->setObjectName(QStringLiteral("btextures"));
        btextures->setGeometry(QRect(330, 80, 20, 20));
        btextures->setChecked(true);
        label_14 = new QLabel(Dialog);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(200, 120, 120, 16));
        bobstacles = new QCheckBox(Dialog);
        bobstacles->setObjectName(QStringLiteral("bobstacles"));
        bobstacles->setGeometry(QRect(330, 120, 20, 20));
        bobstacles->setChecked(true);

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "Vehicle", Q_NULLPTR));
        label1->setText(QApplication::translate("Dialog", "Scene", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog", "Speed", Q_NULLPTR));
        label_3->setText(QApplication::translate("Dialog", "Radius", Q_NULLPTR));
        label_4->setText(QApplication::translate("Dialog", "Width", Q_NULLPTR));
        // label_6->setText(QApplication::translate("Dialog", "Material", Q_NULLPTR));
        label_5->setText(QApplication::translate("Dialog", "Asteroids", Q_NULLPTR));
        label_12->setText(QApplication::translate("Dialog", "Enable Light", Q_NULLPTR));
        blight->setText(QApplication::translate("Dialog", "CheckBox", Q_NULLPTR));
        label_13->setText(QApplication::translate("Dialog", "Enable Textures", Q_NULLPTR));
        btextures->setText(QApplication::translate("Dialog", "CheckBox2", Q_NULLPTR));
        label_14->setText(QApplication::translate("Dialog", "Enable Obstacles", Q_NULLPTR));
        bobstacles->setText(QApplication::translate("Dialog", "CheckBox3", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
