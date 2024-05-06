#ifndef TOOL_H
#define TOOL_H
#include "f_talk.h"
#include "f_findid.h"
#include "f_add.h"
#include "f_beadd.h"
#include "widget.h"
#include "confirm.h"
#include "login.h"
#include "User.h"

#include "CQSigconfig.h"
#include "LimitConfig.h"

#include <QTextBrowser>
#include <QListView>
#include <iostream>

extern User* user;

void Open_F_Talk();
void Open_F_FindID();
void Open_Widget();
void Open_F_Add();
void Open_F_BeAdd();
void Open_Login();


void GetTime(char* buf);
int CheckID(int id);
int CheckGID(int gid);
int CheckID(const std::string& s);
int CheckGID(const std::string& s);
int CheckPassWord(const std::string& s);
int CheckUserName(const std::string& s);
int CheckGroupName(const std::string& s);

void Output_Error(int ret, QTextBrowser&temp);

bool Tip_ID(const std::string& id, QTextBrowser&temp);
bool Tip_GID(const std::string& gid, QTextBrowser&temp);
bool Tip_Password(const std::string& password, QTextBrowser&temp);
bool Tip_UserName(const std::string& username, QTextBrowser&temp);
bool Tip_GroupName(const std::string& groupname, QTextBrowser&temp);






bool ConFirm();


int GetID(const QString& s);
int GetGID(const QString& s);
std::string GetFName(const QString& s);
std::string GetGName(const QString& s);

bool QListView_Remove(QListView& temp);
bool QListView_SelectOne(QListView& temp);

void Init_ListView(QListView& temp);


void Btn_Work_In_ListView(QListView& temp, char sig, bool haveconfirm);

#endif // TOOL_H
