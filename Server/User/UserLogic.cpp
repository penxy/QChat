#include "UserLogic.h"


void UserLogic::User_Create(int IndexOfUser){
    myid = IndexOfUser;
    myname = Rname;
    mypassword = pass;

}

bool UserLogic::User_Login(){
    if(myid == -1)return false;
    if(pass != mypassword)return false;

    this->myid = myid;
    return true;
}
void UserLogic::User_Logout(){
    
}


