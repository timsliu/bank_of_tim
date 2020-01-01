/* multiqueue.cpp
 * Queue that can break chunks off for different threads to operate on
 * Data structure effectively creates a bunch of fixed sized linked lists and
 * stores the heads of each list in a C++ queue
 *
 * The queue currently supports:
 * - only ONE thread adding elements
 * - multiple thread removing elements
 * - pushes and pops MUST not be mixed; can either push to or pop from 
 *   multiqueue but not both at once
 * 
 * Revision History
 * 12/31/19    Tim Liu    copied function prototypes from header and wrtoe
 *                        mQueue_push and pop
 */


#include "multiqueue.h"

/* Name: mQueue_push
 * 
 * Description: adds a new transaction to the multiqueue. Each sub-queue
 *              is a linked list that maxes out at a fixed number of 
 *              nodes (SUBQ_SIZE). The tail of each sub-queue points to NULL.
 *
 * Arguments:   m - pointer to mQueue type
 *              t - pointer to transaction struct
 *
 */

void mQueue_push(mQueue* m, transaction* t){

    Node* n = new Node;           // allocate a new node
    n->trans = t;                 // set the values
    n->next = NULL;

    // node is not the first element of a sub-Q
    if (m->inserts != 0) {
        m->tail->next = n;       // point old tail to n
    }
    else {
        m->heads.push(n);        // this node is a new head of a sub-Q
    }

    m->tail = n;                 // update the tail
    m->inserts = (m->inserts + 1) % SUBQ_SIZE;  // increment and wrap
}

/* Name: mQueue_pop
 *
 * Description: returns the head of the next subqueue created by
 *              the multiqueue; if there is nothing in the queue,
 *              then NULL is returned
 *
 * Arguments:   m - pointer to a multiqueue
 * Returns:     head - pointer to the start of a sub-queue; returns NULL
 *                     if no elements have been added to the multiqueue
 *
 */

Node* mQueue_pop(mQueue* m) {
    m->qlock->lock();           // take lock on the heads queue

    if (m->heads.empty()) {     // queue is empty - return NULL
        return NULL;
    }

    Node* head = m->heads.front();
    m->heads.pop();

    // TODO - to support simultaneous operations, set insert to 0

    m->qlock->unlock();
    return head;
}
