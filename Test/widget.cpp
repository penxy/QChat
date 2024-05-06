#include "widget.h"
#include "ui_widget.h"
#include "tool.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget){
    ui->setupUi(this);
    Show_FriendListInfo();
    Init_Btn();
    Init_List();
}
Widget::~Widget(){
    delete ui;
}

void Widget::Init_Btn(){
    connect(ui->Btn_Back, &QPushButton::clicked, this, [&](){
        this->close();
        Open_Login();
    });
    connect(ui->Btn_FindID, &QPushButton::clicked, this, [&](){
        this->close();
        Open_F_FindID();
    });
    connect(ui->Btn_Add, &QPushButton::clicked, this, [&](){
        this->close();
        Open_F_Add();
    });
    connect(ui->Btn_BeAdd, &QPushButton::clicked, this, [&](){
        this->close();
        Open_F_BeAdd();
    });
    connect(ui->Btn_Del, &QPushButton::clicked, this, [&](){
        Btn_Work_In_ListView(*ui->List_Friend, QC_FDEL, 1);
    });
}
void Widget::Init_List(){
    Init_ListView(*ui->List_Friend);
    connect(ui->List_Friend, &QListView::doubleClicked, this, [&](const QModelIndex idx){
        if(!idx.isValid())return;
        QString temp = idx.data(Qt::DisplayRole).toString();
        user->youid = GetID(temp);
        user->Sname = GetFName(temp);
        this->close();
        Open_F_Talk();
    });
}
void Widget::Show_FriendListInfo(){//show id and name of friends.
    ui->List_Friend->setModel(user->ApplyData(QC_FRIENDLIST));
}
