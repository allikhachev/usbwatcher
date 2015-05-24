/********************************************************************************
** Form generated from reading UI file 'WarningForm.ui'
**
** Created: Sun May 24 18:45:44 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WARNINGFORM_H
#define UI_WARNINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WarningForm
{
public:
    QLabel *message;
    QLabel *label_2;
    QPushButton *okButton;

    void setupUi(QDialog *WarningForm)
    {
        if (WarningForm->objectName().isEmpty())
            WarningForm->setObjectName(QString::fromUtf8("WarningForm"));
        WarningForm->resize(400, 119);
        WarningForm->setSizeGripEnabled(false);
        WarningForm->setModal(false);
        message = new QLabel(WarningForm);
        message->setObjectName(QString::fromUtf8("message"));
        message->setGeometry(QRect(10, 10, 381, 41));
        message->setLineWidth(1);
        message->setTextFormat(Qt::RichText);
        message->setWordWrap(true);
        label_2 = new QLabel(WarningForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 381, 31));
        okButton = new QPushButton(WarningForm);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(294, 85, 98, 27));
        okButton->setDefault(false);

        retranslateUi(WarningForm);

        QMetaObject::connectSlotsByName(WarningForm);
    } // setupUi

    void retranslateUi(QDialog *WarningForm)
    {
        WarningForm->setWindowTitle(QApplication::translate("WarningForm", "Warning", 0, QApplication::UnicodeUTF8));
        message->setText(QApplication::translate("WarningForm", "\320\222\321\213 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\270\320\273\320\270 \320\275\320\265\321\200\320\260\320\267\321\200\320\265\321\210\320\265\320\275\320\275\320\276\320\265 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276 \321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270.", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("WarningForm", "\320\220\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200\321\213 \321\203\320\262\320\265\320\264\320\276\320\274\320\273\320\265\320\275\321\213 \320\276 \320\275\320\260\321\200\321\203\321\210\320\265\320\275\320\270\320\270 \320\267\320\260\320\277\321\200\320\265\321\202\320\260.", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("WarningForm", "ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WarningForm: public Ui_WarningForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WARNINGFORM_H
