/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *pos1;
    QTextEdit *pos2;
    QTextEdit *pos3;
    QTextEdit *at1;
    QTextEdit *at2;
    QTextEdit *at3;
    QTextEdit *up1;
    QTextEdit *up2;
    QTextEdit *up3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QTextEdit *xmin;
    QTextEdit *xmax;
    QTextEdit *ymin;
    QTextEdit *zmin;
    QTextEdit *zmax;
    QTextEdit *ymax;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QCheckBox *blight;
    QLabel *label_12;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(696, 390);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(590, 70, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        pos1 = new QTextEdit(Dialog);
        pos1->setObjectName(QString::fromUtf8("pos1"));
        pos1->setGeometry(QRect(50, 80, 121, 21));
        pos2 = new QTextEdit(Dialog);
        pos2->setObjectName(QString::fromUtf8("pos2"));
        pos2->setGeometry(QRect(200, 80, 121, 21));
        pos3 = new QTextEdit(Dialog);
        pos3->setObjectName(QString::fromUtf8("pos3"));
        pos3->setGeometry(QRect(360, 80, 111, 21));
        at1 = new QTextEdit(Dialog);
        at1->setObjectName(QString::fromUtf8("at1"));
        at1->setGeometry(QRect(50, 120, 121, 21));
        at2 = new QTextEdit(Dialog);
        at2->setObjectName(QString::fromUtf8("at2"));
        at2->setGeometry(QRect(200, 120, 121, 21));
        at3 = new QTextEdit(Dialog);
        at3->setObjectName(QString::fromUtf8("at3"));
        at3->setGeometry(QRect(360, 120, 111, 21));
        up1 = new QTextEdit(Dialog);
        up1->setObjectName(QString::fromUtf8("up1"));
        up1->setGeometry(QRect(50, 160, 121, 21));
        up2 = new QTextEdit(Dialog);
        up2->setObjectName(QString::fromUtf8("up2"));
        up2->setGeometry(QRect(200, 160, 121, 21));
        up3 = new QTextEdit(Dialog);
        up3->setObjectName(QString::fromUtf8("up3"));
        up3->setGeometry(QRect(360, 160, 111, 21));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 60, 71, 16));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 58, 16));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 120, 58, 16));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 160, 58, 16));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(50, 190, 58, 16));
        xmin = new QTextEdit(Dialog);
        xmin->setObjectName(QString::fromUtf8("xmin"));
        xmin->setGeometry(QRect(50, 230, 121, 21));
        xmax = new QTextEdit(Dialog);
        xmax->setObjectName(QString::fromUtf8("xmax"));
        xmax->setGeometry(QRect(50, 280, 121, 21));
        ymin = new QTextEdit(Dialog);
        ymin->setObjectName(QString::fromUtf8("ymin"));
        ymin->setGeometry(QRect(200, 230, 121, 21));
        zmin = new QTextEdit(Dialog);
        zmin->setObjectName(QString::fromUtf8("zmin"));
        zmin->setGeometry(QRect(360, 230, 111, 21));
        zmax = new QTextEdit(Dialog);
        zmax->setObjectName(QString::fromUtf8("zmax"));
        zmax->setGeometry(QRect(360, 280, 111, 21));
        ymax = new QTextEdit(Dialog);
        ymax->setObjectName(QString::fromUtf8("ymax"));
        ymax->setGeometry(QRect(200, 280, 121, 21));
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(50, 210, 58, 16));
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(50, 260, 58, 16));
        label_8 = new QLabel(Dialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(200, 210, 58, 16));
        label_9 = new QLabel(Dialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(200, 260, 58, 16));
        label_10 = new QLabel(Dialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(360, 210, 58, 16));
        label_11 = new QLabel(Dialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(360, 260, 58, 16));
        blight = new QCheckBox(Dialog);
        blight->setObjectName(QString::fromUtf8("blight"));
        blight->setGeometry(QRect(265, 330, 20, 20));
        blight->setChecked(true);
        label_12 = new QLabel(Dialog);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(170, 330, 81, 16));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "GluLookat", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Pos", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "At", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "Up", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "GlOrtho", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "xmin", nullptr));
        label_7->setText(QCoreApplication::translate("Dialog", "xmax", nullptr));
        label_8->setText(QCoreApplication::translate("Dialog", "ymin", nullptr));
        label_9->setText(QCoreApplication::translate("Dialog", "ymax", nullptr));
        label_10->setText(QCoreApplication::translate("Dialog", "zmin", nullptr));
        label_11->setText(QCoreApplication::translate("Dialog", "zmax", nullptr));
        blight->setText(QCoreApplication::translate("Dialog", "CheckBox", nullptr));
        label_12->setText(QCoreApplication::translate("Dialog", "Enable Light", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
