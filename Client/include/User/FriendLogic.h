#ifndef __FRIENDLOGIC_H
#define __FRIENDLOGIC_H

#include "UserLogic.h"

#include <unordered_map>
#include <vector>
#include <set>
#include <map>


#ifndef INFO
#define INFO

struct FMess{
    bool type;//0 you->me  1 me->you
    std::string mess;
    std::string time;
    FMess() = default;
    FMess(int type, const std::string& mess, const std::string& time){
        this->type = type;this->mess = mess;this->time = time;
    }
};

struct Add_Info{
    int id;
    std::string name;
    Add_Info() = default;
    Add_Info(int id, const std::string& name){
        this->id = id;this->name = name;
    }
};
struct FriendInfoStruct{
    int id;
    char name[MAX_USERNAME_SIZE];
    std::vector<FMess>Message;
	FriendInfoStruct() = default;
	FriendInfoStruct(int id, const char* name){
		this->id = id;strcpy(this->name, name);
	}
};
#endif

class FriendLogic : public UserLogic{
public:
	FriendLogic();
	virtual ~FriendLogic() = default;
protected:
	void SendFMess();
    bool Friend_Allow();
    void Friend_Reject();
    bool Friend_Add();
    void Friend_Del();

	void RecvFMess(const FMess&);
	void Friend_BeAllow();
    void Friend_BeReject();
    void Friend_BeAdd();
    void Friend_BeDel();
	
	void Clear_FriendMess();
private:
	void Remove_FriendInfo();
    void Remove_MyAddSet();
    void Remove_MyBeAddSet();

    void Add_FriendInfo();
    void Add_MyAddSet();
    void Add_MyBeAddSet();
	
	void Sort_FriendID();
protected:
	std::vector<Add_Info>MyAddID;
    std::vector<Add_Info>MyBeAddID;

    std::set<int>MyAdd_Set;
    std::set<int>MyBeAdd_Set;
	
	std::vector<FriendInfoStruct>FriendInfo;
    std::unordered_map<int, int>FIdGetIdx;
};







#endif
