#ifndef F_FINDID_H
#define F_FINDID_H

#include <QDialog>

namespace Ui {
class F_FindID;
}

class F_FindID : public QDialog
{
    Q_OBJECT

public:
    explicit F_FindID(QWidget *parent = nullptr);
    ~F_FindID();
private:
    void Init_Btn();
private:
    Ui::F_FindID *ui;
};

#endif // F_FINDID_H
