/* Implementation of a client
 *
 * Revision History
 * 12/29/19    Tim Liu    copied function prototypes from header file
 */


#include "client.h"

// Constructor - by default balance is zero
Client::Client(const string &name, float balance) {
    //TODO
}

// Destructor
Client::~Client() {
    // TODO
}

// Accessor for the client balance
float Client::get_balance() const {
    // TODO
    return checking_balance;
}

// Accessor for the client name 
string Client::get_name() const {
    // TODO
    return "Ben Bernanke";
}
  

// Deposit money into the client's account
void Client::deposit(float amount){
    // TODO
}
  
// Withrdraw money from the client's account
void Client::withdraw(float amount){
    // TODO
}

// Transfer money from one client to another client account
void Client::transfer_from(float amount, Client source) {
    // TODO
}

// Pay interest to the client
void Client::pay_interest() {
    // TODO
}

