#ifndef __WORKQT_H
#define __WORKQT_H
#include "WorkServer.h"

class WorkQt : public WorkServer{
public:
    WorkQt();
    virtual ~WorkQt();
private:
	void RecvUText();
public:
    /* recv from Qt */
    void RecvQTSig();
private:
    /* 通过管道, 发送信号给QT  */
    void SendQTSig(char sig);

    /* wait server sem, and then send to qt */
    void Wait_Server();
private:
    char* RecvBuf;
    char* SendBuf;
};


#endif
