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
#ifndef _SPLAYTREE_H_
#define _SPLAYTREE_H_

#include "main.h"

/* A Heap that determines the earliest time from a bunch of splay trees */
typedef struct heap_splay_tree_str {
    GlomoNode **heapNodePtr;
    long heapSize;
    long length;
} HeapSplayTree;



void GLOMO_HeapSplayInsert(HeapSplayTree *heapSplayTreePtr, GlomoNode *node);
void GLOMO_HeapSplayDelete(HeapSplayTree *heapSplayTreePtr, GlomoNode *node);


#define SPLAYTREE_MAX_FREE_LIST 50000

typedef struct splay_node_str {
    clocktype timeValue;
    void *msg;
    struct splay_node_str *leftPtr;
    struct splay_node_str *rightPtr;
    struct splay_node_str *parentPtr;
} SplayNode;


typedef struct splay_tree_str {
    SplayNode *rootPtr;
    SplayNode *leastPtr;
    long heapPos;
} SplayTree;


void GLOMO_SplayTreeInsert(GlomoNode *node, SplayNode *splayNodePtr);
SplayNode* GLOMO_SplayTreeExtractMin(GlomoNode *node);


#endif /* _SPLAYTREE_H_ */

