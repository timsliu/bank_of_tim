/* main file for Bank of Tim project
 *
 * Revision History
 * 12/29/19    Tim Liu    created skeleton main loop
 * 12/29/19    Tim Liu    added outline for main loop
 * 12/29/19    Tim Liu    added make_transactions
 * 12/30/19    Tim Liu    created mass_transactions for generating large
 *                        numbers of random transactions
 * 12/30/19    Tim Liu    added get_client
 * 12/31/19    Tim Liu    freed dynamically allocated memory in mass_transaction
 * 01/03/19    Tim Liu    removed code for generating transactions and moved to
 *                        transactions.cpp class
 *
 */


#include "economy.h"

using namespace std;


int main() {

    srand(RAND_SEED);                           // initialize random number generator

    Bank BoT(1.0);                              // initialize Bank of Tim to default interest
    Transactions Seattle("seattle");            // create a transactions generator for the Seattle area
    Seattle.add_accounts(BoT, NUM_ACCTS);       // add lots of accounts
    Seattle.add_transactions(BoT, NUM_TRANS);   // create lots of transactions for BoT
    
    BoT.handle_transactions();                  // handle all transactions
    BoT.bank_pay_interest();                    // pay interest - currently doesn't work
    BoT.show_clients();                         // print all client info :O

    return 0;
}






