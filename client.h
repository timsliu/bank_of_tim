/* header file for client.cpp. The client class holds the account
 * information for a single bank customer. The client class holds
 * customer and account information.
 *
 * Revision History
 * 12/28/19    Tim Liu    created file
 * 12/29/19    Tim Liu    added include<string>
 *
 */

#ifndef CLIENT_H
#define CLIENT_H

#include<string>
using namespace std;

class Client {
    int checking_balance;         // balance of customers checking account
    string client_name;             // customer name


public:

    // constructor - by default open account with no balance
    Client(const string &name, int balance);
    // destructor - currently does nothing
    ~Client();

    // accessor functions
    int get_balance() const;       // return current bank balance
    string get_name() const;         // return client name

    // additional functions and transactions supported
    void deposit(int amount);           // add money to checking account
    void withdraw(int amount);          // remove money from account
    void pay_interest(int interest);    // pay interest into this account
    


};

#endif /* CLIENT_H */


