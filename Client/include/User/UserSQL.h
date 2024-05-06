#ifndef __USERSQL_H
#define __USERSQL_H

#include "FriendLogic.h"

static constexpr int CMD_SIZE = 64;
static constexpr int BUFFER_SIZE = 512;

	
class UserSQL : public FriendLogic{
public:
	UserSQL() = default;
	virtual ~UserSQL() = default;
public:
    void Save();// save in sql
    void Load();// read in sql
protected:
	void CreateSQL();
private:
    void ReadInCSV();
    void F(const std::string& s, int idx);
private:
	static constexpr int len_file_path = 5;
	const char* file_path[len_file_path] = {"SQL/Data/FriendTable.csv", "SQL/Data/FriendMessageTable.csv", "SQL/Data/MyAddTable.csv", "SQL/Data/MyBeAddTable.csv", "SQL/Data/UserInfoTable.csv"};
	
	char cmd[CMD_SIZE];
	char buffer[BUFFER_SIZE];
};


#endif