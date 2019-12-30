/* Implementation of bank class
 *
 * Revision History
 * 12/28/19    Tim Liu    copied function headers from bank.h
 * 12/29/19    Tim Liu    filled in basic summary and transaction functions
 * 12/30/19    Tim Liu    modified show_clients to print uniform spaces 
 */


#include <map>
#include <stdio.h>
#include "bank.h"

using namespace std;


/* Name: Bank()
 * 
 * Description:  constructor for bank class 
 * Arguments:    interest (float) - interest rate paid to checking accounts
 */

Bank::Bank(float interest) {
    // set bank interest rate
    this->interest = interest;
}

/* Name: Bank()
 * 
 * Description:  destructor for bank class 
 */
Bank::~Bank() {
    printf("Closing the bank!\n");
}
    

/* Name: get_total_balance()
 * 
 * Description:  calculates the total balance held by the bank
 *               in all client accounts
 * Return:       total balance (float)
 */

float Bank::get_total_balance() {
    float sum = 0.0f;          // total bank balances 

    map<string, Client>::iterator itr;

    // iterate through client list map and sum the balances
    for (itr = client_list.begin(); itr != client_list.end(); ++itr) {
        sum += itr->second.get_balance();
    }
    return sum;
}

/* Name: get_mean()
 * 
 * Description:  calculates the mean balance held by the client bank
 *               accounts
 * Returns:      mean balance (float)
 */
float Bank::get_mean() {
    float sum = get_total_balance();       // find total balance
    return sum/client_list.size();         // divide by the number of clients
}


/* Name: new_client()
 * 
 * Description:  adds a new client to the bank's client list. The client is
 *               rejected if the name already appears in the client list
 * Arguments:    name - name of the new client
 *               balance - starting balance to place in client's account
 */
void Bank::new_client(const string &name, float balance) {

    // try to find the name in the current client list
    map<string, Client>::iterator itr = client_list.find(name);

    // check if client could not be found - open new account
    if (itr == client_list.end()) {
        Client new_client = Client(name, balance);     // create new client
        client_list.insert({name, new_client});        // add client to client_list
        return;
    }

    printf("Client already has account - new account failed\n");

}


/* Name: bank_deposit()
 * 
 * Description:  deposits money into a client's account
 *
 * Arguments:    name - name of the client
 *               amount - balance to add to client's account
 */
void Bank::bank_deposit(const string &client_name, float amount) {

    map<string, Client>::iterator client_itr = client_list.find(client_name);

    if (client_itr == client_list.end()) {
        printf("Client not found - deposit failed");
        return;
    }

    client_itr->second.deposit(amount);      // client found - deposit the amount
    return;
}


/* Name: bank_withdraw()
 * 
 * Description:  withdraw money from a client's account
 *
 * Arguments:    name - name of the client
 *               amount - balance to subtract from the client's account
 * Returns:      None
 */
void Bank::bank_withdraw(const string &client_name, float amount) {

    map<string, Client>::iterator client_itr = client_list.find(client_name);

    if (client_itr == client_list.end()) {
        printf("Client not found - withdraw failed");
        return;
    }

    client_itr->second.withdraw(amount);      // client found - deposit the amount
    return;
}


/* Name: bank_transfer()
 * 
 * Description:  transfer money from one client account to another
 *
 * Arguments:    from_client - name of the client to withdraw from
 *               to_client - name of the client to make deposit in
 *               amount - balance to move between accounts
 * Returns:      None
 */


void Bank::bank_transfer(const string &from_client, const string &to_client, float amount) {
    map<string, Client>::iterator from_client_itr = client_list.find(from_client);
    map<string, Client>::iterator to_client_itr = client_list.find(to_client);

    if (from_client_itr == client_list.end() || to_client_itr == client_list.end()) {
        printf("Client not found - transfer failed");
        return;
    }

    from_client_itr->second.withdraw(amount);       // remove money from one account
    to_client_itr->second.deposit(amount);          // add money to target account
    return;

}


/* Name: bank_pay_interest()
 * 
 * Description:  makes interest payments to all client accounts
 */

void Bank::bank_pay_interest() {
    // iterate through all clients and pay interest

    map<string, Client>::iterator itr;
    
    for (itr = client_list.begin(); itr != client_list.end(); itr++) {
        itr->second.pay_interest(interest);
    }

}

/* Name: handle_transactions()
 * 
 * Description:  removes all transactions from trans_queue and handles them
 *               sequentially
 */
void Bank::handle_transactions() {

    int num_trans = 0;

    while (!trans_queue.empty()) {
        // remove first element from the queue
        transaction t = trans_queue.front();

        switch (t.type) {
            case 0: new_client(t.client_a, t.amount);
                    break;
            case 1: bank_deposit(t.client_a, t.amount);
                    break;
            case 2: bank_withdraw(t.client_a, t.amount);
                    break;
            case 3: bank_transfer(t.client_a, t.client_b, t.amount);
                    break;
            default: printf("Transaction type not recognized %d\n", t.type);
                     break;
        }

        trans_queue.pop();      // remove handled element from the queue
        num_trans++;
    }
    printf("%d transactions handled\n", num_trans);
}

/* Name: add_transaction()
 * 
 * Description:  adds a single transaction to the transaction queue
 *
 * Arguments:    new_trans (transaction) - new transaction
 */
void Bank::add_transaction(const transaction &new_trans) {
    trans_queue.push(new_trans);
}

/* Name: show_clients()
 *
 * Description: prints the names of all clients and the balances
 *              in each account
 */
void Bank::show_clients() {
    map<string, Client>::iterator itr;

    for (itr = client_list.begin(); itr != client_list.end(); itr++) {
        Client c = itr->second;
        string name = c.get_name();
        name.append(NAME_PAD - name.length(), ' ');    // pad name with spaces to uniform length
        printf("Client: %s Balance: %5.2f\n", name.c_str(), c.get_balance());
    }
};
