#include "SmartLock.h"

// Constructor
SmartLock::SmartLock(int id, string name, string location, string accessCode)
    : SmartAppliance(id, name, location, 10.0),  // 10 watts power rating
      isLocked(true), 
      accessCode(accessCode),
      logCount(0),
      maxLogs(50) {
    
     //  array for access log
    accessLog=new string[maxLogs];
    for(int i=0;i<maxLogs;i++){
        accessLog[i]="";
    }
    
    cout << "SmartLock Created: " << getName() << endl;
    cout << "  Access Code: " << accessCode << " (Keep it secret!)" << endl;
}

SmartLock::~SmartLock() {
    cout << "SmartLock Destroyed: " << getName() << endl;
    delete[] accessLog;  
}

void SmartLock::lock() {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Cannot lock. Turn ON first!" << endl;
        return;
    }
    
    isLocked = true;
    cout << getName() << " LOCKED" << endl;
    
    
    if(logCount < maxLogs) {
        // ya part embeded haaa time function use ho raha ha
 // time(0) mean current time la lo , time_t aik integer type variable ha ju number store krta ha 
        // now mean us value ko store kro 
        time_t now = time(0);
        string timeStr = ctime(&now);
       
        if(!timeStr.empty() && timeStr[timeStr.length()-1] == '\n') {
            timeStr = timeStr.substr(0, timeStr.length()-1);
        }
        accessLog[logCount] = "LOCKED at " + timeStr;
        logCount++;
    }
}

void SmartLock::unlock(string code) {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Cannot unlock. Turn ON first!" << endl;
        return;
    }
    
    if(verifyCode(code)) {
        isLocked = false;
        cout << getName() << " UNLOCKED" << endl;
        
        if(logCount < maxLogs) {
            time_t now = time(0);
            string timeStr = ctime(&now);
           
            if(!timeStr.empty() && timeStr[timeStr.length()-1] == '\n') {
                timeStr = timeStr.substr(0, timeStr.length()-1);
            }
            accessLog[logCount] = "UNLOCKED at " + timeStr;
            logCount++;
        }
    } else {
        cout << "Wrong code for " << getName() << endl;
        
       
        if(logCount < maxLogs) {
            time_t now = time(0);
            string timeStr = ctime(&now);  
             // Remove newline from time string  ju last pa ati haa
            if(!timeStr.empty() && timeStr[timeStr.length()-1] == '\n') {
                timeStr = timeStr.substr(0, timeStr.length()-1);
            }
            accessLog[logCount] = "FAILED attempt at " + timeStr;
            logCount++;
        }
    }
}

bool SmartLock::verifyCode(string code) {
    return code == accessCode;
}

void SmartLock::getAccessHistory() const {
  
    cout << "  ACCESS HISTORY for " << getName() << endl;
   
    if(logCount == 0) {
        cout << "  No access records found" << endl;
    } else {
        for(int i = 0; i < logCount; i++) {
            cout << "  " << (i+1) << ". " << accessLog[i];
        }
    }
    
}


void SmartLock::startCycle() {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Turn ON first.." << endl;
        return;
    }
    
    cout << "\n═══════════════════════════════════════════════" << endl;
    cout << "  SMART LOCK SECURITY CYCLE STARTED" << endl;
    cout << "═══════════════════════════════════════════════" << endl;
    cout << "  Lock Status: " << (isLocked ? "LOCKED " : "UNLOCKED ") << endl;
    cout << "  Security Check: " << endl;
    
    if(isLocked) {
        cout << "     Door is secure" << endl;
        cout << "     No unauthorized access" << endl;
        cout << "     Security system active" << endl;
    } else {
        cout << "     Door is UNLOCKED" << endl;
        cout << "     Please lock the door immediately" << endl;
    }
    
    cout << "  Last " << logCount << " access records available" << endl;
    cout << "═══════════════════════════════════════════════" << endl;
}


string SmartLock::getStatus() {
    stringstream ss;
    ss << SmartAppliance::getStatus()
       << "  Locked: " << (isLocked ? "YES " : "NO ")
       << "  Logs: " << logCount;
    return ss.str();
}

void SmartLock::generateReport()  {
    SmartAppliance::generateReport();
    cout << "Device Type: SmartLock" << endl;
    cout << "Lock Status: " << (isLocked ? "LOCKED " : "UNLOCKED ") << endl;
    cout << "Access Code: " << accessCode << endl;
    cout << "Total Access Records: " << logCount << endl;
    
    // Security assessment
    cout << "\nSecurity Assessment: ";
    if(isLocked) {
        cout << "SECURE Door is locked" << endl;
    } else {
        cout << " INSECURE  Door is unlocked!" << endl;
    }
    
    getAccessHistory();
}