#ifndef CONFIRM_H
#define CONFIRM_H

#include <QDialog>
#include "ui_confirm.h"
#include <QPushButton>

namespace Ui {
class Confirm;
}

class Confirm : public QDialog
{
    Q_OBJECT

public:
    explicit Confirm(bool &ok, QWidget *parent = nullptr);
    ~Confirm();

private:
    Ui::Confirm *ui;
};

#endif // CONFIRM_H
