/* 
 * File:   WrningForm.h
 *
 * Created on May 21, 2015, 11:36 PM
 */

#ifndef _WRNINGFORM_H
#define	_WRNINGFORM_H

#include "QDialog"
#include <string>
#include "ui_WarningForm.h"

using namespace std;

class WarningForm : public QDialog {
    Q_OBJECT
public:
    WarningForm();
    virtual ~WarningForm();
public slots:
    void showWarning(string);
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::WarningForm widget;
};

#endif	/* _WRNINGFORM_H */
