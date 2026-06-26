#ifndef USERAUTHENTICATION_H
#define USERAUTHENTICATION_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

class UserAuthentication {
private:
    string username;
    string passwordHash;
    string role;
    bool isLoggedIn;
    string loginTime;
    
    string guestName;
    int guestAccessHours;
    time_t guestAccessStartTime;
    bool hasGuestAccess;
    
    // Validation functions
    bool isValidUsername(string user);
    bool isValidPassword(string pass);
    bool isValidRole(string r);
    bool isStrongPassword(string pass);
    string hashPassword(string pass);
    string getCurrentDate();
    bool isGuestAccessExpired();
    
    // Static members for user database
    static UserAuthentication** userDatabase;
    static int userCount;
    static int maxUsers;
    
public:
    // Constructor / Destructor
    UserAuthentication();
    ~UserAuthentication();
    
    // Core authentication methods
    bool signUp(string user, string pass, string r);
    bool login(string user, string pass);
    void logout();
    bool isLoggedInUser() const { return isLoggedIn; }
    string getCurrentUser() const { return username; }
    string getCurrentRole() const { return role; }
    string getLoginTime() const { return loginTime; }
    
    // Role verification
    bool verifyRole(string requiredRole);
    bool isOwner() const { return role == "owner"; }
    bool isAdmin() const { return role == "admin"; }
    bool isGuest() const { return role == "guest"; }
    
    // Guest access management
    bool grantGuestAccess(string guestName, int hours);
    bool revokeGuestAccess();
    bool checkGuestAccess();
    void showGuestInfo() const;
    
    // Password management
    bool changePassword(string oldPass, string newPass);
    
    // Static user management functions
    static bool addUser(string user, string pass, string role);
    static bool removeUser(string user);
    static void showAllUsers();
    static UserAuthentication* findUser(string user);
    
    // Static initialization
    static void initDatabase();
    
    friend ostream& operator<<(ostream& os, const UserAuthentication& user);
};

#endif