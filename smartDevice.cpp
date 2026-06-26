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
        cout << "Device name set to: " << name << endl;
    }
void SmartDevice::setlocation(string loc) { 
    location = loc;
    cout << "Device location set to: " << location << endl;
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