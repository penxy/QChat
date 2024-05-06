#include "f_add.h"
#include "ui_f_add.h"
#include "tool.h"

extern User* user;

F_Add::F_Add(QWidget *parent) : QDialog(parent), ui(new Ui::F_Add){
    ui->setupUi(this);
    Show_F_AddList();
    Init_Btn();
    Init_List();
}

F_Add::~F_Add(){
    delete ui;
}

void F_Add::Init_Btn(){
    connect(ui->Btn_Back, &QPushButton::clicked, this, [&](){
        this->close();
        Open_Widget();
    });
}
void F_Add::Init_List(){
    Init_ListView(*ui->List_Add);
}
void F_Add::Show_F_AddList(){
    ui->List_Add->setModel(user->ApplyData(QC_MYADD));
}
