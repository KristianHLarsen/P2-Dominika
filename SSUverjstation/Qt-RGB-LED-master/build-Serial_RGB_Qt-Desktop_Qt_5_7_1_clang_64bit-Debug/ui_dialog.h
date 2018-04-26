/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *red_label;
    QLabel *green_label;
    QLabel *blue_label;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QSlider *red_slider;
    QSlider *green_slider;
    QSlider *blue_slider;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *red_value_label;
    QLabel *green_value_label;
    QLabel *blue_value_label;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(560, 160);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 123, 141));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        red_label = new QLabel(layoutWidget);
        red_label->setObjectName(QStringLiteral("red_label"));
        red_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(red_label);

        green_label = new QLabel(layoutWidget);
        green_label->setObjectName(QStringLiteral("green_label"));
        green_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(green_label);

        blue_label = new QLabel(layoutWidget);
        blue_label->setObjectName(QStringLiteral("blue_label"));
        blue_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(blue_label);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(140, 10, 311, 141));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        red_slider = new QSlider(layoutWidget1);
        red_slider->setObjectName(QStringLiteral("red_slider"));
        red_slider->setMaximum(255);
        red_slider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(red_slider);

        green_slider = new QSlider(layoutWidget1);
        green_slider->setObjectName(QStringLiteral("green_slider"));
        green_slider->setMaximum(255);
        green_slider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(green_slider);

        blue_slider = new QSlider(layoutWidget1);
        blue_slider->setObjectName(QStringLiteral("blue_slider"));
        blue_slider->setMaximum(255);
        blue_slider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(blue_slider);

        layoutWidget2 = new QWidget(Dialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(460, 10, 91, 141));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        red_value_label = new QLabel(layoutWidget2);
        red_value_label->setObjectName(QStringLiteral("red_value_label"));

        verticalLayout_3->addWidget(red_value_label);

        green_value_label = new QLabel(layoutWidget2);
        green_value_label->setObjectName(QStringLiteral("green_value_label"));

        verticalLayout_3->addWidget(green_value_label);

        blue_value_label = new QLabel(layoutWidget2);
        blue_value_label->setObjectName(QStringLiteral("blue_value_label"));

        verticalLayout_3->addWidget(blue_value_label);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        red_label->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#ff0000;\">Red LED</span></p></body></html>", Q_NULLPTR));
        green_label->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#00ff00;\">Green LED</span></p></body></html>", Q_NULLPTR));
        blue_label->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#0000ff;\">Blue LED</span></p></body></html>", Q_NULLPTR));
        red_value_label->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">0</span></p></body></html>", Q_NULLPTR));
        green_value_label->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">0</span></p></body></html>", Q_NULLPTR));
        blue_value_label->setText(QApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">0</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
