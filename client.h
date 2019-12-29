/* header file for client.cpp. The client class holds the account
 * information for a single bank customer. The client class holds
 * customer and account information.
 *
 * Revision History
 * 12/28/19    Tim Liu    created file
 * 12/29/19    Tim Liu    added include<string>
 *
 */

#include<string>
using namespace std;

class Client {
    float checking_balance;         // balance of customers checking account
    string client_name;             // customer name


public:

    // constructor - by default open account with no balance
    Client(const string &name, float balance=0.0f);
    // destructor - currently does nothing
    ~Client();

    // accessor functions
    float get_balance() const;       // return current bank balance
    string get_name() const;         // return client name

    // additional functions and transactions supported
    void deposit(float amount);      // add money to checking account
    void withdraw(float amount);     // remove money from account
    void transfer_from(float amount, Client source);   // transfer money from source to this
    void pay_interest();             // pay interest into this account


};


