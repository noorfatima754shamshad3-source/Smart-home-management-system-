       // Base interface class No need .cpp file because ju class inherit kare gie wahi esa implement bi kare gie
#define BOLD    "\033[1m"
#include<conio.h>

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

         // Base class 
#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <iostream>  
using namespace std; 

class SmartDevice{
    private:
    int deviceID;
    string name;
    string location;
    bool isOn;
    string firmwareVersion;
    static int totalDeviceCount;

    public:
   

    SmartDevice();
    SmartDevice(int id, string n, string loc, string fw);
    SmartDevice(const SmartDevice &other);
    virtual ~SmartDevice();

    
    int getDeviceID() const;
    string getName() const;
    string getLocation() const;
    bool getIsOn() const;
    void setIsOn(bool status);

    
    void setname(string n);
    void setlocation(string n);

   


    virtual void toggle()=0;
    virtual string getStatus() =0;
    virtual void generateReport() =0;


     void restart();
    
   
    bool operator==(const SmartDevice &other);
    friend ostream& operator<<(ostream &out, const SmartDevice &other);
    
    
    static int getTotalDeviceCount();


 

};
#endif

#include "smartDevice.h"

int SmartDevice::totalDeviceCount = 0;


SmartDevice::SmartDevice() : deviceID(), name("Unknown"), 
                             location("Unknown"), isOn(false), 
                             firmwareVersion("1.0") {
    totalDeviceCount++;
}


SmartDevice::SmartDevice(int id, string n, string loc,string fw) : deviceID(id), name(n), location(loc), isOn(false), firmwareVersion(fw) {
    totalDeviceCount++;
}


SmartDevice::SmartDevice(const SmartDevice &other){
deviceID=other.deviceID;
 name=other.name;
 location=other.location;
isOn=other.isOn;
 firmwareVersion=other.firmwareVersion;
totalDeviceCount++;
}

SmartDevice::~SmartDevice() {
   totalDeviceCount--;
}


int SmartDevice::getDeviceID() const 
{
     return deviceID;
    }
string SmartDevice::getName() const {
     return name;
     }
string SmartDevice::getLocation() const { 
    return location;
 }
bool SmartDevice::getIsOn() const { 
    return isOn;
 }



void SmartDevice::setname(string n) {
     name = n; 
    }
void SmartDevice::setlocation(string loc) { 
    location = loc;
 }
void SmartDevice::setIsOn(bool status) { 
    isOn = status; 
    cout << name << " is now " << (isOn ? "ON" : "OFF") << endl;
}


void SmartDevice::toggle() {  // ya opposite ka lia
    setIsOn(!isOn);
}

string SmartDevice::getStatus() {   // + la elawa sab try kia possible ni es lia ya combine ka lia use kia
    return name + " is " + string(isOn ? "ON" : "OFF");
}

void SmartDevice::generateReport()  {
    cout <<endl<< "=== Device Report ===" << endl;
    cout << "Device ID: " << deviceID << endl;
    cout << "Name: " << name << endl;
    cout << "Location: " << location << endl;
    cout << "Status: " << isOn << endl;
    cout << "Firmware: " << firmwareVersion << endl;
}

void SmartDevice::restart() {
    cout << name << " is restarting..." << endl;
    isOn = true;
}


bool SmartDevice::operator==(const SmartDevice &other)  {
    return this->deviceID == other.deviceID;
}

ostream& operator<<(ostream &out, const SmartDevice &other) {
    out << "Device: " << other.name << " | ID: " << other.deviceID 
       << " | Location: " << other.location << " | " << other.isOn;
    return out;
}

int SmartDevice::getTotalDeviceCount() {
    return totalDeviceCount;
}

    // All derived classes

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

#include "SmartLight.h"


SmartLight::SmartLight(int id, string n, string loc)
    : SmartDevice(id, n, loc, "LightFW_2.0"), 
      brightness(100), 
      colorTemperature(4000), 
      hexColor("") {
    cout << "SmartLight Created: " << getName() << " (ID: " << getDeviceID() << ")" << endl;
}


SmartLight::~SmartLight() {
    cout << "SmartLight Destroyed: " << getName() << endl;
}

void SmartLight::setBrightness(int brightness) {
    this->brightness = brightness;
  
    if(this->brightness < 0) {
        this->brightness = 0;
    }
    if(this->brightness > 100) {
        this->brightness = 100;
    }
    
    cout << getName() << " brightness set to " << this->brightness << "%" << endl;
}


void SmartLight::setColor(string hexColor) {
    this->hexColor = hexColor;
    cout << getName() << " color set to " << hexColor << endl;
}


void SmartLight::dimToSunset() {
    cout << getName() << " dimming to sunset mode..." << endl;
    
    
    for(int i = brightness; i > 30; i -= 10) {
        setBrightness(i);
    }
    setBrightness(30);
    cout << getName() << " now at 30% brightness (Sunset mode)" << endl;
}


void SmartLight::toggle() {
    setIsOn(!getIsOn());
    
    if(getIsOn()) {
        cout << getName() << " Light turned ON with " << brightness << "% brightness" << endl;
    } else {
        cout << getName() << " Light turned OFF" << endl;
    }
}

string SmartLight::getStatus() {
   
    string baseStatus = SmartDevice::getStatus();
    
   
    string brightnessText = "   Brightness: " + to_string(brightness) + "%";
    
    string colorText = "   Color: " + hexColor;
    
   
    string finalStatus = baseStatus + brightnessText + colorText;
    
    return finalStatus;
}


void SmartLight::generateReport() {
    SmartDevice::generateReport();
    cout << "Device Type: SmartLight" << endl;
    cout << "Brightness: " << brightness << "%" << endl;
    cout << "Color Temperature: " << colorTemperature << "K" << endl;
    cout << "Hex Color: " << hexColor << endl;
    
   
    if(getIsOn()) {
        cout << "Status: Light is ON " << endl;
    } else {
        cout << "Status: Light is OFF " << endl;
    }
}

// Schedule the light (from ScheduleAble interface)
void SmartLight::schedule() {
    cout << getName() << " Light scheduled:" << endl;
    cout << "  - Turn ON at 5:00 AM (05:00) with 100% brightness (Morning wake-up mode)" << endl;
    cout << "  - Turn OFF at 8:00 AM (08:00)" << endl;
    cout << "  - Turn ON at 6:00 PM (18:00) with 80% brightness (Evening mode)" << endl;
    cout << "  - Sunset mode at 6:00 PM (18:00) - Gradually dimming to 30%" << endl;
    cout << "  - Turn OFF at 10:00 PM (22:00) (Night mode)" << endl;
}


void SmartLight::cancelSchedule() {
    cout << getName() << " Light schedule cancelled" << endl;
    cout << "  All scheduled events removed" << endl;
}



#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <iostream>  
using namespace std; 
#include <string>
#include <sstream>

#include "SmartDevice.h"
#include "ScheduleAble.h"


class Thermostat : public SmartDevice, public ScheduleAble {
private:
    float targetTemperature;
    float currentTemperature;
    string mode;  

public:
  
    Thermostat(int id, string name, string location);
    
   
    ~Thermostat();
    
    
    void setTemperature(float temp);
    void changeMode(string m);
    
   
    void toggle() override;
    string getStatus()  override;
    void generateReport()  override;
    

    void schedule() override;
    void cancelSchedule() override;

 

};
#endif

#include "Thermostat.h"

// Constructor with initializer list
Thermostat::Thermostat(int id, string name, string location)
    : SmartDevice(id, name, location, "ThermoFW_1.5"),   // firmware aik embeded software hota ha ju hardwarwe ma permanent store hota ha   
      targetTemperature(22.0), 
      currentTemperature(20.0), 
      mode("auto") {
    cout << "Thermostat Created: " << getName() << endl;
}

Thermostat::~Thermostat() {
    cout << "Thermostat Destroyed: " << getName() << endl;
}


void Thermostat::setTemperature(float temp) {
    targetTemperature = temp;
    cout << getName() << " target temperature set to " << targetTemperature << "°C" << endl;
    
    
    if(mode == "auto") {
        if(currentTemperature < targetTemperature) {
            cout << "  Auto mode ON Heating ki tarf " << targetTemperature << "°C" << endl;
        } else if(currentTemperature > targetTemperature) {
            cout << "  Auto mode ON Cooling ki tarf  " << targetTemperature << "°C" << endl;
        }
    }
}


void Thermostat::changeMode(string m) {
    if(m == "heat" || m == "cool" || m == "auto") {
        mode = m;
        cout << getName() << " mode changed to " << mode << endl;
    } else {
        cout << "Invalid mode Use sirf heat or cool or auto" << endl;
    }
}


void Thermostat::toggle() {
    setIsOn(!getIsOn());
    if(getIsOn()) {
        cout << getName() << " Thermostat turned ON" << endl;
        cout << "  Current Temperature: " << currentTemperature << "°C" << endl;
        cout << "  Target Temperature: " << targetTemperature << "°C" << endl;
        cout << "  Mode: " << mode << endl;
    } else {
        cout << getName() << " Thermostat turned OFF" << endl;
    }
}


string Thermostat::getStatus() {
    stringstream ss;
    ss << SmartDevice::getStatus()
       << "  Current: " << currentTemperature << "°C"
       << "  Target: " << targetTemperature << "°C"
       << "  Mode: " << mode;
    return ss.str();
}


void Thermostat::generateReport()  {
    SmartDevice::generateReport();
    cout << "Device Type: Thermostat" << endl;
    cout << "Target Temperature: " << targetTemperature << "°C" << endl;
    cout << "Current Temperature: " << currentTemperature << "°C" << endl;
    cout << "Mode: " << mode << endl;
    
   
    if(mode == "heat") {
        cout << "Status: Heating mode active" << endl;
    } else if(mode == "cool") {
        cout << "Status: Cooling mode active" << endl;
    } else {
        cout << "Status: Automatic temperature control" << endl;
    }
}


void Thermostat::schedule() {
    cout << getName() << " Thermostat scheduled:" << endl;
    cout << "  - Set temperature to 20°C at 10:00 PM (sleep mode)" << endl;
    cout << "  - Set temperature to 22°C at 7:00 AM (wake up mode)" << endl;
    cout << "  - Set temperature to 18°C at 9:00 AM (away mode)" << endl;  // jab koi ghar ni hota mean ofice time
    cout << "  - Set temperature to 23°C at 5:00 PM (home mode)" << endl;
}


void Thermostat::cancelSchedule() {
    cout << getName() << " Thermostat schedule cancelled" << endl;
}

#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "SmartDevice.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class SecurityCamera : public SmartDevice {
private:
    string resolution;     
    bool isRecording;
    int motionSensitivity;   
    float angle;             

public:
  
    SecurityCamera(int id, string name, string location);
    
   
    ~SecurityCamera();
    

    void startRecording();
    void captureSnapshot();
    void setMotionAlert(int sensitivity);
    
  
    void toggle() override;
    string getStatus()  override;
    void generateReport()  override;
};

#endif


#include "SecurityCamera.h"


SecurityCamera::SecurityCamera(int id, string name, string location)
    : SmartDevice(id, name, location, "CamFW_3.0"), 
      resolution("1080p"), 
      isRecording(false), 
      motionSensitivity(5), 
      angle(0.0) {
    cout << "SecurityCamera Created: " << getName() << endl;
}


SecurityCamera::~SecurityCamera() {
    cout << "SecurityCamera Destroyed: " << getName() << endl;
}

void SecurityCamera::startRecording() {
    if(!getIsOn()) {  // ya function sirf device on ya off ka btata ha jaisa ka ab camera ka bta raha ha

        cout << getName() << " is OFF. Cannot start recording. Turn ON first " << endl;
        return;   // yahi sa function return agr camera ON hre nhi
    }
    
    if(!isRecording) {
        isRecording = true;
        cout << getName() << " started recording at " << resolution << " resolution" << endl;
    } else {
        cout << getName() << " is already recording..." << endl;
    }
}

void SecurityCamera::captureSnapshot() {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Cannot capture snapshot. Turn ON first..." << endl;
        return;
    }

    // jab true ho ga I mean camea ON
    
    cout << getName() << " captured snapshot at " << resolution << " resolution" << endl;
    cout << "  Camera angle: " << angle << "°" << endl;
    cout << "  Snapshot saved to memory  " << endl;
}


void SecurityCamera::setMotionAlert(int sensitivity) {
    if(sensitivity < 1) {
        motionSensitivity = 1;
    } else if(sensitivity > 10) {
        motionSensitivity = 10;
    } else {
        motionSensitivity = sensitivity;
    }
    
    cout << getName() << " motion sensitivity set to " << motionSensitivity << "/10" << endl;
    
            // Alert based on sensitivity level
    if(motionSensitivity >= 8) {
        cout << "   High sensitivity mode: All movements will be detected" << endl;
    } else if(motionSensitivity <= 3) {
        cout << "   Low sensitivity mode: Only major movements detected" << endl;
    } else {
        cout << "   Normal sensitivity mode" << endl;
    }
}


void SecurityCamera::toggle() {
    setIsOn(!getIsOn());    // sab sa pahla ju function ka kam ha vo kara

    
    if(getIsOn()) {
        cout << getName() << " Security Camera activated " << endl;
        cout << "  Resolution: " << resolution << endl;
        cout << "  Motion Sensitivity: " << motionSensitivity << "/10" << endl;
        cout << "  Camera Angle: " << angle << "°" << endl;
        
        // Auto start recording when turned on
        startRecording();
    } else {
        cout << getName() << " Security Camera deactivated" << endl;
        
        if(isRecording) {
            isRecording = false;
            cout << "  Recording stopped due to power off " << endl;
        }
    }
}


string SecurityCamera::getStatus() {
    stringstream ss;
    ss << SmartDevice::getStatus()
       << "  Resolution: " << resolution
       << "  Recording: " << (isRecording ? "YES" : "NO")
       << "  Sensitivity: " << motionSensitivity << "/10"
       << "  Angle: " << angle << "°";
    return ss.str();
}

void SecurityCamera::generateReport() {
    SmartDevice::generateReport();
    cout << "Device Type: Security Camera" << endl;
    cout << "Resolution: " << resolution << endl;
    cout << "Recording Status: " << (isRecording ? "Recording in progress" : "Not recording") << endl;
    cout << "Motion Sensitivity: " << motionSensitivity << "/10" << endl;
    cout << "Camera Angle: " << angle << "°" << endl;
    
    // Additional security info
    cout << "Security Status: ";
    if(!getIsOn()) {
        cout << "OFFLINE  Camera is turned off" << endl;
    } else if(isRecording) {
        cout << "ACTIVE  Monitoring in progress" << endl;
        if(motionSensitivity >= 7) {
            cout << "   High alert mode: All motion will trigger notification" << endl;
        }
    } else {
        cout << "STANDBY  Camera is on but not recording" << endl;   
        // STANDBY ek low power state hai jahan device ON hai lekin active operation nahi kar rahi. Device ready hoti hai lekin kaam nahi kar rahi.
    }
}

#ifndef SMARTAPPLIANCE_H
#define SMARTAPPLIANCE_H

#include "SmartDevice.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class SmartAppliance : public SmartDevice {
private:
    float powerRating;  // in watts
    string runMode;    

public:
  
    SmartAppliance(int id, string name, string location, float powerRating);
    
   
    virtual ~SmartAppliance();
    
    // Pure virtual function makes this class abstract
    virtual void startCycle() = 0;

    float getPowerUsage() const;
    

    void toggle() override;
    string getStatus()  override;
    void generateReport() override;
};

#endif



#include "SmartAppliance.h"


SmartAppliance::SmartAppliance(int id, string name, string location, float powerRating)
    : SmartDevice(id, name, location, "ApplianceFW_1.0"), 
      powerRating(powerRating), 
      runMode("idle") {
    cout << "SmartAppliance Created: " << getName() 
         << " (Power Rating: " << powerRating << "W)" << endl;
}

SmartAppliance::~SmartAppliance() {
    cout << "SmartAppliance Destroyed: " << getName() << endl;
}

float SmartAppliance::getPowerUsage() const {
    return powerRating;
}

void SmartAppliance::toggle() {
    setIsOn(!getIsOn());
    
    if(getIsOn()) {
        cout << getName() << " Appliance turned ON" << endl;
        cout << "  Power Rating: " << powerRating << "W" << endl;
        cout << "  Run Mode: " << runMode << endl;
    } else {
        cout << getName() << " Appliance turned OFF" << endl;
        runMode = "idle";
        cout << "  Run Mode reset to: idle" << endl;   //idle ka matlb kam ka lia ready ho par kar ni raha

    }
}


string SmartAppliance::getStatus()  {
    stringstream ss;
    ss << SmartDevice::getStatus()
       << "  Power: " << powerRating << "W"
       << "  Mode: " << runMode;
    return ss.str();
}

void SmartAppliance::generateReport()  {
    SmartDevice::generateReport();
    cout << "Device Type: SmartAppliance (Abstract Base)" << endl;
    cout << "Power Rating: " << powerRating << " Watts" << endl;
    cout << "Run Mode: " << runMode << endl;
    
   
    if(getIsOn()) {
        float hourlyConsumption = powerRating / 1000.0;  // kWh per hour
        cout << "Estimated Consumption: " << hourlyConsumption << " kWh per hour" << endl;
    } else {
        cout << "Estimated Consumption: 0 kWh (Appliance is OFF)" << endl;
    }
}

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
    cout << "\n\n═══════════════════════════════════════════════" << endl;
    cout << "  ACCESS HISTORY for " << getName() << endl;
    cout << "═══════════════════════════════════════════════" << endl;
    
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


#ifndef SMARTSPEAKER_H
#define SMARTSPEAKER_H

#include "SmartAppliance.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class SmartSpeaker : public SmartAppliance {
private:
    int volume;
    string activeSkill;
    string connectedServices[10];    
    int serviceCount;

public:
    SmartSpeaker(int id, string name, string location);
    ~SmartSpeaker();
    
    void playMusic(string song);
    void setVolume(int v);
    void triggerSkill(string command);
    void addService(string service);
    void showServices() const;
    
    void startCycle() override;
    string getStatus()  override;
    void generateReport() override;
};

#endif

#include "SmartSpeaker.h"

// Constructor
SmartSpeaker::SmartSpeaker(int id, string name, string location)
    : SmartAppliance(id, name, location, 15.0), volume(50), activeSkill("none"), serviceCount(0) {
    
    for(int i = 0; i < 10; i++) {             // like "spotify"  rtc
        connectedServices[i] = "";
    }
    
    addService("Spotify");
    addService("Amazon Music");
    
    cout << "SmartSpeaker Created: " << getName() << endl;
}

SmartSpeaker::~SmartSpeaker() {
    cout << "SmartSpeaker Destroyed: " << getName() << endl;
}


void SmartSpeaker::playMusic(string song) {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Turn ON first.." << endl;
        return;
    }
    
    activeSkill = "music";
    cout << "\n Playing: " << song << endl;
    cout << "   Volume: " << volume << "%" << endl;
}

void SmartSpeaker::setVolume(int v) {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Turn ON first..." << endl;
        return;
    }
    
    if(v < 0) 
    volume = 0;
    else if(v > 100) 
    volume = 100;
    else 
    volume = v;
    
    cout << "Volume: " << volume << "%" << endl;
    
    
}

     // Simple function to check if a word exists in command ->  word (Play)
bool containsWord(string command, string word) {
        // Convert both to lowercase for comparison
    for(int i = 0; i < command.length(); i++) {
        if(command[i] >= 'A' && command[i] <= 'Z') {
            command[i] = command[i] + 32;
        }
    }
    for(int i = 0; i < word.length(); i++) {
        if(word[i] >= 'A' && word[i] <= 'Z') {
            word[i] = word[i] + 32;
        }
    }
    
    // Check if word exists in command 
    for(int i = 0; i <= command.length() - word.length(); i++) {
        bool found = true;
        for(int j = 0; j < word.length(); j++) {
            if(command[i + j] != word[j]) {        
                found = false;
                break;
            }
        }
        if(found) {
            return true;      // word mil gaya

        }
    }
    return false;      // word nhi mila 
}

         // ya function to get word after "play"
string getSongName(string command) {
    string song = "";
    bool afterPlay = false;
    
           // Convert to lowercase
    for(int i = 0; i < command.length(); i++) {
        if(command[i] >= 'A' && command[i] <= 'Z') {
            command[i] = command[i] + 32;
        }
    }
    
            // Find "play" and get after it
    for(int i = 0; i <= command.length() - 4; i++) {
        if(command[i] == 'p' && command[i+1] == 'l' && command[i+2] == 'a' && command[i+3] == 'y') {
            afterPlay = true;
            i = i + 4; // Skip "play"
            // Skip spaces
            while(i < command.length() && command[i] == ' ') {
                i++;
            }
            // Get the song name
            while(i < command.length()) {  // after play..
                song = song + command[i];      
                i++;
            }
            break;
        }
    }
    
    if(song == "") {
        song = "some music";
    }
    
    return song;
}

// Voice command simulation like play music
void SmartSpeaker::triggerSkill(string command) {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Turn ON first.." << endl;
        return;
    }
    
    cout << "\n========================================" << endl;
    cout << "  VOICE COMMAND: \"" << command << "\"" << endl;
    cout << "========================================" << endl;
    
           // Check for PLAY command
    if(containsWord(command, "play")) {
        string song = getSongName(command);
        playMusic(song);
    }
    
     // Check for VOLUME UP
    else if(containsWord(command, "volume") && containsWord(command, "up")) {
        setVolume(volume + 10);
    }
    
         // Check for VOLUME DOWN
    else if(containsWord(command, "volume") && containsWord(command, "down")) {
        setVolume(volume - 10);
    }
    
           // Check for MUTE
    else if(containsWord(command, "mute")) {
        setVolume(0);
    }
    
            // Check for WEATHER
    else if(containsWord(command, "weather")) {
        activeSkill = "weather";
        cout << "\nChecking weather..." << endl;
        cout << "   Today: Sunny " << endl;
    }
    
  // Check for TIME
    else if(containsWord(command, "time")) {
        activeSkill = "time";
        cout << "\n Current time: " << endl;
        time_t now = time(0);
        cout << "   " << ctime(&now);
    }
    
    // Check for STOP
    else if(containsWord(command, "stop")) {
        activeSkill = "none";
        cout << "\n Playback stopped" << endl;
    }
    
             // Check for HELLO
    else if(containsWord(command, "hello") || containsWord(command, "hi")) {
        activeSkill = "assistant";
        cout << "\n Hello! Ma ap ki kia help karo..." << endl;
    }
    // Unknown command
    else {
        cout << "\n Command not recognized...." << endl;
        cout << "   Only Valid Commands are -> play, volume up, volume down, mute, weather, time, stop, hello" << endl;
    }
    
    
}

     
void SmartSpeaker::addService(string service) {
    if(serviceCount < 10) {
        connectedServices[serviceCount] = service;
        serviceCount++;
    }
}


void SmartSpeaker::showServices() const {
    for(int i = 0; i < serviceCount; i++) {
        cout << connectedServices[i];
        if(i < serviceCount - 1) cout << ", ";
    }
    cout << endl;
}


void SmartSpeaker::startCycle() {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Turn ON first ..." << endl;
        return;
    }
    
    cout << "\n=== SMART SPEAKER STARTUP ===" << endl;
    cout << "Initializing..." << endl;
    cout << "Volume: " << volume << "%" << endl;
    cout << "Connected services: ";
    showServices();
    cout << "Ready for voice commands!" << endl;
}


string SmartSpeaker::getStatus() {
    stringstream ss;
    ss << SmartAppliance::getStatus()
       << "  Volume: " << volume << "%"
       << "  Mode: " << activeSkill;
    return ss.str();
}


void SmartSpeaker::generateReport() {
    SmartAppliance::generateReport();
    cout << "Device Type: SmartSpeaker" << endl;
    cout << "Volume: " << volume << "%" << endl;
    cout << "Active Skill: " << activeSkill << endl;
    cout << "Services: ";
    showServices();
}




     // Main classes


#ifndef ROOM_H
#define ROOM_H

#include "SmartDevice.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Room {
private:
    int roomID;
    string roomName;
    int floor;
    SmartDevice** devices;  // Dynamic array of SmartDevice pointers  har device store kara ga
    int deviceCount;
    int maxDevices;
    
public:

    Room(int id, string name, int floor);
    
  
    ~Room();
    
  
    void addDevice(SmartDevice* d);
    void removeDevice(int deviceID);
    void turnAllOff();
    void getRoomStatus() const;
    
  
    int getRoomID() const;
    string getRoomName() const;
    int getFloor() const;
    int getDeviceCount() const;
    
  
    SmartDevice* getDevice(int index) const;
    
  
    friend ostream& operator<<(ostream& out, const Room& other);
};

#endif


#include "Room.h"


Room::Room(int id, string name, int floor) 
    : roomID(id), roomName(name), floor(floor), deviceCount(0), maxDevices(20) {
    
              // Allocate array for device pointers  ya har index pa each device ka pointer store ho ga okay

    devices = new SmartDevice*[maxDevices];
    
    
    for(int i = 0; i < maxDevices; i++) {
        devices[i] = nullptr;
    }
    
    cout << "Room Created: " << roomName << " (ID: " << roomID 
         << ", Floor: " << floor << ")" << endl;
}


Room::~Room() {
    cout << "Room Destroyed: " << roomName << endl;
    
    // Devices are AGGREGATED (not owned) so we DON'T delete them here
    // We only delete the array that holds pointers, not the devices themselves
    // ya aggregation ha not composition
    delete[] devices;
}


void Room::addDevice(SmartDevice* d) {
    if(deviceCount < maxDevices) {
        devices[deviceCount] = d;
        deviceCount++;
        cout << " " << d->getName() << " added to " << roomName << endl;
    } else {
        cout << " Room is full! Cannot add more devices to " << roomName << endl;
    }
}


void Room::removeDevice(int deviceID) {
    for(int i = 0; i < deviceCount; i++) {
       
        if(devices[i]->getDeviceID() == deviceID) {
            cout << " " << devices[i]->getName() << " removed from " << roomName << endl;
            
               // Shift remaining devices left
            for(int j = i; j < deviceCount - 1; j++) {
                devices[j] = devices[j + 1];
            }
            devices[deviceCount - 1] = nullptr;
            deviceCount--;
            return; // out of loop
        }
    }
    cout << "Device with ID " << deviceID << " not found in " << roomName << endl;
}


void Room::turnAllOff() {
    cout << "\n Turning OFF all devices in " << roomName << "..." << endl;
    
    for(int i = 0; i < deviceCount; i++) {
        if(devices[i] != nullptr && devices[i]->getIsOn()) {  
            devices[i]->toggle();  // Turn off
        }
    }
    
    cout << " All devices in " << roomName << " are now OFF" << endl;
}


void Room::getRoomStatus() const {
    cout << "\n========================================" << endl;
    cout << "  ROOM: " << roomName << " (Floor " << floor << ")" << endl;
    cout << "  Room ID: " << roomID << endl;
    cout << "========================================" << endl;
    
    if(deviceCount == 0) {
        cout << "   No devices in this room" << endl;
    } else {
        cout << "   Devices in this room (" << deviceCount << "):" << endl;
        cout << "  ----------------------------------------" << endl;
        
        for(int i = 0; i < deviceCount; i++) {
            cout << "  " << (i+1) << ". " << devices[i]->getStatus() << endl;
        }
        
        cout << "  ----------------------------------------" << endl;
        
        // Count how many devices are ON
        int onCount = 0;
        for(int i = 0; i < deviceCount; i++) {
            if(devices[i]->getIsOn()) { // ya function ju check krta ha devices ON check
                onCount++;
            }
        }
        
        cout << "  Conclusion: " << onCount << "/" << deviceCount << " devices are ON" << endl;
    }
    cout << "========================================\n" << endl;
}


int Room::getRoomID() const {
    return roomID;
}

string Room::getRoomName() const {
    return roomName;
}

int Room::getFloor() const {
    return floor;
}

int Room::getDeviceCount() const {
    return deviceCount;
}
 

SmartDevice* Room::getDevice(int index) const {
    if(index >= 0 && index < deviceCount) {
        return devices[index];
    }
    return nullptr;
}
ostream& operator<<(ostream& out, const Room& other) {
    out << "Room: " << other.roomName << " | ID: " << other.roomID 
       << " | Floor: " << other.floor << " | Devices: " << other.deviceCount;
    return out;
}

#ifndef AUTOMATION_H
#define AUTOMATION_H

#include "SmartDevice.h"
#include <iostream>
#include <typeinfo>
#include <string>
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

#ifndef ENERGYLOG_H
#define ENERGYLOG_H

#include "SmartDevice.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream> 
using namespace std;

class EnergyLog {
private:
    int logID;
    SmartDevice* deviceReference; 
    float kilowattHours;
    string timestamp;
    static EnergyLog** allLogs; // Static array for all logs   es ak matlb record store kara pointer array
    static int logCount;
    static int maxLogs;
    
    // File handling helpers
    static string getCurrentDate();
    static string getCurrentMonth();

public:
  
    EnergyLog(SmartDevice* device, float kwh);

    ~EnergyLog();
    
   
    void recordUsage(float kwh);  // aik aik device ka usage
    
   
    static void getMonthlyReport(SmartDevice* device); // kisi aik device ki report
    
    
    static void compareToAverage(float avg);// kisi aik  device ki report
    
    // Static methods es lia ka object ak bina kam krna + total devices consumption etc

    static void showAllLogs();
    static void showTotalConsumption();
    static float getDeviceTotal(SmartDevice* device);
    
    // File handling methods
    static void saveToFile();      
    static void loadFromFile();    // Load logs from file
    static void generateBill();    
    
  
    int getLogID() const;
    float getKilowattHours() const;
    string getTimestamp() const;
    
  
    friend ostream& operator<<(ostream& os, const EnergyLog& log);
};

#endif

#include "EnergyLog.h"
#include <iomanip>

EnergyLog** EnergyLog::allLogs = nullptr;  
int EnergyLog::logCount = 0;
int EnergyLog::maxLogs = 100;


string EnergyLog::getCurrentDate() {
    time_t now = time(0);
    string fullTime = ctime(&now);  // now ka kam ha readable bnana
    
    // ctime() returns Sun May 24 15:30:00 2026\n
    // Remove newline from end
    if(!fullTime.empty() && fullTime[fullTime.length() - 1] == '\n') {
        fullTime = fullTime.substr(0, fullTime.length() - 1);  // substring ka use mean indexing sa aik last wali remove ho sakti ha
    }
    
    return fullTime;
}
// Exactly same jaisa as your getCurrentDate
string EnergyLog::getCurrentMonth() {
    time_t now = time(0);
    string fullTime = ctime(&now);
    
   
    if(!fullTime.empty() && fullTime[fullTime.length() - 1] == '\n') {
        fullTime = fullTime.substr(0, fullTime.length() - 1);
    }
    
    
    
    string month = "";
    string year = "";
    
    if(fullTime.length() > 7) {
        month = fullTime.substr(4, 3);
        year = fullTime.substr(24, 4);      
    }
    
    return month + " " + year;
}




EnergyLog::EnergyLog(SmartDevice* device, float kwh) {
    // Pehle check karo ke allLogs already exist to nahi karta
    if(allLogs == nullptr) {
        allLogs = new EnergyLog*[maxLogs];
        for(int i = 0; i < maxLogs; i++) {
            allLogs[i] = nullptr;
        }
        loadFromFile();
    }
    
    logID = logCount + 1;
    deviceReference = device;
    kilowattHours = kwh;
    timestamp = getCurrentDate();
    
    if(logCount < maxLogs) {
        allLogs[logCount] = this;
        logCount++;
    }
    
    cout << " EnergyLog Created: " << device->getName() 
         << " consumed " << kwh << " kWh at " << timestamp << endl;
    
    saveToFile();
}


EnergyLog::~EnergyLog() {
    cout << "EnergyLog Destroyed: Log ID " << logID << endl;
}


void EnergyLog::recordUsage(float kwh) {
    kilowattHours += kwh;
    timestamp = getCurrentDate();  // ab jab change kia vo date ay giee

    
    cout << " Updated: " << deviceReference->getName() 
         << " total now " << kilowattHours << " kWh" << endl;
    
   
    saveToFile();
}


void EnergyLog::saveToFile() {
    ofstream file("energylog.txt");
    
    if(!file.is_open()) {
        cout <<" eRROR " << endl;
        return;
    }
    
    
    file << "========================================\n";
    file << "     ENERGY LOG DATABASE\n";
    file << "========================================\n";
    file << "Generated: " << getCurrentDate() << "\n";
    file << "Total Logs: " << logCount << "\n";
    file << "========================================\n\n";
    
    // Write each log THAT occurr
    for(int i = 0; i < logCount; i++) {
        if(allLogs[i] != nullptr) {
            file << "LOG ID: " << allLogs[i]->logID << "\n";
            file << "Device Name: " << allLogs[i]->deviceReference->getName() << "\n";
            file << "Device ID: " << allLogs[i]->deviceReference->getDeviceID() << "\n";
            file << "Consumption: " << allLogs[i]->kilowattHours << " kWh\n";
            file << "Timestamp: " << allLogs[i]->timestamp << "\n";
            file << "----------------------------------------\n";
        }
    }
    
    
    float total = 0;
    for(int i = 0; i < logCount; i++) {
        if(allLogs[i] != nullptr) {
            total += allLogs[i]->kilowattHours;  // total bijli kitni use hooi
        }
    }
    
    file << "\n========================================\n";
    file << "TOTAL CONSUMPTION: " << total << " kWh\n";
    file << "========================================\n";
    
    file.close();
    cout << "Data saved to energylog.txt" << endl;
}


void EnergyLog::loadFromFile() {
    ifstream file("energylog.txt");
    
    if(!file.is_open()) {
        cout<<"file no exist"<<endl;
        return;
    }
    
   
    // we just note that file exists
    cout << " Here existing energylog.txt file" << endl;
    file.close();
}

// Get monthly report  file sa read kra ga
void EnergyLog::getMonthlyReport(SmartDevice* device) {
    float total = 0.0;
    int recordCount = 0;
    string currentMonth = getCurrentMonth();
    
    cout << "\n========================================" << endl;
    cout << "   MONTHLY ENERGY REPORT" << endl;
    cout << "========================================" << endl;
    cout << "Month: " << currentMonth << endl;
    cout << "Device: " << device->getName() << endl;
    cout << "Device ID: " << device->getDeviceID() << endl;
    cout << "----------------------------------------" << endl;
    
    for(int i = 0; i < logCount; i++) {
        if(allLogs[i] != nullptr && allLogs[i]->deviceReference == device) {  // yaha pa device check ho giee
            total += allLogs[i]->kilowattHours;
            recordCount++;
            cout << "  " << recordCount << ". Usage: " << allLogs[i]->kilowattHours 
                 << " kWh on " << allLogs[i]->timestamp << endl;
        }
    }
    
    cout << "----------------------------------------" << endl;
    cout << " Total Records: " << recordCount << endl;
    cout << " Total Consumption: " << total << " kWh" << endl;
    
    if(recordCount > 0) {
        float average = total / recordCount;
        cout << "Average per Record: " << average << " kWh" << endl;
    }
    
    // Calculate estimated cost
    float cost = total * 15;  //  15 rupees per kWh
    cout << " Estimated Cost: Rs. " << fixed << setprecision(2) << cost << endl;
    cout << "========================================\n" << endl;
    
    
    ofstream reportFile("monthly_report.txt", ios::app);
    if(reportFile.is_open()) {
        reportFile << "Month: " << currentMonth << " | Device: " << device->getName()
                   << " | Consumption: " << total << " kWh | Cost: Rs. " << cost << endl;
        reportFile.close();
    }
}


void EnergyLog::compareToAverage(float avg) {
    float total = 0.0;
    for(int i = 0; i < logCount; i++) {
        if(allLogs[i] != nullptr) {
            total += allLogs[i]->kilowattHours;  // yaha sa total aa gaya
        }
    }
    
    float overallAverage = (logCount > 0) ? total / logCount : 0;   // yaha sa entries ka mutabiq average ay giee
    
    cout << "\n========================================" << endl;
    cout << "   ENERGY COMPARISON REPORT" << endl;
    cout << "========================================" << endl;
    cout << "Your Average Consumption: " << fixed << setprecision(3) << overallAverage << " kWh" << endl;
    cout << "Reference Average: " << avg << " kWh" << endl;
    cout << "----------------------------------------" << endl;
    
    if(overallAverage > avg) {
        float difference = overallAverage - avg;
        cout << " WARNING: You are using " << difference 
             << " kWh MORE than average!" << endl;
        cout << " Energy Saving Tips:" << endl;
        cout << "   • Turn off lights when leaving room" << endl;
        cout << "   • Use LED bulbs instead of traditional" << endl;
        cout << "   • Unplug devices when not in use" << endl;
    } else if(overallAverage < avg) {
        float difference = avg - overallAverage;
        cout << " EXCELLENT: You are using " << difference 
             << " kWh LESS than average!" << endl;
        cout << " Keep up the good energy saving habits!" << endl;
    } else {
        cout << " You are exactly at the average consumption." << endl;
    }
    cout << "========================================\n" << endl;
    
    
    ofstream compareFile("energy_comparison.txt");
    if(compareFile.is_open()) {
        compareFile << "=== ENERGY COMPARISON ===" << endl;
        compareFile << "Date: " << getCurrentDate() << endl;
        compareFile << "Your Average: " << overallAverage << " kWh" << endl;
        compareFile << "Reference Average: " << avg << " kWh" << endl;
        if(overallAverage > avg) {
            compareFile << "Status: ABOVE AVERAGE - Need improvement" << endl;
        } else if(overallAverage < avg) {
            compareFile << "Status: BELOW AVERAGE - Excellent!" << endl;
        } else {
            compareFile << "Status: AVERAGE" << endl;
        }
        compareFile.close();
        cout << " Comparison saved to energy_comparison.txt" << endl;
    }
}

void EnergyLog::showAllLogs() {
    cout << "\n========================================" << endl;
    cout << "   ALL ENERGY LOGS" << endl;
    cout << "========================================" << endl;
    
    if(logCount == 0) {
        cout << "  No energy logs found." << endl;
    } else {
        float total = 0;
        for(int i = 0; i < logCount; i++) {
            if(allLogs[i] != nullptr) {
                cout << (i+1) << ". " << *(allLogs[i]) << endl;
                total += allLogs[i]->kilowattHours;
            }
        }
        cout << "----------------------------------------" << endl;
        cout << "  GRAND TOTAL: " << total << " kWh" << endl;
    }
    cout << "========================================\n" << endl;
}


void EnergyLog::showTotalConsumption() {
    float total = 0.0;
    for(int i = 0; i < logCount; i++) {
        if(allLogs[i] != nullptr) {
            total += allLogs[i]->kilowattHours;
        }
    }
    
    cout << "\n========================================" << endl;
    cout << "   TOTAL ENERGY CONSUMPTION" << endl;
    cout << "========================================" << endl;
    cout << "Total Logs: " << logCount << endl;
    cout << "Total Energy: " << fixed << setprecision(2) << total << " kWh" << endl;
    

    float estimatedCost = total * 15;
    cout << " Estimated Cost: Rs. " << fixed << setprecision(2) << estimatedCost << endl;
    cout << "========================================\n" << endl;
}


void EnergyLog::generateBill() {
    float total = 0.0;
    for(int i = 0; i < logCount; i++) {
        if(allLogs[i] != nullptr) {
            total += allLogs[i]->kilowattHours;
        }
    }
    
    float cost = total * 15; 
    
    cout << "\n========================================" << endl;
    cout << "    ELECTRICITY BILL" << endl;
    cout << "========================================" << endl;
    cout << "Bill Date: " << getCurrentDate() << endl;
    cout << "Bill Month: " << getCurrentMonth() << endl;
    cout << "----------------------------------------" << endl;
    cout << "Total Units Consumed: " << fixed << setprecision(2) << total << " kWh" << endl;
    cout << "Rate per Unit: Rs. 15.00" << endl;
    cout << "----------------------------------------" << endl;
    cout << "TOTAL AMOUNT: Rs. " << fixed << setprecision(2) << cost << endl;
    cout << "========================================\n" << endl;
    
   
    ofstream billFile("electricity_bill.txt");
    if(billFile.is_open()) {
        billFile << "=== ELECTRICITY BILL ===" << endl;
        billFile << "Date: " << getCurrentDate() << endl;
        billFile << "Month: " << getCurrentMonth() << endl;
        billFile << "Total Consumption: " << total << " kWh" << endl;
        billFile << "Rate: Rs. 15 per kWh" << endl;
        billFile << "Total Amount: Rs. " << cost << endl;
        billFile.close();
        cout << " Bill saved to electricity_bill.txt" << endl;
    }
}

          // Get total for a specific device
float EnergyLog::getDeviceTotal(SmartDevice* device) {
    float total = 0.0;
    for(int i = 0; i < logCount; i++) {
        if(allLogs[i] != nullptr && allLogs[i]->deviceReference == device) {
            total += allLogs[i]->kilowattHours;
        }
    }
    return total;
}


int EnergyLog::getLogID() const {
    return logID;
}

float EnergyLog::getKilowattHours() const {
    return kilowattHours;
}

string EnergyLog::getTimestamp() const {
    return timestamp;
}

ostream& operator<<(ostream& os, const EnergyLog& log) {
    os << "Log ID: " << log.logID 
       << " | Device: " << log.deviceReference->getName()
       << " | Usage: " << log.kilowattHours << " kWh"
       << " | Time: " << log.timestamp;
    return os;
}

  // Main system classes

#ifndef SMARTHOME_H
#define SMARTHOME_H

#include "Room.h"
#include "Automation.h"
#include "EnergyLog.h"
#include <iostream>
#include <string>
using namespace std;

class SmartHome {
private:
    int homeID;
    string ownerName;
    string wifiNetwork;
    Room** rooms;           // Array of Room pointers
    int roomCount;
    int maxRooms;
    Automation** automations;  // Array of Automation pointers
    int autoCount;
    int maxAutomations;
    
   
    bool isValidHomeID(int id);
    bool isValidOwnerName(string name);
    bool isValidWifiNetwork(string wifi);
    bool isRoomExists(int roomID);
    bool isAutomationExists(int ruleID);
    int findRoomIndex(int roomID);
    int findAutomationIndex(int ruleID);

public:
    
    SmartHome(int id, string owner, string wifi);
   
    ~SmartHome();
  
    // room manages yaha en functions sa hun ga
    bool addRoom(Room* r);
    bool removeRoom(int roomID);
    Room* getRoom(int roomID);
    int getRoomCount() const;
    void showAllRooms() const;
    
    // Automation manages yaha en functions sa hun ga
    bool addAutomation(Automation* a);
    bool removeAutomation(int ruleID);
    Automation* getAutomation(int ruleID);
    int getAutomationCount() const;
    void showAllAutomations() const;
    
    // Device management  Template function   like (camera.smartlight,speaker etc)
    template<typename T>
    T* findDevice(int deviceID);
    
   
    void getEnergyDashboard() const;
   
    int getHomeID() const;
    string getOwnerName() const;
    string getWifiNetwork() const;
    
    bool setOwnerName(string name);
    bool setWifiNetwork(string wifi);
    
   
   
void showHomeInfo() const;
void showHomeInfoToFile() const; 
    
  
    friend ostream& operator<<(ostream& os, const SmartHome& home);
};

// template function .h file ma implement karna zarori ha .cpp ma liking error data ha
template<typename T>
T* SmartHome::findDevice(int deviceID) {
    
    for(int i = 0; i < roomCount; i++) {  // Search in all rooms
        if(rooms[i] != nullptr) {
           
            int devCount = rooms[i]->getDeviceCount(); // Get device count from room ka aik room ma kitni devices hain          
           
            for(int j = 0; j < devCount; j++) {   //tgrough nested loop Search through each device in this room
                SmartDevice* device = rooms[i]->getDevice(j);
                
                if(device != nullptr && device->getDeviceID() == deviceID) {
                    // Try to cast ka matlb convert krta ha like hm smartlight chah raha ha lakin pointer smartdevice ka ha usa smartlight* ma change krna
                    T* found = dynamic_cast<T*>(device);
                    if(found != nullptr) {
                        cout << " Device found: " << device->getName() << endl;
                        return found;
                    }
                }
            }
        }
    }
    
    cout << " Device with ID " << deviceID << " not found.." << endl;
    return nullptr;
}

#endif

#include "SmartHome.h"



bool SmartHome::isValidHomeID(int id) {
    return (id > 0);
}

bool SmartHome::isValidOwnerName(string name) {
    
    if(name.length() == 0) {
        return false;
    }
    
   
    for(int i = 0; i < name.length(); i++) {
        char c = name[i];
        if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
            return false;
        }
    }
    return true;
}

bool SmartHome::isValidWifiNetwork(string wifi) {
   
    if(wifi.length() == 0) {
        return false;
    }
    
    return (wifi.length() >= 3);
}

bool SmartHome::isRoomExists(int roomID) {
    for(int i = 0; i < roomCount; i++) {
        if(rooms[i] != nullptr && rooms[i]->getRoomID() == roomID) {
            return true;
        }
    }
    return false;
}

bool SmartHome::isAutomationExists(int ruleID) {
    for(int i = 0; i < autoCount; i++) {
        if(automations[i] != nullptr && automations[i]->getRuleID() == ruleID) {
            return true;
        }
    }
    return false;
}

int SmartHome::findRoomIndex(int roomID) {
    for(int i = 0; i < roomCount; i++) {
        if(rooms[i] != nullptr && rooms[i]->getRoomID() == roomID) {
            return i;
        }
    }
    return -1;
}

int SmartHome::findAutomationIndex(int ruleID) {
    for(int i = 0; i < autoCount; i++) {
        if(automations[i] != nullptr && automations[i]->getRuleID() == ruleID) {
            return i;
        }
    }
    return -1;
}



SmartHome::SmartHome(int id, string owner, string wifi) 
    : roomCount(0), maxRooms(20), autoCount(0), maxAutomations(50) {
    
  
    if(!isValidHomeID(id)) {
        cout << " Invalid Home ID! Setting to default 1." << endl;
        homeID = 1;
    } else {
        homeID = id;
    }
    
   
    if(!isValidOwnerName(owner)) {
        cout << " Invalid Owner Name! Setting to default 'Unknown'." << endl;
        ownerName = "Unknown";
    } else {
        ownerName = owner;
    }
    
    
    if(!isValidWifiNetwork(wifi)) {
        cout << " Invalid WiFi Network Name! Setting to default 'HomeWiFi'." << endl;
        wifiNetwork = "HomeWiFi";
    } else {
        wifiNetwork = wifi;
    }
    
  
    rooms = new Room*[maxRooms];
    for(int i = 0; i < maxRooms; i++) {
        rooms[i] = nullptr;
    }
    
    automations = new Automation*[maxAutomations];
    for(int i = 0; i < maxAutomations; i++) {
        automations[i] = nullptr;
    }
    
    cout << "\n SMART HOME SYSTEM CREATED " << endl;
    cout << "   Home ID: " << homeID << endl;
    cout << "   Owner: " << ownerName << endl;
    cout << "   WiFi: " << wifiNetwork << endl;
    cout << "   Max Rooms: " << maxRooms << endl;
    cout << "   Max Automations: " << maxAutomations << endl;
}

SmartHome::~SmartHome() {
    cout << "\n SHUTTING DOWN SMART HOME SYSTEM " << endl;
    
    for(int i = 0; i < roomCount; i++) {
        if(rooms[i] != nullptr) {
            delete rooms[i];
            rooms[i] = nullptr;
        }
    }
    delete[] rooms;
    
    
    for(int i = 0; i < autoCount; i++) {
        if(automations[i] != nullptr) {
            delete automations[i];
            automations[i] = nullptr;
        }
    }
    delete[] automations;
    
    cout << "   System shutdown complete." << endl;
}



bool SmartHome::addRoom(Room* r) {
    if(r == nullptr) {
        cout << " Cannot add null room!" << endl;
        return false;
    }
    if(isRoomExists(r->getRoomID())) {
        cout << " Room with ID " << r->getRoomID() << " already exists!" << endl;
        return false;
    }
   
    if(roomCount >= maxRooms) {
        cout << " Cannot add more rooms. Maximum limit reached (" << maxRooms << ")" << endl;
        return false;
    }
  
    rooms[roomCount] = r;
    roomCount++;
    
    cout << " Room added: " << r->getRoomName() << " (ID: " << r->getRoomID() << ")" << endl;
    return true;
}

bool SmartHome::removeRoom(int roomID) {
    int index = findRoomIndex(roomID);
    
    if(index == -1) {
        cout << " Room with ID " << roomID << " not found!" << endl;
        return false;
    }
    
  
    delete rooms[index];
    rooms[index] = nullptr;
    
    // baqii remaining rooms left
    for(int i = index; i < roomCount - 1; i++) {
        rooms[i] = rooms[i + 1];
    }
    rooms[roomCount - 1] = nullptr;
    roomCount--;
    
    cout << " Room ID " << roomID << " removed successfully!" << endl;
    return true;
}

Room* SmartHome::getRoom(int roomID) {
    int index = findRoomIndex(roomID);
    if(index != -1) {
        return rooms[index];
    }
    cout << " Room with ID " << roomID << " not found!" << endl;
    return nullptr;
}

int SmartHome::getRoomCount() const {
    return roomCount;
}

void SmartHome::showAllRooms() const {
    cout << "\n========================================" << endl;
    cout << "   ALL ROOMS IN SMART HOME" << endl;
    cout << "========================================" << endl;
    
    if(roomCount == 0) {
        cout << "   No rooms in this home." << endl;
    } else {
        for(int i = 0; i < roomCount; i++) {
            if(rooms[i] != nullptr) {
                cout << "   " << (i+1) << ". " << *(rooms[i]) << endl;
            }
        }
    }
    cout << "========================================\n" << endl;
}



bool SmartHome::addAutomation(Automation* a) {
    if(a == nullptr) {
        cout << " Cannot add null automation!" << endl;
        return false;
    }
   
    if(isAutomationExists(a->getRuleID())) {
        cout << " Automation with ID " << a->getRuleID() << " already exists!" << endl;
        return false;
    }
    
    
    if(autoCount >= maxAutomations) {
        cout << " Cannot add more automations. Maximum limit reached (" << maxAutomations << ")" << endl;
        return false;
    }
    
   
    automations[autoCount] = a;
    autoCount++;
    
    cout << " Automation added: ID " << a->getRuleID() << endl;
    return true;
}

bool SmartHome::removeAutomation(int ruleID) {
    int index = findAutomationIndex(ruleID);
    
    if(index == -1) {
        cout << " Automation with ID " << ruleID << " not found!" << endl;
        return false;
    }
    
    
    delete automations[index];
    automations[index] = nullptr;
    
    // baqi remaining automations left
    for(int i = index; i < autoCount - 1; i++) {
        automations[i] = automations[i + 1];
    }
    automations[autoCount - 1] = nullptr;
    autoCount--;
    
    cout << " Automation ID " << ruleID << " removed successfully!" << endl;
    return true;
}

Automation* SmartHome::getAutomation(int ruleID) {
    int index = findAutomationIndex(ruleID);
    if(index != -1) {
        return automations[index];
    }
    cout << " Automation with ID " << ruleID << " not found!" << endl;
    return nullptr;
}

int SmartHome::getAutomationCount() const {
    return autoCount;
}

void SmartHome::showAllAutomations() const {
    cout << "\n========================================" << endl;
    cout << "   ALL AUTOMATIONS IN SMART HOME" << endl;
    cout << "========================================" << endl;
    
    if(autoCount == 0) {
        cout << "   No automations in this home." << endl;
    } else {
        for(int i = 0; i < autoCount; i++) {
            if(automations[i] != nullptr) {
                cout << "   " << (i+1) << ". " << *(automations[i]) << endl;
            }
        }
    }
    cout << "========================================\n" << endl;
}



void SmartHome::getEnergyDashboard() const {
    cout << "\n========================================" << endl;
    cout << "    ENERGY DASHBOARD " << endl;
    cout << "========================================" << endl;
    cout << "Home: " << ownerName << " (ID: " << homeID << ")" << endl;
    cout << "WiFi Network: " << wifiNetwork << endl;
    cout << "----------------------------------------" << endl;
    
    if(roomCount == 0) {
        cout << "   No rooms in this home." << endl;
    } else {
        
        EnergyLog::showAllLogs();
        
        EnergyLog::showTotalConsumption();
        
  
        EnergyLog::compareToAverage(0.5);
    }
    
    cout << "========================================\n" << endl;
}



int SmartHome::getHomeID() const {
    return homeID;
}

string SmartHome::getOwnerName() const {
    return ownerName;
}

string SmartHome::getWifiNetwork() const {
    return wifiNetwork;
}



bool SmartHome::setOwnerName(string name) {
    if(!isValidOwnerName(name)) {
        cout << " Invalid owner name! Must contain only letters and spaces." << endl;
        return false;
    }
    
    ownerName = name;
    cout << " Owner name updated to: " << ownerName << endl;
    return true;
}

bool SmartHome::setWifiNetwork(string wifi) {
    if(!isValidWifiNetwork(wifi)) {
        cout << " Invalid WiFi network name! Must be at least 3 characters." << endl;
        return false;
    }
    
    wifiNetwork = wifi;
    cout << " WiFi network updated to: " << wifiNetwork << endl;
    return true;
}



void SmartHome::showHomeInfo() const {
    cout << "\n================================================================================" << endl;
    cout << "                          SMART HOME SYSTEM REPORT                             " << endl;
    cout << "================================================================================" << endl;
    
    // BASIC INFORMATION
    cout << "\n  [1] BASIC INFORMATION" << endl;
    cout << "  ----------------------------------------------------------------------------" << endl;
    cout << "      Home ID:        " << homeID << endl;
    cout << "      Owner Name:     " << ownerName << endl;
    cout << "      WiFi Network:   " << wifiNetwork << endl;
    
    // ROOMS INFORMATION
    cout << "\n  [2] ROOMS INFORMATION" << endl;
    cout << "  ----------------------------------------------------------------------------" << endl;
    cout << "      Total Rooms:    " << roomCount << " / " << maxRooms << endl;
    
    if(roomCount > 0) {
        int totalDevices = 0;
        int floor1Count = 0, floor2Count = 0, floor3Count = 0;
        
        for(int i = 0; i < roomCount; i++) {
            if(rooms[i] != nullptr) {
                totalDevices += rooms[i]->getDeviceCount();
                if(rooms[i]->getFloor() == 1) floor1Count++;
                else if(rooms[i]->getFloor() == 2) floor2Count++;
                else if(rooms[i]->getFloor() == 3) floor3Count++;
            }
        }
        
        cout << "      Total Devices:   " << totalDevices << endl;
        cout << "\n      Rooms by Floor:" << endl;
        cout << "        - Floor 1:  " << floor1Count << " room(s)" << endl;
        cout << "        - Floor 2:  " << floor2Count << " room(s)" << endl;
        cout << "        - Floor 3:  " << floor3Count << " room(s)" << endl;
        
        cout << "\n      ROOM DETAILS:" << endl;
        cout << "      --------------------------------------------------------------------" << endl;
        for(int i = 0; i < roomCount; i++) {
            if(rooms[i] != nullptr) {
                cout << "        " << (i+1) << ". " << rooms[i]->getRoomName() 
                     << " (ID: " << rooms[i]->getRoomID() 
                     << ", Floor: " << rooms[i]->getFloor() 
                     << ", Devices: " << rooms[i]->getDeviceCount() << ")" << endl;
            }
        }
    } else {
        cout << "      [WARNING] No rooms added yet." << endl;
    }
    
    // AUTOMATIONS INFORMATION
    cout << "\n  [3] AUTOMATIONS INFORMATION" << endl;
    cout << "  ----------------------------------------------------------------------------" << endl;
    cout << "      Total Automations: " << autoCount << " / " << maxAutomations << endl;
    
    if(autoCount > 0) {
        int active = 0, inactive = 0;
        for(int i = 0; i < autoCount; i++) {
            if(automations[i] != nullptr) {
                if(automations[i]->getIsActive()) active++;
                else inactive++;
            }
        }
        cout << "        - Active Rules:   " << active << endl;
        cout << "        - Inactive Rules: " << inactive << endl;
        
        cout << "\n      AUTOMATION RULES:" << endl;
        cout << "      --------------------------------------------------------------------" << endl;
        for(int i = 0; i < autoCount; i++) {
            if(automations[i] != nullptr) {
                string status = automations[i]->getIsActive() ? "ACTIVE" : "INACTIVE";
                cout << "        " << (i+1) << ". Rule ID: " << automations[i]->getRuleID()
                     << " | " << status << endl;
                cout << "           Trigger: " << automations[i]->getTriggerCondition()
                     << " | Time: " << automations[i]->getTriggerTime() << endl;
            }
        }
    } else {
        cout << "      [WARNING] No automations added yet." << endl;
    }
    
    // SUMMARY
    cout << "\n  [4] SUMMARY" << endl;
    cout << "  ----------------------------------------------------------------------------" << endl;
    
    int totalDevicesSummary = 0;
    for(int i = 0; i < roomCount; i++) {
        if(rooms[i] != nullptr) {
            totalDevicesSummary += rooms[i]->getDeviceCount();
        }
    }
    
    cout << "        Home Owner:    " << ownerName << endl;
    cout << "        Total Rooms:   " << roomCount << " rooms" << endl;
    cout << "        Total Devices: " << totalDevicesSummary << " devices" << endl;
    cout << "        Automations:   " << autoCount << " rules" << endl;
    
    // STATUS
    cout << "\n  [5] SYSTEM STATUS" << endl;
    cout << "  ----------------------------------------------------------------------------" << endl;
    
    if(roomCount > 0 && autoCount > 0 && totalDevicesSummary > 0) {
        cout << "        Status:  FULLY OPERATIONAL" << endl;
        cout << "        Message: All systems are working perfectly." << endl;
    } else if(roomCount > 0 && totalDevicesSummary > 0) {
        cout << "        Status:  PARTIAL CONFIGURATION" << endl;
        cout << "        Message: Add automations for full automation." << endl;
    } else if(roomCount > 0) {
        cout << "        Status:  MINIMAL SETUP" << endl;
        cout << "        Message: Add devices and automations." << endl;
    } else {
        cout << "        Status:  NOT CONFIGURED" << endl;
        cout << "        Message: Please add rooms to get started." << endl;
    }
    
    cout << "\n================================================================================" << endl;
}

void SmartHome::showHomeInfoToFile() const {
    ofstream file("home_report.txt");
    
    if(!file.is_open()) {
        cout << "ERROR: Could not create home_report.txt file!" << endl;
        return;
    }
    
    // ==================== FILE OUTPUT (SAME AS TERMINAL) ====================
    
    file << "\n================================================================================" << endl;
    file << "                          SMART HOME SYSTEM REPORT                             " << endl;
    file << "================================================================================" << endl;
    
    // BASIC INFORMATION
    file << "\n  [1] BASIC INFORMATION" << endl;
    file << "  ----------------------------------------------------------------------------" << endl;
    file << "      Home ID:        " << homeID << endl;
    file << "      Owner Name:     " << ownerName << endl;
    file << "      WiFi Network:   " << wifiNetwork << endl;
    
    // ROOMS INFORMATION
    file << "\n  [2] ROOMS INFORMATION" << endl;
    file << "  ----------------------------------------------------------------------------" << endl;
    file << "      Total Rooms:    " << roomCount << " / " << maxRooms << endl;
    
    if(roomCount > 0) {
        int totalDevices = 0;
        int floor1Count = 0, floor2Count = 0, floor3Count = 0;
        
        for(int i = 0; i < roomCount; i++) {
            if(rooms[i] != nullptr) {
                totalDevices += rooms[i]->getDeviceCount();
                if(rooms[i]->getFloor() == 1) floor1Count++;
                else if(rooms[i]->getFloor() == 2) floor2Count++;
                else if(rooms[i]->getFloor() == 3) floor3Count++;
            }
        }
        
        file << "      Total Devices:   " << totalDevices << endl;
        file << "\n      Rooms by Floor:" << endl;
        file << "        - Floor 1:  " << floor1Count << " room(s)" << endl;
        file << "        - Floor 2:  " << floor2Count << " room(s)" << endl;
        file << "        - Floor 3:  " << floor3Count << " room(s)" << endl;
        
        file << "\n      ROOM DETAILS:" << endl;
        file << "      --------------------------------------------------------------------" << endl;
        for(int i = 0; i < roomCount; i++) {
            if(rooms[i] != nullptr) {
                file << "        " << (i+1) << ". " << rooms[i]->getRoomName() 
                     << " (ID: " << rooms[i]->getRoomID() 
                     << ", Floor: " << rooms[i]->getFloor() 
                     << ", Devices: " << rooms[i]->getDeviceCount() << ")" << endl;
            }
        }
    } else {
        file << "      [WARNING] No rooms added yet." << endl;
    }
    
    // AUTOMATIONS INFORMATION
    file << "\n  [3] AUTOMATIONS INFORMATION" << endl;
    file << "  ----------------------------------------------------------------------------" << endl;
    file << "      Total Automations: " << autoCount << " / " << maxAutomations << endl;
    
    if(autoCount > 0) {
        int active = 0, inactive = 0;
        for(int i = 0; i < autoCount; i++) {
            if(automations[i] != nullptr) {
                if(automations[i]->getIsActive()) active++;
                else inactive++;
            }
        }
        file << "        - Active Rules:   " << active << endl;
        file << "        - Inactive Rules: " << inactive << endl;
        
        file << "\n      AUTOMATION RULES:" << endl;
        file << "      --------------------------------------------------------------------" << endl;
        for(int i = 0; i < autoCount; i++) {
            if(automations[i] != nullptr) {
                string status = automations[i]->getIsActive() ? "ACTIVE" : "INACTIVE";
                file << "        " << (i+1) << ". Rule ID: " << automations[i]->getRuleID()
                     << " | " << status << endl;
                file << "           Trigger: " << automations[i]->getTriggerCondition()
                     << " | Time: " << automations[i]->getTriggerTime() << endl;
            }
        }
    } else {
        file << "      [WARNING] No automations added yet." << endl;
    }
    
    // SUMMARY
    file << "\n  [4] SUMMARY" << endl;
    file << "  ----------------------------------------------------------------------------" << endl;
    
    int totalDevicesSummary = 0;
    for(int i = 0; i < roomCount; i++) {
        if(rooms[i] != nullptr) {
            totalDevicesSummary += rooms[i]->getDeviceCount();
        }
    }
    
    file << "        Home Owner:    " << ownerName << endl;
    file << "        Total Rooms:   " << roomCount << " rooms" << endl;
    file << "        Total Devices: " << totalDevicesSummary << " devices" << endl;
    file << "        Automations:   " << autoCount << " rules" << endl;
    
    // STATUS
    file << "\n  [5] SYSTEM STATUS" << endl;
    file << "  ----------------------------------------------------------------------------" << endl;
    
    if(roomCount > 0 && autoCount > 0 && totalDevicesSummary > 0) {
        file << "        Status:  FULLY OPERATIONAL" << endl;
        file << "        Message: All systems are working perfectly." << endl;
    } else if(roomCount > 0 && totalDevicesSummary > 0) {
        file << "        Status:  PARTIAL CONFIGURATION" << endl;
        file << "        Message: Add automations for full automation." << endl;
    } else if(roomCount > 0) {
        file << "        Status:  MINIMAL SETUP" << endl;
        file << "        Message: Add devices and automations." << endl;
    } else {
        file << "        Status:  NOT CONFIGURED" << endl;
        file << "        Message: Please add rooms to get started." << endl;
    }
    
    file << "\n================================================================================" << endl;
    
    file.close();
    
    cout << "\nHome report saved to 'home_report.txt'" << endl;
}



ostream& operator<<(ostream& os, const SmartHome& home) {
    os << "[SmartHome: ID=" << home.homeID 
       << " | Owner=" << home.ownerName
       << " | WiFi=" << home.wifiNetwork
       << " | Rooms=" << home.roomCount
       << " | Automations=" << home.autoCount << "]";
    return os;
}


#ifndef USERAUTHENTICATION_H
#define USERAUTHENTICATION_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

class UserAuthentication {
private:
    string username;
    string passwordHash;
    string role;
    bool isLoggedIn;
    string loginTime;
    
    string guestName;
    int guestAccessHours;
    time_t guestAccessStartTime;
    bool hasGuestAccess;
    
    // Validation functions
    bool isValidUsername(string user);
    bool isValidPassword(string pass);
    bool isValidRole(string r);
    bool isStrongPassword(string pass);
    string hashPassword(string pass);
    string getCurrentDate();
    bool isGuestAccessExpired();
    
    // Static members for user database
    static UserAuthentication** userDatabase;
    static int userCount;
    static int maxUsers;
    
public:
    // Constructor / Destructor
    UserAuthentication();
    ~UserAuthentication();
    
    // Core authentication methods
    bool signUp(string user, string pass, string r);
    bool login(string user, string pass);
    void logout();
    bool isLoggedInUser() const { return isLoggedIn; }
    string getCurrentUser() const { return username; }
    string getCurrentRole() const { return role; }
    string getLoginTime() const { return loginTime; }
    
    // Role verification
    bool verifyRole(string requiredRole);
    bool isOwner() const { return role == "owner"; }
    bool isAdmin() const { return role == "admin"; }
    bool isGuest() const { return role == "guest"; }
    
    // Guest access management
    bool grantGuestAccess(string guestName, int hours);
    bool revokeGuestAccess();
    bool checkGuestAccess();
    void showGuestInfo() const;
    
    // Password management
    bool changePassword(string oldPass, string newPass);
  
    static bool addUser(string user, string pass, string role);
    static bool removeUser(string user);
    static void showAllUsers();
    static UserAuthentication* findUser(string user);
    
    static void initDatabase();
    
    friend ostream& operator<<(ostream& os, const UserAuthentication& user);

    static void saveUsersToFile();
static void loadUsersFromFile();
};

#endif

#include "UserAuthentication.h"
#include <iomanip>
#include <cctype>


UserAuthentication** UserAuthentication::userDatabase = nullptr;
int UserAuthentication::userCount = 0;
int UserAuthentication::maxUsers = 100;


void UserAuthentication::initDatabase() {
    if(userDatabase == nullptr) {
        userDatabase = new UserAuthentication*[maxUsers];
        for(int i = 0; i < maxUsers; i++) {
            userDatabase[i] = nullptr;
        }
        // Create default owner account
        UserAuthentication* defaultOwner = new UserAuthentication();
        defaultOwner->username = "noor";
        defaultOwner->passwordHash = defaultOwner->hashPassword("Admin123");
        defaultOwner->role = "owner";
        defaultOwner->isLoggedIn = false;
        userDatabase[0] = defaultOwner;
        userCount = 1;
    }
}


bool UserAuthentication::isValidUsername(string user) {
    if(user.length() == 0) {
        cout << "[ERROR] Username cannot be empty!" << endl;
        return false;
    }
    
    if(user.length() < 3) {
        cout << "[ERROR] Username too short! Minimum 3 characters required." << endl;
        return false;
    }
    
    if(user.length() > 20) {
        cout << "[ERROR] Username too long! Maximum 20 characters allowed." << endl;
        return false;
    }
    
    for(int i = 0; i < user.length(); i++) {
        char c = user[i];
        if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || 
             (c >= '0' && c <= '9') || c == '_')) {
            cout << "[ERROR] Username can only contain letters, numbers, and underscore!" << endl;
            return false;
        }
    }
    
    char firstChar = user[0];
    if(!((firstChar >= 'A' && firstChar <= 'Z') || (firstChar >= 'a' && firstChar <= 'z'))) {
        cout << "[ERROR] Username must start with a letter!" << endl;
        return false;
    }
    
    return true;
}

bool UserAuthentication::isValidPassword(string pass) {
    if(pass.length() == 0) {
        cout << "[ERROR] Password cannot be empty!" << endl;
        return false;
    }
    
    if(pass.length() < 6) {
        cout << "[ERROR] Password too short! Minimum 6 characters required." << endl;
        return false;
    }
    
    if(pass.length() > 20) {
        cout << "[ERROR] Password too long! Maximum 20 characters allowed." << endl;
        return false;
    }
    
    return true;
}

bool UserAuthentication::isStrongPassword(string pass) {
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    
    for(int i = 0; i < pass.length(); i++) {
        char c = pass[i];
        if(c >= 'A' && c <= 'Z') hasUpper = true;
        else if(c >= 'a' && c <= 'z') hasLower = true;
        else if(c >= '0' && c <= '9') hasDigit = true;
        else hasSpecial = true;
    }
    
    if(!hasUpper) {
        cout << "[WARNING] Weak password: Add at least one uppercase letter!" << endl;
        return false;
    }
    if(!hasLower) {
        cout << "[WARNING] Weak password: Add at least one lowercase letter!" << endl;
        return false;
    }
    if(!hasDigit) {
        cout << "[WARNING] Weak password: Add at least one number!" << endl;
        return false;
    }
    if(!hasSpecial) {
        cout << "[WARNING] Weak password: Add at least one special character (!@#$%^&*)!" << endl;
        return false;
    }
    
    return true;
}

bool UserAuthentication::isValidRole(string r) {
    return (r == "owner" || r == "admin" || r == "guest");
}

string UserAuthentication::hashPassword(string pass) {
    string hash = "";
    for(int i = 0; i < pass.length(); i++) {
        hash += char(pass[i] + 1);
    }
    return hash;
}

string UserAuthentication::getCurrentDate() {
    time_t now = time(0);
    string fullTime = ctime(&now);  // now ka kam ha readable bnana
    
    // ctime() returns Sun May 24 15:30:00 2026\n
    // Remove newline from end
    if(!fullTime.empty() && fullTime[fullTime.length() - 1] == '\n') {
        fullTime = fullTime.substr(0, fullTime.length() - 1);  // substring ka use mean indexing sa aik last wali remove ho sakti ha
    }
    
    return fullTime;
}

bool UserAuthentication::isGuestAccessExpired() {
    if(!hasGuestAccess) return true;
    
    time_t now = time(0);
    double diffSeconds = difftime(now, guestAccessStartTime);
    double diffHours = diffSeconds / 3600.0;
    
    return (diffHours >= guestAccessHours);
}


UserAuthentication::UserAuthentication() 
    : username(""), passwordHash(""), role("guest"), isLoggedIn(false), 
      loginTime(""), guestName(""), guestAccessHours(0), 
      guestAccessStartTime(0), hasGuestAccess(false) {
    
    initDatabase();  // Initialize static database
}

UserAuthentication::~UserAuthentication() {
}

UserAuthentication* UserAuthentication::findUser(string user) {
    for(int i = 0; i < userCount; i++) {
        if(userDatabase[i] != nullptr && userDatabase[i]->username == user) {
            return userDatabase[i];
        }
    }
    return nullptr;
}

bool UserAuthentication::addUser(string user, string pass, string role) {
    // Check if user already exists
    if(findUser(user) != nullptr) {
        cout << "[ERROR] Username already exists!" << endl;
        return false;
    }
    
    UserAuthentication* newUser = new UserAuthentication();
    newUser->username = user;
    newUser->passwordHash = newUser->hashPassword(pass);
    newUser->role = role;
    newUser->isLoggedIn = false;
    
    if(userCount < maxUsers) {
        userDatabase[userCount] = newUser;
        userCount++;
        cout << " User '" << user << "' added successfully!" << endl;
        return true;
    }
    saveUsersToFile();
    
    
    cout << " User database is full!" << endl;
    return false;
}

bool UserAuthentication::removeUser(string user) {
    for(int i = 0; i < userCount; i++) {
        if(userDatabase[i] != nullptr && userDatabase[i]->username == user) {
            delete userDatabase[i];
            for(int j = i; j < userCount - 1; j++) {
                userDatabase[j] = userDatabase[j + 1];
            }
            userDatabase[userCount - 1] = nullptr;
            userCount--;
            cout << " User '" << user << "' removed successfully!" << endl;
            return true;
        }
    }
    saveUsersToFile();
    
    
    cout << " User '" << user << "' not found!" << endl;
    return false;
}

void UserAuthentication::showAllUsers() {
    cout << "\n========================================" << endl;
    cout << "             ALL USERS                   " << endl;
    cout << "========================================" << endl;
    
    if(userCount == 0) {
        cout << "   No users found." << endl;
    } else {
        for(int i = 0; i < userCount; i++) {
            if(userDatabase[i] != nullptr) {
                string roleTag = (userDatabase[i]->role == "owner") ? "[OWNER]" : 
                                 (userDatabase[i]->role == "admin") ? "[ADMIN]" : "[GUEST]";
                cout << "   " << (i+1) << ". " << roleTag << " " 
                     << userDatabase[i]->username << endl;
            }
        }
    }
    cout << "========================================" << endl;
}

bool UserAuthentication::signUp(string user, string pass, string r) {
    cout << "\n========================================" << endl;
    cout << "           SIGN UP PROCESS               " << endl;
    cout << "========================================" << endl;
    
    if(!isValidUsername(user)) {
        return false;
    }
    
    // Check if username already exists
    if(findUser(user) != nullptr) {
        cout << "[ERROR] Username '" << user << "' already exists!" << endl;
        return false;
    }
    
    if(!isValidPassword(pass)) {
        return false;
    }
    
    if(!isStrongPassword(pass)) {
        cout << "[ERROR] Password is not strong enough!" << endl;
        return false;
    }
    
    if(!isValidRole(r)) {
        cout << "[ERROR] Invalid role! Use: owner, admin, or guest" << endl;
        return false;
    }
    
    // Check only one owner
    if(r == "owner") {
        for(int i = 0; i < userCount; i++) {
            if(userDatabase[i] != nullptr && userDatabase[i]->role == "owner") {
                cout << "[ERROR] An owner already exists! Only one owner allowed." << endl;
                return false;
            }
        }
    }
    
    // Create new user
    username = user;
    passwordHash = hashPassword(pass);
    role = r;
    isLoggedIn = false;
    
    // Add to database
    if(userCount < maxUsers) {
        UserAuthentication* newUser = new UserAuthentication();
        newUser->username = username;
        newUser->passwordHash = passwordHash;
        newUser->role = role;
        newUser->isLoggedIn = false;
        userDatabase[userCount] = newUser;
        userCount++;
    }
    
    cout << "\n[SUCCESS] SIGN UP SUCCESSFUL!" << endl;
    cout << "   Username: " << username << endl;
    cout << "   Role: " << role << endl;
    cout << "   Please login to continue." << endl;
     saveUsersToFile();
    return true;
}


bool UserAuthentication::login(string user, string pass) {
    cout << "\n========================================" << endl;
    cout << "             LOGIN PROCESS               " << endl;
    cout << "========================================" << endl;
    
    if(isLoggedIn) {
        cout << "[WARNING] You are already logged in as '" << username << "'!" << endl;
        return false;
    }
    
    // Find user in database
    UserAuthentication* foundUser = findUser(user);
    
    if(foundUser == nullptr) {
        cout << "[ERROR] User '" << user << "' not found!" << endl;
        cout << "   Please sign up first." << endl;
        return false;
    }
    
    // Verify password
    string hashedPass = hashPassword(pass);
    if(foundUser->passwordHash != hashedPass) {
        cout << "[ERROR] Incorrect password!" << endl;
        return false;
    }
    
    // Login successful
    username = foundUser->username;
    passwordHash = foundUser->passwordHash;
    role = foundUser->role;
    isLoggedIn = true;
    loginTime = getCurrentDate();
    
    cout << "\n[SUCCESS] LOGIN SUCCESSFUL!" << endl;
    cout << "   Welcome, " << username << "!" << endl;
    cout << "   Role: " << role << endl;
    cout << "   Login Time: " << loginTime << endl;
    
    return true;
}

void UserAuthentication::logout() {
    if(!isLoggedIn) {
        cout << "[WARNING] You are not logged in!" << endl;
        return;
    }
    
    cout << "\n========================================" << endl;
    cout << "            LOGOUT PROCESS               " << endl;
    cout << "========================================" << endl;
    
    cout << "[SUCCESS] Goodbye, " << username << "!" << endl;
    cout << "   Logout Time: " << getCurrentDate() << endl;
    
    username = "";
    passwordHash = "";
    role = "guest";
    isLoggedIn = false;
    loginTime = "";
}


bool UserAuthentication::verifyRole(string requiredRole) {
    if(!isLoggedIn) {
        cout << "[ERROR] You are not logged in!" << endl;
        return false;
    }
    
    if(role == requiredRole) {
        return true;
    }
    
    if(role == "owner") {
        return true;
    }
    
    if(role == "admin" && (requiredRole == "admin" || requiredRole == "guest")) {
        return true;
    }
    
    cout << "[ERROR] Access denied! Required role: " << requiredRole << endl;
    cout << "   Your role: " << role << endl;
    return false;
}


bool UserAuthentication::grantGuestAccess(string gName, int hours) {
    if(!isLoggedIn) {
        cout << "[ERROR] You must be logged in to grant guest access!" << endl;
        return false;
    }
    
    if(!verifyRole("owner") && !verifyRole("admin")) {
        cout << "[ERROR] Only owner or admin can grant guest access!" << endl;
        return false;
    }
    
    if(hours < 1 || hours > 24) {
        cout << "[ERROR] Guest access hours must be between 1 and 24!" << endl;
        return false;
    }
    
    guestName = gName;
    guestAccessHours = hours;
    guestAccessStartTime = time(0);
    hasGuestAccess = true;
    
    cout << "\n[SUCCESS] GUEST ACCESS GRANTED!" << endl;
    cout << "   Guest Name: " << guestName << endl;
    cout << "   Access Hours: " << guestAccessHours << " hours" << endl;
    cout << "   Start Time: " << getCurrentDate() << endl;
    
    return true;
}

bool UserAuthentication::revokeGuestAccess() {
    if(!hasGuestAccess) {
        cout << "[ERROR] No active guest access to revoke!" << endl;
        return false;
    }
    
    hasGuestAccess = false;
    guestName = "";
    guestAccessHours = 0;
    
    cout << "[SUCCESS] Guest access revoked successfully!" << endl;
    return true;
}

bool UserAuthentication::checkGuestAccess() {
    if(!hasGuestAccess) return false;
    
    if(isGuestAccessExpired()) {
        cout << "[WARNING] Guest access has expired!" << endl;
        hasGuestAccess = false;
        return false;
    }
    
    time_t now = time(0);
    double remainingHours = guestAccessHours - (difftime(now, guestAccessStartTime) / 3600.0);
    
    cout << "[OK] Guest access valid! Remaining time: " << fixed << setprecision(1) 
         << remainingHours << " hours" << endl;
    
    return true;
}

void UserAuthentication::showGuestInfo() const {
    if(!hasGuestAccess) {
        cout << "No active guest access." << endl;
        return;
    }
    
    cout << "\n========================================" << endl;
    cout << "         GUEST ACCESS INFO               " << endl;
    cout << "========================================" << endl;
    cout << "   Guest Name: " << guestName << endl;
    cout << "   Access Hours: " << guestAccessHours << " hours" << endl;
    
    time_t now = time(0);
    double remaining = guestAccessHours - (difftime(now, guestAccessStartTime) / 3600.0);
    cout << "   Remaining: " << fixed << setprecision(1) << remaining << " hours" << endl;
}

// ==================== PASSWORD MANAGEMENT ====================

bool UserAuthentication::changePassword(string oldPass, string newPass) {
    if(!isLoggedIn) {
        cout << "[ERROR] You must be logged in to change password!" << endl;
        return false;
    }
    
    if(hashPassword(oldPass) != passwordHash) {
        cout << "[ERROR] Incorrect old password!" << endl;
        return false;
    }
    
    if(!isValidPassword(newPass)) {
        return false;
    }
    
    if(!isStrongPassword(newPass)) {
        cout << "[ERROR] New password is not strong enough!" << endl;
        return false;
    }
    
    passwordHash = hashPassword(newPass);
    
    // Update in database
    for(int i = 0; i < userCount; i++) {
        if(userDatabase[i] != nullptr && userDatabase[i]->username == username) {
            userDatabase[i]->passwordHash = passwordHash;
            break;
        }
    }
    
    cout << "[SUCCESS] Password changed successfully!" << endl;
    return true;
}

// ==================== OPERATOR OVERLOADING ====================

ostream& operator<<(ostream& os, const UserAuthentication& user) {
    os << "[User: " << user.username 
       << " | Role: " << user.role 
       << " | Status: " << (user.isLoggedIn ? "Online" : "Offline") << "]";
    return os;
}

void UserAuthentication::saveUsersToFile() {
    ofstream file("users.txt");
    
    if(!file.is_open()) {
        cout << "ERROR: Cannot create users.txt file!" << endl;
        return;
    }
    
    file << "========================================\n";
    file << "         USER DATABASE\n";
    file << "========================================\n";
    file << "Total Users: " << userCount << "\n";
    
    
    for(int i = 0; i < userCount; i++) {
        if(userDatabase[i] != nullptr) {
            file << "Username: " << userDatabase[i]->username << "\n";
            file << "Role: " << userDatabase[i]->role << "\n";
            file << "PasswordHash: " << userDatabase[i]->passwordHash << "\n";
          
        }
    }
    
    file.close();
    cout << "Users saved to users.txt" << endl;
}

void UserAuthentication::loadUsersFromFile() {
    ifstream file("users.txt");
    
    if(!file.is_open()) {
        cout << "No existing users file found." << endl;
        return;
    }
    
    // File exists  we just note it
    cout << "Existing users.txt file found." << endl;
    file.close();
}



#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <typeinfo>
using namespace std;


#include "ScheduleAble.h"
#include "SmartDevice.h"
#include "SmartLight.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "SmartAppliance.h"
#include "SmartLock.h"
#include "SmartSpeaker.h"
#include "Room.h"
#include "Automation.h"
#include "EnergyLog.h"
#include "SmartHome.h"
#include "UserAuthentication.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

     // Device type constants    // constant jaha par ma na equal ccheck kia wwaha par en ka use aya ha
      // automation am device type check krna ka lia

const int TYPE_LIGHT = 1;
const int TYPE_THERMOSTAT = 2;
const int TYPE_CAMERA = 3;
const int TYPE_LOCK = 4;
const int TYPE_SPEAKER = 5;

// Global arrays for device management
const int MAX_TOTAL_DEVICES = 50;
SmartDevice* allDevices[MAX_TOTAL_DEVICES];
int totalDevices = 0;


SmartHome* myHome = nullptr;// Global pointers for home and authentication jis ma hm devices aur home ka data store kar rahay hain
UserAuthentication* auth = nullptr;
bool isLoggedIn = false;
bool isSystemRunning = true;


void displayWelcomeBanner();
void displayLoginMenu();
void displayMainMenu();
void displayDeviceMenu();
void displayRoomMenu();
void displayAutomationMenu();
void displayEnergyMenu();
void displaySecurityMenu();
void displayVoiceMenu();
void displayReportsMenu();
void displayAdvancedMenu();

void handleLoginMenu(int choice);
void handleMainMenu(int choice);
void handleDeviceMenu(int choice);
void handleRoomMenu(int choice);
void handleAutomationMenu(int choice);
void handleEnergyMenu(int choice);
void handleSecurityMenu(int choice);
void handleVoiceMenu(int choice);
void handleReportsMenu(int choice);
void handleAdvancedMenu(int choice);

void loginUser();
void registerUser();

void addDevice();
void viewAllDevices();
void toggleDevice();
void updateDeviceInfo();
void removeDevice();

void createRoom();// Room Management functions
void viewAllRooms();
void addDeviceToRoom();
void removeDeviceFromRoom();
void turnOffAllDevicesInRoom();
void getRoomStatus();

void createAutomationRule();// Automation functions
void addActionToRule();
void activateAutomation();
void deactivateAutomation();
void editAutomationCondition();
void evaluateTrigger();
void displayAllRules();
//void removeAction();

void logEnergyUsage();// Energy functions
void viewMonthlyReport();
void compareToAverage();
void fullEnergyDashboard();


void lockUnlockDoor();// Security functions
void startCameraRecording();
void captureSnapshot();
void grantGuestAccess();
//void viewAccessHistory();
void armDisarmCamera();


void sendVoiceCommand();// Voice functions
void viewConnectedServices();
void changeVolume();


void generateAllReports();// Reports functions
void displayAllStatus();
void toggleAllDevices();
void operatorEqualDemo();

// Advanced functions
void findDeviceTemplate();
void showTotalDeviceCount();
void scheduleDevice();
void cancelSchedule();


void waitForEnter();// Utility functions ya output clear and clean up memory ka lia
void clearScreen();
void cleanupMemory();
int findDeviceIndex(int deviceID);

SmartDevice* findDeviceByID(int deviceID);


void clearScreen() {
    system("clear || cls");
}

void waitForEnter() {
    cout << "\n\t\t\t\t\t\tPress Enter to continue...";
    cin.ignore();
    cin.get();
}

int findDeviceIndex(int deviceID) {
    for(int i = 0; i < totalDevices; i++) {
        if(allDevices[i] != nullptr && allDevices[i]->getDeviceID() == deviceID) {
            return i;
        }
    }
    return -1;
}

SmartDevice* findDeviceByID(int deviceID) {
    int index = findDeviceIndex(deviceID);
    if(index != -1) {
        return allDevices[index];
    }
    return nullptr;
}

void cleanupMemory() {
    cout << "\n\t\t\t\t          CLEANING UP MEMORY             " << endl;
    
    for(int i = 0; i < totalDevices; i++) {
        if(allDevices[i] != nullptr) {
            delete allDevices[i];
            allDevices[i] = nullptr;
        }
    }
    totalDevices = 0;
    
    if(myHome != nullptr) {
        delete myHome;
        myHome = nullptr;
    }
    
    if(auth != nullptr) {
        delete auth;
        auth = nullptr;
    }
    
    cout << "\t\t\t\tAll memory freed successfully!" << endl;
}

void centerText(string text) {
    cout << "\t\t\t\t\t\t" << text << endl;
}

void displayWelcomeBanner() {
    cout << "\n\n\n\n";
   
    centerText("--------------------<-|->--------------------");
     cout<<BOLD;
    centerText("         SMART HOME DEVICE SIMULATOR        ");
     cout<<RESET;
     
    centerText("--------------------<-|->--------------------");
    //centerText("----------------------------------------");
    
}

void displayLoginMenu() {
    cout << "\n\n";
     cout<<GREEN;
    centerText("         SMART HOME => LOGIN PORTAL       ");
    cout<<"\n";
    cout<<RESET;
    centerText("  1. Login                              ");
    centerText("  2. Register                           ");
    cout<<RED;
    centerText("  0. Exit Program                       ");
        cout<<RESET;

    cout << "\n\t\t\t\t\t\t  Enter your choice: ";
}

void displayMainMenu() {
    cout << "\n\n";

     cout<<GREEN;
    centerText("           SMART HOME DASHBOARD          ");
    cout<<RESET;

    centerText("  1. Device Management                  ");
    centerText("  2. Room Management                    ");
    centerText("  3. Automation Rules                   ");
    centerText("  4. Energy Monitoring                  ");
    centerText("  5. Security and Access Control        ");
    centerText("  6. Voice Command Simulation           ");
    centerText("  7. System Reports and Polymorphism Demo ");
    centerText("  8. Advanced Features Templates OOP    ");
    cout<<RED;
    centerText("  0. Logout                             ");
        cout<<RESET;
    cout << "\n\t\t\t\t  Enter your choice: ";
}

void displayDeviceMenu() {
    cout << "\n\n";
    cout<<GREEN;
     
    centerText("           DEVICE MANAGEMENT             ");
        cout<<RESET;
    centerText("  1. Add New Device                     ");
    centerText("  2. View All Devices                   ");
    centerText("  3. Toggle Device ON OFF               ");
    centerText("  4. Update Device Info                 ");
    centerText("  5. Remove Device                      ");
    cout<<RED;
    centerText("  0. Back                               ");
    cout<<RESET;
    cout << "\n\t\t\t\t  Enter your choice: ";
}

void displayRoomMenu() {
    cout << "\n\n";
    cout<<GREEN;
    
    centerText("            ROOM MANAGEMENT              ");
    cout<<RESET;
    centerText("  1. Create New Room                    ");
    centerText("  2. View All Rooms                     ");
    centerText("  3. Add Device to Room                 ");
    centerText("  4. Remove Device from Room            ");
    centerText("  5. Turn OFF All in Room               ");
    centerText("  6. Get Room Status                    ");
    centerText("  0. Back                               ");
    centerText("----------------------------------------");
    cout << "\n\t\t\t\t  Enter your choice: ";
}

void displayAutomationMenu() {
            cout << "\n\n";
    cout<<GREEN;
    centerText("           AUTOMATION RULES              ");
    cout<<RESET;    
    centerText("  1. Create New Rule                    ");
    centerText("  2. Add Action to Rule                 ");
    centerText("  3. Activate Rule                      ");
    centerText("  4. Deactivate Rule                    ");
    centerText("  5. Edit Rule Condition                ");
    centerText("  6. Evaluate Test Trigger              ");
    centerText("  7. Display All Rules                  ");
    //centerText("  8. Remove Action                      ");
    cout<<RED;  
    centerText("  0. Back                               ");
        cout<<RESET;
   
    cout << "\n\t\t\t\t  Enter your choice: ";
}

void displayEnergyMenu() {
    cout << "\n\n";
    cout<<GREEN;
    centerText("           ENERGY MONITORING             ");
    cout<<RESET;
    centerText("  1. Log Energy Usage                   ");
    centerText("  2. View Monthly Report                ");
    centerText("  3. Compare to Average                 ");
    centerText("  4. Full Energy Dashboard              ");
    centerText("  5. Generate Electricity Bill          ");  
    cout<<RED;
    centerText("  0. Back                               ");
    cout<<RESET;
   
    cout << "\n\t\t\t\t  Enter your choice: ";
}

void displaySecurityMenu() {
    cout << "\n\n";
    cout<<GREEN;
    
    centerText("         SECURITY AND ACCESS CONTROL     ");
    cout<<RESET;
    centerText("  1. Lock Unlock Door                   ");
    centerText("  2. Start Camera Recording             ");
    centerText("  3. Capture Snapshot                   ");
    centerText("  4. Grant Guest Access                 ");
    //centerText("  5. View Access History                ");
    centerText("  5. Arm Disarm Camera                  ");
    cout<<RED;
    centerText("  0. Back                               ");
    cout<<RESET;    
    cout << "\n\t\t\t\t  Enter your choice: ";
}

void displayVoiceMenu() {
    cout << "\n\n";
    cout<<GREEN;
    centerText("         VOICE COMMAND SIMULATOR         ");
    cout<<RESET;
    centerText("  1. Send Voice Command                 ");
    centerText("  2. View Connected Services            ");
    centerText("  3. Change Volume                      ");
        cout<<RED;
    centerText("  0. Back                               ");
        cout<<RESET;
    
    cout << "\n\t\t\t\t  Enter your choice: ";
}

void displayReportsMenu() {
    cout << "\n\n";
    cout<<GREEN;
    centerText("      REPORTS AND POLYMORPHISM DEMO      ");
    cout<<RESET;
    centerText("  1. Generate All Reports               ");
    centerText("  2. Display All Status                 ");
    centerText("  3. Toggle All Devices                 ");
    centerText("  4. Operator Equal Demo                ");
    centerText("  5. Save Home Report to File           ");  
    cout<<RED;
    centerText("  0. Back                               ");
    cout<<RESET;
    
    cout << "\n\t\t\t\t  Enter your choice: ";
}

void displayAdvancedMenu() {
    cout << "\n\n";
    cout<<GREEN;
    centerText("                   OOP FEATURES          ");
    cout<<RESET;
    centerText("  1. Find Device Template               ");
    centerText("  2. Total Device Count Static          ");
    centerText("  3. Schedule Device                    ");
    centerText("  4. Cancel Schedule                    ");
        cout<<RED;
    centerText("  0. Back                               ");
        cout<<RESET;
    
    cout << "\n\t\t\t\t  Enter your choice: ";
}



// void loginUser() {
//     string username, password;
    
//     cout << "\n\n";
    
//     centerText("               LOGIN                    ");
    
//     cout << "\t\t\t\t  Username: ";
//     cin >> username;
//     cout << "\t\t\t\t  Password: ";
//     cin >> password;
    
//     if(auth->login(username, password)) {
//         isLoggedIn = true;
//         centerText("SUCCESS Login Successful.");
        
//         string ownerName = auth->getCurrentUser();
//         myHome = new SmartHome(1, ownerName, "HomeWiFi");
//         centerText("Smart Home Initialized for " + ownerName);
//     } else {
//         centerText("ERROR Invalid credentials. Try again.");
//     }
//     waitForEnter();
// }

// void registerUser() {
//     string username, password, role;
    
//     cout << "\n\n";
    
//     centerText("              REGISTER                  ");
    
//     cout << "\t\t\t\t  Username: ";
//     cin >> username;
//     cout << "\t\t\t\t  Password: ";
//     cin >> password;
//     cout << "\t\t\t\t  Role owner admin guest: ";
//     cin >> role;
    
//     if(auth->signUp(username, password, role)) {
//         centerText(" Registered. Please login now.");
//     }
//     waitForEnter();
// }
void registerUser() {
    string username, password, role;
    
    cout << "\n\n";
    cout<<GREEN;

    centerText("              REGISTER                  ");
    cout<<RESET;
    
    // ==================== USERNAME INPUT (3 attempts) ====================
    for(int attempt = 1; attempt <= 3; attempt++) {
        cout << "\t\t\t\t  Username: ";
        cin >> username;
        
        // Check empty
        if(username.empty()) {
            centerText("     Username cannot be empty!");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Check length
        if(username.length() < 3) {
            centerText("     Username too short. Minimum 3 characters required.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        if(username.length() > 20) {
            centerText("     Username too long. Maximum 20 characters allowed.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Check for valid characters
        bool validChars = true;
        for(int i = 0; i < username.length(); i++) {
            char c = username[i];
            if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || 
                 (c >= '0' && c <= '9') || c == '_')) {
                validChars = false;
                break;
            }
        }
        
        if(!validChars) {
            centerText("     Username can only contain letters, numbers, and underscore!");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Check first character is letter
        char firstChar = username[0];
        if(!((firstChar >= 'A' && firstChar <= 'Z') || (firstChar >= 'a' && firstChar <= 'z'))) {
            centerText("     Username must start with a letter!");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Username valid, break out of loop
        break;
    }
    
    // ==================== PASSWORD INPUT (3 attempts) ====================
    for(int attempt = 1; attempt <= 3; attempt++) {
        cout << "\t\t\t\t  Password: ";
        cin >> password;
        
        // Check empty
        if(password.empty()) {
            centerText("     Password cannot be empty!");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Check length
        if(password.length() < 6) {
            centerText("     Password too short. Minimum 6 characters required.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        if(password.length() > 20) {
            centerText("     Password too long! Maximum 20 characters allowed.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Password strength check
        bool hasUpper = false;
        bool hasLower = false;
        bool hasDigit = false;
        bool hasSpecial = false;
        
        for(int i = 0; i < password.length(); i++) {
            char c = password[i];
            if(c >= 'A' && c <= 'Z') hasUpper = true;
            else if(c >= 'a' && c <= 'z') hasLower = true;
            else if(c >= '0' && c <= '9') hasDigit = true;
            else hasSpecial = true;
        }
        
        if(!hasUpper) {
            centerText("     Password must contain at least one uppercase letter (A-Z)!");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        if(!hasLower) {
            centerText("     Password must contain at least one lowercase letter (a-z)!");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        if(!hasDigit) {
            centerText("     Password must contain at least one number (0-9)!");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        if(!hasSpecial) {
            centerText("     Password must contain at least one special character (!@#$%^&*)!");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Check for common weak passwords
        string weakPasswords[] = {"password", "123456", "qwerty", "admin", "letmein", "welcome", "hello"};
        bool isWeak = false;
        for(int i = 0; i < 7; i++) {
            if(password == weakPasswords[i]) {
                isWeak = true;
                break;
            }
        }
        
        if(isWeak) {
            centerText("     Password is too weak! Choose a stronger password.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Password valid, break out of loop
        break;
    }
    
    // ==================== ROLE INPUT (3 attempts) ====================
    for(int attempt = 1; attempt <= 3; attempt++) {
        cout << "\t\t\t\t  Role (owner/admin/guest): ";
        cin >> role;
        
        if(role != "owner" && role != "admin" && role != "guest") {
            centerText("     Invalid role! Please enter: owner, admin, or guest");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Role valid, break out of loop
        break;
    }
    
    if(auth->signUp(username, password, role)) {
        centerText("     Registration Successful.");
        centerText("     Please login now.");
    } else {
        centerText("     Registration Failed. Please try again.");
    }
    waitForEnter();
}
void loginUser() {
    string username, password;
    bool usernameValid = false;
    bool passwordValid = false;
    
    cout << "\n\n";
    cout<<GREEN;
    centerText("               LOGIN                    ");
    cout<<RESET;
    
    // ==================== USERNAME INPUT (3 attempts) ====================
    for(int attempt = 1; attempt <= 3; attempt++) {
        cout << "\t\t\t\t  Username: ";
        cin >> username;
        
        if(username.empty()) {
            centerText("     Username cannot be empty.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        if(username.length() < 3 || username.length() > 20) {
            centerText("     Username must be 3-20 characters.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Username valid, break from loop
        usernameValid = true;
        break;
    }
    
    // If username validation failed, return
    if(!usernameValid) {
        return;
    }
    
    // ==================== PASSWORD INPUT (3 attempts) ====================
    for(int attempt = 1; attempt <= 3; attempt++) {
        cout << "\t\t\t\t  Password: ";
        cin >> password;
        
        if(password.empty()) {
            centerText("     Password cannot be empty.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        if(password.length() < 6 || password.length() > 20) {
            centerText("     Password must be 6-20 characters.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
        
        // Password format valid, now check authentication
        if(auth->login(username, password)) {
            isLoggedIn = true;
            centerText("     Login Successful.");
            
            string ownerName = auth->getCurrentUser();
            myHome = new SmartHome(1, ownerName, "HomeWiFi");
            centerText("     Smart Home Initialized for " + ownerName);
            waitForEnter();
            return;
        } else {
            // Authentication failed
            centerText("     Invalid credentials.");
            if(attempt == 3) {
                centerText("     Maximum attempts reached. Returning to menu...");
                waitForEnter();
                return;
            }
            centerText("     Attempt " + to_string(attempt) + " of 3 failed. Try again.");
            continue;
        }
    }
    
    waitForEnter();
}

void addDevice() {
    
    if(totalDevices >= MAX_TOTAL_DEVICES) {
        centerText(" Maximum device limit reached.");
        waitForEnter();
        return;
    }
    
    cout << "\n\n";
    cout<<GREEN;
    centerText("            ADD NEW DEVICE               ");
    cout<<RESET;
    
    centerText("  Device Types:");
    centerText("    1 SmartLight");
    centerText("    2 Thermostat");
    centerText("    3 SecurityCamera");
    centerText("    4 SmartLock");
    centerText("    5 SmartSpeaker");
   
    
    int type, id;
    string name, location;
    
    // ==================== DEVICE TYPE VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter device type (1-5): ";
        if(!(cin >> type)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Enter a number between 1 and 5.");
            continue;
        }
        if(type < 1 || type > 5) {
            centerText("     Device type must be between 1 and 5.");
            continue;
        }
        break;
    }
    
    // ==================== DEVICE ID VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter device ID: ";
        if(!(cin >> id)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Device ID must be a number.");
            continue;
        }
        if(id <= 0) {
            centerText("     Device ID must be a positive number.");
            continue;
        }
        if(findDeviceByID(id) != nullptr) {
            centerText("     Device ID " + to_string(id) + " already exists.");
            continue;
        }
        break;
    }
    
    cin.ignore();
    
    // ==================== DEVICE NAME VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter device name: ";
        getline(cin, name);
        
        if(name.empty()) {
            centerText("     Device name cannot be empty.");
            continue;
        }
        if(name.length() < 2) {
            centerText("     Device name too short. Minimum 2 characters.");
            continue;
        }
        if(name.length() > 30) {
            centerText("     Device name too long. Maximum 30 characters.");
            continue;
        }
        
        bool validChars = true;
        for(int i = 0; i < name.length(); i++) {
            char c = name[i];
            if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ' || c == '-')) {
                validChars = false;
                break;
            }
        }
        if(!validChars) {
            centerText("     Device name can only contain letters, spaces, and hyphens.");
            continue;
        }
        break;
    }
    
    // ==================== LOCATION VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter location: ";
        getline(cin, location);
        
        if(location.empty()) {
            centerText("     Location cannot be empty.");
            continue;
        }
        if(location.length() < 2) {
            centerText("     Location too short. Minimum 2 characters.");
            continue;
        }
        if(location.length() > 40) {
            centerText("     Location too long. Maximum 40 characters.");
            continue;
        }
        
        bool validChars = true;
        for(int i = 0; i < location.length(); i++) {
            char c = location[i];
            if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || 
                 (c >= '0' && c <= '9') || c == ' ' || c == '-' || c == ',' || c == '.')) {
                validChars = false;
                break;
            }
        }
        if(!validChars) {
            centerText("     Location can only contain letters, numbers, spaces, hyphens, commas, and dots.");
            continue;
        }
        break;
    }
    
    SmartDevice* device = nullptr;
    
    switch(type) {
        case 1: {
            int brightness;
            while(true) {
                cout << "\t\t\t\t  Enter brightness (0 to 100): ";
                if(!(cin >> brightness)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    centerText("     Invalid input. Enter a number between 0 and 100.");
                    continue;
                }
                if(brightness < 0 || brightness > 100) {
                    centerText("     Brightness must be between 0 and 100.");
                    continue;
                }
                break;
            }
            device = new SmartLight(id, name, location);
            SmartLight* light = dynamic_cast<SmartLight*>(device);
            if(light) light->setBrightness(brightness);
            break;
        }
        case 2: {
            float temp;
            string mode;
            
            while(true) {
                cout << "\t\t\t\t  Enter target temperature (10 to 40): ";
                if(!(cin >> temp)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    centerText("     Invalid input. Enter a number.");
                    continue;
                }
                if(temp < 10 || temp > 40) {
                    centerText("     Temperature must be between 10 and 40.");
                    continue;
                }
                break;
            }
            
            while(true) {
                cout << "\t\t\t\t  Enter mode (heat/cool/auto): ";
                cin >> mode;
                
                for(int i = 0; i < mode.length(); i++) {
                    mode[i] = tolower(mode[i]);
                }
                
                if(mode != "heat" && mode != "cool" && mode != "auto") {
                    centerText("     Invalid mode. Use heat, cool, or auto.");
                    continue;
                }
                break;
            }
            
            device = new Thermostat(id, name, location);
            Thermostat* thermo = dynamic_cast<Thermostat*>(device);
            if(thermo) {
                thermo->setTemperature(temp);
                thermo->changeMode(mode);
            }
            break;
        }
        case 3: {
            string resolution;
            int sensitivity;
            
            while(true) {
                cout << "\t\t\t\t  Enter resolution (720p/1080p/4K): ";
                cin >> resolution;
                
                if(resolution != "720p" && resolution != "1080p" && resolution != "4K") {
                    centerText("     Invalid resolution. Use 720p, 1080p, or 4K.");
                    continue;
                }
                break;
            }
            
            while(true) {
                cout << "\t\t\t\t  Enter motion sensitivity (1 to 10): ";
                if(!(cin >> sensitivity)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    centerText("     Invalid input. Enter a number between 1 and 10.");
                    continue;
                }
                if(sensitivity < 1 || sensitivity > 10) {
                    centerText("     Sensitivity must be between 1 and 10.");
                    continue;
                }
                break;
            }
            
            device = new SecurityCamera(id, name, location);
            SecurityCamera* cam = dynamic_cast<SecurityCamera*>(device);
            if(cam) cam->setMotionAlert(sensitivity);
            break;
        }
        case 4: {
            string code;
            
            while(true) {
                cout << "\t\t\t\t  Enter access code (4 digits): ";
                cin >> code;
                
                if(code.length() != 4) {
                    centerText("     Access code must be exactly 4 digits.");
                    continue;
                }
                
                bool isDigit = true;
                for(int i = 0; i < code.length(); i++) {
                    if(code[i] < '0' || code[i] > '9') {
                        isDigit = false;
                        break;
                    }
                }
                if(!isDigit) {
                    centerText("     Access code must contain only digits 0-9.");
                    continue;
                }
                break;
            }
            
            device = new SmartLock(id, name, location, code);
            break;
        }
        case 5: {
            int volume;
            
            while(true) {
                cout << "\t\t\t\t  Enter volume (0 to 100): ";
                if(!(cin >> volume)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    centerText("     Invalid input. Enter a number between 0 and 100.");
                    continue;
                }
                if(volume < 0 || volume > 100) {
                    centerText("     Volume must be between 0 and 100.");
                    continue;
                }
                break;
            }
            
            device = new SmartSpeaker(id, name, location);
            SmartSpeaker* speaker = dynamic_cast<SmartSpeaker*>(device);
            if(speaker) speaker->setVolume(volume);
            break;
        }
        default:
            centerText(" Invalid device type.");
            waitForEnter();
            return;
    }
    
    allDevices[totalDevices] = device;
    totalDevices++;
    
    centerText("SUCCESS Device added successfully.");
    centerText("  Total devices: " + to_string(totalDevices) + " / " + to_string(MAX_TOTAL_DEVICES));
    waitForEnter();
}
void viewAllDevices() {
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("            ALL DEVICES                  ");
    centerText("----------------------------------------");
    
    if(totalDevices == 0) {
        centerText("  No devices found.");
    } else {
        for(int i = 0; i < totalDevices; i++) {
            centerText("  " + to_string(i+1) + ". " + allDevices[i]->getStatus());
        }
        centerText("\n  Total Devices: " + to_string(totalDevices));
    }
    centerText("----------------------------------------");
    waitForEnter();
}

void toggleDevice() {
    int id;
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("            TOGGLE DEVICE                ");
    centerText("----------------------------------------");
   while(true) {
    cout << "\t\t\t\t  Enter device ID: ";
    if(!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        centerText("     Invalid input. Please enter a number.");
        continue;
    }
    break;
}
    
    SmartDevice* device = findDeviceByID(id);
    if(device != nullptr) {
        device->toggle();
        centerText("Device toggled successfully!");
    } else {
        centerText("ERROR Device not found!");
    }
    waitForEnter();
}

void updateDeviceInfo() {
    int id;
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("           UPDATE DEVICE INFO            ");
    centerText("----------------------------------------");
  while(true) {
    cout << "\t\t\t\t  Enter device ID: ";
    if(!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        centerText("     Invalid input. Please enter a number.");
        continue;
    }
    break;
}
    
    SmartDevice* device = findDeviceByID(id);
    if(device != nullptr) {
        string newName, newLocation;
        cout << "\t\t\t\t  Enter new name current " << device->getName() << ": ";
        cin.ignore();
        getline(cin, newName);
        cout << "\t\t\t\t  Enter new location current " << device->getLocation() << ": ";
        getline(cin, newLocation);
        device->setname(newName);
        device->setlocation(newLocation);
        centerText("SUCCESS Device info updated!");
    } else {
        centerText("ERROR Device not found!");
    }
    waitForEnter();
}

void removeDevice() {
    int id;
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("            REMOVE DEVICE                ");
    centerText("----------------------------------------");
       while(true) {
    cout << "\t\t\t\t  Enter device ID to remove: ";
    if(!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        centerText("     Invalid input. Please enter a number.");
        continue;
    }
    break;
}
    
    int index = findDeviceIndex(id);
    if(index != -1) {
        delete allDevices[index];
        
        for(int i = index; i < totalDevices - 1; i++) {
            allDevices[i] = allDevices[i + 1];
        }
        allDevices[totalDevices - 1] = nullptr;
        totalDevices--;
        
        centerText("SUCCESS Device removed successfully!");
    } else {
        centerText("ERROR Device not found!");
    }
    waitForEnter();
}
void createRoom() {
    int id;
    int floor;
    string name;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("            CREATE NEW ROOM              ");
    centerText("----------------------------------------");
    
    // ==================== ROOM ID VALIDATION (Integer only) ====================
    while(true) {
        cout << "\t\t\t\t  Enter room ID: ";
        if(!(cin >> id)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("      Invalid input. Room ID must be a number.");
            continue;
        }
        
        if(id <= 0) {
            centerText("      Room ID must be a positive number!");
            continue;
        }
        
        // Check if room ID already exists
        if(myHome->getRoom(id) != nullptr) {
            centerText("      Room ID " + to_string(id) + " already exists!");
            continue;
        }
        
        break;
    }
    
    cin.ignore(); // Clear input buffer
    
    // ==================== ROOM NAME VALIDATION (Alphabets + Spaces only) ====================
    while(true) {
        cout << "\t\t\t\t  Enter room name: ";
        getline(cin, name);
        
        // Check if empty
        if(name.empty()) {
            centerText("          Room name cannot be empty!");
            continue;
        }
        
        // Check length (2-30 characters)
        if(name.length() < 2) {
            centerText("      Room name too short! Minimum 2 characters.");
            continue;
        }
        
        if(name.length() > 30) {
            centerText("      Room name too long! Maximum 30 characters.");
            continue;
        }
        
        // Check if contains only alphabets and spaces
        bool validChars = true;
        for(int i = 0; i < name.length(); i++) {
            char c = name[i];
            if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
                centerText("      Room name can only contain letters (A-Z, a-z) and spaces!");
                validChars = false;
                break;
            }
        }
        
        if(!validChars) {
            centerText("      Room name can only contain letters (A-Z, a-z) and spaces!");
            continue;
        }
        
        break;
    }
    
    // ==================== FLOOR NUMBER VALIDATION (1 to 3) ====================
    while(true) {
        cout << "\t\t\t\t  Enter floor number (1 to 3): ";
        if(!(cin >> floor)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("      Invalid input. Floor number must be a number.");
            continue;
        }
        
        if(floor < 1 || floor > 3) {
            centerText("      Floor number must be between 1 and 3.");
            continue;
        }
        
        break;
    }
    
    Room* room = new Room(id, name, floor);
    myHome->addRoom(room);
    
    centerText("     Room created successfully!");
    waitForEnter();
}

void viewAllRooms() {
    myHome->showAllRooms();
    waitForEnter();
}

void addDeviceToRoom() {
    int roomId, deviceId;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("          ADD DEVICE TO ROOM             ");
    centerText("----------------------------------------");
    
    myHome->showAllRooms();
    
    // ==================== ROOM ID VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter room ID: ";
        if(!(cin >> roomId)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Room ID must be a number.");
            continue;
        }
        if(roomId <= 0) {
            centerText("     Room ID must be a positive number.");
            continue;
        }
        break;
    }
    
    // ==================== DEVICE ID VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter device ID: ";
        if(!(cin >> deviceId)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Device ID must be a number.");
            continue;
        }
        if(deviceId <= 0) {
            centerText("     Device ID must be a positive number.");
            continue;
        }
        break;
    }
    
    Room* room = myHome->getRoom(roomId);
    SmartDevice* device = findDeviceByID(deviceId);
    
    if(room != nullptr && device != nullptr) {
        room->addDevice(device);
        centerText("SUCCESS Device added to room.");
    } else {
        if(room == nullptr) {
            centerText("ERROR Room not found.");
        }
        if(device == nullptr) {
            centerText("ERROR Device not found.");
        }
    }
    waitForEnter();
}
void removeDeviceFromRoom() {
    int roomId, deviceId;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("         REMOVE DEVICE FROM ROOM         ");
    centerText("----------------------------------------");
    
    myHome->showAllRooms();
    
    // ==================== ROOM ID VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter room ID: ";
        if(!(cin >> roomId)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Room ID must be a number.");
            continue;
        }
        if(roomId <= 0) {
            centerText("     Room ID must be a positive number.");
            continue;
        }
        break;
    }
    
    // ==================== DEVICE ID VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter device ID: ";
        if(!(cin >> deviceId)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Device ID must be a number.");
            continue;
        }
        if(deviceId <= 0) {
            centerText("     Device ID must be a positive number.");
            continue;
        }
        break;
    }
    
    Room* room = myHome->getRoom(roomId);
    if(room != nullptr) {
        room->removeDevice(deviceId);
    } else {
        centerText("ERROR Room not found.");
    }
    waitForEnter();
}

void turnOffAllDevicesInRoom() {
    int roomId;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("         TURN OFF ALL IN ROOM            ");
    centerText("----------------------------------------");
    
    myHome->showAllRooms();
   while(true) {
    cout << "\t\t\t\t  Enter room ID: ";
    if(!(cin >> roomId)) {
        cin.clear();
        cin.ignore(1000, '\n');
        centerText("     Invalid input. Please enter a number.");
        continue;
    }
    break;
}
    
    Room* room = myHome->getRoom(roomId);
    if(room != nullptr) {
        room->turnAllOff();
        centerText("SUCCESS All devices turned OFF!");
    } else {
        centerText("ERROR Room not found!");
    }
    waitForEnter();
}

void getRoomStatus() {
    int roomId;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("            ROOM STATUS                  ");
    centerText("----------------------------------------");
    
    myHome->showAllRooms();
    while(true) {
        cout << "\t\t\t\t  Enter room ID: ";
        if(!(cin >> roomId)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Please enter a number.");
            continue;
        }
        break;
    }
    
    Room* room = myHome->getRoom(roomId);
    if(room != nullptr) {
        room->getRoomStatus();
    } else {
        centerText("ERROR Room not found!");
    }
    waitForEnter();
}


void createAutomationRule() {
    int id;
    string condition;
    string time;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("          CREATE AUTOMATION RULE         ");
    centerText("----------------------------------------");
    
    // ==================== RULE ID VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter rule ID: ";
        if(!(cin >> id)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Rule ID must be a number.");
            continue;
        }
        if(id <= 0) {
            centerText("     Rule ID must be a positive number.");
            continue;
        }
        // Check if rule ID already exists
        if(myHome->getAutomation(id) != nullptr) {
            centerText("     Rule ID " + to_string(id) + " already exists.");
            continue;
        }
        break;
    }
    
    // ==================== TRIGGER CONDITION VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter trigger condition (motion/motion_time/time): ";
        cin >> condition;
        
        // Convert to lowercase
        for(int i = 0; i < condition.length(); i++) {
            condition[i] = tolower(condition[i]);
        }
        
        if(condition != "motion" && condition != "motion_time" && condition != "time") {
            centerText("     Invalid condition. Use motion, motion_time, or time.");
            continue;
        }
        break;
    }
    
    // ==================== TRIGGER TIME VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter trigger time (HH:MM format, e.g., 22:00): ";
        cin >> time;
        
        // Check length (must be 5 characters)
        if(time.length() != 5) {
            centerText("     Invalid format. Use HH:MM (e.g., 22:00).");
            continue;
        }
        
        // Check colon at position 2
        if(time[2] != ':') {
            centerText("     Invalid format. Missing colon. Use HH:MM (e.g., 22:00).");
            continue;
        }
        
        // Check hours (first two characters)
        bool validHours = true;
        int hours = 0;
        if(time[0] >= '0' && time[0] <= '9' && time[1] >= '0' && time[1] <= '9') {
            hours = (time[0] - '0') * 10 + (time[1] - '0');
            if(hours < 0 || hours > 23) {
                validHours = false;
            }
        } else {
            validHours = false;
        }
        
        if(!validHours) {
            centerText("     Invalid hours. Hours must be between 00 and 23.");
            continue;
        }
        
        // Check minutes (last two characters)
        bool validMinutes = true;
        int minutes = 0;
        if(time[3] >= '0' && time[3] <= '9' && time[4] >= '0' && time[4] <= '9') {
            minutes = (time[3] - '0') * 10 + (time[4] - '0');
            if(minutes < 0 || minutes > 59) {
                validMinutes = false;
            }
        } else {
            validMinutes = false;
        }
        
        if(!validMinutes) {
            centerText("     Invalid minutes. Minutes must be between 00 and 59.");
            continue;
        }
        
        break;
    }
    
    Automation* rule = new Automation(id, condition, time);
    myHome->addAutomation(rule);
    
    centerText("SUCCESS Automation rule created successfully.");
    waitForEnter();
}

void addActionToRule() {
    int id;
    string action;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("           ADD ACTION TO RULE            ");
    centerText("----------------------------------------");
    
    myHome->showAllAutomations();
    
    // ==================== RULE ID VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter rule ID: ";
        if(!(cin >> id)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Rule ID must be a number.");
            continue;
        }
        if(id <= 0) {
            centerText("     Rule ID must be a positive number.");
            continue;
        }
        break;
    }
    
    // ==================== ACTION VALIDATION (Case Insensitive) ====================
    string validActions[] = {"turn_on_lights", "turn_off_lights", "start_recording", "send_alert", "lock_doors"};
    int validCount = 5;
    
    while(true) {
        cout << "\t\t\t\t  Enter action (turn_on_lights/turn_off_lights/start_recording/send_alert/lock_doors): ";
        cin >> action;
        
        // Convert to lowercase
        for(int i = 0; i < action.length(); i++) {
            action[i] = tolower(action[i]);
        }
        
        bool isValid = false;
        for(int i = 0; i < validCount; i++) {
            if(action == validActions[i]) {
                isValid = true;
                break;
            }
        }
        
        if(!isValid) {
            centerText("     Invalid action.");
            centerText("     Allowed actions: turn_on_lights, turn_off_lights, start_recording, send_alert, lock_doors.");
            continue;
        }
        break;
    }
    
    Automation* rule = myHome->getAutomation(id);
    if(rule != nullptr) {
        rule->addAction(action);
        centerText("     Action added successfully to Rule " + to_string(id) + ".");
    } else {
        centerText("     Rule ID " + to_string(id) + " not found.");
    }
    waitForEnter();
}

void activateAutomation() {
    int id;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("           ACTIVATE AUTOMATION           ");
    centerText("----------------------------------------");
    
    myHome->showAllAutomations();
    
    // ==================== RULE ID VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter rule ID to activate: ";
        if(!(cin >> id)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Rule ID must be a number.");
            continue;
        }
        if(id <= 0) {
            centerText("     Rule ID must be a positive number.");
            continue;
        }
        break;
    }
    
    Automation* rule = myHome->getAutomation(id);
    if(rule != nullptr) {
        if(rule->getIsActive()) {
            centerText("     Rule " + to_string(id) + " is already active.");
        } else {
            rule->activate();
            centerText("     Rule " + to_string(id) + " activated successfully.");
        }
    } else {
        centerText("     Rule ID " + to_string(id) + " not found.");
    }
    waitForEnter();
}

 void deactivateAutomation() {
    int id;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("          DEACTIVATE AUTOMATION          ");
    centerText("----------------------------------------");
    
    myHome->showAllAutomations();
    
    // ==================== RULE ID VALIDATION ====================
    while(true) {
        cout << "\t\t\t\t  Enter rule ID to deactivate: ";
        if(!(cin >> id)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("     Invalid input. Rule ID must be a number.");
            continue;
        }
        if(id <= 0) {
            centerText("     Rule ID must be a positive number.");
            continue;
        }
        break;
    }
    
    Automation* rule = myHome->getAutomation(id);
    if(rule != nullptr) {
        if(!rule->getIsActive()) {
            centerText("     Rule " + to_string(id) + " is already inactive.");
        } else {
            rule->deactivate();
            centerText("     Rule " + to_string(id) + " deactivated successfully.");
        }
    } else {
        centerText("     Rule ID " + to_string(id) + " not found.");
    }
    waitForEnter();
}

void editAutomationCondition() {
    int id;
    string newCondition;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("          EDIT AUTOMATION RULE           ");
    centerText("----------------------------------------");
    
    myHome->showAllAutomations();
    
    cout << "\t\t\t\t  Enter rule ID to edit: ";
    if(!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        centerText("      Invalid input. Please enter a numeric ID.");
        waitForEnter();
        return;
    }
    
    if(id <= 0) {
        centerText("      Rule ID must be a positive number.");
        waitForEnter();
        return;
    }
    
    Automation* rule = myHome->getAutomation(id);
    if(rule == nullptr) {
        centerText("      Rule with ID " + to_string(id) + " not found!");
        waitForEnter();
        return;
    }
    
    // ==================== STRICT VALIDATION FOR TRIGGER CONDITION ====================
    bool validCondition = false;
    string validConditions[] = {"motion", "time", "motion_time"};
    
    do {
        cout << "\t\t\t\t  Enter new trigger condition (motion/time/motion_time): ";
        cin >> newCondition;
        
        validCondition = false;
        for(int i = 0; i < 3; i++) {
            if(newCondition == validConditions[i]) {
                validCondition = true;
                break;
            }
        }
        
        if(!validCondition) {
            centerText("      Invalid condition. Please enter one of:");
            centerText("     motion, time, or motion_time");
        }
        
    } while(!validCondition);
    
    rule->editRule(newCondition);
    centerText("     Rule " + to_string(id) + " updated successfully!");
    
    waitForEnter();
}

void evaluateTrigger() {
    int id;
    string currentCondition;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("           EVALUATE TRIGGER              ");
    centerText("----------------------------------------");
    
    // Rule ID input with validation
    cout << "\t\t\t\t  Enter rule ID to evaluate: ";
    if(!(cin >> id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        centerText("     Invalid input Please enter a numeric ID.");
        waitForEnter();
        return;
    }
    
    bool validCondition = false;
   
    string validConditions[] = {"motion", "time", "none"};
    
    do {
        cout << "\t\t\t\t  Enter current condition (motion/time/none): ";
        cin >> currentCondition;
        
        // Check if input is valid
        validCondition = false;
        for(int i = 0; i < 3; i++) {
            if(currentCondition == validConditions[i]) {
                validCondition = true;
                break;
            }
        }
        
        if(!validCondition) {
            centerText("      Invalid condition. Please enter one of:");
            centerText("     motion, time, or none");
        }
        
    } while(!validCondition);
    
    Automation* rule = myHome->getAutomation(id);
    if(rule != nullptr) {
        if(rule->evaluateTrigger(currentCondition, "22:30")) {
            centerText("SUCCESS Condition matched! Actions will execute.");
            rule->executeActions(allDevices, totalDevices);
        } else {
            centerText("INFO Condition did not match.");
        }
    } else {
        centerText(" Rule not found.");
    }
    waitForEnter();
}

void displayAllRules() {
    myHome->showAllAutomations();
    waitForEnter();
}

// void removeAction() {
//     centerText("This feature is under development.");
//     waitForEnter();
// }

void logEnergyUsage() {
    int deviceId;
    float kwh;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("           LOG ENERGY USAGE              ");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter device ID: ";
    cin >> deviceId;
    cout << "\t\t\t\t  Enter kWh consumed: ";
    cin >> kwh;
    
    SmartDevice* device = findDeviceByID(deviceId);
    if(device != nullptr) {
        EnergyLog* log = new EnergyLog(device, kwh);
        log->recordUsage(kwh);
        centerText("SUCCESS Energy usage logged!");
    } else {
        centerText(" Rule not found.");
    }
    waitForEnter();
}

void viewMonthlyReport() {
    EnergyLog::showAllLogs();
    waitForEnter();
}

void compareToAverage() {
    float avg;
    centerText("----------------------------------------");
    centerText("           COMPARE TO AVERAGE            ");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter reference average kWh: ";
    cin >> avg;
    EnergyLog::compareToAverage(avg);
    waitForEnter();
}

void fullEnergyDashboard() {
    myHome->getEnergyDashboard();
    waitForEnter();
}


void lockUnlockDoor() {
    int id;
    string code;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("            LOCK UNLOCK DOOR             ");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter door lock device ID: ";
    cin >> id;
    cout << "\t\t\t\t  Enter access code: ";
    cin >> code;
    
    SmartDevice* device = findDeviceByID(id);
    if(device != nullptr) {
        SmartLock* lock = dynamic_cast<SmartLock*>(device);
        if(lock != nullptr) {
            if(lock->verifyCode(code)) {
                lock->unlock(code);
                centerText("SUCCESS Door unlocked!");
            } else {
                centerText("ERROR Wrong code!");
            }
        } else {
            centerText("ERROR Device is not a lock!");
        }
    } else {
        centerText("ERROR Device not found.");
    }
    waitForEnter();
}

void startCameraRecording() {
    int id;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("         START CAMERA RECORDING          ");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter camera device ID: ";
    cin >> id;
    
    SmartDevice* device = findDeviceByID(id);
    if(device != nullptr) {
        SecurityCamera* cam = dynamic_cast<SecurityCamera*>(device);
        if(cam != nullptr) {
            cam->startRecording();
        } else {
            centerText("ERROR Device is not a camera!");
        }
    } else {
        centerText("ERROR Device not found!");
    }
    waitForEnter();
}

void captureSnapshot() {
    int id;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("           CAPTURE SNAPSHOT              ");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter camera device ID: ";
    cin >> id;
    
    SmartDevice* device = findDeviceByID(id);
    if(device != nullptr) {
        SecurityCamera* cam = dynamic_cast<SecurityCamera*>(device);
        if(cam != nullptr) {
            cam->captureSnapshot();
        } else {
            centerText("ERROR Device is not a camera!");
        }
    } else {
        centerText("ERROR Device not found!");
    }
    waitForEnter();
}

void grantGuestAccess() {
    if(!auth->verifyRole("owner")) {
        centerText("ERROR Only owner can grant guest access!");
        waitForEnter();
        return;
    }
    
    string guestName;
    int hours;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("           GRANT GUEST ACCESS            ");
    centerText("----------------------------------------");
    
    bool validName = false;
    do {
        cout << "\t\t\t\t  Enter guest name (alphabets only): ";
        cin >> guestName;
        
        // Check if empty
        if(guestName.empty()) {
            centerText("         Guest name cannot be empty.");
            continue;
        }
        
        // Check if contains only alphabets (A-Z, a-z)
        bool onlyAlpha = true;
        for(int i = 0; i < guestName.length(); i++) {
            char c = guestName[i];
            if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
                onlyAlpha = false;
                break;
            }
        }
        
        if(!onlyAlpha) {
            centerText("     [ERROR] Guest name must contain only alphabets (A-Z, a-z)!");
            continue;
        }
        
        validName = true;
        
    } while(!validName);
    
    bool validHours = false;
    do {
        cout << "\t\t\t\t  Enter access hours (1 to 24): ";
        
        if(!(cin >> hours)) {
            cin.clear();
            cin.ignore(1000, '\n');
            centerText("      Invalid input. Please enter a number.");
            continue;
        }
        
        if(hours < 1 || hours > 24) {
            centerText("      Hours must be between 1 and 24!");
            continue;
        }
        
        validHours = true;
        
    } while(!validHours);
    
    auth->grantGuestAccess(guestName, hours);
    waitForEnter();
}

// void viewAccessHistory() {
//     int id;
    
//     cout << "\n\n";
//     centerText("----------------------------------------");
//     centerText("           VIEW ACCESS HISTORY           ");
//     centerText("----------------------------------------");
//     cout << "\t\t\t\t  Enter lock device ID: ";
//     cin >> id;
    
//     SmartDevice* device = findDeviceByID(id);
//     if(device != nullptr) {
//         SmartLock* lock = dynamic_cast<SmartLock*>(device);
//         if(lock != nullptr) {
//             lock->getAccessHistory();
//         } else {
//             centerText("ERROR Device is not a lock.");
//         }
//     } else {
//         centerText("ERROR Device not found.");
//     }
//     waitForEnter();
// }

void armDisarmCamera() {
    int id;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("           activate or deactivate CAMERA             ");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter camera device ID: ";
    cin >> id;
    
    SmartDevice* device = findDeviceByID(id);
    if(device != nullptr) {
        device->toggle();
        centerText("SUCCESS Camera toggled.");
    } else {
        centerText(" Device not found.");
    }
    waitForEnter();
}
 

void sendVoiceCommand() {
    string command;
    
    cout << "\n\n";
    centerText("----------------------------------------");
    centerText("           VOICE COMMAND SIMULATOR       ");
    centerText("----------------------------------------");
    centerText("  Available commands:");
    centerText("    - play music");
    centerText("    - volume up");
    centerText("    - volume down");
    centerText("    - weather");
    centerText("    - time");
    centerText("    - stop");
    centerText("    - hello");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter your voice command: ";
    cin.ignore();
    getline(cin, command);
    
    SmartSpeaker* speaker = nullptr;
    for(int i = 0; i < totalDevices; i++) {
        speaker = dynamic_cast<SmartSpeaker*>(allDevices[i]);
        if(speaker != nullptr) break;
    }
    
    if(speaker != nullptr) {
        speaker->triggerSkill(command);
    } else {
        centerText("ERROR No speaker device found.");
        centerText("  Please add a SmartSpeaker first.");
    }
    waitForEnter();
}

void viewConnectedServices() {
    SmartSpeaker* speaker = nullptr;
    for(int i = 0; i < totalDevices; i++) {
        speaker = dynamic_cast<SmartSpeaker*>(allDevices[i]);  // ya dynamic_cast object ko SmartSpeaker* me convert karta hai
        if(speaker != nullptr) 
        break; // agar conversion successful hua to loop se bahar aa jao
    }
    
    if(speaker != nullptr) {
        cout << "\n\n";
        centerText("----------------------------------------");
        centerText("         CONNECTED SERVICES             ");
        centerText("----------------------------------------");
        speaker->showServices();
    } else {
        centerText("ERROR No speaker device found!");
    }
    waitForEnter();
}

void changeVolume() {
    int volume;
    
    SmartSpeaker* speaker = nullptr;
    for(int i = 0; i < totalDevices; i++) {
        speaker = dynamic_cast<SmartSpeaker*>(allDevices[i]);
        if(speaker != nullptr) break;
    }
    
    if(speaker != nullptr) {
        cout << "\n\n";
        centerText("----------------------------------------");
        centerText("            CHANGE VOLUME               ");
        centerText("----------------------------------------");
        cout << "\t\t\t\t  Enter volume 0 to 100: ";
        cin >> volume;
        speaker->setVolume(volume);
    } else {
        centerText("ERROR No speaker device found!");
    }
    waitForEnter();
}


void generateAllReports() {
    centerText("----------------------------------------");
    centerText("         GENERATING ALL REPORTS          ");
    centerText("----------------------------------------");
    
    for(int i = 0; i < totalDevices; i++) {
        centerText("--- Report " + to_string(i+1) + " ---");
        allDevices[i]->generateReport();
    }
    waitForEnter();
}

void displayAllStatus() {
    centerText("----------------------------------------");
    centerText("           ALL DEVICES STATUS            ");
    centerText("----------------------------------------");
    
    for(int i = 0; i < totalDevices; i++) {
        centerText("  " + allDevices[i]->getStatus());
    }
    waitForEnter();
}

void toggleAllDevices() {   // run time ploymorphism ka demo hai
    centerText("----------------------------------------");
    centerText("         TOGGLING ALL DEVICES            ");
    centerText("----------------------------------------");
    
    for(int i = 0; i < totalDevices; i++) {
        centerText("  Toggling " + allDevices[i]->getName() + "... ");
        allDevices[i]->toggle(); //Polymorphism yahan par har device ka apna toggle behavior hoga, chahe wo light ho, thermostat ho ya camera. Sab apne hisab se toggle honge.
    }
    waitForEnter();
}

void operatorEqualDemo() {
    int id1, id2;
    
    centerText("----------------------------------------");
    centerText("          OPERATOR EQUAL                 ");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter first device ID: ";
    cin >> id1;
    cout << "\t\t\t\t  Enter second device ID: ";
    cin >> id2;
    
    SmartDevice* dev1 = findDeviceByID(id1);
    SmartDevice* dev2 = findDeviceByID(id2);
    
    if(dev1 != nullptr && dev2 != nullptr) {
        if(*dev1 == *dev2) {
            centerText("RESULT Both devices are EQUAL same ID");
        } else {
            centerText("RESULT Devices are NOT EQUAL");
        }
    } else {
        centerText("ERROR One or both devices not found.");
    }
    waitForEnter();
}

void findDeviceTemplate() {
    int type, id;
    
    centerText("----------------------------------------");
    centerText("          FIND DEVICE TEMPLATE           ");
    centerText("----------------------------------------");
    centerText("  Device types:");
    centerText("    1 SmartLight");
    centerText("    2 Thermostat");
    centerText("    3 SecurityCamera");
    centerText("    4 SmartLock");
    centerText("    5 SmartSpeaker");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter device type to search: ";
    cin >> type;
    cout << "\t\t\t\t  Enter device ID: ";
    cin >> id;
    
    SmartDevice* found = nullptr;
     

    // apni marzi ki device through template find karne ke liye dynamic_cast ka use kiya hai.
    switch(type) {
        case 1:
            found = findDeviceByID(id);
            if(found) {
                SmartLight* light = dynamic_cast<SmartLight*>(found);
                if(light) 
                centerText("FOUND " + light->getStatus());
                else 
                centerText("     Device found but not a Light.");
            }
            break;
        case 2:
            found = findDeviceByID(id);
            if(found) {
                Thermostat* thermo = dynamic_cast<Thermostat*>(found);
                if(thermo) centerText("FOUND " + thermo->getStatus());
                else 
                centerText("     Device found but not a Thermostat!");
            }
            break;
        case 3:
            found = findDeviceByID(id);
            if(found) {
                SecurityCamera* cam = dynamic_cast<SecurityCamera*>(found);
                if(cam) centerText("FOUND " + cam->getStatus());
                else 
                centerText("     Device found but not a Camera!");
            }
            break;
        default:
            centerText("ERROR Invalid type!");
    }
    
    if(found == nullptr) {
        centerText("ERROR Device not found!");
    }
    waitForEnter();
}

void showTotalDeviceCount() {
    centerText("----------------------------------------");
    centerText("         TOTAL DEVICE COUNT              ");
    centerText("----------------------------------------");
    centerText("  Static Device Count: " + to_string(SmartDevice::getTotalDeviceCount()));
    centerText("  Array Device Count: " + to_string(totalDevices));
    waitForEnter();
}

void scheduleDevice() {
    int id;
    
    centerText("----------------------------------------");
    centerText("           SCHEDULE DEVICE               ");
    centerText("----------------------------------------");
    cout << "\t\t\t\t  Enter device ID Light or Thermostat: ";
    cin >> id;
    
    SmartDevice* device = findDeviceByID(id);
    if(device != nullptr) {
        ScheduleAble* schedulable = dynamic_cast<ScheduleAble*>(device);
        if(schedulable != nullptr) {
            schedulable->schedule();
        } else {
            centerText("     This device does not support scheduling.");
        }
    } else {
        centerText("     Device not found!");
    }
    waitForEnter();
}

void cancelSchedule() {
    int id;
    
    centerText("----------------------------------------");
    centerText("           CANCEL SCHEDULE               ");
    centerText("----------------------------------------");
    
    
    cout << "\t\t\t\t  Enter device ID Light or Thermostat: ";
    if(!(cin >> id)) {
        cin.clear(); 
        cin.ignore(1000, '\n');  
        centerText("     Invalid input. Please enter a numeric ID.");
        waitForEnter();
        return;
    }
    if(id <= 0) {
        centerText("     Invalid ID. Device ID must be a positive number.");
        waitForEnter();
        return;
    }
    
    SmartDevice* device = findDeviceByID(id);
    
    if(device == nullptr) {
        centerText("     Please check the device ID and try again.");
        waitForEnter();
        return;
    }
    
    ScheduleAble* schedulable = dynamic_cast<ScheduleAble*>(device);
    if(schedulable == nullptr) {
      
        centerText("     Only SmartLight and Thermostat devices can be scheduled.");
        waitForEnter();
        return;
    }
    
    
    schedulable->cancelSchedule();
    centerText("     Schedule cancelled successfully for " + device->getName());
    
    waitForEnter();
}
// MENU HANDLERS


void handleLoginMenu(int choice) {
    switch(choice) {
        case 1:
            loginUser();
            break;
        case 2:
            registerUser();
            break;
        case 0:
        cout<<RED;
            centerText("Goodbye...");
            cout<<RESET;
            cleanupMemory();
            exit(0);
            break;
        default:
            centerText("ERROR Invalid choice!");
            waitForEnter();
    }
}

void handleMainMenu(int choice) {
    int subChoice;
    switch(choice) {
        case 1:
            do {
                clearScreen();
                displayDeviceMenu();
                cin >> subChoice;
                handleDeviceMenu(subChoice);
            } while(subChoice != 0);
            break;
        case 2:
            do {
                clearScreen();
                displayRoomMenu();
                cin >> subChoice;
                handleRoomMenu(subChoice);
            } while(subChoice != 0);
            break;
        case 3:
            do {
                clearScreen();
                displayAutomationMenu();
                cin >> subChoice;
                handleAutomationMenu(subChoice);
            } while(subChoice != 0);
            break;
        case 4:
            do {
                clearScreen();
                displayEnergyMenu();
                cin >> subChoice;
                handleEnergyMenu(subChoice);
            } while(subChoice != 0);
            break;
        case 5:
            do {
                clearScreen();
                displaySecurityMenu();
                cin >> subChoice;
                handleSecurityMenu(subChoice);
            } while(subChoice != 0);
            break;
        case 6:
            do {
                clearScreen();
                displayVoiceMenu();
                cin >> subChoice;
                handleVoiceMenu(subChoice);
            } while(subChoice != 0);
            break;
        case 7:
            do {
                clearScreen();
                displayReportsMenu();
                cin >> subChoice;
                handleReportsMenu(subChoice);
            } while(subChoice != 0);
            break;
        case 8:
            do {
                clearScreen();
                displayAdvancedMenu();
                cin >> subChoice;
                handleAdvancedMenu(subChoice);
            } while(subChoice != 0);
            break;
        case 0:
            isLoggedIn = false;
            centerText("INFO Logged out successfully.");
            break;
        default:
            centerText(" Invalid choice.");
            waitForEnter();
    }
}

void handleDeviceMenu(int choice) {
    switch(choice) {
        case 1: addDevice(); break;
        case 2: viewAllDevices(); break;
        case 3: toggleDevice(); break;
        case 4: updateDeviceInfo(); break;
        case 5: removeDevice(); break;
        case 0: break;
        default: centerText(" Invalid choice."); waitForEnter();
    }
}

void handleRoomMenu(int choice) {
    switch(choice) {
        case 1: createRoom(); break;
        case 2: viewAllRooms(); break;
        case 3: addDeviceToRoom(); break;
        case 4: removeDeviceFromRoom(); break;
        case 5: turnOffAllDevicesInRoom(); break;
        case 6: getRoomStatus(); break;
        case 0: break;
        default: centerText(" Invalid choice."); waitForEnter();
    }
}

void handleAutomationMenu(int choice) {
    switch(choice) {
        case 1: createAutomationRule(); break;
        case 2: addActionToRule(); break;
        case 3: activateAutomation(); break;
        case 4: deactivateAutomation(); break;
        case 5: editAutomationCondition(); break;
        case 6: evaluateTrigger(); break;
        case 7: displayAllRules(); break;
       // case 8: removeAction(); break;
        case 0: break;
        default: centerText(" Invalid choice.   ");
         waitForEnter();
    }
}

void handleEnergyMenu(int choice) {
    switch(choice) {
        case 1: logEnergyUsage(); break;
        case 2: viewMonthlyReport(); break;
        case 3: compareToAverage(); break;
        case 4: fullEnergyDashboard(); break;
        case 5: 
            EnergyLog::generateBill(); 
            cout << " Bill generation function completed." << endl;
            waitForEnter();
            break;
        case 0: break;
        default: centerText("     Invalid choice."); 
        waitForEnter();
    }
}

void handleSecurityMenu(int choice) {
    switch(choice) {
        case 1: lockUnlockDoor(); break;
        case 2: startCameraRecording(); break;
        case 3: captureSnapshot(); break;
        case 4: grantGuestAccess(); break;
        //case 5: viewAccessHistory(); break;
        case 5: armDisarmCamera(); break;
        case 0: break;
        default: centerText("     Invalid choice."); waitForEnter();
    }
}

void handleVoiceMenu(int choice) {
    switch(choice) {
        case 1: sendVoiceCommand(); break;
        case 2: viewConnectedServices(); break;
        case 3: changeVolume(); break;
        case 0: break;
        default: centerText("     Invalid choice.");
         waitForEnter();
    }
}

// void handleReportsMenu(int choice) {
//     switch(choice) {
//         case 1: generateAllReports(); break;
//         case 2: displayAllStatus(); break;
//         case 3: toggleAllDevices(); break;
//         case 4: operatorEqualDemo(); break;
//         case 0: break;
//         default: centerText("     Invalid choice."); waitForEnter();
//     }
// }
void handleReportsMenu(int choice) {
    switch(choice) {
        case 1: generateAllReports(); break;
        case 2: displayAllStatus(); break;
        case 3: toggleAllDevices(); break;
        case 4: operatorEqualDemo(); break;
         case 5: 
            if(myHome) {
                cout << "myHome exists, calling showHomeInfoToFile()" << endl;
                myHome->showHomeInfoToFile();
            } else {
                cout << "myHome is NULL! Cannot save report." << endl;
            }
             waitForEnter();  
            break;
        case 0: break;
        default: centerText("     Invalid choice."); waitForEnter();
    }
}

void handleAdvancedMenu(int choice) {
    switch(choice) {
        case 1: findDeviceTemplate(); break;
        case 2: showTotalDeviceCount(); break;
        case 3: scheduleDevice(); break;
        case 4: cancelSchedule(); break;
        case 0: break;
        default: centerText("     Invalid choice."); waitForEnter();
    }
}
int integerInput(int minVal, int maxVal) {
    string input = "";
    char ch;
    int value;

    while (true) {
        input = "";

        while (true) {
            ch = _getch();

            // Enter
            if (ch == 13) {
                if (!input.empty()) { cout << endl; break; }
                continue;
            }

            // Backspace
            if (ch == 8) {
                if (!input.empty()) {
                    input.pop_back();
                    cout << "\b \b";
                }
                continue;
            }

           // Digit
if (ch >= '0' && ch <= '9') {
    // Leading zero rok lo (e.g., "07"), lekin sirf "0" allow karo
    if (ch == '0' && input.empty() && minVal > 0) continue; // 0 se shuru nahi (agar min > 0)
    if (ch != '0' && input == "0") continue; // "0" ke baad aur digit nahi

    string temp = input + ch;
    int tempVal = stoi(temp);

    if (tempVal > maxVal) continue;

    input += ch;
    cout << ch;
}
        }

        if (input.empty()) {
            cout << "\n\t\t\t\t    Cannot be empty! Try again: ";
            continue;
        }

        value = stoi(input);

        if (value < minVal || value > maxVal) {
            cout << "\n\t\t\t\t    Enter between "
                 << minVal << " and " << maxVal << ": ";
            input = "";
            continue;
        }

        return value;
    }
}

int main() {
    clearScreen();
    displayWelcomeBanner();
    
    auth = new UserAuthentication();
    
    int loginChoice;
    while(!isLoggedIn) {
        displayLoginMenu();
         loginChoice = integerInput(0, 15);
        handleLoginMenu(loginChoice);
    }
    
    int mainChoice;
    while(isSystemRunning && isLoggedIn) {
        clearScreen();
        displayMainMenu();
        mainChoice = integerInput(0, 15);
        
        if(mainChoice == 0) {
            isLoggedIn = false;
            centerText("INFO Logged out successfully.");
            break;
              if(auth) {
                UserAuthentication::saveUsersToFile();
            }
            break;
        }
        
        handleMainMenu(mainChoice);
    }
    // final save before exit
    if(auth) {
        UserAuthentication::saveUsersToFile();
    }
    
    cleanupMemory();
    cout<<RED;
    centerText("All memory freed. Goodbye.");
    cout<<RESET;
    
    return 0;
}






