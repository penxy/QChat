#include "UserSQL.h"

#include <assert.h>
#include <fstream>
#include <sstream>

#define debug(x) std::cout << #x << " = " << x << "\n"




template<typename T>
T GetStr(T value) {
    return value;
}
template<typename T, typename... Args>
T GetStr(T first, Args... rest) {
    return first + GetStr(rest...);
}






/*

void WriteInCSV();
void Save();
void Load();
void CreateSQL();
void ReadInCSV();

*/


/*-------------------------------------------------SQL----------------------------------------------------*/
void WriteInCSV(std::ostringstream& os, const std::string& file_path){
    std::ofstream file(file_path);
    assert(file.is_open());
    file << os.str();
    file.close();
    os.str("");
}

void UserSQL::Save(){
    std::ostringstream os;
    os << "id,name\n";
    for(int i=0;i<(int)FriendInfo.size();i++){
        os << FriendInfo[i].id << "," << FriendInfo[i].name << "\n";
    }
    WriteInCSV(os, file_path[0]);

    os << "id,type,time,message\n";
    for(int i=0;i<(int)FriendInfo.size();i++){
        for(int j=0;j<FriendInfo[i].Message.size();j++){
            os << FriendInfo[i].id << "," << FriendInfo[i].Message[j].type << "," << FriendInfo[i].Message[j].time << "," << FriendInfo[i].Message[j].mess << "\n";
			WriteLog(std::to_string(FriendInfo[i].id) + "," + std::to_string(FriendInfo[i].Message[j].type) + "," + FriendInfo[i].Message[j].time + "," + FriendInfo[i].Message[j].mess);
		}
    }
    WriteInCSV(os, file_path[1]);

    os << "id,name\n";
    for(int i=0;i<MyAddID.size();i++){
        os << MyAddID[i].id << "," << MyAddID[i].name << "\n";
    }
    WriteInCSV(os, file_path[2]);

    os << "id,name\n";
    for(int i=0;i<MyBeAddID.size();i++){
        os << MyBeAddID[i].id << "," << MyBeAddID[i].name << "\n";
    }
    WriteInCSV(os, file_path[3]);

	std::string name = MyName;
    os << "id,name\n";
    os << myid << "," << name << "\n";
    WriteInCSV(os, file_path[4]);

    snprintf(cmd, sizeof(cmd), "./SQL/write.sh %d", myid);
    system(cmd);
	ClearBuf(cmd);
}

void UserSQL::F(const std::string& s, int idx){
	std::vector<std::string>v;
	std::string temp;
	for(int i=0;i<s.size();i++){
		if(s[i] == ',')v.push_back(temp), temp.clear();
		else temp.push_back(s[i]);
	}
	v.push_back(temp);
	int id = std::stoi(v[0]);

	if(idx == 0){
		FriendInfo.push_back(FriendInfoStruct(id, v[1].c_str()));
		FIdGetIdx[id] = FriendInfo.size() - 1;
	}else if(idx == 1){
		//std::string __char = ",";
		//WriteLog(GetStr(std::to_string(id), __char, v[1], __char, v[2], __char, v[3]));
		FriendInfo[FIdGetIdx[id]].Message.push_back(FMess(std::stoi(v[1]), v[2], v[3]));
	}else if(idx == 2){
		MyAdd_Set.insert(id);
		MyAddID.push_back(Add_Info(id, v[1]));
	}else if(idx == 3){
		MyBeAdd_Set.insert(id);
		MyBeAddID.push_back(Add_Info(id, v[1]));
	}else if(idx == 4){
		//...
	}
}


void UserSQL::ReadInCSV(){//idx of file_path[]
	for(int idx=0;idx<len_file_path;idx++){
		bool __first_line = false;//to ignore first line in the file

		int line_idx = 0;
		std::ifstream in(file_path[idx]);
		std::string line;
		while(std::getline(in, line)){
			if(!__first_line){
				__first_line = true;
				continue;
			}
			F(line, idx);

			//1
		}
	}
}
void UserSQL::Load(){
    //read db to csv
    snprintf(cmd, sizeof(cmd), "./SQL/read.sh %d", myid);
    system(cmd);
	ClearBuf(cmd);

    ReadInCSV();
}

void UserSQL::CreateSQL(){
    snprintf(cmd, sizeof(cmd), "./SQL/CreateTable.sh %d", myid);
    system(cmd);
	ClearBuf(cmd);
}
/*-------------------------------------------------SQL----------------------------------------------------*/

/*
1
			5.5 have bug, split fail.
			//run the shell to get infomathion of string
			snprintf(cmd, CMD_SIZE, "python3 Shell/StrOp.py %s %s", line.c_str(), ",");
			FILE* pipe = popen(cmd, "r");
			//ClearBuf(cmd);

			
			line_idx = 0;
			while (fgets(buffer, sizeof(buffer), pipe) != NULL) {  

				buffer[strcspn(buffer, "\n")] = 0;
				std::cout << "buffer: " << buffer << "\n";
				if(idx == 0){//id name
					if(line_idx == 0){
						finfo.id = std::stoi(buffer);
						FIdGetIdx[finfo.id] = (int)FriendInfo.size();
						line_idx = 1;
					}else if(line_idx == 1){
						strcpy(finfo.name, buffer);
						FriendInfo.push_back(finfo);
						line_idx = 0;
					}
				}else if(idx == 1){//id type time mess
					if(line_idx == 0){
						id = std::stoi(buffer);
						line_idx++;
					}else if(line_idx == 1){
						fmess.type = std::stoi(buffer);
						line_idx++;
					}else if(line_idx == 2){
						fmess.time = buffer;
						line_idx++;
					}else if(line_idx == 3){
						fmess.mess = buffer;
						FriendInfo[FIdGetIdx[id]].Message.push_back(fmess);
						line_idx = 0;
					}
				}else if(idx == 2){//id name
					if(line_idx == 0){
						add_info.id = std::stoi(buffer);
						line_idx++;
					}else if(line_idx == 1){
						add_info.name = buffer;
						MyAdd_Set.insert(add_info.id);
						MyAddID.push_back(add_info);
						line_idx = 0;
					}
				}else if(idx == 3){//id name
					if(line_idx == 0){
						add_info.id = std::stoi(buffer);
						line_idx++;
					}else if(line_idx == 1){
						add_info.name = buffer;
						MyBeAdd_Set.insert(add_info.id);
						MyBeAddID.push_back(add_info);
						line_idx = 0;
					}
				}
				ClearBuf(buffer);  
			}  

			assert(pclose(pipe) == 0);
			*/