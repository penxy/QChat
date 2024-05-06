#include "buffer.h"

#define debug(x) std::cout << #x << " = " << x << "\n";

Buffer::Buffer(){init();}
Buffer::~Buffer(){}
void Buffer::init(){Sum.resize(SumCapacity = INIT_SUMSIZE, 0);buffer.resize(BufCapacity = INIT_BUFSIZE, '\0');tot = ReadPos = ReadSumIdx = p = 0;}//remove if(tot == 0)return;

char* Buffer::Get_ReadIdx(){return &buffer[ReadPos];}
int Buffer::Get_ReadLen(){return Sum[p] - ReadPos;}

void Buffer::Read(){
	if(is_empty()){init();return;}

	int l = ReadSumIdx;
	int r = tot;
	int mid;
	while(l <= r){
		mid = (l + r) >> 1;
		if(Sum[mid] - ReadPos <= MAX_RECV_SIZE)l = mid + 1, p = mid;
		else r = mid - 1;
	}
	//send(c_sock, Get_ReadIdx(), Get_ReadLen(), 0);	
	//AfterRead();
}

void Buffer::AfterRead(){
	ReadSumIdx = p;
	ReadPos = Sum[p];
}

void Buffer::Write(char* buf, int len){
	//int len = recv(c_sock, buf, MAX_SEND_SIZE, 0);

	if(BufCapacity - Sum[tot] < len){
		if(!EnsureWrite(len))return;

	}
	strcpy(&buffer[Sum[tot]], buf);
	if(tot + 1 >= SumCapacity){
		if((SumCapacity <<= 1) > MAX_SUMSIZE){std::cerr << "Error SumCapacity\n";exit(1);}
		Sum.resize(SumCapacity);
	}
	tot++;
	Sum[tot] = Sum[tot - 1] + len;
}

bool Buffer::EnsureWrite(int len){
	if(BufCapacity - Sum[tot] + ReadPos < len){
		if((BufCapacity <<= 1) > MAX_BUFSIZE){return false;}
		buffer.resize(BufCapacity, '\0');		
	}else{
		std::copy(buffer.begin() + Sum[ReadSumIdx], buffer.begin() + Sum[tot], buffer.begin());
		std::for_each(Sum.begin() + ReadSumIdx + 1, Sum.begin() + tot + 1, [&](int &x){ x -= ReadPos; });
		std::copy(Sum.begin() + ReadSumIdx + 1, Sum.begin() + tot + 1, Sum.begin() + 1);
		tot -= ReadSumIdx;
		ReadSumIdx = ReadPos = 0;
	}
	return true;
}
bool Buffer::is_empty(){
	return ReadPos == Sum[tot];
}