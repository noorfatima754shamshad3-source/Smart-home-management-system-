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