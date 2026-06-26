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