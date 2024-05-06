#ifndef __TOSTOP_H
#define __TOSTOP_H


/*
	define the stop to break loop of all thread
*/

class ToStop{
public:
	ToStop() = default;
	virtual ~ToStop() = default;
public:
	static void Stop();
	static bool non_stop;	
};


#endif