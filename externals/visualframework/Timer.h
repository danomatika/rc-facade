/*==============================================================================
    Dan Wilcox <danomatika@gmail.com>, 2009
==============================================================================*/
#ifndef VISUAL_TIMER_H
#define VISUAL_TIMER_H

#include "Common.h"

namespace visual {

/**
	\class	Timer
	\brief	a simple timer/alarm
*/
class Timer
{
	public:
    
    	Timer() : alarmstamp(0) {set();}
        Timer(const unsigned int alarmTime) {setAlarm(alarmTime);}
        virtual ~Timer() {}
        
        /// set the timestamp to the current time
        inline void set()
        {
        	timestamp = Graphics::getMillis();
        }
        
        /// set the timestamp and alarm
        /// \param	alarmTime	how many ms i nthe future the alrm should go off
        inline void setAlarm(const unsigned int alarmTime)
        {
        	timestamp = Graphics::getMillis();
        	alarmstamp = timestamp + alarmTime;
        }
        
        /// has the alarm gone off?
        inline bool alarm()
        {
        	return Graphics::getMillis() >= alarmstamp;
        }
        
        /// returns how many ms have expired since the timestamp was last set
        inline unsigned int getDiff()
        {
        	return Graphics::getMillis() - timestamp;
        }
        
    protected:
    
    	unsigned int alarmstamp;	///< future timestamp
    	unsigned int timestamp; 	///< current timestamp
};

} // namespace

#endif // VISUAL_TIMER_H
