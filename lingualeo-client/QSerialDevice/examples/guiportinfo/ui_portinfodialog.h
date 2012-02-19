/********************************************************************************
** Form generated from reading UI file 'portinfodialog.ui'
**
** Created: Sun 19. Feb 19:48:07 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PORTINFODIALOG_H
#define UI_PORTINFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *portsGroupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *portNameLabel;
    QComboBox *portsComboBox;
    QPushButton *updateButton;
    QSpacerItem *horizontalSpacer;
    QGroupBox *infoGroupBox;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *locationNameLabel;
    QLabel *locationValueLabel;
    QLabel *descriptionNameLabel;
    QLabel *descriptionValueLabel;
    QLabel *manufacturerNameLabel;
    QLabel *manufacturerValueLabel;
    QGridLayout *gridLayout_2;
    QPushButton *validButton;
    QLabel *validLabel;
    QPushButton *busyButton;
    QLabel *busyLabel;
    QPushButton *ratesButton;
    QComboBox *ratesComboBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(293, 255);
        gridLayout_4 = new QGridLayout(Dialog);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        portsGroupBox = new QGroupBox(Dialog);
        portsGroupBox->setObjectName(QString::fromUtf8("portsGroupBox"));
        horizontalLayout = new QHBoxLayout(portsGroupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        portNameLabel = new QLabel(portsGroupBox);
        portNameLabel->setObjectName(QString::fromUtf8("portNameLabel"));

        horizontalLayout->addWidget(portNameLabel);

        portsComboBox = new QComboBox(portsGroupBox);
        portsComboBox->setObjectName(QString::fromUtf8("portsComboBox"));

        horizontalLayout->addWidget(portsComboBox);

        updateButton = new QPushButton(portsGroupBox);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));

        horizontalLayout->addWidget(updateButton);

        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_4->addWidget(portsGroupBox, 0, 0, 1, 1);

        infoGroupBox = new QGroupBox(Dialog);
        infoGroupBox->setObjectName(QString::fromUtf8("infoGroupBox"));
        gridLayout_3 = new QGridLayout(infoGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        locationNameLabel = new QLabel(infoGroupBox);
        locationNameLabel->setObjectName(QString::fromUtf8("locationNameLabel"));

        gridLayout->addWidget(locationNameLabel, 0, 0, 1, 1);

        locationValueLabel = new QLabel(infoGroupBox);
        locationValueLabel->setObjectName(QString::fromUtf8("locationValueLabel"));

        gridLayout->addWidget(locationValueLabel, 0, 1, 1, 1);

        descriptionNameLabel = new QLabel(infoGroupBox);
        descriptionNameLabel->setObjectName(QString::fromUtf8("descriptionNameLabel"));

        gridLayout->addWidget(descriptionNameLabel, 1, 0, 1, 1);

        descriptionValueLabel = new QLabel(infoGroupBox);
        descriptionValueLabel->setObjectName(QString::fromUtf8("descriptionValueLabel"));

        gridLayout->addWidget(descriptionValueLabel, 1, 1, 1, 1);

        manufacturerNameLabel = new QLabel(infoGroupBox);
        manufacturerNameLabel->setObjectName(QString::fromUtf8("manufacturerNameLabel"));

        gridLayout->addWidget(manufacturerNameLabel, 2, 0, 1, 1);

        manufacturerValueLabel = new QLabel(infoGroupBox);
        manufacturerValueLabel->setObjectName(QString::fromUtf8("manufacturerValueLabel"));

        gridLayout->addWidget(manufacturerValueLabel, 2, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        validButton = new QPushButton(infoGroupBox);
        validButton->setObjectName(QString::fromUtf8("validButton"));

        gridLayout_2->addWidget(validButton, 0, 0, 1, 1);

        validLabel = new QLabel(infoGroupBox);
        validLabel->setObjectName(QString::fromUtf8("validLabel"));

        gridLayout_2->addWidget(validLabel, 0, 1, 1, 1);

        busyButton = new QPushButton(infoGroupBox);
        busyButton->setObjectName(QString::fromUtf8("busyButton"));

        gridLayout_2->addWidget(busyButton, 1, 0, 1, 1);

        busyLabel = new QLabel(infoGroupBox);
        busyLabel->setObjectName(QString::fromUtf8("busyLabel"));

        gridLayout_2->addWidget(busyLabel, 1, 1, 1, 1);

        ratesButton = new QPushButton(infoGroupBox);
        ratesButton->setObjectName(QString::fromUtf8("ratesButton"));

        gridLayout_2->addWidget(ratesButton, 2, 0, 1, 1);

        ratesComboBox = new QComboBox(infoGroupBox);
        ratesComboBox->setObjectName(QString::fromUtf8("ratesComboBox"));

        gridLayout_2->addWidget(ratesComboBox, 2, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);


        gridLayout_4->addWidget(infoGroupBox, 1, 0, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Simple port info application", 0, QApplication::UnicodeUTF8));
        portsGroupBox->setTitle(QApplication::translate("Dialog", "Available ports:", 0, QApplication::UnicodeUTF8));
        portNameLabel->setText(QApplication::translate("Dialog", "Current port name:", 0, QApplication::UnicodeUTF8));
        updateButton->setText(QApplication::translate("Dialog", "Update", 0, QApplication::UnicodeUTF8));
        infoGroupBox->setTitle(QApplication::translate("Dialog", "Current port info:", 0, QApplication::UnicodeUTF8));
        locationNameLabel->setText(QApplication::translate("Dialog", "Location:", 0, QApplication::UnicodeUTF8));
        locationValueLabel->setText(QApplication::translate("Dialog", "***", 0, QApplication::UnicodeUTF8));
        descriptionNameLabel->setText(QApplication::translate("Dialog", "Description:", 0, QApplication::UnicodeUTF8));
        descriptionValueLabel->setText(QApplication::translate("Dialog", "***", 0, QApplication::UnicodeUTF8));
        manufacturerNameLabel->setText(QApplication::translate("Dialog", "Manufacturer:", 0, QApplication::UnicodeUTF8));
        manufacturerValueLabel->setText(QApplication::translate("Dialog", "***", 0, QApplication::UnicodeUTF8));
        validButton->setText(QApplication::translate("Dialog", "Check valid", 0, QApplication::UnicodeUTF8));
        validLabel->setText(QApplication::translate("Dialog", "***", 0, QApplication::UnicodeUTF8));
        busyButton->setText(QApplication::translate("Dialog", "Check busy", 0, QApplication::UnicodeUTF8));
        busyLabel->setText(QApplication::translate("Dialog", "***", 0, QApplication::UnicodeUTF8));
        ratesButton->setText(QApplication::translate("Dialog", "Get rates", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PORTINFODIALOG_H
