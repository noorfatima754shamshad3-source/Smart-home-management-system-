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