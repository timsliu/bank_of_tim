/* bank_types.h
 * Header for types that are used by the bank class and data structures
 * such as multiqueue
 *
 * Revision History
 * 12/31/19    Tim Liu    split from bank.h to avoid circular dependency
 * 01/02/20    Tim Liu    changed amount to int from float
 *
 *
 */

#ifndef BANK_TYPES_H
#define BANK_TYPES_H

#include<stdio.h>
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
    int amount;             // amount of money
    string client_a;        // 1st client name
    string client_b;        // 2nd client name
};

#endif /* BANK_TYPES_H */

