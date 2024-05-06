#include "f_talk.h"
#include "ui_f_talk.h"
#include "tool.h"
#include <QKeyEvent>

F_Talk::F_Talk(QWidget *parent) : QDialog(parent), ui(new Ui::F_Talk){
    ui->setupUi(this);
    ui->Edit_Mess->installEventFilter(this);
    Init_Btn();
    Show_F_Info();
    Show_F_Mess();
}

F_Talk::~F_Talk(){
    delete ui;
}


void F_Talk::Init_Btn(){
    connect(ui->Btn_Back, &QPushButton::clicked, this, [&](){
        this->close();
        Open_Widget();
    });
    connect(ui->Btn_Clear, &QPushButton::clicked, this, [&](){
        ui->Edit_Mess->clear();
    });
    connect(ui->Btn_Send, &QPushButton::clicked, this, [&](){
        Mess_Append();
        user->message = ui->Edit_Mess->toPlainText().toStdString();
        user->SendSig(QC_FSENDMESSAGE);
        Edit_Clear();
    });
    connect(ui->Btn_ClearMess, &QPushButton::clicked, this, [&](){
        if(!ConFirm())return;
        Mess_Clear();
        user->SendSig(QC_FMESSAGECLEAR);
    });
}


void F_Talk::Mess_Append(){
    static char buf[24];
    GetTime(buf);
    ui->Show_Mess->append(buf);
    ui->Show_Mess->append(ui->Edit_Mess->toPlainText());
    ui->Show_Mess->append("");
}
void F_Talk::Mess_Clear(){
    ui->Show_Mess->clear();
}

void F_Talk::Edit_Clear(){
    ui->Edit_Mess->clear();
}


void F_Talk::Show_F_Info(){
    ui->Show_Info->setText(user->Sname.c_str());
}
void F_Talk::Show_F_Mess(){
    Mess_Clear();
    Json::Value data = user->ApplyMessage(QC_FRIENDMESS);
    for(auto temp : data["arr"]){
        std::string s = (temp["type"].asBool() == false ? "you " : "Me ");
        s += temp["time"].asString();
        ui->Show_Mess->append(s.c_str());
        ui->Show_Mess->append(temp["mess"].asCString());
        ui->Show_Mess->append("");
    }
}

bool F_Talk::eventFilter(QObject *obj, QEvent *event){
    if(obj == ui->Edit_Mess && event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent* >(event);
        if(keyEvent && (keyEvent->key() == Qt::Key_Return)){
            ui->Btn_Send->click();return 1;
        }
    }return 0;
}
