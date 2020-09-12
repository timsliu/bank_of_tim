# Bank of Tim
Bank of Tim is a parallel, multi-threaded program that handles bank
transactions for a simulated bank. The Bank of Tim (BoT) is not a real bank, but
instead simulates common bank transactions with optimized software.  BoT is
written in C++14 and uses OpenMP.

# Project organization
This section describes how the project is organized and how different pieces
interact. There are several components in the Bank of Tim project:

1. The **economy** is the entry point of the program, and is where other
structures such as banks and transactions are generated.
2. A **bank** handles transactions and maintains a database of client accounts.
3. A **client** is an account at a bank.
4. Clients can make **transactions** with a bank, including deposits, 
withdrawals, and transfers between accounts.

# Implementation and Optimizations
This section describes how the bank is implemented and certain optimizations
for improving performance.

# Compilation

# Testing and Benchmarking

# Planned features
Version 1 Features
- Single threaded
- Text file with list of transactions
- Only checking accounts with fixed interest rate
- Transfers between different accounts
- Bank has unlimited capital
- Bank can generate statistics on size and distribution of money supply
- Individuals can have multiple accounts 

Version 2 Features
- Random generation of transactions
- Transactions have timestamps and interest is paid out at set times
- Multithreaded interest payout and summary of money
- Different accounts with different interest levels
- Using SIMD to accelerate interest payout

Later features
- Investment banking; account holders can hold stock
- Bank can make loans and calculates credit scores
- Multi threaded generation of transactions (worker and consumers)
- Overdraw fees and rejected transactions
- Tax collection
- Hashing user information and encryption
