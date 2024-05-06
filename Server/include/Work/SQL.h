#ifndef __SQL_H
#define __SQL_H

#include "ClientLogic.h"

//保留 5.4
class SQL : public ClientLogic{
public:
	SQL() = default;
	virtual ~SQL() = default;	
};


#endif