/*
 * header file for economy.h
 * 
 * Revision history
 * 12/29/19    Tim Liu    added make_transactions
 * 12/30/19    Tim Liu    added mass_transactions and used_names struct
 */

#include <queue>
#include <string>
#include <iostream>
#include <fstream>

#include <stdlib.h>    
#include <time.h>      

#include "bank.h"

#define NUM_TRANS 100      // number of transactions to generate
#define NAME_USED 88       // marker indicating a name is used

#define ACCOUNT_BATCH 256   // number of attempts at making accounts

#define RAND_SEED 7        // seed for random number generator

struct used_names {
    int num_names;
    int* name_array;
};
int main();
void make_transactions(Bank &active_bank);
void mass_transactions(Bank &active_bank);
