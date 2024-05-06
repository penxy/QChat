#ifndef F_TALK_H
#define F_TALK_H

#include <QDialog>

namespace Ui {
class F_Talk;
}

class F_Talk : public QDialog
{
    Q_OBJECT

public:
    explicit F_Talk(QWidget *parent = nullptr);
    ~F_Talk();
private:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    void Init_Btn();

    void Mess_Append();
    void Mess_Clear();

    void Edit_Clear();

    void Show_F_Info();
    void Show_F_Mess();
private:
    Ui::F_Talk *ui;
};

#endif // F_TALK_H
