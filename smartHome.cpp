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