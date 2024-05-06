#include "ToStop.h"


bool ToStop::non_stop = true;

void ToStop::Stop(){
	non_stop = false;	
}

