#include "tool.h"
const int dx = 100;
const int dy = 100;

void Open_F_Talk(){
    F_Talk* new_win = new F_Talk;
    new_win->setAttribute(Qt::WA_DeleteOnClose);
    new_win->move(dx, dy);
    new_win->show();
}
void Open_F_FindID(){
    F_FindID* new_win = new F_FindID;
    new_win->setAttribute(Qt::WA_DeleteOnClose);
    new_win->move(dx, dy);
    new_win->show();
}
void Open_Widget(){
    Widget* new_win = new Widget;
    new_win->setAttribute(Qt::WA_DeleteOnClose);
    new_win->move(dx, dy);
    new_win->show();
}
void Open_F_Add(){
    F_Add* new_win = new F_Add;
    new_win->setAttribute(Qt::WA_DeleteOnClose);
    new_win->move(dx, dy);
    new_win->show();
}
void Open_F_BeAdd(){
    F_BeAdd* new_win = new F_BeAdd;
    new_win->setAttribute(Qt::WA_DeleteOnClose);
    new_win->move(dx, dy);
    new_win->show();
}
void Open_Login(){
    Login* new_win = new Login;
    new_win->setAttribute(Qt::WA_DeleteOnClose);
    new_win->move(dx, dy);
    new_win->show();
}


void GetTime(char* buf){
    time_t now = time(0);
    strftime(buf, 24, "Me: %F %H:%M:%S", localtime(&now));
}
int CheckID(int id){
    return CheckID(std::to_string(id));
}
int CheckGID(int gid){
    return CheckID(std::to_string(gid));
}
int CheckID(const std::string& s){
    if(s.size() != ID_LEN)return ERROR_LEN;
    for(const char& c : s){
        if(c < '0' || '9' < c)return ERROR_NODIGIT;
    }
    int id = std::stoi(s);
    if(id < 0 || MAX_ID <= id)return ERROR_RANGE;
    return ERROR_NONE;
}
int CheckGID(const std::string& s){
    if(s.size() != GID_LEN)return ERROR_LEN;
    for(const char& c : s){
        if(c < '0' || '9' < c)return ERROR_NODIGIT;
    }
    int gid = std::stoi(s);
    if(gid < 0 || MAX_GID <= gid)return ERROR_RANGE;
    return ERROR_NONE;
}

int CheckPassWord(const std::string& s){
    if(s.empty())return ERROR_LEN;
    if(s.size() > MAX_USERPASSWORD_SIZE)return ERROR_LEN;
    if(std::count(s.begin(), s.end(), ' ') != 0)return ERROR_HASSPACE;
    return 0;
}
int CheckUserName(const std::string& s){
    if(s.empty())return ERROR_LEN;
    if(s.size() > MAX_USERNAME_SIZE)return ERROR_LEN;
    if(std::count(s.begin(), s.end(), ' ') != 0)return ERROR_HASSPACE;
    return 0;
}
int CheckGroupName(const std::string& s){
    if(s.empty())return ERROR_LEN;
    if(s.size() > MAX_GROUPNAME_SIZE)return ERROR_LEN;
    if(std::count(s.begin(), s.end(), ' ') != 0)return ERROR_HASSPACE;
    return 0;
}

void Output_Error(int ret, QTextBrowser&temp){
    if(ret == ERROR_LEN)temp.setText("len error");
    else if(ret == ERROR_HASSPACE)temp.setText("has space");
    else if(ret == ERROR_NODIGIT)temp.setText("has non-digit");
    else if(ret == ERROR_RANGE)temp.setText("range error");
    else temp.setText("id OK");
}


bool Tip_ID(const std::string& id, QTextBrowser&temp){
    int ret = CheckID(id);
    Output_Error(ret, temp);
    return ret == ERROR_NONE;
}

bool Tip_GID(const std::string& gid, QTextBrowser&temp){
    int ret = CheckGID(gid);
    Output_Error(ret, temp);
    return ret == ERROR_NONE;
}
bool Tip_Password(const std::string& password, QTextBrowser&temp){
    int ret = CheckPassWord(password);
    Output_Error(ret, temp);
    return ret == ERROR_NONE;
}
bool Tip_UserName(const std::string& username, QTextBrowser&temp){
    int ret = CheckUserName(username);
    Output_Error(ret, temp);
    return ret == ERROR_NONE;
}
bool Tip_GroupName(const std::string& groupname, QTextBrowser&temp){
    int ret = CheckGroupName(groupname);
    Output_Error(ret, temp);
    return ret == ERROR_NONE;
}

bool ConFirm(){
    bool ok = 0;
    Confirm check(ok);
    check.exec();
    return ok;
}








int GetID(const QString& s){
    return s.left(ID_LEN).toInt();
}
int GetGID(const QString& s){
    return s.left(GID_LEN).toInt();
}
std::string GetFName(const QString& s){
    return s.right(s.size() - ID_LEN - __space.size()).toStdString();
}
std::string GetGName(const QString& s){
    return s.right(s.size() - GID_LEN - __space.size()).toStdString();
}


bool QListView_Remove(QListView& temp){
    QModelIndexList selectedIndexes = temp.selectionModel()->selectedIndexes();
    if(selectedIndexes.size() != 1)return 0;
    int row = selectedIndexes.at(0).row();
    temp.model()->removeRow(row);
    temp.clearSelection();
    return 1;
}
bool QListView_SelectOne(QListView& temp){
    return temp.selectionModel()->selectedIndexes().size() == 1;
}

void Init_ListView(QListView& temp){//set can not write
    temp.setEditTriggers(QAbstractItemView::NoEditTriggers);
    temp.clearSelection();
}



void Btn_Work_In_ListView(QListView& temp, char sig, bool haveconfirm){
    if(!QListView_SelectOne(temp))return;
    if(haveconfirm && !ConFirm())return;
    if(!QListView_Remove(temp))return;
    user->SendSig(sig);
}

