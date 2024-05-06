#include "FriendLogic.h"



FriendLogic::FriendLogic() : friend_size(0){
    friends = new int[MAX_FRIENDS_SIZE];
}
FriendLogic::~FriendLogic(){
    delete[] friends;
}
void FriendLogic::Friend_Allow(){
    FIdGetIdx[youid] = friend_size;
    friends[friend_size] = youid;
    friend_size++;
}
void FriendLogic::Friend_Del(){
    std::swap(FIdGetIdx[youid], FIdGetIdx[friend_size - 1]);
    friend_size--;
}