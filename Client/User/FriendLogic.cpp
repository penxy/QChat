#include "FriendLogic.h"

#define debug(x) std::cout << #x << " = " << x << "\n"
FriendLogic::FriendLogic(){
    //for(int i=0;i<MAX_FRIENDS_SIZE;i++)FIdGetIdx[i] = -1;
}


/*

void Remove_FriendInfo();
void Remove_MyAddSet();
void Remove_MyBeAddSet();

void Add_FriendInfo();
void Add_MyAddSet();
void Add_MyBeAddSet();

void Sort_FriendID();

*/

/*-------------------------Tool-------------------------------*/
void FriendLogic::Remove_FriendInfo(){
    int idx = FIdGetIdx[youid];
	FIdGetIdx[FriendInfo.back().id] = idx;
    std::swap(FriendInfo[idx], FriendInfo.back());
	FriendInfo.pop_back();
    Sort_FriendID();
}

void FriendLogic::Remove_MyAddSet(){
    if(MyAdd_Set.count(youid) == 0)return;
	int idx = -1;
    for(int i=0;i<(int)MyAddID.size()&&idx==-1;i++){
        if(MyAddID[i].id == youid)idx = i;
    }
    MyAdd_Set.erase(youid);
    MyAddID.erase(MyAddID.begin() + idx);
}

void FriendLogic::Remove_MyBeAddSet(){
	if(MyBeAdd_Set.count(youid) == 0)return;
    int idx = -1;
    for(int i=0;i<(int)MyBeAddID.size()&&idx==-1;i++){
        if(MyBeAddID[i].id == youid)idx = i;
    }
    MyBeAdd_Set.erase(youid);
    MyBeAddID.erase(MyBeAddID.begin() + idx);
}

void FriendLogic::Add_FriendInfo(){
    FIdGetIdx[youid] = FriendInfo.size();
	FriendInfo.push_back(FriendInfoStruct(youid, Sname.c_str()));
    Sort_FriendID();
}

void FriendLogic::Add_MyAddSet(){
    if(MyAdd_Set.count(youid))return;
	MyAdd_Set.insert(youid);
    MyAddID.push_back(Add_Info(youid, Sname));
}


void FriendLogic::Add_MyBeAddSet(){
    if(MyBeAdd_Set.count(youid))return;
    MyBeAdd_Set.insert(youid);
    MyBeAddID.push_back(Add_Info(youid, Rname));
}
void FriendLogic::Sort_FriendID(){
    auto HeapSort = [&](auto HeapSort, int node, int all) -> void{
        int p = node;
        int left = (node << 1) +  1;
        int right = left + 1;
        if(left < all && FriendInfo[p].id < FriendInfo[left].id)p = left;
        if(right < all && FriendInfo[p].id < FriendInfo[right].id)p = right;

        if(p == node)return;
		std::swap(FIdGetIdx[FriendInfo[node].id], FIdGetIdx[FriendInfo[p].id]);
        std::swap(FriendInfo[node], FriendInfo[p]);
        HeapSort(HeapSort, p, all);
    };
	int FriendsSize = FriendInfo.size();
    for(int i=FriendsSize/2;i>=0;i--){
        HeapSort(HeapSort, i, FriendsSize);
    }
    for(int i=FriendsSize-1;i>=0;i--){
		std::swap(FIdGetIdx[FriendInfo[0].id], FIdGetIdx[FriendInfo[i].id]);
		std::swap(FriendInfo[0], FriendInfo[i]);
        HeapSort(HeapSort, 0, i);
    }
}


/*-------------------------Tool-------------------------------*/



/*

void SendFMess();
void Friend_Allow();
void Friend_Reject();
void Friend_Add();
void Friend_Del();

*/


/*-------------------------Send-------------------------------*/
void FriendLogic::SendFMess(){
    FriendInfo[FIdGetIdx[youid]].Message.push_back(FMess(1, message, get_time_10()));
}
bool FriendLogic::Friend_Allow(){
	if(FriendInfo.size() == MAX_FRIENDS_SIZE)return false;
	Add_FriendInfo();
    Remove_MyBeAddSet();
    return true;
}
void FriendLogic::Friend_Reject(){
    Remove_MyBeAddSet();
}
bool FriendLogic::Friend_Add(){
	if(MyAdd_Set.count(youid))return false;
	Add_MyAddSet();
	return true;
}
void FriendLogic::Friend_Del(){
    Remove_FriendInfo();
}
/*-------------------------Send-------------------------------*/





/*

void RecvFMess(const FMess&);
void Friend_BeAllow();
void Friend_BeReject();
void Friend_BeAdd();
void Friend_BeDel();

*/

/*-------------------------Recv-------------------------------*/
void FriendLogic::RecvFMess(const FMess&t){
    FriendInfo[FIdGetIdx[youid]].Message.push_back(t);
}
void FriendLogic::Friend_BeAllow(){
    Sname = Rname;
    debug(Sname);
	Add_FriendInfo();
    Remove_MyAddSet();
}
void FriendLogic::Friend_BeReject(){
    Remove_MyAddSet();
}
void FriendLogic::Friend_BeAdd(){
    Add_MyBeAddSet();
}
void FriendLogic::Friend_BeDel(){
	Remove_FriendInfo();	
}


/*-------------------------Recv-------------------------------*/



/*

void Clear_FriendMess();

*/
/*-------------------------Other------------------------------*/

void FriendLogic::Clear_FriendMess(){
	int idx = FIdGetIdx[youid];
	FriendInfo[idx].Message.clear();
}

/*-------------------------Other------------------------------*/