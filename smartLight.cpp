#include "SmartLight.h"


SmartLight::SmartLight(int id, string n, string loc)
    : SmartDevice(id, n, loc, "LightFW_2.0"), 
      brightness(100), 
      colorTemperature(4000), 
      hexColor("white") {
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