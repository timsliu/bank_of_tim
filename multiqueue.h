/* Multiheaded queue
 * 
 * Header file for multiqueue, a data structure that serially adds elements
 * to a queue and maintains a list of heads for different threads to
 * start grabbing elements from
 *
 * Revision History
 * 12/31/19    Tim Liu    created file
 */

#ifndef MULTIQUEUE_H
#define MULTIQUEUE_H

#include<queue>
#include<mutex>

#include "bank_types.h"

#define SUBQ_SIZE 64              // size of the part of the queue to be
                                  // distributed to each thread

struct Node {
    Node* next;
    transaction* trans;
};

struct mQueue {
    int inserts;                  // number of elements inserted since last head
    int chunk_size;               // number of nodes to distribue
    queue<Node*> heads;           // pointers to heads to distribute
    mutex* qlock;                 // lock for accessing heads queue
    Node* tail;                   // pointer to last element of mQueue
};


void mQueue_push(mQueue* m, transaction* t);

Node* mQueue_pop(mQueue* m);

#endif /* MULTIQUEUE_H */
