#ifndef BILL_H
#define BILL_H

#include <string>
using namespace std;

class Bill {
private:
    int billID;
    int studentID;
    double amount;
    double lateFee;
    bool isPaid;
    string dueDate;
    string issueDate;
    
public:
    Bill();
    Bill(int id, int stuID, double amt, string issue, string due);
    ~Bill();
    
    // Getters
    int getBillID() const;
    int getStudentID() const;

    // Values used in saveData()
    double getAmount() const;
    double getLateFee() const;
    string getIssueDate() const;

    double getTotalAmount() const;
    bool getIsPaid() const;
    string getDueDate() const;

    
    // Setters
    void setLateFee(double fee);
    void markAsPaid();
    void setAmount(double amt);
    
    // Calculate late fee
    void calculateLateFee(string currentDate);
    
    // Display
    void displayBill() const;
    
    // Overloaded operators
    bool operator>(const Bill& other) const;
    friend ostream& operator<<(ostream& os, const Bill& bill);
};

#endif