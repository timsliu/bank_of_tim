/* Implementation of bank class
 *
 * Revision History
 * 12/28/19    Tim Liu    copied function headers from bank.h
 */


#include <map>
#include "client.h"
#include "bank.h"

using namespace std;


// Bank constructor
Bank::Bank() {
    //TODO
}

// Bank destructor
Bank::~Bank() {
    //TODO
}
    
float Bank::get_total_balance() {
    // TODO
    return 0.0f;
}

float Bank::get_mean() {
    // TODO
    return 0.0f;
}
void Bank::new_client(const string &name) {
    // TODO

}
void Bank::bank_depost(const string &client_name, float amount) {
    // TODO
}
void Bank::bank_withdraw(const string &client_name, float amount) {
    // TODO
}

void Bank::bank_transfer(const string &from_client, const string &to_client, float amount) {
    // TODO
}
void Bank::bank_pay_interest() {
    // TODO
}
