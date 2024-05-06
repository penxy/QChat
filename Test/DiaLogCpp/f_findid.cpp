#include "f_findid.h"
#include "ui_f_findid.h"
#include "tool.h"

F_FindID::F_FindID(QWidget *parent) : QDialog(parent), ui(new Ui::F_FindID){
    ui->setupUi(this);
    Init_Btn();
}

F_FindID::~F_FindID(){
    delete ui;
}

void F_FindID::Init_Btn(){
    connect(ui->Btn_Back, &QPushButton::clicked, this, [&](){
        this->close();
        Open_Widget();
    });
    connect(ui->Btn_Find, &QPushButton::clicked, this, [&](){
        std::string id = ui->Edit_ID->toPlainText().toStdString();
        if(!Tip_ID(id, *ui->Tip_ID))return;
        user->youid = std::stoi(id);
        user->ApplyRes(QC_USEARCHUSER);
    });
}
