/* header file for bank.cpp. The Bank class holds a list of clients and
 * the information in their respective accounts.
 *
 * Revision History
 * 12/28/19    Tim Liu    created file
 * 12/29/19    Tim Liu    added transaction struct
 *
 */

#include <map>
#include <queue>
#include "client.h"

#define NAME_PAD 25

using namespace std;

// struct specifying a transaction the bank needs to execute

// type transaction
//   0  open new account
//   1  deposit
//   2  withdraw
//   3  transfer
//   4  pay interest to all accounts
// 
struct transaction {
    int type;               // integer representing type of transaction
    float amount;           // amount of money
    string client_a;        // 1st client name
    string client_b;        // 2nd client name
};


class Bank {

    map<string, Client> client_list;       // list of clients - super duper private!!
    queue<transaction> trans_queue;        // queue of pending transactions for bank to handle
    float interest;                        // bank interest rate as a percent

public:
    // constructor - by default create a bank with 1.0% interest
    Bank(float interest=1.0f);
    // destructor
    ~Bank();

    // summary functions
    float get_total_balance();        // calculate total bank holdings
    float get_mean();                 // get average balance
    void show_clients();              // print all clients and balances

    // transactions
    void new_client(const string &name, float balance=0.0f);      // add a new client
    void bank_deposit(const string &client_name, float amount);   // deposit money into a client's account
    void bank_withdraw(const string &client_name, float amount);  // withdraw money from a client account

    void bank_transfer(const string &from_client, const string &to_client, float amount);   // transfer money
    void bank_pay_interest();                                     // add interest payment to all accounts

    // functions for handling transactions
    void handle_transactions();                           // performs transactions in trans_queue
    void add_transaction(const transaction &new_trans);    // add a transaction to the trans_queue

};
