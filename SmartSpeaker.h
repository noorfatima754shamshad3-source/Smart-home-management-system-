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