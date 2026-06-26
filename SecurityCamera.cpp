#include "SecurityCamera.h"


SecurityCamera::SecurityCamera(int id, string name, string location)
    : SmartDevice(id, name, location, "CamFW_3.0"), 
      resolution("1080p"), 
      isRecording(false), 
      motionSensitivity(5), 
      angle(0.0) {
    cout << "SecurityCamera Created: " << getName() << endl;
}


SecurityCamera::~SecurityCamera() {
    cout << "SecurityCamera Destroyed: " << getName() << endl;
}

void SecurityCamera::startRecording() {
    if(!getIsOn()) {  // ya function sirf device on ya off ka btata ha jaisa ka ab camera ka bta raha ha

        cout << getName() << " is OFF. Cannot start recording. Turn ON first " << endl;
        return;   // yahi sa function return agr camera ON hre nhi
    }
    
    if(!isRecording) {
        isRecording = true;
        cout << getName() << " started recording at " << resolution << " resolution" << endl;
    } else {
        cout << getName() << " is already recording..." << endl;
    }
}

void SecurityCamera::captureSnapshot() {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Cannot capture snapshot. Turn ON first..." << endl;
        return;
    }

    // jab true ho ga I mean camea ON
    
    cout << getName() << " captured snapshot at " << resolution << " resolution" << endl;
    cout << "  Camera angle: " << angle << "°" << endl;
    cout << "  Snapshot saved to memory  " << endl;
}


void SecurityCamera::setMotionAlert(int sensitivity) {
    if(sensitivity < 1) {
        motionSensitivity = 1;
    } else if(sensitivity > 10) {
        motionSensitivity = 10;
    } else {
        motionSensitivity = sensitivity;
    }
    
    cout << getName() << " motion sensitivity set to " << motionSensitivity << "/10" << endl;
    
            // Alert based on sensitivity level
    if(motionSensitivity >= 8) {
        cout << "   High sensitivity mode: All movements will be detected" << endl;
    } else if(motionSensitivity <= 3) {
        cout << "   Low sensitivity mode: Only major movements detected" << endl;
    } else {
        cout << "   Normal sensitivity mode" << endl;
    }
}


void SecurityCamera::toggle() {
    setIsOn(!getIsOn());    // sab sa pahla ju function ka kam ha vo kara

    
    if(getIsOn()) {
        cout << getName() << " Security Camera activated " << endl;
        cout << "  Resolution: " << resolution << endl;
        cout << "  Motion Sensitivity: " << motionSensitivity << "/10" << endl;
        cout << "  Camera Angle: " << angle << "°" << endl;
        
        // Auto start recording when turned on
        startRecording();
    } else {
        cout << getName() << " Security Camera deactivated" << endl;
        
        if(isRecording) {
            isRecording = false;
            cout << "  Recording stopped due to power off " << endl;
        }
    }
}


string SecurityCamera::getStatus() {
    stringstream ss;
    ss << SmartDevice::getStatus()
       << "  Resolution: " << resolution
       << "  Recording: " << (isRecording ? "YES" : "NO")
       << "  Sensitivity: " << motionSensitivity << "/10"
       << "  Angle: " << angle << "°";
    return ss.str();
}

void SecurityCamera::generateReport() {
    SmartDevice::generateReport();
    cout << "Device Type: Security Camera" << endl;
    cout << "Resolution: " << resolution << endl;
    cout << "Recording Status: " << (isRecording ? "Recording in progress" : "Not recording") << endl;
    cout << "Motion Sensitivity: " << motionSensitivity << "/10" << endl;
    cout << "Camera Angle: " << angle << "°" << endl;
    
    // Additional security info
    cout << "Security Status: ";
    if(!getIsOn()) {
        cout << "OFFLINE  Camera is turned off" << endl;
    } else if(isRecording) {
        cout << "ACTIVE  Monitoring in progress" << endl;
        if(motionSensitivity >= 7) {
            cout << "   High alert mode: All motion will trigger notification" << endl;
        }
    } else {
        cout << "STANDBY  Camera is on but not recording" << endl;   
        // STANDBY ek low power state hai jahan device ON hai lekin active operation nahi kar rahi. Device ready hoti hai lekin kaam nahi kar rahi.
    }
}