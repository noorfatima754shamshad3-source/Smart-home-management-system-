#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <iostream>  
using namespace std; 

class SmartDevice{
    private:
    int deviceID;
    string name;
    string location;
    bool isOn;
    string firmwareVersion;
    static int totalDeviceCount;

    public:
   

    SmartDevice();
    SmartDevice(int id, string n, string loc, string fw);
    SmartDevice(const SmartDevice &other);
    virtual ~SmartDevice();

    
    int getDeviceID() const;
    string getName() const;
    string getLocation() const;
    bool getIsOn() const;
    void setIsOn(bool status);


    void setname(string n);
    void setlocation(string n);
    

   


    virtual void toggle()=0;
    virtual string getStatus() =0;
    virtual void generateReport() =0;


     void restart();
    
   
    bool operator==(const SmartDevice &other);
    friend ostream& operator<<(ostream &out, const SmartDevice &other);
    
    
    static int getTotalDeviceCount();


 

};
#endif