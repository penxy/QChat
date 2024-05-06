#include "UserInfo.h"

/* buffer */
void UserInfo::WriteInBuffer(char* buf){
    buffer.Write(buf, strlen(buf));    
}
char* UserInfo::GetReadIdx(){
    return buffer.Get_ReadIdx();
}
int UserInfo::GetReadLen(){
    return buffer.Get_ReadLen();
}
bool UserInfo::empty_buffer(){
    return buffer.is_empty();
}


void UserInfo::Read(){
    buffer.Read();
}

void UserInfo::AfterRead(){
    buffer.AfterRead();
}