#ifndef SCHEDULEABLE_H
#define SCHEDULEABLE_H

#include <iostream>  
using namespace std; 

class ScheduleAble{
    public:
    virtual void schedule() = 0;
    virtual void cancelSchedule() = 0;

    virtual ~ScheduleAble(){
        cout<<"ScheduleAble Destructor "<<endl;
    }

};
#endif