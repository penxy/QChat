#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void Init_Btn();
    void Init_List();

    void Show_FriendListInfo();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
