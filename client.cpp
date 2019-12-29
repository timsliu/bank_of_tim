/* Implementation of a client
 *
 * Revision History
 * 12/29/19    Tim Liu    copied function prototypes from header file
 * 12/29/19    Tim Liu    filled in basic functions for deposit, withdraw,
 *                        constructor, and accessors   
 */


#include "client.h"

// Constructor - by default balance is zero
Client::Client(const string &name, float balance) {
    client_name = name;             // set client name
    checking_balance = balance;     // set checking account balance   
}

// Destructor
Client::~Client() {
    // nothing to do
}

// Accessor for the client balance
float Client::get_balance() const {
    return checking_balance;      // return checking account balance
}

// Accessor for the client name 
string Client::get_name() const {
    return client_name;
}
  

// Deposit money into the client's account
void Client::deposit(float amount){
    checking_balance += amount;    // add passed amount to account
}
  
// Withrdraw money from the client's account
void Client::withdraw(float amount){
    checking_balance -= amount;     //subtract set amount
}


// Pay interest to the client
void Client::pay_interest(float interest) {
    
    if (checking_balance > 0) {
        // only pay interest to positive balances
        checking_balance *= (1 + interest/100);
    }

}

