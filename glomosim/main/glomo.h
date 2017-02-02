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
 * $Id: glomo.h,v 1.25 2001/02/15 03:06:06 mineo Exp $
 *
 * Declaration of some functions for partition entity.
 */

#ifndef _GLOMO_H_
#define _GLOMO_H_

#include "main.h"
#include "propagation.h"
#include "driver.h"
#include "queue.h"
#include "splaytree.h"
#include "heap.h"
#include "lookahead.h"

#define MAX_CACHED_PAYLOAD_SIZE 1024

#define MAX_LOOKAHEAD_VALUE  (10 * MILLI_SECOND)
   
typedef union message_list_cell_str {
    Message messageCell;
    union message_list_cell_str* next;
} MessageListCell;

typedef union message_payload_list_cell_str {
    char payloadMemory[MAX_CACHED_PAYLOAD_SIZE];
    union message_payload_list_cell_str* next;
} MessagePayloadListCell;

typedef union splay_node_list_cell_str {
    SplayNode splayNodeCell;
    union splay_node_list_cell_str* next;
} SplayNodeListCell;

/*
 * Information kept about all partitions by
 * the Driver.
 */
struct glomo_area_str {
    ename   partitionEname; /* ename of partition */
    double  start_x;        /* starting x position */
    double  start_y;        /* starting y position */
    double  end_x;          /* ending x position */
    double  end_y;          /* ending y position */
};


struct glomo_area_nearest_str {
    ename  partitionEname;
    double nearestX;
    double nearestY;
};

struct glomo_remote_link_str {
    NODE_ADDR  sourceNodeAddr;
    NODE_ADDR  destNodeAddr;
    int        destInterfaceId;
    GlomoNode *destNodePtr;
};

typedef struct glomo_wired_partition_str {
    ename            partitionEname;
    int              numLinks;
    clocktype       *outputTime;
    GlomoRemoteLink *link;
} GlomoWiredPartition;

/*
 * typedef to GlomoPartition in main.h
 */
struct glomo_partition_str {
    int    partitionId;        // Identifier for this partition
    int    indexX;             // Index (x axis) for this partition
    int    indexY;             // Index (y axis) for this partition
    int    numPartitionsX;
    int    numPartitionsY;
    GlomoAreaInfo          thisArea; // This partition
    GlomoAreaInfo        **area;     // All the partitions
    GlomoAreaNearestInfo  *areaNearest;
    GlomoNodePositionInfo *nodePositions;

    int    numWiredPartitions;
    GlomoWiredPartition   *wiredPartition;

    double extra_x_y_padding;
    GlomoCoordinates terrainDimensions;

    GlomoNode **nodeData;      /* Information about all nodes */

    GlomoProp propData;

    /*
     * This is a pointer to a node in this partition. A node keeps pointers
     * to other nodes in the same partition.
     * If this partitcular node moves out of this partition, this variable
     * will also have to be updated.
     */
    GlomoNode       *firstNode;

    /* information about neighbors  */
    GlomoNeighbor neighborData[GLOMO_MAX_NEIGHBOR_PARTITIONS];

    
    
    
    int msgFreeListNum;
    MessageListCell *msgFreeList;
    int msgPayloadFreeListNum;
    MessagePayloadListCell *msgPayloadFreeList;
    int splayNodeFreeListNum;
    SplayNodeListCell *splayNodeFreeList;

    /*
     * Each node keeps a splay tree of all its future messages.
     * The partition keeps a heap of all the nodes in the partition,
     * so that we can easily retrieve the earliest message in this
     * particular partition.
     */
    HeapSplayTree heapSplayTree;

    /*
     * This heap represents mobility events generated for nodes
     * in this partition.
     */
    Heap mobilityInternal;
    
    /* 
    // This heap represents future mobility events leaving to
    // other partitions.  
    //
    */ 
   
    Heap mobilityOutgoing;

    FILE    *statFd;       /* file description used for statistics */
};


/*
 * The partition entity.
 */
entity GLOMOPartition(long partitionId, ename creator);


/*
 * MACRO     GLOMO_IsPartitionMember
 * PURPOSE      Determine if a node belongs to this partition.
 *
 * Parameters:
 *     pos_x:     x position of node
 *     pos_y:     y positino of node
 *     start_x:   starting x position of partition
 *     start_y:   starting y position of partition
 *     end_x:     ending x position of partition
 *     end_y:     ending y position of partition
 */
#define GLOMO_IsPartitionMember(pos_x, pos_y, start_x, start_y, end_x, end_y) \
                               ((pos_x >= start_x) && (pos_x < end_x) && \
                                (pos_y >= start_y) && (pos_y < end_y))


/*
 * FUNCTION     GLOMO_MsgSendReal
 * PURPOSE      Function call used to send a message within GlomoSim.
 *
 * Parameters:
 *    node:       node which is sending message
 *    msg:
 *    dest:       ename of destination entity
 *    delay:      delay suffered by this message.
 */
void GLOMO_MsgSendReal(GlomoNode *node, Message *msg,
                       ename dest, clocktype delay);

/*
 * FUNCTION     GLOMO_CallLayer
 * PURPOSE      Function used to call the appropriate layer to execute
 *              instructions for the message
 *
 * Parameters
 *     nodeData:     node for which message is to be delivered
 *     msgHdr:       message for which instructions are to be executed
 */
void GLOMO_CallLayer(GlomoNode *node, Message *msg);

extern clocktype PrintSimTimeInterval;
#define NUM_SIM_TIME_STATUS_PRINTS 100

#endif /* _GLOMO_H_ */

