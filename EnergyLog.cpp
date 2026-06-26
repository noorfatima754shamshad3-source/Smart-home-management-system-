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