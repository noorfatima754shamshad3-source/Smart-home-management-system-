#include "SmartSpeaker.h"

// Constructor
SmartSpeaker::SmartSpeaker(int id, string name, string location)
    : SmartAppliance(id, name, location, 15.0), volume(50), activeSkill("none"), serviceCount(0) {
    
    for(int i = 0; i < 10; i++) {             // like "spotify"  rtc
        connectedServices[i] = "";
    }
    
    addService("Spotify");
    addService("Amazon Music");
    
    cout << "SmartSpeaker Created: " << getName() << endl;
}

SmartSpeaker::~SmartSpeaker() {
    cout << "SmartSpeaker Destroyed: " << getName() << endl;
}


void SmartSpeaker::playMusic(string song) {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Turn ON first.." << endl;
        return;
    }
    
    activeSkill = "music";
    cout << "\n Playing: " << song << endl;
    cout << "   Volume: " << volume << "%" << endl;
}

void SmartSpeaker::setVolume(int v) {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Turn ON first..." << endl;
        return;
    }
    
    if(v < 0) 
    volume = 0;
    else if(v > 100) 
    volume = 100;
    else 
    volume = v;
    
    cout << "Volume: " << volume << "%" << endl;
    
    
}

     // Simple function to check if a word exists in command ->  word (Play)
bool containsWord(string command, string word) {
        // Convert both to lowercase for comparison
    for(int i = 0; i < command.length(); i++) {
        if(command[i] >= 'A' && command[i] <= 'Z') {
            command[i] = command[i] + 32;
        }
    }
    for(int i = 0; i < word.length(); i++) {
        if(word[i] >= 'A' && word[i] <= 'Z') {
            word[i] = word[i] + 32;
        }
    }
    
    // Check if word exists in command 
    for(int i = 0; i <= command.length() - word.length(); i++) {
        bool found = true;
        for(int j = 0; j < word.length(); j++) {
            if(command[i + j] != word[j]) {        
                found = false;
                break;
            }
        }
        if(found) {
            return true;      // word mil gaya

        }
    }
    return false;      // word nhi mila 
}

         // ya function to get word after "play"
string getSongName(string command) {
    string song = "";
    bool afterPlay = false;
    
           // Convert to lowercase
    for(int i = 0; i < command.length(); i++) {
        if(command[i] >= 'A' && command[i] <= 'Z') {
            command[i] = command[i] + 32;
        }
    }
    
            // Find "play" and get after it
    for(int i = 0; i <= command.length() - 4; i++) {
        if(command[i] == 'p' && command[i+1] == 'l' && command[i+2] == 'a' && command[i+3] == 'y') {
            afterPlay = true;
            i = i + 4; // Skip "play"
            // Skip spaces
            while(i < command.length() && command[i] == ' ') {
                i++;
            }
            // Get the song name
            while(i < command.length()) {  // after play..
                song = song + command[i];      
                i++;
            }
            break;
        }
    }
    
    if(song == "") {
        song = "some music";
    }
    
    return song;
}

// Voice command simulation like play music
void SmartSpeaker::triggerSkill(string command) {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Turn ON first.." << endl;
        return;
    }
    
    cout << "\n========================================" << endl;
    cout << "  VOICE COMMAND: \"" << command << "\"" << endl;
    cout << "========================================" << endl;
    
           // Check for PLAY command
    if(containsWord(command, "play")) {
        string song = getSongName(command);
        playMusic(song);
    }
    
     // Check for VOLUME UP
    else if(containsWord(command, "volume") && containsWord(command, "up")) {
        setVolume(volume + 10);
    }
    
         // Check for VOLUME DOWN
    else if(containsWord(command, "volume") && containsWord(command, "down")) {
        setVolume(volume - 10);
    }
    
           // Check for MUTE
    else if(containsWord(command, "mute")) {
        setVolume(0);
    }
    
            // Check for WEATHER
    else if(containsWord(command, "weather")) {
        activeSkill = "weather";
        cout << "\nChecking weather..." << endl;
        cout << "   Today: Sunny " << endl;
    }
    
  // Check for TIME
    else if(containsWord(command, "time")) {
        activeSkill = "time";
        cout << "\n Current time: " << endl;
        time_t now = time(0);
        cout << "   " << ctime(&now);
    }
    
    // Check for STOP
    else if(containsWord(command, "stop")) {
        activeSkill = "none";
        cout << "\n Playback stopped" << endl;
    }
    
             // Check for HELLO
    else if(containsWord(command, "hello") || containsWord(command, "hi")) {
        activeSkill = "assistant";
        cout << "\n Hello! Ma ap ki kia help karo..." << endl;
    }
    // Unknown command
    else {
        cout << "\n Command not recognized...." << endl;
        cout << "   Only Valid Commands are -> play, volume up, volume down, mute, weather, time, stop, hello" << endl;
    }
    
    
}

     
void SmartSpeaker::addService(string service) {
    if(serviceCount < 10) {
        connectedServices[serviceCount] = service;
        serviceCount++;
    }
}


void SmartSpeaker::showServices() const {
    for(int i = 0; i < serviceCount; i++) {
        cout << connectedServices[i];
        if(i < serviceCount - 1) cout << ", ";
    }
    cout << endl;
}


void SmartSpeaker::startCycle() {
    if(!getIsOn()) {
        cout << getName() << " is OFF. Turn ON first ..." << endl;
        return;
    }
    
    cout << "\n=== SMART SPEAKER STARTUP ===" << endl;
    cout << "Initializing..." << endl;
    cout << "Volume: " << volume << "%" << endl;
    cout << "Connected services: ";
    showServices();
    cout << "Ready for voice commands!" << endl;
}


string SmartSpeaker::getStatus() {
    stringstream ss;
    ss << SmartAppliance::getStatus()
       << "  Volume: " << volume << "%"
       << "  Mode: " << activeSkill;
    return ss.str();
}


void SmartSpeaker::generateReport() {
    SmartAppliance::generateReport();
    cout << "Device Type: SmartSpeaker" << endl;
    cout << "Volume: " << volume << "%" << endl;
    cout << "Active Skill: " << activeSkill << endl;
    cout << "Services: ";
    showServices();
}