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