/*
 * header file for economy.h
 * 
 * Revision history
 * 12/29/19    Tim Liu    added make_transactions
 * 12/30/19    Tim Liu    added mass_transactions and used_names struct
 * 01/03/20    Tim Liu    moved code for generating transactions to 
 *                        transactions.h
 */


#define NUM_ACCTS 256       // number of attempts at making accounts
#define NUM_TRANS 1024      // number of transactions to issue
#define RAND_SEED 7         // seed for random number generator

#include <queue>
#include <string>

#include <stdlib.h>    
#include <time.h>      

#include "bank.h"
#include "transactions.h"


int main();
