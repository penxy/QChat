#include "f_beadd.h"
#include "ui_f_beadd.h"
#include "tool.h"
#include <QDebug>


F_BeAdd::F_BeAdd(QWidget *parent) : QDialog(parent), ui(new Ui::F_BeAdd){
    ui->setupUi(this);
    Init_Btn();
    Init_List();
    Show_F_BeAddList();
}

F_BeAdd::~F_BeAdd(){
    delete ui;
}
void F_BeAdd::Init_Btn(){
    connect(ui->Btn_Back, &QPushButton::clicked, this, [&](){
        this->close();
        Open_Widget();
    });
    connect(ui->Btn_Allow, &QPushButton::clicked, this, [&](){
        Btn_Work_In_ListView(*ui->List_BeAdd, QC_FALLOW, 0);
    });
    connect(ui->Btn_Reject, &QPushButton::clicked, this, [&](){
        Btn_Work_In_ListView(*ui->List_BeAdd, QC_FREJECT, 0);
    });
}
void F_BeAdd::Init_List(){
    Init_ListView(*ui->List_BeAdd);
    connect(ui->List_BeAdd, &QListView::clicked, this, [&](const QModelIndex idx){//点到好友
        if(!idx.isValid())return;
        QString temp = idx.data(Qt::DisplayRole).toString();
        user->youid = GetID(temp);
        user->Sname = GetFName(temp);
    });
}
void F_BeAdd::Show_F_BeAddList(){
    ui->List_BeAdd->setModel(user->ApplyData(QC_BEADD));
}
