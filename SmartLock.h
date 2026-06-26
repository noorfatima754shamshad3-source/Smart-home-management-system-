#ifndef SMARTLOCK_H
#define SMARTLOCK_H

#include "SmartAppliance.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class SmartLock : public SmartAppliance {
private:
    bool isLocked;
    string accessCode;
    string* accessLog;  // Dynamic array of strings
    int logCount;
    int maxLogs;

public:

    SmartLock(int id, string name, string location, string accessCode);

    ~SmartLock();
    
    void lock();
    void unlock(string code);
    bool verifyCode(string code);
    void getAccessHistory() const;
    
    
    void startCycle() override;
    string getStatus()  override;
    void generateReport() override;
};

#endif