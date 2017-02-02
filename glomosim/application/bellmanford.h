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
 * $Id: bellmanford.h,v 1.5 1999/09/05 04:28:37 jmartin Exp $
 *
 * PURPOSE:         Simulate the Bellman-Ford routing protocol in the
 *                  network layer.
 *
 * NOTE:            This implementation has no notion of a "request" or
 *                  "response" as described in RIP.
 */

#ifndef _BELLMANFORD_H_
#define _BELLMANFORD_H_

/* Routing table timeout. */
#define ROUTING_BELLMANFORD_TIMEOUT                     (60 * SECOND)

/* RIP implementation. */
#define ROUTING_BELLMANFORD_INFINITY                    16

/* Periodic braoadcasting of routing tables at this interval. */
#define ROUTING_BELLMANFORD_BC_TIMER                    (10 * SECOND)

/* Used to avoid synchronization of routing table updates. */
#define ROUTING_BELLMANFORD_RANDOM_TIMER                (100 * MILLI_SECOND)

/* Don't broadcast route change to neighbor if routing table
 * is going to be broadcasted within this value.
 */
#define ROUTING_BELLMANFORD_TRIGGER_UPDATE_TIMER        (100 * MILLI_SECOND)

#define ROUTING_BELLMANFORD_PKT_HEADER_SIZE            20

/* Make sure this plus header is less than MAX_APP_DATA_UNIT. */
#define ROUTING_BELLMANFORD_MAX_BROADCAST_RT_SIZE      512

#define ROUTING_BELLMANFORD_BROADCAST_RT_ENTRY_SIZE (sizeof(RoutingBellmanfordBroadcastRoutingTableRow))

#define ROUTING_BELLMANFORD_NUM_OF_BROADCAST_RT_ENTRY (ROUTING_BELLMANFORD_MAX_BROADCAST_RT_SIZE / ROUTING_BELLMANFORD_BROADCAST_RT_ENTRY_SIZE)


/* Describes one entry in routing table. */
typedef struct  RoutingBellmanfordRoutingTableRow_t 
{
    /* Node id of the next hop node. */
    NODE_ADDR nextHop;

    /* This distance is measured in terms of number of hops. */
    short dist;

    /* Used to determine if routing information is old. */
    clocktype lastModified;

    /* Used to trigger updates if route info changed. */
    BOOL routeChanged;
} RoutingBellmanfordRoutingTableRow;


/* Describes routing table information for all nodes. */
typedef struct RoutingBellmanfordRoutingTable_t 
{
    /* Time when the next routing table broadcast will take place. */
    clocktype nextRTBroadcast;

    /* Tells if a triggered update occured. */
    BOOL triggeredUpdate;

    /* One row for each destination. */
    RoutingBellmanfordRoutingTableRow *row; 
} RoutingBellmanfordRoutingTable;


/* 
 * Describes one entry in routing table that is broadcasted
 * for routing table updates.
 */
typedef struct RoutingBellmanfordBroadcastRoutingTableRow_t 
{
    /* Destination node. */
    NODE_ADDR destAddr;

    /* 
     * Not needed in specification, but needed here
     * due to protocol using broadcast instead of
     * flooding for wireless networks.  Needed for
     * split horizon with poisoned reverse.
     */
    NODE_ADDR nextHop;

    /* Distance to destination node. */
    int dist;

    /* Used to pad memory when memory usage of this struct is not aligned. */
    int padding;
} RoutingBellmanfordBroadcastRoutingTableRow;


typedef struct RoutingBellmanfordHeader_t
{
    /* Source address. */
    NODE_ADDR sourceAddr;

    /* Destination address. */
    NODE_ADDR destAddr;

    /* Size of payload. */
    int payloadSize;
} RoutingBellmanfordHeader;


/*
 * For statistics and measurements.
 */
typedef struct RoutingBellmanfordRoutingStats_t 
{
    /* Total number of routing table broadcasts. */
    int numRTBroadcast;   

    /* Total number of triggered routing table updates. */
    int numTriggerUpdate;

    /* Total number of routing table updates. */
    int numRTUpdate;      

    /* Total number of packets received from Transport Layer. */
    int numFromUdp;

} RoutingBellmanfordRoutingStats;


/* Bellmanford data structure. */
typedef struct glomo_routing_bellmanford_str 
{
    /* Keeps track of routing tables of all nodes. */
    RoutingBellmanfordRoutingTable routeTable;

    /* Keeps track of different network statistics. */
    RoutingBellmanfordRoutingStats stats;
} GlomoRoutingBellmanford;




/*
 * NAME:        RoutingBellmanfordLayer.
 *
 * PURPOSE:     Handles all messages sent to bellmandford.
 *
 * PARAMETERS:  nodePtr, node receiving message.
 *              msg, message for node to interpret.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordLayer(GlomoNode *nodePtr,
                             Message *msg);


/*
 * NAME:        RoutingBellmanfordInit.
 *
 * PURPOSE:     Handling all initializations needed by bellmanford.
 *
 * PARAMETERS:  nodePtr, node doing the initialization.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordInit(GlomoNode *nodePtr);


/*
 * NAME:        RoutingBellmanfordFinalize.
 *
 * PURPOSE:     Handling all finalization needed by bellmanford.
 *
 * PARAMETERS:  nodePtr, node doing the finalization.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordFinalize(GlomoNode *nodePtr);



/*
 * NAME:        RoutingBellmanfordHandleRTPacket.
 *
 * PURPOSE:     Decide what to do when a routing table packet arrives.
 *
 * PARAMETERS:  nodePtr, node handling the data packet.
 *              header, header of routing table packet.
 *              payload, routing table packet. 
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordHandleRTPacket(GlomoNode *nodePtr, 
                                      RoutingBellmanfordHeader *header,
                                      char *payload);


/*
 * NAME:        RoutingBellmanfordInitRoutingTable.
 *
 * PURPOSE:     Initialize the routing table of a node.
 *
 * PARAMETERS:  nodePtr, node which routing table is initialized.
 *              routeTablePtr, routing table of this node.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordInitRoutingTable(GlomoNode *nodePtr, 
                            RoutingBellmanfordRoutingTable *routeTablePtr);


/*
 * NAME:        RoutingBellmanfordBuildHeader.
 *
 * PURPOSE:     Builds the routing layer header.
 *
 * PARAMETERS:  sourceId, source sending the packet.
 *              destId, destination of the packet to be sent.
 *              payloadSize, size of the payload.
 *
 * RETURN:      A routing header.
 *
 * ASSUMPTION:  None.
 */

RoutingBellmanfordHeader
RoutingBellmanfordBuildHeader(NODE_ADDR sourceAddr,
                              NODE_ADDR destAddr,
                              int payloadSize);


/*
 * NAME:        RoutingBellmanfordPrintBroadcastRoutingTable.
 *
 * PURPOSE:     Print the routing table that was broadcasted.
 *              Used for debugging purposes only.
 *
 * PARAMETERS:  nodePtr, node that routing table belongs to.
 *              neighRTPtr, routing table broadcasted by neighbor.
 *              numOfRTEntries, number of routing table entreis in
 *                              neighbor routing table.
 *
 * RETRUN: None. 
 * 
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordPrintBroadcastRoutingTable(GlomoNode *nodePtr,
                    RoutingBellmanfordBroadcastRoutingTableRow *neighRTPtr,
                    int numOfRTEntries);


/*
 * NAME:        RoutingBellmanfordPrintRoutingTable.
 *
 * PURPOSE:     Print the routing table entries of all nodes.  Used for
 *              debugging purposes only.
 *
 * PARAMETERS:  nodePtr, node that routing table belongs to.
 *              routeTablePtr, routing table to be printed.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordPrintRoutingTable(GlomoNode *nodePtr, 
                            RoutingBellmanfordRoutingTable *routeTablePtr);


/*
 * NAME:        RoutingBellmanfordBroadcastTriggerUpdate.
 *
 * PURPOSE:     Broadcasts the routing table due to triggered updates.
 *
 * PARAMETERS:  nodePtr, node that is broadcasting the routing table.
 *              routeTablePtr, routing table for all nodes.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordBroadcastTriggerUpdate(GlomoNode *nodePtr,
                            RoutingBellmanfordRoutingTable *routeTablePtr);


/*
 * NAME:        RoutingBellmanfordBroadcastRoutingTable.
 *
 * PURPOSE:     Broadcasts the routing table of the node to all its neighbors.
 *
 * PARAMETERS:  nodePtr, node that is broadcasting the routing table.
 *              routeTablePtr, routing table for all nodes.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordBroadcastRoutingTable(GlomoNode *nodePtr,
                           RoutingBellmanfordRoutingTable *routeTablePtr);


/*
 * NAME:        RoutingBellmanfordHandleRoutingTableTO.
 *
 * PURPOSE:     Takes care of routing table timeouts.
 *
 * PARAMETERS:  nodePtr, node that is handle the routing table
 *                       timeouts.
 *              routeTablePtr, routing table for all nodes.
 *
 * RETURN: None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordHandleRoutingTableTO(GlomoNode *nodePtr,
                            RoutingBellmanfordRoutingTable *routeTablePtr);


/*
 * NAME:        RoutingBellmanfordUpdateRoutingTable.
 *
 * PURPOSE:     Updates the routing table of the node using the neighbor's 
 *              routing table broadcast.
 *
 * PARAMETERS:  nodePtr, node that is going to update its routing table.
 *              neighborId, neighboring node that broadcasted the
 *                          routing table update.
 *              numOfRTEntries, number of routing table entries in
 *                              neighboring node's broadcasted
 *                              routing table update.
 *              routeTablePtr, routing table for all nodes.
 *              neighRTPtr, routing table entries from neighbor node.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordUpdateRoutingTable(GlomoNode *nodePtr, 
                    NODE_ADDR neighborAddr,
                    int numOfRTEntries, 
                    RoutingBellmanfordRoutingTable *routeTablePtr, 
                    RoutingBellmanfordBroadcastRoutingTableRow *neighRTPtr);

/*
 * NAME:        RoutingBellmanfordHandleRouteChange.
 *
 * PURPOSE:     Trigger routing tabe updates to neighbors when route
 *              is changed.
 *
 * PARAMETERS:  nodePtr, node that is handling the route change.
 *              routeTablePtr, routing table for all nodes.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordHandleRouteChange(GlomoNode *nodePtr,
                            RoutingBellmanfordRoutingTable *routeTablePtr);


/*
 * NAME:        RoutingBellmanfordRoutingTableLookUp.
 *
 * PURPOSE:     Forwards a packet to the next hop node.  The packet is
 *              dropped if the destination is unreachable.
 *
 * PARAMETERS:  destId, node packet is to be sent to.
 *              routeTablePtr, routing table for all nodes.
 *
 * RETURN:      The next hop node of the routing table referring
 *              to the routing table of this node for a packet whose
 *              destination is given by destId.
 *
 * ASSUMPTION:  None.
 */

int RoutingBellmanfordRoutingTableLookUp(NODE_ADDR destAddr,
                                RoutingBellmanfordRoutingTable *routeTablePtr);



/*
 * NAME:        RoutingBellmanfordInitRoutingStats.
 *
 * PURPOSE:     Initialize all network layer statistics.
 *
 * PARAMETERS:  nodePtr, node keeping track of the statistics.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordInitRoutingStats(GlomoNode *node);


/*
 * NAME:        RoutingBellmanfordPrintRoutingStats.
 *
 * PURPOSE:     Print networks layer statistics.
 *
 * PARAMETERS:  nodePtr, statistics of the node.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingBellmanfordPrintRoutingStats(GlomoNode *nodePtr);


#endif /* _BELLMANFORD_H_ */

