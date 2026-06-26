#ifndef AUTOMATION_H
#define AUTOMATION_H

#include "SmartDevice.h"
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

class Automation {
private:
    int ruleID;
    string triggerCondition;  // motion, time, temperature   enhi ka use case ha
    string triggerTime;       // 22:00 for 10:00 pm
    
   
    string actionList[10];    // Max 10 actions
    int actionCount;
    
    bool isActive;

public:

    Automation(int id, string condition, string time);
    
  
    ~Automation();
   
    void activate();
    void deactivate();
    void editRule(string newCondition);
    void addAction(string action);
    bool evaluateTrigger(string currentCondition, string currentTime);
    void executeActions(SmartDevice** devices, int deviceCount);
    
    
    int getRuleID() const;
    string getTriggerCondition() const;
    string getTriggerTime() const;
    bool getIsActive() const;
    
   
    friend ostream& operator<<(ostream& os, const Automation& autoRule);
};

#endif