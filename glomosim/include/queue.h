/*
 * GloMoSim is COPYRIGHTED software.  Release 2.02 of GloMoSim is available 
 * at no cost to educational users only.
 *
 * Commercial use of this software requires a separate license.  No cost,
 * evaluation licenses are available for such purposes; please contact
 * info@scalable-networks.com
 *
 * By obtaining copies of this and any other files that comprise GloMoSim2.02,
 * you, the Licensee, agree to abide by the following conditions and
 * understandings with respect to the copyrighted software:
 *
 * 1.Permission to use, copy, and modify this software and its documentation
 *   for education and non-commercial research purposes only is hereby granted
 *   to Licensee, provided that the copyright notice, the original author's
 *   names and unit identification, and this permission notice appear on all
 *   such copies, and that no charge be made for such copies. Any entity
 *   desiring permission to use this software for any commercial or
 *   non-educational research purposes should contact: 
 *
 *   Professor Rajive Bagrodia 
 *   University of California, Los Angeles 
 *   Department of Computer Science 
 *   Box 951596 
 *   3532 Boelter Hall 
 *   Los Angeles, CA 90095-1596 
 *   rajive@cs.ucla.edu
 *
 * 2.NO REPRESENTATIONS ARE MADE ABOUT THE SUITABILITY OF THE SOFTWARE FOR ANY
 *   PURPOSE. IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *
 * 3.Neither the software developers, the Parallel Computing Lab, UCLA, or any
 *   affiliate of the UC system shall be liable for any damages suffered by
 *   Licensee from the use of this software.
 */

// Use the latest version of Parsec if this line causes a compiler error.
/*
 * $Id: queue.h,v 1.6 1999/12/08 17:24:41 jmartin Exp $
 *
 * Definition of queueing structures and functions used
 * by the framework in the simulation.
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

/*
 * Field to indicate if the item being inserted into the queue
 * should be inserted in the front or the end of the queue.
 */
enum {
    QUEUE_INSERT_END = 10,
    QUEUE_INSERT_FRONT
};


/*
 * The item which will be inserted into a queue.
 * "item" refers to the user provided data item.
 * The "next" and "prev" field refer to the next
 * and previous item in the queue.
 */
typedef struct qitem_str {
    struct qitem_str *next;
    struct qitem_str *prev;
    void *item;
} QueueItem;


/*
 * The queue structure.
 * We keep pointers to the first and last items in queue.
 * We also keep a count of the number of items in queue.
 */
typedef struct q_str {
    QueueItem *first;
    QueueItem *last;
    int itemsInQueue;
    QueueItem* freeListPtr;
} Queue;



/*
 * FUNCTION     GLOMO_MessageEnqueue
 * PURPOSE      Function called by user to insert message into the queue.
 *
 * Parameters:
 *    inQueue:    the queue in which the item is to be inserted
 *    inMsg:      the message being enqueued
 *    insertPos:  the position where the item will be inserted
 */
void GLOMO_MessageEnqueue(Queue *inQueue, int insertPos,
                          void *inMsg);

/*
 * FUNCTION      GLOMO_MessageDequeue
 * PURPOSE       Function called by user to remove message from queue.
 *
 * Parameters:
 *    outQueue:   the queue from which item is dequeued
 *
 * The actual message is returned. If there are no meessages
 * currently stored in the queue NULL is returned back.
 */
void* GLOMO_MessageDequeue(Queue *outQueue);


#endif /* _QUEUE_H_ */

