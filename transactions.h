/* transactions.h
 * 
 * Header file for class that generates transactions for an instance
 * of the bank class
 *
 * Revision History
 * 01/03/20    Tim Liu    created file
 */


#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <time.h>

#include "bank.h"

#define NAME_USED 88       // marker indicating a name has been used


struct used_names {
    int num_names;
    int* name_array;
};


class Transactions {
private:
    vector<string> first_names;
    vector<string> last_names;
    int add_names(vector<string> &names, const string &name_file, const string &name_type);

    int num_first;              // number of first names
    int num_last;               // number of last names
                              
    int* name_array;            // compact list of names that have been used
    used_names compact_names;   // struct holding name_array and number used
    int* one_hot_names;         // one hot vector tracking which names have been used


public:
    
    void Transactions();
    void ~Transactions();
    add_accounts(Bank &active_bank, int num_accounts);
    add_transactions(Bank &active_bank, int num_transactions);
    void small_transactions(Bank &active_bank);
    void get_client(string &client_name);
}

#endif /* TRANSACTIONS_H */
