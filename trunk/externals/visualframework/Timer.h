/*==============================================================================

	Timer.h

	visualframework: a simple 2d graphics framework
  
	Copyright (C) 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
    
    	Timer() : alarmMS(0), alarmstamp(0) {set();}
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
        	alarmMS = alarmTime;
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
        
        /// returns the difference between 0 and 1 (normalized)
        inline float getDiffN()
        {
        	return getDiff()/alarmMS;
        }
        
    protected:
    
    	unsigned int alarmMS;	///< length of alarm
    	unsigned int timestamp;	///< current timestamp
        unsigned int alarmstamp; ///< future timestamp
};

} // namespace

#endif // VISUAL_TIMER_H
