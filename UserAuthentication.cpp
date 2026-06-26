#include "UserAuthentication.h"
#include <iomanip>
#include <cctype>


UserAuthentication** UserAuthentication::userDatabase = nullptr;
int UserAuthentication::userCount = 0;
int UserAuthentication::maxUsers = 100;


void UserAuthentication::initDatabase() {
    if(userDatabase == nullptr) {
        userDatabase = new UserAuthentication*[maxUsers];
        for(int i = 0; i < maxUsers; i++) {
            userDatabase[i] = nullptr;
        }
        
        // Create default owner account
        UserAuthentication* defaultOwner = new UserAuthentication();
        defaultOwner->username = "Noor";
        defaultOwner->passwordHash = defaultOwner->hashPassword("Admin123");
        defaultOwner->role = "owner";
        defaultOwner->isLoggedIn = false;
        userDatabase[0] = defaultOwner;
        userCount = 1;
    }
}


bool UserAuthentication::isValidUsername(string user) {
    if(user.length() == 0) {
        cout << "[ERROR] Username cannot be empty!" << endl;
        return false;
    }
    
    if(user.length() < 3) {
        cout << "[ERROR] Username too short! Minimum 3 characters required." << endl;
        return false;
    }
    
    if(user.length() > 20) {
        cout << "[ERROR] Username too long! Maximum 20 characters allowed." << endl;
        return false;
    }
    
    for(int i = 0; i < user.length(); i++) {
        char c = user[i];
        if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || 
             (c >= '0' && c <= '9') || c == '_')) {
            cout << "[ERROR] Username can only contain letters, numbers, and underscore!" << endl;
            return false;
        }
    }
    
    char firstChar = user[0];
    if(!((firstChar >= 'A' && firstChar <= 'Z') || (firstChar >= 'a' && firstChar <= 'z'))) {
        cout << "[ERROR] Username must start with a letter!" << endl;
        return false;
    }
    
    return true;
}

bool UserAuthentication::isValidPassword(string pass) {
    if(pass.length() == 0) {
        cout << "[ERROR] Password cannot be empty!" << endl;
        return false;
    }
    
    if(pass.length() < 6) {
        cout << "[ERROR] Password too short! Minimum 6 characters required." << endl;
        return false;
    }
    
    if(pass.length() > 20) {
        cout << "[ERROR] Password too long! Maximum 20 characters allowed." << endl;
        return false;
    }
    
    return true;
}

bool UserAuthentication::isStrongPassword(string pass) {
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    
    for(int i = 0; i < pass.length(); i++) {
        char c = pass[i];
        if(c >= 'A' && c <= 'Z') hasUpper = true;
        else if(c >= 'a' && c <= 'z') hasLower = true;
        else if(c >= '0' && c <= '9') hasDigit = true;
        else hasSpecial = true;
    }
    
    if(!hasUpper) {
        cout << "[WARNING] Weak password: Add at least one uppercase letter!" << endl;
        return false;
    }
    if(!hasLower) {
        cout << "[WARNING] Weak password: Add at least one lowercase letter!" << endl;
        return false;
    }
    if(!hasDigit) {
        cout << "[WARNING] Weak password: Add at least one number!" << endl;
        return false;
    }
    if(!hasSpecial) {
        cout << "[WARNING] Weak password: Add at least one special character (!@#$%^&*)!" << endl;
        return false;
    }
    
    return true;
}

bool UserAuthentication::isValidRole(string r) {
    return (r == "owner" || r == "admin" || r == "guest");
}

string UserAuthentication::hashPassword(string pass) {
    string hash = "";
    for(int i = 0; i < pass.length(); i++) {
        hash += char(pass[i] + 1);
    }
    return hash;
}

string UserAuthentication::getCurrentDate() {
    time_t now = time(0);
    string fullTime = ctime(&now);  // now ka kam ha readable bnana
    
    // ctime() returns Sun May 24 15:30:00 2026\n
    // Remove newline from end
    if(!fullTime.empty() && fullTime[fullTime.length() - 1] == '\n') {
        fullTime = fullTime.substr(0, fullTime.length() - 1);  // substring ka use mean indexing sa aik last wali remove ho sakti ha
    }
    
    return fullTime;
}

bool UserAuthentication::isGuestAccessExpired() {
    if(!hasGuestAccess) return true;
    
    time_t now = time(0);
    double diffSeconds = difftime(now, guestAccessStartTime);
    double diffHours = diffSeconds / 3600.0;
    
    return (diffHours >= guestAccessHours);
}


UserAuthentication::UserAuthentication() 
    : username(""), passwordHash(""), role("guest"), isLoggedIn(false), 
      loginTime(""), guestName(""), guestAccessHours(0), 
      guestAccessStartTime(0), hasGuestAccess(false) {
    
    initDatabase();  // Initialize static database
}

UserAuthentication::~UserAuthentication() {
}

UserAuthentication* UserAuthentication::findUser(string user) {
    for(int i = 0; i < userCount; i++) {
        if(userDatabase[i] != nullptr && userDatabase[i]->username == user) {
            return userDatabase[i];
        }
    }
    return nullptr;
}

bool UserAuthentication::addUser(string user, string pass, string role) {
    // Check if user already exists
    if(findUser(user) != nullptr) {
        cout << "[ERROR] Username already exists!" << endl;
        return false;
    }
    
    UserAuthentication* newUser = new UserAuthentication();
    newUser->username = user;
    newUser->passwordHash = newUser->hashPassword(pass);
    newUser->role = role;
    newUser->isLoggedIn = false;
    
    if(userCount < maxUsers) {
        userDatabase[userCount] = newUser;
        userCount++;
        cout << "[SUCCESS] User '" << user << "' added successfully!" << endl;
        return true;
    }
    
    cout << "[ERROR] User database is full!" << endl;
    return false;
}

bool UserAuthentication::removeUser(string user) {
    for(int i = 0; i < userCount; i++) {
        if(userDatabase[i] != nullptr && userDatabase[i]->username == user) {
            delete userDatabase[i];
            for(int j = i; j < userCount - 1; j++) {
                userDatabase[j] = userDatabase[j + 1];
            }
            userDatabase[userCount - 1] = nullptr;
            userCount--;
            cout << "[SUCCESS] User '" << user << "' removed successfully!" << endl;
            return true;
        }
    }
    
    cout << "[ERROR] User '" << user << "' not found!" << endl;
    return false;
}

void UserAuthentication::showAllUsers() {
    cout << "\n========================================" << endl;
    cout << "             ALL USERS                   " << endl;
    cout << "========================================" << endl;
    
    if(userCount == 0) {
        cout << "   No users found." << endl;
    } else {
        for(int i = 0; i < userCount; i++) {
            if(userDatabase[i] != nullptr) {
                string roleTag = (userDatabase[i]->role == "owner") ? "[OWNER]" : 
                                 (userDatabase[i]->role == "admin") ? "[ADMIN]" : "[GUEST]";
                cout << "   " << (i+1) << ". " << roleTag << " " 
                     << userDatabase[i]->username << endl;
            }
        }
    }
    cout << "========================================" << endl;
}

bool UserAuthentication::signUp(string user, string pass, string r) {
    cout << "\n========================================" << endl;
    cout << "           SIGN UP PROCESS               " << endl;
    cout << "========================================" << endl;
    
    if(!isValidUsername(user)) {
        return false;
    }
    
    // Check if username already exists
    if(findUser(user) != nullptr) {
        cout << "[ERROR] Username '" << user << "' already exists!" << endl;
        return false;
    }
    
    if(!isValidPassword(pass)) {
        return false;
    }
    
    if(!isStrongPassword(pass)) {
        cout << "[ERROR] Password is not strong enough!" << endl;
        return false;
    }
    
    if(!isValidRole(r)) {
        cout << "[ERROR] Invalid role! Use: owner, admin, or guest" << endl;
        return false;
    }
    
    // Check only one owner
    if(r == "owner") {
        for(int i = 0; i < userCount; i++) {
            if(userDatabase[i] != nullptr && userDatabase[i]->role == "owner") {
                cout << "[ERROR] An owner already exists! Only one owner allowed." << endl;
                return false;
            }
        }
    }
    
    // Create new user
    username = user;
    passwordHash = hashPassword(pass);
    role = r;
    isLoggedIn = false;
    
    // Add to database
    if(userCount < maxUsers) {
        UserAuthentication* newUser = new UserAuthentication();
        newUser->username = username;
        newUser->passwordHash = passwordHash;
        newUser->role = role;
        newUser->isLoggedIn = false;
        userDatabase[userCount] = newUser;
        userCount++;
    }
    
    cout << "\n[SUCCESS] SIGN UP SUCCESSFUL!" << endl;
    cout << "   Username: " << username << endl;
    cout << "   Role: " << role << endl;
    cout << "   Please login to continue." << endl;
    
    return true;
}


bool UserAuthentication::login(string user, string pass) {
    cout << "\n========================================" << endl;
    cout << "             LOGIN PROCESS               " << endl;
    cout << "========================================" << endl;
    
    if(isLoggedIn) {
        cout << "[WARNING] You are already logged in as '" << username << "'!" << endl;
        return false;
    }
    
    // Find user in database
    UserAuthentication* foundUser = findUser(user);
    
    if(foundUser == nullptr) {
        cout << "[ERROR] User '" << user << "' not found!" << endl;
        cout << "   Please sign up first." << endl;
        return false;
    }
    
    // Verify password
    string hashedPass = hashPassword(pass);
    if(foundUser->passwordHash != hashedPass) {
        cout << "[ERROR] Incorrect password!" << endl;
        return false;
    }
    
    // Login successful
    username = foundUser->username;
    passwordHash = foundUser->passwordHash;
    role = foundUser->role;
    isLoggedIn = true;
    loginTime = getCurrentDate();
    
    cout << "\n[SUCCESS] LOGIN SUCCESSFUL!" << endl;
    cout << "   Welcome, " << username << "!" << endl;
    cout << "   Role: " << role << endl;
    cout << "   Login Time: " << loginTime << endl;
    
    return true;
}

void UserAuthentication::logout() {
    if(!isLoggedIn) {
        cout << "[WARNING] You are not logged in!" << endl;
        return;
    }
    
    cout << "\n========================================" << endl;
    cout << "            LOGOUT PROCESS               " << endl;
    cout << "========================================" << endl;
    
    cout << "[SUCCESS] Goodbye, " << username << "!" << endl;
    cout << "   Logout Time: " << getCurrentDate() << endl;
    
    username = "";
    passwordHash = "";
    role = "guest";
    isLoggedIn = false;
    loginTime = "";
}


bool UserAuthentication::verifyRole(string requiredRole) {
    if(!isLoggedIn) {
        cout << "[ERROR] You are not logged in!" << endl;
        return false;
    }
    
    if(role == requiredRole) {
        return true;
    }
    
    if(role == "owner") {
        return true;
    }
    
    if(role == "admin" && (requiredRole == "admin" || requiredRole == "guest")) {
        return true;
    }
    
    cout << "[ERROR] Access denied! Required role: " << requiredRole << endl;
    cout << "   Your role: " << role << endl;
    return false;
}


bool UserAuthentication::grantGuestAccess(string gName, int hours) {
    if(!isLoggedIn) {
        cout << "[ERROR] You must be logged in to grant guest access!" << endl;
        return false;
    }
    
    if(!verifyRole("owner") && !verifyRole("admin")) {
        cout << "[ERROR] Only owner or admin can grant guest access!" << endl;
        return false;
    }
    
    if(hours < 1 || hours > 24) {
        cout << "[ERROR] Guest access hours must be between 1 and 24!" << endl;
        return false;
    }
    
    guestName = gName;
    guestAccessHours = hours;
    guestAccessStartTime = time(0);
    hasGuestAccess = true;
    
    cout << "\n[SUCCESS] GUEST ACCESS GRANTED!" << endl;
    cout << "   Guest Name: " << guestName << endl;
    cout << "   Access Hours: " << guestAccessHours << " hours" << endl;
    cout << "   Start Time: " << getCurrentDate() << endl;
    
    return true;
}

bool UserAuthentication::revokeGuestAccess() {
    if(!hasGuestAccess) {
        cout << "[ERROR] No active guest access to revoke!" << endl;
        return false;
    }
    
    hasGuestAccess = false;
    guestName = "";
    guestAccessHours = 0;
    
    cout << "[SUCCESS] Guest access revoked successfully!" << endl;
    return true;
}

bool UserAuthentication::checkGuestAccess() {
    if(!hasGuestAccess) return false;
    
    if(isGuestAccessExpired()) {
        cout << "[WARNING] Guest access has expired!" << endl;
        hasGuestAccess = false;
        return false;
    }
    
    time_t now = time(0);
    double remainingHours = guestAccessHours - (difftime(now, guestAccessStartTime) / 3600.0);
    
    cout << "[OK] Guest access valid! Remaining time: " << fixed << setprecision(1) 
         << remainingHours << " hours" << endl;
    
    return true;
}

void UserAuthentication::showGuestInfo() const {
    if(!hasGuestAccess) {
        cout << "No active guest access." << endl;
        return;
    }
    
    cout << "\n========================================" << endl;
    cout << "         GUEST ACCESS INFO               " << endl;
    cout << "========================================" << endl;
    cout << "   Guest Name: " << guestName << endl;
    cout << "   Access Hours: " << guestAccessHours << " hours" << endl;
    
    time_t now = time(0);
    double remaining = guestAccessHours - (difftime(now, guestAccessStartTime) / 3600.0);
    cout << "   Remaining: " << fixed << setprecision(1) << remaining << " hours" << endl;
}

// ==================== PASSWORD MANAGEMENT ====================

bool UserAuthentication::changePassword(string oldPass, string newPass) {
    if(!isLoggedIn) {
        cout << "[ERROR] You must be logged in to change password!" << endl;
        return false;
    }
    
    if(hashPassword(oldPass) != passwordHash) {
        cout << "[ERROR] Incorrect old password!" << endl;
        return false;
    }
    
    if(!isValidPassword(newPass)) {
        return false;
    }
    
    if(!isStrongPassword(newPass)) {
        cout << "[ERROR] New password is not strong enough!" << endl;
        return false;
    }
    
    passwordHash = hashPassword(newPass);
    
    // Update in database
    for(int i = 0; i < userCount; i++) {
        if(userDatabase[i] != nullptr && userDatabase[i]->username == username) {
            userDatabase[i]->passwordHash = passwordHash;
            break;
        }
    }
    
    cout << "[SUCCESS] Password changed successfully!" << endl;
    return true;
}

// ==================== OPERATOR OVERLOADING ====================

ostream& operator<<(ostream& os, const UserAuthentication& user) {
    os << "[User: " << user.username 
       << " | Role: " << user.role 
       << " | Status: " << (user.isLoggedIn ? "Online" : "Offline") << "]";
    return os;
}