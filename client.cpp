/* Implementation of a client
 *
 * Revision History
 * 12/29/19    Tim Liu    copied function prototypes from header file
 * 12/29/19    Tim Liu    filled in basic functions for deposit, withdraw,
 *                        constructor, and accessors  
 * 01/02/20    Tim Liu    modified depoist method to be thread safe
 *
 * TODO - change balance to be an integer instead of a float in order to
 *        use synchronization primitives
 */


#include "client.h"

// Constructor - by default balance is zero
Client::Client(const string &name, int balance) {
    client_name = name;             // set client name
    checking_balance = balance;     // set checking account balance   
}

// Destructor
Client::~Client() {
    // nothing to do
}

// Accessor for the client balance
int Client::get_balance() const {
    return checking_balance;      // return checking account balance
}

// Accessor for the client name 
string Client::get_name() const {
    return client_name;
}
  

// Deposit money into the client's account - updated to be thread safe
void Client::deposit(int amount){
    while (1) {
        int old_balance = checking_balance;      // record old balance
        int new_balance = old_balance + amount ; // calculate new balance

        // atomically swap in new value
        bool success = __sync_bool_compare_and_swap(&checking_balance, 
                                                    old_balance, 
                                                    new_balance);
        if (success){
            break;
        }
    }
}
  
// Withrdraw money from the client's account
void Client::withdraw(int amount){
    checking_balance -= amount;     //subtract set amount
}


// Pay interest to the client
// TODO - change this to account for using integers
void Client::pay_interest(int interest) {
    
    if (checking_balance > 0) {
        // only pay interest to positive balances
        checking_balance *= (1 +  interest/100);
    }

}

