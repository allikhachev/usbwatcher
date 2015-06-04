/*
 * File:   WrningForm.cpp
 *
 * Created on May 21, 2015, 11:36 PM
 */

#include "WarningForm.h"
#include "QCloseEvent"
#include "QTextCodec"

WarningForm::WarningForm() {
    widget.setupUi(this);
    connect(widget.okButton, SIGNAL(pressed()), this, SLOT(hide()));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
}

void WarningForm::showWarning(string deviceId) {
    string message = "Вы подключили неразрешенное устройство c идентификатором " + deviceId;
    widget.message->setText(trUtf8(message.c_str()));
    show();
}

void WarningForm::closeEvent(QCloseEvent *event) {
    event->ignore();
    hide();
}

WarningForm::~WarningForm() {
}
