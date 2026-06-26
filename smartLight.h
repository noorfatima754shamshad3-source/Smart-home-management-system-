#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H

#include <iostream>  
#include <string> 

using namespace std; 

#include "SmartDevice.h"
#include "ScheduleAble.h"


class SmartLight:public SmartDevice ,public ScheduleAble{
    private:
    int brightness;
    int colorTemperature;
    string hexColor;

public:
    SmartLight(int id, string n, string loc);
    ~SmartLight();
    
   
    void setBrightness(int brightness);
    void setColor(string hexColor);
    void dimToSunset();
    
   
    void toggle() override;
    string getStatus()  override;
    void generateReport() override;
    
    
    void schedule() override;
    void cancelSchedule() override;


};
#endif