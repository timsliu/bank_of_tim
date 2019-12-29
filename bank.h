/* header file for bank.cpp. The Bank class holds a list of clients and
 * the information in their respective accounts.
 *
 * Revision History
 * 12/28/19    Tim Liu    created file
 *
 */

#include <map>
#include "client.h"

using namespace std;


class Bank {

    map<string, Client> client_list;       // list of clients - super duper private!!

public:
    // constructor - by default create a bank with 1.0% interest
    Bank(float interest=1.0f);

    // summary functions
    float get_total_balance();        // calculate total bank holdings
    float get_mean();                 // get average balance

    // actions
    void new_client(const string &name);                          // add a new client
    void bank_depost(const string &client_name, float amount);    // deposit money into a client's account
    void bank_withdraw(const string &client_name, float amount);  // withdraw money from a client account

    void bank_transfer(const string &from_client, const string &to_client, float amount);   // transfer money
    void bank_pay_interest();                                     // add interest payment to all accounts


};
