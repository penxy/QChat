#ifndef F_BEADD_H
#define F_BEADD_H

#include <QDialog>

namespace Ui {
class F_BeAdd;
}

class F_BeAdd : public QDialog
{
    Q_OBJECT

public:
    explicit F_BeAdd(QWidget *parent = nullptr);
    ~F_BeAdd();
private:
    void Init_Btn();
    void Init_List();

    void Show_F_BeAddList();
private:
    Ui::F_BeAdd *ui;
};

#endif // F_BEADD_H
