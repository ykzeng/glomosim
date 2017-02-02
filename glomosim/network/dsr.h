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
 * Name: dsr.h
 *
 * Written by S.J. Lee (sjlee@cs.ucla.edu)
 *
 */

/*
 NOTE: The parameter values followed the DSR Internet Draft and NS2 code
       released by CMU. Read the NOTE of dsr.pc for more details
*/

#ifndef _DSR_H_
#define _DSR_H_

#include "ip.h"
#include "nwcommon.h"
#include "main.h"

#define DSR_MAX_SR_LEN                  9

/* Broadcast jittering time to avoid collisions */
#define DSR_BROADCAST_JITTER            10 * MILLI_SECOND

/* Max time between route requests */
#define DSR_MAX_REQUEST_PERIOD          10 * SECOND

/* Length of one backoff period */
#define DSR_REQUEST_PERIOD              500 * MILLI_SECOND

/* TO for non propagating request */
#define DSR_RING0_REQUEST_TO            30 * MILLI_SECOND

/* Saved in Request table for this amount of time */
#define DSR_FLUSH_INTERVAL              30 * SECOND

// Maximum time a packet will be buffered waiting for a route.
#define DSR_MAX_PACKET_BUFFER_TIME       11110 * SECOND

#define DSR_MAX_TTL                      255

#define IPOPT_DSR  217

/* DSR option fields for IP header */
typedef struct {
   unsigned char salvagedBit;
   unsigned char segmentLeft;
} DsrIpOptionType;

/* Type of packet */
typedef enum {
    DSR_ROUTE_REQUEST,
    DSR_ROUTE_REPLY,
    DSR_ROUTE_ERROR
} DSR_PacketType;

typedef struct
{
    DSR_PacketType pktType;
    NODE_ADDR srcAddr;
    NODE_ADDR targetAddr;
    int seqNumber;
    int hopCount;
    NODE_ADDR path[DSR_MAX_SR_LEN];
} DSR_RouteRequest;
    
typedef struct
{
    DSR_PacketType pktType;
    NODE_ADDR targetAddr;                 /* Source of the route */
    NODE_ADDR srcAddr;                    /* Destination of the route */
    int hopCount;
    int segLeft;
    NODE_ADDR path[DSR_MAX_SR_LEN];
} DSR_RouteReply;

typedef struct
{
    DSR_PacketType pktType;
    NODE_ADDR srcAddr;                 /* Originator of the Route Error */
    NODE_ADDR destAddr;                /* Source of the broken route */
    NODE_ADDR unreachableAddr;         /* Immediate downstream of broken link */
    int hopCount;
    BOOL salvaged;
    NODE_ADDR path[DSR_MAX_SR_LEN];
} DSR_RouteError;

typedef struct RCE
{
    NODE_ADDR destAddr;
    int hopCount;                        /* Hop length to the destAddr */
    NODE_ADDR path[DSR_MAX_SR_LEN];
    struct RCE *prev;
    struct RCE *next;
} DSR_RouteCacheEntry;

typedef struct
{
    DSR_RouteCacheEntry *head;
    int count;                         /* Count of current entries */
} DSR_RouteCache;

typedef struct RQE
{
    NODE_ADDR destAddr;
    clocktype lastRequest;             /* Time when last sent a request */ 
    clocktype backoffInterval;         /* No additional Req for this time */
    int ttl;
    struct RQE *next;
} DSR_RequestTableEntry;

typedef struct
{
    DSR_RequestTableEntry *head;
    int count;
} DSR_RequestTable;
 
typedef struct STE
{
    NODE_ADDR srcAddr;
    int seqNumber;
    struct STE *next;
} DSR_RequestSeenEntry;

typedef struct
{
    DSR_RequestSeenEntry *front; 
    DSR_RequestSeenEntry *rear;
    int count; 
} DSR_RequestSeen;

typedef struct fifo
{
    NODE_ADDR destAddr;
    clocktype timestamp;
    Message *msg;
    struct fifo *next;
} DSR_BUFFER_Node;

typedef struct
{
    DSR_BUFFER_Node *head;
    int size;
} DSR_BUFFER;

typedef struct
{
    NODE_ADDR destAddr;
    int ttl;
} DSR_CR;

typedef struct
{
    /* Total number of route request packets transmitted */
    int numRequestSent;

    /* Total number of route reply packets transmitted */
    int numReplySent;

    /* Total number of route error packets transmitted */
    int numErrorSent;

    /* Total number of data packets originated as the source */
    int numDataSent;

    /* Total number of data packets tranmitted */
    int numDataTxed;

    /* Total number of data packets received as the destination */
    int numDataReceived;

    int numRoutes;

    int numHops;
    
    int numLinkBreaks;
    
    int numSalvagedPackets;
    int numDroppedPackets;
    
    
} DSR_Stats;

typedef struct glomo_network_dsr_str {
    DSR_RouteCache routeCacheTable;
    DSR_RequestTable requestTable;
    DSR_RequestSeen requestSeenTable;
    DSR_BUFFER buffer;
    int seqNumber;
    DSR_Stats stats;    
} GlomoRoutingDsr;

void RoutingDsrInit(
    GlomoNode *node, 
    GlomoRoutingDsr **dsrPtr, 
    const GlomoNodeInput *nodeInput);

void RoutingDsrFinalize(GlomoNode *node);

void RoutingDsrHandleRequest(GlomoNode *node, Message *msg, int ttl);

void RoutingDsrHandleReply(
    GlomoNode *node, Message *msg, NODE_ADDR destAddr);

void RoutingDsrHandleError(
    GlomoNode *node, Message *msg, NODE_ADDR srcAddr, NODE_ADDR destAddr);

void RoutingDsrInitRouteCache(DSR_RouteCache *routeCache);

void RoutingDsrInitRequestSeen(DSR_RequestSeen *requestSeen);

void RoutingDsrInitRequestTable(DSR_RequestTable *requestTable);

void RoutingDsrInitSeq(GlomoNode *node);

void RoutingDsrInitBuffer(DSR_BUFFER *buffer);

void RoutingDsrInitStats(GlomoNode *node);

void RoutingDsrDeleteSeenTable(DSR_RequestSeen *requestSeen);

BOOL RoutingDsrCheckRouteExist(NODE_ADDR destAddr, DSR_RouteCache *routeCache);

BOOL RoutingDsrLookupRequestSeen(NODE_ADDR srcAddr,
                                 int seq,
                                 DSR_RequestSeen *requestSeen);

BOOL RoutingDsrLookupRequestTable(NODE_ADDR destAddr,
                                  DSR_RequestTable *requestTable);

void RoutingDsrInsertRequestSeen(GlomoNode *node,
                                 NODE_ADDR srcAddr,
                                 int seq,
                                 DSR_RequestSeen *requestSeen);

void RoutingDsrInsertRouteCache(NODE_ADDR destAddr,
                                int hopCount,
                                NODE_ADDR *path,
                                DSR_RouteCache *routeCache);

DSR_RouteCacheEntry *RoutingDsrInsertRCInOrder(NODE_ADDR destAddr,
                                               int hopCount,
                                               NODE_ADDR *path,
                                               DSR_RouteCacheEntry *old,
                                               DSR_RouteCacheEntry *last);

void RoutingDsrInsertRequestTable(NODE_ADDR destAddr,
                                  DSR_RequestTable *requestTable);
 
DSR_RequestTableEntry *RoutingDsrInsertRTInOrder(NODE_ADDR destAddr,
                                                 DSR_RequestTableEntry *old);

void RoutingDsrInsertBuffer(Message *msg, NODE_ADDR destAddr,
                            DSR_BUFFER *buffer);

DSR_BUFFER_Node *RoutingDsrInsertBufInOrder(Message *msg, NODE_ADDR destAddr,
                                            DSR_BUFFER_Node *old);

BOOL RoutingDsrCompareRoute(NODE_ADDR destAddr,
                            int hopCount,
                            NODE_ADDR *path,
                            DSR_RouteCache *routeCache);
 
void RoutingDsrDeleteRouteCache(GlomoNode *node,
                                NODE_ADDR fromHop,
                                NODE_ADDR nextHop,
                                DSR_RouteCache *routeCache);


void RoutingDsrRemoveOldPacketsFromBuffer(DSR_BUFFER *buffer);

BOOL RoutingDsrDeleteBuffer(NODE_ADDR destAddr, DSR_BUFFER *buffer);

void RoutingDsrDeleteRequestTable(NODE_ADDR destAddr, 
                                  DSR_RequestTable *requestTable);

BOOL RoutingDsrCheckDataSeen(
    GlomoNode *node, NODE_ADDR *header, int currentHop);

BOOL RoutingDsrCheckRequestPath(
    GlomoNode *node, NODE_ADDR *path, int currentHop);

NODE_ADDR *RoutingDsrGetRoute(NODE_ADDR destAddr, DSR_RouteCache *routeCache);

int RoutingDsrGetHop(NODE_ADDR destAddr, DSR_RouteCache *routeCache); 

int RoutingDsrGetSeq(GlomoNode *node); 
 
BOOL RoutingDsrCheckUnprocessedPath(GlomoNode *node,
                                    int currentHop,
                                    int segmentLeft,
                                    NODE_ADDR *header);
 
Message *
RoutingDsrGetBufferedPacket(NODE_ADDR destAddr, DSR_BUFFER *buffer);

BOOL RoutingDsrLookupBuffer(NODE_ADDR destAddr, DSR_BUFFER *buffer);

void RoutingDsrUpdateRequestTable(NODE_ADDR destAddr, 
                                  DSR_RequestTable *requestTable);

void RoutingDsrUpdateTtl(NODE_ADDR destAddr, 
                         DSR_RequestTable *requestTable);

BOOL RoutingDsrCheckRequestTable(NODE_ADDR destAddr, 
                                 DSR_RequestTable *requestTable);

clocktype RoutingDsrGetBackoff(NODE_ADDR destAddr,
                               DSR_RequestTable *requestTable);

void RoutingDsrHandleProtocolPacket(
    GlomoNode *node, Message *msg, NODE_ADDR srcAddr,
    NODE_ADDR destAddr, int ttl);

void RoutingDsrHandleProtocolEvent(GlomoNode *node, Message *msg);

void RoutingDsrRouterFunction(
    GlomoNode *node,
    Message *msg,
    NODE_ADDR destAddr,
    BOOL *packetWasRouted);

void RoutingDsrPeekFunction(GlomoNode *node, const Message *msg);

void RoutingDsrPacketDropNotificationHandler(
   GlomoNode *node, const Message* msg, const NODE_ADDR nextHopAddress);

void RoutingDsrSetTimer(
    GlomoNode *node, long eventType, DSR_CR cr, clocktype delay);

void RoutingDsrInitiateRREQ(GlomoNode *node, NODE_ADDR destAddr);

void RoutingDsrRetryRREQ(GlomoNode *node, NODE_ADDR destAddr, int ttl);

void RoutingDsrTransmitData(GlomoNode *node, Message *msg, NODE_ADDR destAddr);

void RoutingDsrRelayRREQ(GlomoNode *node, Message *msg, int ttl);

void RoutingDsrInitiateRREP(GlomoNode *node, Message *msg);

void RoutingDsrInitiateRREPbyIN(GlomoNode *node, Message *msg);

void RoutingDsrRelayRREP(GlomoNode *node, Message *msg);

void RoutingDsrInitiateRERR(GlomoNode *node, NODE_ADDR destAddr, 
                            NODE_ADDR unreachableAddr, NODE_ADDR *errorPath);

void RoutingDsrRelayRERR(GlomoNode *node, Message *msg);

void RoutingDsrSalvageData(GlomoNode *node, Message *msg);

void RoutingDsrSalvageRERR(GlomoNode *node, NODE_ADDR targetAddr,
                           NODE_ADDR srcAddr, NODE_ADDR unreachableAddr);

void RoutingDsrGratuitousRREP(GlomoNode *node, NODE_ADDR srcAddr,
                    NODE_ADDR destAddr, NODE_ADDR *old, int count, int length);

void AddCustomDsrIpOptionFields(GlomoNode* node, Message* msg);

DsrIpOptionType* GetPtrToDsrIpOptionField(Message* msg);

extern double ceil(double x);

#endif /* _DSR_H_ */

