#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "SmartDevice.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class SecurityCamera : public SmartDevice {
private:
    string resolution;     
    bool isRecording;
    int motionSensitivity;   
    float angle;             

public:
  
    SecurityCamera(int id, string name, string location);
    
   
    ~SecurityCamera();
    

    void startRecording();
    void captureSnapshot();
    void setMotionAlert(int sensitivity);
    
  
    void toggle() override;
    string getStatus()  override;
    void generateReport()  override;
};

#endif