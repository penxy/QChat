#include "confirm.h"


Confirm::Confirm(bool&ok, QWidget *parent) : QDialog(parent), ui(new Ui::Confirm){
    ui->setupUi(this);
    connect(ui->Btn_YES, &QPushButton::clicked, this, [&](){
        ok = 1;
        this->close();
    });
    connect(ui->Btn_NO, &QPushButton::clicked, this, [&](){
        ok = 0;
        this->close();
    });
}

Confirm::~Confirm(){
    delete ui;
}
