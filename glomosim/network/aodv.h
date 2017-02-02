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
 * Name: aodv.h
 *
 * Implemented by SJ Lee (sjlee@cs.ucla.edu)
 */

/*
 NOTE: The parameter values followed the AODV Internet Draft
       (draft-ietf-manet-aodv-03.txt) and NS2 code by Samir R. Das
       Read the NOTE of aodv.pc for more details
*/

#ifndef _AODV_H_
#define _AODV_H_

#include "ip.h"
#include "main.h"
#include "nwcommon.h"

#define ACTIVE_ROUTE_TO                         10 * SECOND

#define NODE_TRAVERSAL_TIME                     40 * MILLI_SECOND

#define NET_DIAMETER                            35

#define RREP_WAIT_TIME              3 * NODE_TRAVERSAL_TIME * NET_DIAMETER / 2

#define BAD_LINK_LIFETIME                       2 * RREP_WAIT_TIME

#define BCAST_ID_SAVE                           30 * SECOND

#define REV_ROUTE_LIFE                          RREP_WAIT_TIME

#define MY_ROUTE_TO                             2 * ACTIVE_ROUTE_TO

#define RREQ_RETRIES                            2

#define TTL_START                               1

#define TTL_INCREMENT                           2

#define TTL_THRESHOLD                           7

#define AODV_INFINITY                           255

#define BROADCAST_JITTER                        10 * MILLI_SECOND

/* Packet Types */



typedef unsigned char AODV_PacketType;

#define AODV_RREQ 0
#define AODV_RREP 1
#define AODV_RERR 2



typedef struct
{
    AODV_PacketType pktType;
    int bcastId;
    NODE_ADDR destAddr;
    int destSeq;
    NODE_ADDR srcAddr;
    int srcSeq;
    NODE_ADDR lastAddr;
    int hopCount;
} AODV_RREQ_Packet;

typedef struct
{
    AODV_PacketType pktType;
    NODE_ADDR srcAddr;
    NODE_ADDR destAddr;
    int destSeq;
    int hopCount;
    clocktype lifetime;
} AODV_RREP_Packet;


typedef struct 
{
  NODE_ADDR destinationAddress;
  int destinationSequenceNumber; 
} AODV_AddressSequenceNumberPairType;

#define AODV_MAX_RERR_DESTINATIONS 250

typedef struct
{
    AODV_PacketType pktType;          // 1 byte
    unsigned char filling[2];
    unsigned char destinationCount;
    AODV_AddressSequenceNumberPairType 
       destinationPairArray[AODV_MAX_RERR_DESTINATIONS];
} AODV_RERR_Packet;


static //inline//
int AODV_RERR_PacketSize(const AODV_RERR_Packet* rerrPacket) {
   return 
      (sizeof(rerrPacket->pktType) + 
       sizeof(rerrPacket->filling) +
       sizeof(rerrPacket->destinationCount) +
       (rerrPacket->destinationCount * 
        sizeof(AODV_AddressSequenceNumberPairType)));
}



typedef struct RTE
{
    NODE_ADDR destAddr;
    int destSeq;
    int hopCount;
    int lastHopCount;
    NODE_ADDR nextHop;
    clocktype lifetime;
    BOOL activated;
    BOOL source;
    struct RTE *next;
} AODV_RT_Node;

typedef struct
{
    AODV_RT_Node *head;
    int size;
} AODV_RT;

typedef struct NTE
{
    NODE_ADDR destAddr;
    struct NTE *next;
} AODV_NT_Node;

typedef struct
{
    AODV_NT_Node *head;
    int size;
} AODV_NT;

typedef struct RSE
{
    NODE_ADDR srcAddr;
    int bcastId;
    struct RSE *next;
} AODV_RST_Node;

typedef struct
{
    AODV_RST_Node *front;
    AODV_RST_Node *rear;
    int size;
} AODV_RST;

typedef struct FIFO
{
    NODE_ADDR destAddr;
    clocktype timestamp;
    Message *msg;
    struct FIFO *next;
} AODV_BUFFER_Node;

typedef struct
{
    AODV_BUFFER_Node *head;
    int size;
} AODV_BUFFER;

typedef struct SE
{
    NODE_ADDR destAddr;
    int ttl;
    int times;
    struct SE *next;
} AODV_SENT_Node;

typedef struct
{
    AODV_SENT_Node *head;
    int size;
} AODV_SENT;

typedef struct
{
    int numRequestSent;
    int numReplySent;
    int numRerrSent;
    int numRerrResent;
    int numDataSent;        /* Data Sent as the source of the route */
    int numDataTxed;
    int numDataReceived;    /* Data Received as the destination of the route */
    int numHops;
    int numRoutes;
    int numPacketsDropped;
    int numBrokenLinks;
    int numBrokenLinkRetries;
} AODV_Stats;

typedef struct glomo_network_aodv_str 
{
    AODV_RT routeTable;
    AODV_NT nbrTable;
    AODV_RST seenTable;
    AODV_BUFFER buffer;
    AODV_SENT sent;
    AODV_Stats stats;
    int seqNumber;
    int bcastId;
} GlomoRoutingAodv;

void RoutingAodvInit(
    GlomoNode *node, 
    GlomoRoutingAodv **aodvPtr, 
    const GlomoNodeInput *nodeInput);

void RoutingAodvFinalize(GlomoNode *node);

void RoutingAodvHandleData(GlomoNode *node, Message *msg, NODE_ADDR destAddr);

void RoutingAodvHandleRequest(GlomoNode *node, Message *msg, int ttl);

void RoutingAodvHandleReply(
    GlomoNode *node, Message *msg, NODE_ADDR srcAddr, NODE_ADDR destAddr);

void RoutingAodvInitRouteTable(AODV_RT *routeTable);

void RoutingAodvInitNbrTable(AODV_NT *nbrTable);

void RoutingAodvInitSeenTable(AODV_RST *seenTable);

void RoutingAodvInitBuffer(AODV_BUFFER *buffer);

void RoutingAodvInitSent(AODV_SENT *sent);

void RoutingAodvInitStats(GlomoNode *node);

void RoutingAodvInitSeq(GlomoNode *node);

void RoutingAodvInitBcastId(GlomoNode *node);

NODE_ADDR RoutingAodvGetNextHop(NODE_ADDR destAddr, AODV_RT *routeTable);

int RoutingAodvGetBcastId(GlomoNode *node);

int RoutingAodvGetSeq(NODE_ADDR destAddr, AODV_RT *routeTable);

int RoutingAodvGetMySeq(GlomoNode *node);

int RoutingAodvGetHopCount(NODE_ADDR destAddr, AODV_RT *routeTable);

int RoutingAodvGetLastHopCount(NODE_ADDR destAddr, AODV_RT *routeTable);

int RoutingAodvGetTtl(NODE_ADDR destAddr, AODV_SENT *sent);

int RoutingAodvGetTimes(NODE_ADDR destAddr, AODV_SENT *sent);

clocktype RoutingAodvGetLifetime(NODE_ADDR destAddr, AODV_RT *routeTable);

Message *
RoutingAodvGetBufferedPacket(NODE_ADDR destAddr, AODV_BUFFER *buffer);

BOOL RoutingAodvCheckRouteExist(NODE_ADDR destAddr, AODV_RT *routeTable);

BOOL RoutingAodvCheckNbrExist(NODE_ADDR destAddr, AODV_NT *nbrTable);

BOOL RoutingAodvLookupSeenTable(NODE_ADDR srcAddr, 
                                int bcastId,
                                AODV_RST *seenTable);

BOOL RoutingAodvLookupBuffer(NODE_ADDR destAddr, AODV_BUFFER *buffer);

BOOL RoutingAodvCheckSent(NODE_ADDR destAddr, AODV_SENT *sent);


void RoutingAodvHandleProtocolPacket(
    GlomoNode *node, Message *msg, NODE_ADDR srcAddr, 
    NODE_ADDR destAddr, int ttl);

void RoutingAodvHandleProtocolEvent(GlomoNode *node, Message *msg);

void RoutingAodvRouterFunction(
    GlomoNode *node,
    Message *msg,
    NODE_ADDR destAddr,
    BOOL *packetWasRouted);

void RoutingAodvPacketDropNotificationHandler(
   GlomoNode *node, const Message* msg, const NODE_ADDR nextHopAddress);

void RoutingAodvSetTimer(
    GlomoNode *node, long eventType, NODE_ADDR destAddr, clocktype delay);

void RoutingAodvInitiateRREQ(GlomoNode *node, NODE_ADDR destAddr);

void RoutingAodvRetryRREQ(GlomoNode *node, NODE_ADDR destAddr);

void RoutingAodvTransmitData(GlomoNode *node, Message *msg, NODE_ADDR destAddr);

void RoutingAodvRelayRREQ(GlomoNode *node, Message *msg, int ttl);

void RoutingAodvInitiateRREP(GlomoNode *node, Message *msg);

void RoutingAodvInitiateRREPbyIN(GlomoNode *node, Message *msg);

void RoutingAodvRelayRREP(GlomoNode *node, Message *msg, NODE_ADDR destAddr);

#endif /* _AODV_H_ */


