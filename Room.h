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