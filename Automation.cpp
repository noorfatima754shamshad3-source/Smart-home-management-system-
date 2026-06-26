#include "Automation.h"


Automation::Automation(int id, string condition, string time)
    : ruleID(id), triggerCondition(condition), triggerTime(time), 
      actionCount(0), isActive(false) {
    
   
    for(int i = 0; i < 10; i++) {
        actionList[i] = "";
    }
    
    cout << "Automation Rule Created: ID=" << ruleID 
         << "  Condition=" << triggerCondition 
         << "  Time=" << triggerTime << endl;
}


Automation::~Automation() {
    cout << "Automation Rule Destroyed: ID=" << ruleID << endl;
}


void Automation::activate() {
    isActive = true;
    cout << " Automation Rule " << ruleID << " ACTIVATED" << endl;
}


void Automation::deactivate() {
    isActive = false;
    cout << " Automation Rule " << ruleID << " DEACTIVATED" << endl;
}

// through this we can change condition and time
void Automation::editRule(string newCondition) {
    triggerCondition = newCondition;
    cout << " Automation Rule " << ruleID << " UPDATED" << endl;
    cout << "   New Condition: " << triggerCondition << endl;
}


void Automation::addAction(string action) {
    if(actionCount < 10) {
        actionList[actionCount] = action;
        actionCount++;
        cout << " Action added to Rule " << ruleID << ": " << action << endl;
    } else {
        cout << " Cannot add more actions. Maximum 10 actions per rule." << endl;
    }
}


bool Automation::evaluateTrigger(string currentCondition, string currentTime) {
    if(!isActive) {
        return false;
    }
    
    cout << "\n Evaluating Automation Rule " << ruleID << "..." << endl;
    cout << "   Rule Condition: " << triggerCondition << endl;
    cout << "   Current Condition: " << currentCondition << endl;
    
    bool conditionMatched = false;
    

    if(triggerCondition == "motion" && currentCondition == "motion") {
        conditionMatched = true;
        cout << "    Motion detected. Condition matched." << endl;
    }
    
    
    else if(triggerCondition == "time" && currentTime == triggerTime) {
        conditionMatched = true;
        cout << "    Time matched. (" << triggerTime << ") Condition matched." << endl;
    }
    
    // Check for MOTION + TIME combination
    else if(triggerCondition == "motion_time" && currentCondition == "motion") {
        // Check if current time is after trigger time
        if(currentTime >= triggerTime) {
            conditionMatched = true;
            cout << "    Motion detected after " << triggerTime << "! Condition matched." << endl;
        } else {
            cout << "    Motion detected but before " << triggerTime << endl;
        }
    }
  
    else if(triggerCondition == "temperature" && currentCondition == "temperature") {
        conditionMatched = true;
        cout << "    Temperature condition matched." << endl;
    }
    
    else {
        cout << "    Condition did NOT match." << endl;
    }
    
    return conditionMatched;
}


void Automation::executeActions(SmartDevice** devices, int deviceCount) {
    if(!isActive) {
        cout << "Automation Rule " << ruleID << " is not active." << endl;
        return;
    }
    
    if(actionCount == 0) {
        cout << "No actions defined for Rule " << ruleID << endl;
        return;
    }
    
    cout << "\n EXECUTING Automation Rule " << ruleID << " Actions..." << endl;
    cout << "========================================" << endl;
    
    for(int i = 0; i < actionCount; i++) {
        string action = actionList[i];
        cout << "  -> Action " << (i+1) << ": " << action << endl;
        
       
        if(action == "turn_on_lights") {
           
            for(int j = 0; j < deviceCount; j++) {
                if(devices[j] != nullptr) {
                    string deviceType = typeid(*devices[j]).name();  // ya pa us device ak actual object bna ga 
                    if(deviceType.find("Light") != string::npos) {  // yaha pa check ho raha ha kis position par match hoa ha light with device 
                        if(!devices[j]->getIsOn()) {   
                            devices[j]->toggle();  // opposite
                            cout << "      Light turned ON" << endl;
                        }
                    }
                }
            }
        }
        else if(action == "turn_off_lights") {
          
            for(int j = 0; j < deviceCount; j++) {
                if(devices[j] != nullptr) {
                    string deviceType = typeid(*devices[j]).name();
                    if(deviceType.find("Light") != string::npos) {
                        if(devices[j]->getIsOn()) {
                            devices[j]->toggle();
                            cout << "     💡 Light turned OFF" << endl;
                        }
                    }
                }
            }
        }
        else if(action == "lock_doors") {
           
            for(int j = 0; j < deviceCount; j++) {
                if(devices[j] != nullptr) {
                    string deviceType = typeid(*devices[j]).name();
                    if(deviceType.find("Lock") != string::npos) {
                        cout << "      Door locked" << endl;
                    }
                }
            }
        }
        else if(action == "start_recording") {
            
            for(int j = 0; j < deviceCount; j++) {
                if(devices[j] != nullptr) {
                    string deviceType = typeid(*devices[j]).name();
                    if(deviceType.find("Camera") != string::npos) {
                        cout << "      Camera recording started" << endl;
                    }
                }
            }
        }
        else if(action == "send_alert") {
            cout << "      ALERT: Security event triggered!" << endl;
        }
        else {
            cout << "      inValid action: " << action << endl;
        }
    }
    
    cout << "========================================" << endl;
    cout << " Rule " << ruleID << " execution completed." << endl;
}

int Automation::getRuleID() const {
    return ruleID;
}

string Automation::getTriggerCondition() const {
    return triggerCondition;
}

string Automation::getTriggerTime() const {
    return triggerTime;
}

bool Automation::getIsActive() const {
    return isActive;
}


ostream& operator<<(ostream& os, const Automation& autoRule) {
    os << "[Automation: ID=" << autoRule.ruleID 
       << " | Condition=" << autoRule.triggerCondition 
       << " | Time=" << autoRule.triggerTime 
       << " | Active=" << (autoRule.isActive ? "Yes" : "No")
       << " | Actions=" << autoRule.actionCount << "]";
    return os;
}