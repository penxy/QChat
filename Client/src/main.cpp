#include "SemServer.h"
#include "SemQt.h"
#include "User.h"
#include "Client.h"

static constexpr char* QtPath = "QT/Test";
SemServer sem_server = SemServer();
SemQt sem_qt = SemQt();
pid_t QtId;
User *user;

void Init(){
    Client* client = new Client();
    client->Run();
    delete client;
}

int main(int argc, char* argv[]){
    user = new User();
    Init();
    //delete user;
    return 0;
}