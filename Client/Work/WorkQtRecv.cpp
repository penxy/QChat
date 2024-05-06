#include "WorkQtRecv.h"
#include "User.h"
#include "SemQt.h"
#include "tool.h"

#include <sys/sem.h>
#include <sys/stat.h>

extern User* user;
extern pid_t QtId;
extern SemQt sem_qt;

#define debug(x) std::cout << #x << " = " << x << "\n"

WorkQtRecv::WorkQtRecv(){    
    if(access(pipe_path, F_OK) != -1);
	else mkfifo(pipe_path, 0666);

    key_t key = ftok("sem/sem_set", 'S');
    sem_id = semget(key, 1, IPC_CREAT | 0666);

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;
}
void WorkQtRecv::SetRecv(){
    RecvBuf = sem_qt.Get_RecvSharedMemory();
}


void* WorkQtRecv::Run(void* arg){
    char pid_client[10];
    strcpy(pid_client, std::to_string(getpid()).c_str());
    
    QtId = fork();
    if(QtId == 0){
        char sem_id_str[10];
        sprintf(sem_id_str, "%d", sem_id);
        setenv("SEM_ID", sem_id_str, 1);
        
        char *const argv[] = {"QT", pid_client, NULL};
        execv(Qt_path, argv);
        WriteLog("exec error");
    }else{
        while(non_stop){
            semop(sem_id, &op, 1);
            Recv();
        }
    }
    pthread_exit(NULL);
}


void WorkQtRecv::Recv(){
    int fd = open(pipe_path, O_RDONLY);
    int ret = read(fd, RecvBuf, MAX_PIPE_SIZE - 1);
    if(ret == -1)perror("pipe: ");
    close(fd);
    WriteLog(std::string("Recv From Qt: ") + std::string(RecvBuf));
    user->RecvQTSig();
}

