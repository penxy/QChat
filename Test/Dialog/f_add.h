#ifndef F_ADD_H
#define F_ADD_H

#include <QDialog>

namespace Ui {
class F_Add;
}

class F_Add : public QDialog
{
    Q_OBJECT

public:
    explicit F_Add(QWidget *parent = nullptr);
    ~F_Add();
private:
    void Init_Btn();
    void Init_List();

    void Show_F_AddList();
private:
    Ui::F_Add *ui;
};

#endif // F_ADD_H
