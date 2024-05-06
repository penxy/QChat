#include "UserLogic.h"

#define debug(x) std::cout << #x << " = " << x << "\n"

UserLogic::UserLogic() : login_ok(false){

}
void UserLogic::User_Login(){	
	login_ok = true;
	OK = true;
}
void UserLogic::User_Create(){
	OK = true;
}



