/* transactions.cpp
 *
 * Class for generating new transactions of different types
 *
 * Revision History
 * 01/03/20    Tim Liu    copied functions for generating transactions
 *                        from economy.cpp
 * 01/04/20    Tim Liu    fixed duplicate names name_file
 *
 */


#include <vector>

#include "transactions.h"
#include "bank.h"


/* Name: Transactions (constructor)
 * 
 * Description: Constructor for the transactions class. Calls add_names to build
 *              vectors of first and last names and allocates memory for arrays
 *              holding which names have been used.
 *
 */

Transactions::Transactions(string city_name) {

    this->city_name = city_name;

    // parse the name files
    num_first = add_names(first_names, "first_names.txt", "first");
    num_last  = add_names(last_names, "last_names.txt", "last");


    // compact array of names that have been used
    name_array = (int*) calloc(num_first * num_last, sizeof(int));
    compact_names = {0, name_array};    // struct for holding names compactly

    // one hot vector to track used names
    one_hot_names = (int*) calloc(num_first * num_last, sizeof(int));
}


/* Name: Transactions (destructor)
 * 
 * Description: Destructor for the transactions class. Frees memory that was 
 *              dynamically allocated for name_array and one_hot_names
 *
 */
Transactions::~Transactions() {
    free(name_array);
    free(one_hot_names);
}


/* Name: add_names
 *
 * Description: opens a text file of names and parses the contents; adds each line
 *              of the passed file to a vector of names
 *
 * Arguments:   names - vector to fill with names
 *              name_file - file to open and parse
 *              name_type - "first" or "last" names
 *
 */

int Transactions::add_names(vector<string> &names, const string &name_file, const string &name_type) {

    int num_names = 0;    // number of first names

    printf("Adding %s names...\n", name_type.c_str());
    printf("File name: %s\n", name_file.c_str());

    ifstream names_txt{name_file};         // open name file

    // check if the file opening failed
    if (!names_txt) {
        throw invalid_argument("Couldn't open file\n");
    }

    // add all names to the passed name vector
    while (names_txt) {
        string new_name;
        names_txt >> new_name;
        if (new_name == "") break;     // check if empty line read in

        names.push_back(new_name);
        num_names++;
    }
   
    printf("%d %s names added\n", num_names, name_type.c_str());

    //TODO - close the ifstream?

    return num_names;
}

/* Name: add_accounts
 *
 * Description: randomly generates names and opens
 *              accounts for each name in the active_bank. The checks
 *              that no duplicate names are added (the Bank class also
 *              checks for duplicates). Note that num_accounts is not
 *              the number of accounts generated but the number that are
 *              attempted; duplicates will not be generated so the actual
 *              number of accounts open will be smaller.
 *
 * Arguments:   active_bank - bank to open accounts at
 *              num_accounts - number of times to attempt opening an account
 *
 */

void Transactions::add_accounts(Bank &active_bank, int num_accounts) {


    // Generate a bunch of unique accounts
    for (int i = 0; i < num_accounts; i++) {
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

        int start_balance = (rand() % 20) * 5;                          // randomly generate start balance
        active_bank.add_transaction(0, start_balance, new_name, "x");   // add to the bank

    }
}



/* Name: add_accounts
 *
 * Description: randomly generates names and creates random transactions
 *              for each selected name. This function will only generate
 *              transactions for clients that have opened an account
 *
 * Arguments:   active_bank - bank to open accounts at
 *              num_transactions - number of transactions to create
 *
 * TODO - make the distribution of transactions tunable
 *
 */

void Transactions::add_transactions(Bank &active_bank, int num_transactions) {

    // Generate a bunch of transactions
    for (int i = 0; i < num_transactions; i++) {       
        int trans_code = rand() % 3 + 1;             // choose a transaction to execute; no new clients

        string c1;                                   // name of first client
        string c2;                                   // name of second client

        if (trans_code == 3) {
            get_client(c1);    // transfer transaction - get two clients
            get_client(c2);
        }
        else {
            get_client(c1);    // other transaction - one client
            c2 = "x";                                                  // fill other client with blank
        }

        int amount = (rand() % 30) * 5;                                // randomly generate amount
        active_bank.add_transaction(trans_code, amount, c1, c2);       // add transaction to our bank
    }
}



/* Name: get_client
 *
 * Description: randomly generates the name of a client who already has
 *              an open account
 *
 * Arguments:   client_name (string) - string to fill in with name of client
 *
 */
void Transactions::get_client(string &client_name) {

    int name_index = rand() % compact_names.num_names;   // choose random client name
    int name_id = compact_names.name_array[name_index];  // look up name id
    int num_last = last_names.size();                    // get number of last names

    int first = name_id/num_last;            // recover first and last name index
    int last  = name_id % num_last;

    client_name = first_names[first] + " " + last_names[last]; // fill passed string

}


/* Name: make_transactions
 *
 * Description: creates a small set of bank transactions and adds them to
 *              the passed Bank object. To create a large number of random
 *              transactions use add_transactions
 *
 * Arguments:   active_bank (Bank) - reference to a bank where the transactions
 *              should be added to
 *
 */
void small_transactions(Bank &active_bank) {

    // create a bunch of new transactions
    active_bank.add_transaction(0, 100.0f, "Ben Bernanke", "x");
    active_bank.add_transaction(0, 100.0f, "Janet Yellen", "x");
    active_bank.add_transaction(1, 50.0f, "Ben Bernanke", "x");
    active_bank.add_transaction(2, 40.0f, "Janet Yellen", "x");
    active_bank.add_transaction(3, 40.0f, "Janet Yellen", "Ben Bernanke");

}
