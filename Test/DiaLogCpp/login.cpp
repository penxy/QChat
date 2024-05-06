#include "login.h"
#include "ui_login.h"
#include "tool.h"


//#define DEBUG 1

//00000 12345
//00001 12345

Login::Login(QWidget *parent) : QDialog(parent), ui(new Ui::Login){
    ui->setupUi(this);
    Init_Btn();
}

Login::~Login(){
    delete ui;
}
void Login::Init_Btn(){
    connect(ui->Btn_Back, &QPushButton::clicked, this, [&](){
        this->close();
    });
    connect(ui->Btn_Create, &QPushButton::clicked, this, [&](){

    });
    connect(ui->Btn_Login, &QPushButton::clicked, this, [&](){
#ifdef DEBUG
        this->close();
        Open_Widget();
#else
        ui->Edit_ID->setText("00000");
        ui->Edit_Pass->setText("12345");
        std::string id = ui->Edit_ID->toPlainText().toStdString();
        if(!Tip_ID(id, *ui->Tip_Login))return;
        std::string pass = ui->Edit_Pass->toPlainText().toStdString();
        if(!Tip_Password(pass, *ui->Tip_Login))return;

        user->myid = std::stoi(id);
        user->password = pass;

        user->ApplyRes(QC_USERLOGIN);
        if(!user->OK){
            ui->Tip_Login->setText("id or password error");
        }else{
            this->close();
            Open_Widget();
        }
#endif
    });
}
