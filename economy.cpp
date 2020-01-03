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
 *
 */


#include "economy.h"

using namespace std;


int main() {

    srand(RAND_SEED);            // initialize random number generator

    Bank BoT(1.0);           // initialize Bank of Tim to default interest
    //make_transactions(BoT);      // create transactions for BoT
    mass_transactions(BoT);      // create lots of transactions for BoT
    BoT.handle_transactions();   // handle all transactions
    BoT.bank_pay_interest();
    BoT.show_clients();          // print all client info :O

    return 0;
}

/* Name: make_transactions
 *
 * Description: creates a set of bank transaction orders and adds them to
 *              the passed Bank object
 *
 * Arguments:   active_bank (Bank) - reference to a bank where the transactions
 *              should be added to
 *
 */
void make_transactions(Bank &active_bank) {

    // create a bunch of new transactions
    active_bank.add_transaction(0, 100.0f, "Ben Bernanke", "x");
    active_bank.add_transaction(0, 100.0f, "Janet Yellen", "x");
    active_bank.add_transaction(1, 50.0f, "Ben Bernanke", "x");
    active_bank.add_transaction(2, 40.0f, "Janet Yellen", "x");
    active_bank.add_transaction(3, 40.0f, "Janet Yellen", "Ben Bernanke");

}


/* Name: mass_transactions
 *
 * Description: creates a large set of bank transaction orders and adds them to
 *              the passed Bank object
 *
 * Arguments:   active_bank (Bank) - reference to a bank where the transactions
 *              should be added to
 *
 */
void mass_transactions(Bank &active_bank) {

    int num_first = 0;    // number of first names
    int num_last = 0;     // number of last names

    printf("Entered mass_transactions\n");


    // read in first and last names to string array
    vector<string> first_names;
    vector<string> last_names;


    ifstream first_name_file{"first_names.txt"};         // open first name file
    ifstream last_name_file{"last_names.txt"};           // open last name file

    // check if one of the file openings failed
    if (!first_name_file) {
        printf("open failed!");
        throw invalid_argument("Couldn't open file\n");
    }

    
    // add all first names to first name vector
    while (first_name_file) {
        string new_first_name;
        first_name_file >> new_first_name;
        if (new_first_name == "") break;     // check if empty line read in

        first_names.push_back(new_first_name);
        num_first++;
    }
   
    // add all last names to the last name vector
    while (last_name_file) {
        string new_last_name;
        last_name_file >> new_last_name;
        if (new_last_name == "") break;    // check if empty line read in
        
        last_names.push_back(new_last_name);
        num_last++;
    }

    printf("First names: %d  Last names: %d\n", num_first, num_last);

    //return;

    // compact array of names that have been used
    int* name_array = (int*) calloc(num_first * num_last, sizeof(int));
    used_names compact_names = {0, name_array};    // struct for holding names compactly

    // one hot vector to track used names
    int* one_hot_names = (int*) calloc(num_first * num_last, sizeof(int));


    // Step 1 - generate a bunch of unique accounts
    for (int i = 0; i < ACCOUNT_BATCH; i++) {
        int first = rand() % num_first;          // index of first name
        int last  = rand() % num_last;           // index of last name

        int name_id = first * num_last + last;

        // check if name already taken
        if (one_hot_names[name_id] == NAME_USED) continue;

        one_hot_names[name_id] = NAME_USED;                            // mark name was used
        compact_names.name_array[compact_names.num_names] = name_id;   // add to compact list
        compact_names.num_names++;                                     // inc number of used names


        // create name string
        string new_name = first_names[first] + " " + last_names[last];

        int start_balance = (rand() % 20) * 5;                        // randomly generate start balance
        active_bank.add_transaction(0, start_balance, new_name, "x");   // add to the bank

    }

    // Stage 2 - generate a bunch of transactions
    for (int i = 0; i < TRANSACTION_BATCH; i++) {       
        int trans_code = rand() % 3 + 1;             // choose a transaction to execute; no new clients

        string c1;                                   // name of first client
        string c2;                                   // name of second client

        if (trans_code == 3) {
            get_client(compact_names, c1, first_names, last_names);    // transfer transaction - get two clients
            get_client(compact_names, c2, first_names, last_names);
        }
        else {
            get_client(compact_names, c1, first_names, last_names);    // other transaction - one client
            c2 = "x";                                                  // fill other client with blank
        }

        int amount = (rand() % 30) * 5;                              // randomly generate amount
        active_bank.add_transaction(trans_code, amount, c1, c2);       // add transaction to our bank
    }

    // free the dynamically allocated memory
    free(one_hot_names);
    free(compact_names.name_array);
}



/* Name: get_client
 *
 * Description: randomly generates the name of a client who already has
 *              an open account
 *
 * Arguments:   compact_names (used_names) - struct holding names that have been used
 *              client_name (string) - string to fill in with name of client
 *              first_names (vector) - vector of all used first names
 *              last_names (vector) - vector of all used last names
 *
 */
void get_client(const used_names &compact_names, string &client_name,
                vector<string> &first_names, vector<string> &last_names){

    int name_index = rand() % compact_names.num_names;   // choose random client name
    int name_id = compact_names.name_array[name_index];  // look up name id
    int num_last = last_names.size();                    // get number of last names

    int first = name_id/num_last;            // recover first and last name index
    int last  = name_id % num_last;

    client_name = first_names[first] + " " + last_names[last]; // fill passed string

}
