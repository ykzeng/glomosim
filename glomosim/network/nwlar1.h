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
#ifndef LAR1_H
#define LAR1_H

#include "ip.h"
#include "nwcommon.h"
#include "main.h"

#define LAR1_RREQ_JITTER           10 * MILLI_SECOND
#define LAR1_REQ_TIMEOUT           2 * SECOND
#define LAR1_SEND_BUFFER_SIZE      128
#define LAR1_MAX_ROUTE_LENGTH      9
#define LAR1_MAX_SEQ_NUM           1024
#define LAR1_REQUEST_SEEN_LIFETIME 30 * SECOND

typedef enum {
    LAR1_ROUTE_REQUEST,
    LAR1_ROUTE_REPLY,
    LAR1_ROUTE_ERROR
} LAR1_PacketType;

typedef struct lar1_location {
    long x;
    long y;
} LAR1_Location;

typedef struct lar1_rcentry {
    NODE_ADDR destAddr;
    BOOL inUse;
    BOOL valid;
    double destVelocity;
    NODE_ADDR *path;
    int pathLength;
    clocktype locationTimestamp;
    LAR1_Location destLocation;
    struct lar1_rcentry *next;
} LAR1_RouteCacheEntry;

typedef struct lar1_reqseenentry {
    NODE_ADDR sourceAddr;
    int seqNum;
    clocktype lifetime;
    struct lar1_reqseenentry *next;
} LAR1_RequestSeenEntry;

typedef struct lar1_reqsententry {
    NODE_ADDR destAddr;
    struct lar1_reqsententry *next;
} LAR1_RequestSentEntry;

typedef struct lar1_sendbufferentry {
    NODE_ADDR destAddr;
    Message *msg;
    BOOL reTx;
    clocktype times;
} LAR1_SendBufferEntry;

typedef struct lar1_zone {
    LAR1_Location bottomLeft;
    LAR1_Location topLeft;
    LAR1_Location topRight;
    LAR1_Location bottomRight;
} LAR1_Zone;

typedef struct lar1_routerequest {
    LAR1_PacketType packetType;
    NODE_ADDR sourceAddr;
    NODE_ADDR destAddr;
    BOOL flooding;
    int currentHop;
    int seqNum;
    LAR1_Zone requestZone;
} LAR1_RouteRequest;

typedef struct lar1_routereply {
    LAR1_PacketType packetType;
    NODE_ADDR sourceAddr;
    NODE_ADDR destAddr;
    int segmentLeft;
    double destVelocity;
    clocktype locationTimestamp;
    LAR1_Location destLocation;
} LAR1_RouteReply;

typedef struct lar1_routeerror {
    LAR1_PacketType packetType;
    NODE_ADDR sourceAddr;
    NODE_ADDR destAddr;
    NODE_ADDR fromHop;
    NODE_ADDR nextHop;
    int segmentLeft;
} LAR1_RouteError;

typedef struct glomo_network_lar1 {
    LAR1_RouteCacheEntry *routeCacheHead;
    LAR1_RequestSeenEntry *reqSeenHead;
    LAR1_RequestSentEntry *reqSentHead;
    LAR1_SendBufferEntry *sendBuf[LAR1_SEND_BUFFER_SIZE];

    int sendBufHead,
        sendBufTail;
    int seqNum;

    long DataPacketsSentAsSource,
         DataPacketsRelayed,
         RouteRequestsSentAsSource,
         RouteRepliesSentAsRecvr,
         RouteErrorsSentAsErrorSource,
         RouteRequestsRelayed,
         RouteRepliesRelayed,
         RouteErrorsRelayed;

    BOOL statsCollected;

} GlomoNetworkLar1;



//
// FUNCTION     NetworkLar1Init()
// PURPOSE      Initialize LAR1 Routing Protocol Dataspace
// PARAMETERS   lar1            - pointer for dataspace
//              nodeInput
//
void NetworkLar1Init(
   GlomoNode* node, 
   GlomoNetworkLar1** lar1,
   const GlomoNodeInput* nodeInput);
   
//
// FUNCTION     NetworkLar1Finalize()
// PURPOSE      Finalize statistics Collection
//
void NetworkLar1Finalize(GlomoNode *node);

//
// FUNCTION     NetworkLar1HandleProtocolPacket()
// PURPOSE      Process a LAR1 generated control packet
// PARAMETERS   msg             - The packet
//
void NetworkLar1HandleProtocolPacket(GlomoNode* node, Message* msg);

//
// FUNCTION     NetworkLar1HandleCheckTimeoutAlarm()
// PURPOSE      Process timeouts sent by LAR1 to itself
// PARAMETERS   msg             - the timer
//
void NetworkLar1HandleCheckTimeoutAlarm(GlomoNode* node, Message* msg);

//
// FUNCTION     NetworkLar1NodeInZone()
// PURPOSE      Returns TRUE if node is within the zone coordinates
// PARAMETERS   zone            - structure containing corner coordinates
//
BOOL NetworkLar1NodeInZone(GlomoNode *node, LAR1_Zone *zone);

//
// FUNCTION     NetworkLar1HandleRouteErrorPacket()
// PURPOSE      Handle received LAR1 Route Error control packets
// PARAMETERS   msg             - the control packet
//
void NetworkLar1HandleRouteErrorPacket(GlomoNode *node, Message *msg);

//
// FUNCTION     NetworkLar1HandleRouteReply()
// PURPOSE      Handle received LAR1 Route Reply control packets
// PARAMETERS   msg             - the control packet
//
void NetworkLar1HandleRouteReply(GlomoNode *node, Message *msg);

//
// FUNCTION     NetworkLar1TransmitData()
// PURPOSE      Retrieve route from route cache, transmit data packet
// PARAMETERS   outMsg          - the packet to be sent
//
void NetworkLar1TransmitData(GlomoNode *node, Message *outMsg);

//
// FUNCTION     NetworkLar1RetrieveSendBuf()
// PURPOSE      Retrieve next data packet for transmission for specified
//              destination
// PARAMETERS   destAddr        - destination node
//
Message *NetworkLar1RetrieveSendBuf(GlomoNetworkLar1 *lar1,
                                    NODE_ADDR destAddr);

//
// FUNCTION     NetworkLar1HandleRouteRequest()
// PURPOSE      Determine course of action for LAR RREQ packet
// PARAMETERS   msg     - the packet
//
void NetworkLar1HandleRouteRequest(GlomoNode *node, Message *msg);


//
// FUNCTION     NetworkLar1InitiateRouteReply()
// PURPOSE      Create and transmit LAR Route Reply packet
// PARAMETERS   oldMsg     - the original LAR Route Request packet
//
void NetworkLar1InitiateRouteReply(GlomoNode *node, Message *oldMsg);

 
//
// FUNCTION     NetworkLar1NodeInReqPath()
// PURPOSE      Return TRUE if node address appears in path array
// PARAMETERS   path    - array of NODE_ADDR
//              hopcount- number of entries in path array
//
BOOL NetworkLar1NodeInReqPath(GlomoNode *node, NODE_ADDR *path, int hopcount);

//
// FUNCTION     NetworkLar1FlushRequestSeenCache()
// PURPOSE      Remove Request Seen Cache entries older than
//              LAR1_REQUEST_SEEN_LIFETIME
// PARAMETERS   lar1            - LAR1 variable space
//

void NetworkLar1FlushRequestSeenCache(GlomoNetworkLar1 *lar1);

//
// FUNCTION     NetworkLar1InsertRequestSeen()
// PURPOSE      Insert Request source address and sequence num into cache
// PARAMETERS   sourceAddr      - source of LAR Request Packet
//              seqNum          - sequence number assigned by source
//
void NetworkLar1InsertRequestSeen(GlomoNetworkLar1 *lar1,
                                  NODE_ADDR sourceAddr,
                                  int seqNum);


//
// FUNCTION     NetworkLar1InsertRequestSent()
// PURPOSE      Insert destination address for locally generated
//              LAR Request Packet into cache
// PARAMETERS   destAddr        - destination address
//
void NetworkLar1InsertRequestSent(GlomoNetworkLar1 *lar1,
                                  NODE_ADDR destAddr);


//
// FUNCTION     NetworkLar1RemoveRequestSent()
// PURPOSE      Remove destination address for locally generated
//              LAR Request Packet from cache (Reply received)
// PARAMETERS   destAddr        - destination address
//
void NetworkLar1RemoveRequestSent(GlomoNetworkLar1 *lar1,
                                  NODE_ADDR destAddr);

//
// FUNCTION     NetworkLar1LookupRequestSeen()
// PURPOSE      Return TRUE if the (source addr, seq num) appears in cache
// PARAMETERS   sourceAddr      - source of LAR Request Packet
//              seqNum          - sequence number of LAR Request Packet
//
BOOL NetworkLar1LookupRequestSeen(LAR1_RequestSeenEntry *reqSeen,
                                  NODE_ADDR sourceAddr,
                                  int seqNum);


//
// FUNCTION     NetworkLar1PropagateRouteRequest()
// PURPOSE      Propagate a received LAR Route Request Packet
// PARAMETERS   oldMsg          - the received LAR Route Request Packet
//
void NetworkLar1PropagateRouteRequest(GlomoNode *node, Message *oldMsg);


//
// FUNCTION     NetworkLar1InitiateRouteRequest()
// PURPOSE      Initiate a new LAR Route Request Packet
// PARAMETERS   destAddr        - the destination for which route is needed
//
void NetworkLar1InitiateRouteRequest(GlomoNode *node, NODE_ADDR destAddr);

//
// FUNCTION     NetworkLar1CalculateReqZone()
// PURPOSE      Calculate and set the request zone in a LAR Request Packet
//              for a given destination
// PARAMETERS   msg             - the LAR Request Packet to be sent
//              destAddr        - the destination for which route is needed
//
BOOL NetworkLar1CalculateReqZone(GlomoNode *node, Message *msg,
                                 NODE_ADDR destAddr);


//
// FUNCTION     NetworkLar1BufferPacket()
// PURPOSE      Place packet into send buffer, awaiting valid path
//              and return TRUE if buffering is successful
// PARAMETERS   msg             - the data packet to be buffered
//              destAddr        - the destination of this data packet
//
BOOL NetworkLar1BufferPacket(GlomoNode *node, Message *msg,
                             NODE_ADDR destAddr);


//
// FUNCTION     NetworkLar1PendingRouteReq()
// PURPOSE      Return TRUE if this node has sent a LAR Route Request Packet
//              for the given destination.
// PARAMETERS   destAddr        - the destination to check
//
BOOL NetworkLar1PendingRouteReq(GlomoNode *node,
                                NODE_ADDR destAddr);

//
// FUNCTION     NetworkLar1RouteExists()
// PURPOSE      Return TRUE if this node has a valid route to the destination
// PARAMETERS   destAddr        - the destination to check
//
BOOL NetworkLar1RouteExists(LAR1_RouteCacheEntry *cacheEntry,
                            NODE_ADDR destAddr);


//
// FUNCTION     NetworkLar1RetrieveCacheEntry()
// PURPOSE      Return the Route Cache Entry for the given destination if
//              one exists.
// PARAMETERS   cacheEntry      - the head pointer of the route cache
//              destAddr        - the destination to check
//
LAR1_RouteCacheEntry *NetworkLar1RetrieveCacheEntry(
    LAR1_RouteCacheEntry *cacheEntry,
    NODE_ADDR destAddr);


//
// FUNCTION     NetworkLar1InsertRoute()
// PURPOSE      Extract route information from a LAR Route Reply Packet
//              and insert info into the Route Cache.
// PARAMETERS   pkt             - the LAR Route Reply packet
//              path            - the path given in the route reply
//              numEntries      - the number of entries in the path array
//
void NetworkLar1InsertRoute(GlomoNetworkLar1 *lar1,
                            LAR1_RouteReply *pkt,
                            NODE_ADDR *path,
                            int numEntries);


//
// FUNCTION     NetworkLar1SetTimer()
// PURPOSE      Set a timer to expire just in case a route reply is not
//              received in the allotted time.
// PARAMETERS   eventType       - the event that is triggered by the timer
//              destAddr        - the destination node that the timer is
//                                interested in
//              delay           - the delay between now and timer expiration
//
void NetworkLar1SetTimer(GlomoNode *node, long eventType, NODE_ADDR destAddr,
                         clocktype delay);


//
// FUNCTION     NetworkLar1RouterFunction()
// PURPOSE      Determine the routing action to take for a the given data
//              packet, and set the PacketWasRouted variable to TRUE if no
//              further handling of this packet by IP is necessary.
// PARAMETERS   msg             - the data packet
//              destAddr        - the destination node of this data packet
//              PacketWasRouted - variable that indicates to IP that it
//                                no longer needs to act on this data packet
//
/* The Following must match RouterFunctionType defined in nwip.h */

void NetworkLar1RouterFunction(GlomoNode* node, Message* msg,
                               NODE_ADDR destAddr, BOOL *PacketWasRouted);



//
// FUNCTION     NetworkLar1FreeCacheEntry()
// PURPOSE      Free the memory used by a route rache entry
// PARAMETERS   cacheEntry      - the entry to free
//
void NetworkLar1FreeCacheEntry(LAR1_RouteCacheEntry *cacheEntry);


//
// FUNCTION     NetworkLar1InvalidateRoutesThroughBrokenLink()
// PURPOSE      Mark as unusable routes in the cache which contain the
//              given node pair
// PARAMETERS   fromHop         - the first node in the node pair
//              toHop           - the receiving node of the node pair
//
void NetworkLar1InvalidateRoutesThroughBrokenLink(
    GlomoNode *node,
    NODE_ADDR fromHop,
    NODE_ADDR toHop);


//
// FUNCTION     NetworkLar1DeleteRoute()
// PURPOSE      Remove route to the given destination from the route cache
// PARAMETERS   destAddr        - the given destination
//
void NetworkLar1DeleteRoute(
    GlomoNode *node,
    NODE_ADDR destAddr);


//
// FUNCTION     NetworkLar1TransmitErrorPacket()
// PURPOSE      Given a packet which MAC 802.11 was unable to transmit to
//              the neighbor node listed in the source route, this function
//              will transmit to the data packet's source node, a LAR
//              Route Error indicating that the route is broken at this link.
// PARAMETERS   oldMsg          - the data packet
//              nextHop         - the nextHop to which the data packet should
//                                have gone
//
void NetworkLar1TransmitErrorPacket(GlomoNode *node, const Message *oldMsg,
                                    NODE_ADDR nextHop);

//
// FUNCTION     NetworkLar1HandleBrokenLink()
// PURPOSE      Handle message from MAC 802.11 regarding broken link
// PARAMETERS   msg             - the packet returned by MAC 802.11
//
void NetworkLar1HandleBrokenLink(GlomoNode *node, const Message *msg);


//
// FUNCTION     NetworkLar1PacketDropNotificationHandler()
// PURPOSE      Handle internal messages from MAC Layer
// PARAMETERS   msg             - the packet returned by MAC
//
void NetworkLar1PacketDropNotificationHandler(
    GlomoNode *node, const Message* msg, const NODE_ADDR nextHopAddress);


#endif

