#include "widget.h"
#include "User.h"
#include "login.h"

#include <QApplication>

User* user;

int main(int argc, char *argv[]){
    user = new User(std::stoi(getenv("SEM_ID")));

    QApplication a(argc, argv);

    Login w;
    w.show();

    return a.exec();
}
