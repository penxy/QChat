#ifndef __BUFFER_H
#define __BUFFER_H

#ifdef DEBUG
#define INIT_SUMSIZE				4
#define MAX_SUMSIZE					16
#define INIT_BUFSIZE				8
#define MAX_BUFSIZE					32
#else
#define INIT_SUMSIZE				512
#define MAX_SUMSIZE					4096
#define INIT_BUFSIZE				512
#define MAX_BUFSIZE					4096
#endif

#define MAX_RECV_SIZE				512
#define MAX_SEND_SIZE				512


#include <vector>
#include <algorithm>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

class Buffer{
public:
	Buffer();
	~Buffer();
public:
	/* Read, and then, can get read_idx and read_len */
	void Read();
	void Write(char* buf, int len);
public:
	char* Get_ReadIdx();
	int Get_ReadLen(); 
	
	bool is_empty();
	void AfterRead();
private:
	void init();
	bool EnsureWrite(int len);//if can not write in, drop it.
private:
	int p;
	int BufCapacity;
	int SumCapacity;
	int tot;
	std::vector<int>Sum;
	std::vector<char>buffer;
	int ReadPos;
	int ReadSumIdx;
};


#endif
