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
 * Name: odmrp.h
 * Purpose: To simulate On-Demand Multicast Routing Protocol (ODMRP) 
 */


#ifndef _ODMRP_H_
#define _ODMRP_H_

#include "ip.h"
#include "nwcommon.h"
#include "main.h"

/* Maximum number of multicast groups in simulation. */
#define ODMRP_MAX_GROUP                   10 

/* Maximum number of sources for each multicast group. */
#define ODMRP_MAX_SOURCE                  20

/* Join Reply refresh time. */
#define ODMRP_JR_REFRESH                    3 * SECOND

/* Fg_FLAG times out after ODMRP_FG_TIMEOUT after receiving JR. */
#define ODMRP_FG_TIMEOUT                    4 * SECOND

/* To prevent congestion. */
#define ODMRP_CONGESTION_TIME               250 * MILLI_SECOND

/* Interval to check for implicit acks. */
#define ODMRP_CHECKACK_INTERVAL             75 * MILLI_SECOND

/* Maximum number of transmissions allowed for a JR. */
#define ODMRP_MAX_NUM_TX                      3

/* Maximum Hop Count Join Query can travel. */
#define ODMRP_MAX_HOP                       10

/* Lifetime of entries stored for Join Reply (wsu not used for now). */
#define ODMRP_JR_LIFETIME                   120 * SECOND

/* Entry in receiver's member table expires after this period. */
#define ODMRP_MEM_TIMEOUT                   120 * SECOND

/* For checking timer for sending Join Query. */
#define ODMRP_TIMER_INTERVAL                10 * MILLI_SECOND

/* Time for intermediate FG nodes to wait before forwarding JR. */
#define ODMRP_JR_PAUSE_TIME                 25 * MILLI_SECOND

/* Jittering time when broadcast to avoid collisions. */
#define ODMRP_BROADCAST_JITTER              10 * MILLI_SECOND

/* Jittering time when sending Join Replies. */
#define ODMRP_JR_JITTER                     15 * MILLI_SECOND

/* Jittering time when retransmitting Join Replies */
#define ODMRP_JR_RETX_JITTER                    15 * MILLI_SECOND

/* Flush the entry in the message cache after this amount of time */
#define ODMRP_FLUSH_INTERVAL                10 * SECOND

#define IPOPT_ODMRP  219

/* ODMRP option fields for IP header */
typedef struct{
    unsigned char query;
    NODE_ADDR lastAddr;
    unsigned char seqNumber;
    unsigned char hopCount;
} OdmrpIpOptionType;

typedef enum 
{
    ODMRP_JOIN_REPLY,
    ODMRP_ACK
} ODMRP_PacketType;

typedef struct
{
    ODMRP_PacketType pktType;

    /* Was last node a FG? */
    BOOL IAmFG;

    /* Number of entries in the table. */
    int count;

    NODE_ADDR srcAddr[ODMRP_MAX_SOURCE]; 
    NODE_ADDR nextAddr[ODMRP_MAX_SOURCE];  
    BOOL ackReq[ODMRP_MAX_SOURCE];  
} ODMRP_JoinReply;

typedef struct
{
    ODMRP_PacketType pktType;
    NODE_ADDR mcastAddr;
    NODE_ADDR srcAddr;
} ODMRP_Ack;

typedef struct odmrpATEE
{
    NODE_ADDR srcAddr;
    NODE_ADDR nextAddr;
    int numTx;
    struct odmrpATEE *prev;
    struct odmrpATEE *next;
} ODMRP_AT_Snode;

typedef struct odmrpATE
{
    NODE_ADDR mcastAddr;
    clocktype lastSent;
    ODMRP_AT_Snode *head;
    int size;
    struct odmrpATE *next;
} ODMRP_AT_Node;

typedef struct
{
    ODMRP_AT_Node *head;
    int size;
} ODMRP_AT;

typedef struct odmrpME
{
    NODE_ADDR mcastAddr;
    clocktype timestamp;
    struct odmrpME *next;
} ODMRP_M_Node;

typedef struct
{
    ODMRP_M_Node *head;
    int size;
} ODMRP_Membership;

typedef struct odmrpFFE
{
    NODE_ADDR mcastAddr;
    clocktype timestamp;
    struct odmrpFFE *next;
} ODMRP_FF_Node;

typedef struct
{
    ODMRP_FF_Node *head;
    int size;
} ODMRP_FgFlag;

typedef struct odmrpMTEE
{
    NODE_ADDR srcAddr;
    clocktype timestamp;
    struct odmrpMTEE *prev;
    struct odmrpMTEE *next;
} ODMRP_MT_Snode;

typedef struct odmrpMTE
{
    NODE_ADDR mcastAddr;
    BOOL sent;                      /* Flag to indicate join reply sent. */
    clocktype lastSent;             /* Last time that sent join reply. */
    clocktype queryLastReceived;    /* Join Query last received time */
    ODMRP_MT_Snode *head;
    int size;
    struct odmrpMTE *next;
} ODMRP_MT_Node;

typedef struct        /* Member Table */
{
    ODMRP_MT_Node *head;
    int size;
} ODMRP_MT;

typedef struct odmrpRPTEE
{
    NODE_ADDR srcAddr;
    struct odmrpRPTEE *next;
} ODMRP_RPT_Snode;

typedef struct odmrpRPTE
{
    NODE_ADDR mcastAddr;
    ODMRP_RPT_Snode *head;
    int size;
    struct odmrpRPTE *next;
} ODMRP_RPT_Node;

typedef struct     /* Response Table: to keep track of which source to reply */
{
    ODMRP_RPT_Node *head;
    int size;
} ODMRP_RPT;

typedef struct odmrpTTEE
{
    NODE_ADDR srcAddr;
    clocktype timestamp;
    clocktype FGExpireTime;
    struct odmrpTTEE *prev;
    struct odmrpTTEE *next;
} ODMRP_TT_Snode;

typedef struct odmrpTTE
{
    NODE_ADDR mcastAddr;
    BOOL sent;                /* whether Join Reply has been sent */
    ODMRP_TT_Snode *head;
    int size;
    struct odmrpTTE *next;
} ODMRP_TT_Node;

typedef struct   /* Temp Table: maintained to build join replies */
{
    ODMRP_TT_Node *head;
    int size; 
} ODMRP_TT;

typedef struct odmrpRTE
{
    NODE_ADDR destAddr;
    NODE_ADDR nextAddr;
    int hopCount;
    clocktype timestamp;
    struct odmrpRTE *next;
} ODMRP_RT_Node;

typedef struct  /* Route Table */
{
    ODMRP_RT_Node *head;
    int size;
} ODMRP_RT;

typedef struct odmrpMCE
{
    NODE_ADDR srcAddr;
    int seqNumber;
    BOOL sent; 
    struct odmrpMCE *next;
} ODMRP_MC_Node;

typedef struct /* Message Cache */
{
    ODMRP_MC_Node *front;
    ODMRP_MC_Node *rear;
    int size;
} ODMRP_MC;

typedef struct odmrpSSE
{
    NODE_ADDR mcastAddr;
    clocktype minExpireTime;
    clocktype lastSent;
    BOOL nextQuerySend;       /* Send Join Query for next data? */
    struct odmrpSSE *next;
} ODMRP_SS_Node;

typedef struct  /* Source Sent */
{
    ODMRP_SS_Node *head;
    int size;
} ODMRP_SS;

typedef struct
{
    /* Total number of join query txed. */
    int numQueryTxed;

    /* Total number of join reply packets sent. */
    int numReplySent;

    /* Total number of explicit acks sent. */
    int numAckSent;

    /* Total number of data packets sent by the source. */
    int numDataSent;

    /* Total number of data packets received by the destination. */
    int numDataReceived;

    /* Total number of data packets should be received by the destination. */
    int numDataToReceive;

    /* Total number of data packets transmitted by each node. */
    int numDataTxed;

} ODMRP_Stats;

typedef struct glomo_network_odmrp_str 
{
    ODMRP_Membership memberFlag;
    ODMRP_FgFlag fgFlag;
    ODMRP_MT memberTable;
    ODMRP_TT tempTable;
    ODMRP_RT routeTable;
    ODMRP_MC messageCache;
    int seqTable;
    ODMRP_SS sentTable;
    ODMRP_Stats stats;    
    ODMRP_AT ackTable;
    ODMRP_RPT responseTable;
} GlomoRoutingOdmrp;

void RoutingOdmrpHandleProtocolEvent(GlomoNode *node, Message *msg);

void RoutingOdmrpHandleProtocolPacket(GlomoNode *node,
                                      Message *msg,
                                      NODE_ADDR srcAddr,
                                      NODE_ADDR destAddr);

void RoutingOdmrpRouterFunction(GlomoNode *node,
                                Message *msg,
                                NODE_ADDR destAddr,
                                BOOL *packetWasRouted);

void RoutingOdmrpInit(GlomoNode *node,
                      GlomoRoutingOdmrp **odmrpPtr,
                      const GlomoNodeInput *nodeInput);

void RoutingOdmrpFinalize(GlomoNode *node);

void RoutingOdmrpHandleData(GlomoNode *node, Message *msg);

void RoutingOdmrpHandleJoinQuery(GlomoNode *node, Message *msg);

void RoutingOdmrpHandleReply(
       GlomoNode *node, Message *msg, NODE_ADDR lastAddr, NODE_ADDR mcastAddr);

void RoutingOdmrpHandleAck(
       GlomoNode *node, Message *msg, NODE_ADDR lastAddr, NODE_ADDR targetAddr);

void RoutingOdmrpInitMembership(ODMRP_Membership *memberFlag);

void RoutingOdmrpInitFgFlag(ODMRP_FgFlag *fgFlag);

void RoutingOdmrpInitMemberTable(ODMRP_MT *memberTable);

void RoutingOdmrpInitResponseTable(ODMRP_RPT *responseTable);

void RoutingOdmrpInitTempTable(ODMRP_TT *tempTable);

void RoutingOdmrpInitRouteTable(ODMRP_RT *routeTable);

void RoutingOdmrpInitMessageCache(ODMRP_MC *messageCache);

void RoutingOdmrpInitSeqTable(GlomoNode *node);

void RoutingOdmrpInitSent(ODMRP_SS *sentTable);

void RoutingOdmrpInitStats(GlomoNode *node);

void RoutingOdmrpDeleteMsgCache(ODMRP_MC *messageCache);

BOOL RoutingOdmrpLookupMessageCache(
                 NODE_ADDR srcAddr, int seqNumber, ODMRP_MC *messageCache);

BOOL RoutingOdmrpLookupMembership(NODE_ADDR mcastAddr,
                                  ODMRP_Membership *memberFlag);

BOOL RoutingOdmrpLookupFgFlag(NODE_ADDR mcastAddr,
                              ODMRP_FgFlag *fgFlag);

BOOL RoutingOdmrpLookupMemberTable(NODE_ADDR mcastAddr,
                                   ODMRP_MT *memberTable);

BOOL RoutingOdmrpLookupSentTable(NODE_ADDR mcastAddr,
                                 ODMRP_SS *sentTable);

BOOL RoutingOdmrpCheckFgExpired(NODE_ADDR mcastAddr,
                                ODMRP_FgFlag *fgFlag);

void RoutingOdmrpSetMemberFlag(NODE_ADDR mcastAddr,
                               ODMRP_Membership *memberFlag);

ODMRP_M_Node *RoutingOdmrpSetMemFlagInOrder(
                             NODE_ADDR mcastAddr, ODMRP_M_Node *old);

void RoutingOdmrpResetMemberFlag(NODE_ADDR mcastAddr,
                                 ODMRP_Membership *memberFlag);

void RoutingOdmrpUpdateFgFlag(NODE_ADDR mcastAddr, ODMRP_FgFlag *fgFlag);

void RoutingOdmrpSetFgFlag(NODE_ADDR mcastAddr, ODMRP_FgFlag *fgFlag);

ODMRP_FF_Node *RoutingOdmrpSetFgFlagInOrder(
                                NODE_ADDR mcastAddr, ODMRP_FF_Node *old);

void RoutingOdmrpResetFgFlag(NODE_ADDR mcastAddr,
                             ODMRP_FgFlag *fgFlag);

void RoutingOdmrpSetSent(NODE_ADDR mcastAddr, ODMRP_SS *sentTable);

ODMRP_SS_Node *RoutingOdmrpSetSentInOrder(
                                NODE_ADDR mcastAddr, ODMRP_SS_Node *old);

void RoutingOdmrpDeleteSourceSent(NODE_ADDR mcastAddr, ODMRP_SS *sentTable);

ODMRP_MT_Node *RoutingOdmrpGetMTEntry(
                  NODE_ADDR mcastAddr, ODMRP_MT *memberTable);

void RoutingOdmrpInsertMemberTable(NODE_ADDR mcastAddr,
                                   NODE_ADDR srcAddr,
                                   ODMRP_MT *memberTable);

ODMRP_MT_Node *RoutingOdmrpInsertMTInOrder(
                   NODE_ADDR mcastAddr, NODE_ADDR srcAddr, ODMRP_MT_Node *old);

BOOL RoutingOdmrpCheckMSExist(NODE_ADDR srcAddr, ODMRP_MT_Node *mcast);

ODMRP_MT_Snode *RoutingOdmrpInsertMemberSource(
                                    NODE_ADDR srcAddr, ODMRP_MT_Node *mcast);

ODMRP_MT_Snode *RoutingOdmrpInsertMSInOrder(
                  NODE_ADDR srcAddr, ODMRP_MT_Snode *old, ODMRP_MT_Snode *last);

void RoutingOdmrpCheckSourceExpired(NODE_ADDR mcastAddr, ODMRP_MT *memberTable);

ODMRP_TT_Node *RoutingOdmrpGetTTEntry(NODE_ADDR mcastAddr, ODMRP_TT *tempTable);

void RoutingOdmrpInsertTempTable(NODE_ADDR mcastAddr,
                                 NODE_ADDR srcAddr,
                                 ODMRP_TT *tempTable);

ODMRP_TT_Node *RoutingOdmrpInsertTTInOrder(
                   NODE_ADDR mcastAddr, NODE_ADDR srcAddr, ODMRP_TT_Node *old);

BOOL RoutingOdmrpCheckTSExist(NODE_ADDR srcAddr, ODMRP_TT_Node *mcast);

ODMRP_TT_Snode *RoutingOdmrpInsertTempSource(
                                     NODE_ADDR srcAddr, ODMRP_TT_Node *mcast);

ODMRP_TT_Snode *RoutingOdmrpInsertTSInOrder(
                  NODE_ADDR srcAddr, ODMRP_TT_Snode *old, ODMRP_TT_Snode *last);

BOOL RoutingOdmrpCheckTempChanged(NODE_ADDR mcastAddr, ODMRP_TT *tempTable);

void RoutingOdmrpCheckTempExpired(NODE_ADDR mcastAddr, ODMRP_TT *tempTable);

ODMRP_RPT_Node *RoutingOdmrpGetRPTEntry(
                                NODE_ADDR mcastAddr, ODMRP_RPT *rspnsTable);

void RoutingOdmrpInsertResponseTable(
             NODE_ADDR mcastAddr, NODE_ADDR srcAddr, ODMRP_RPT *rspnsTable);

ODMRP_RPT_Node *RoutingOdmrpInsertRPTInOrder(
                   NODE_ADDR mcastAddr, NODE_ADDR srcAddr, ODMRP_RPT_Node *old);

BOOL RoutingOdmrpCheckRPSExist(NODE_ADDR srcAddr, ODMRP_RPT_Node *mcast);

ODMRP_RPT_Snode *RoutingOdmrpInsertResponseSource(
                                    NODE_ADDR srcAddr, ODMRP_RPT_Node *mcast);

ODMRP_RPT_Snode *RoutingOdmrpInsertRPSInOrder(
                                   NODE_ADDR srcAddr, ODMRP_RPT_Snode *old);

ODMRP_AT_Node *RoutingOdmrpGetATEntry(NODE_ADDR mcastAddr, ODMRP_AT *ackTable);

void RoutingOdmrpInsertAckTable(
              NODE_ADDR mcastAddr, ODMRP_AT *ackTable, ODMRP_JoinReply *reply);

ODMRP_AT_Node *RoutingOdmrpInsertATInOrder(
              NODE_ADDR mcastAddr, ODMRP_AT_Node *old, ODMRP_JoinReply *reply);

BOOL RoutingOdmrpCheckASExist(NODE_ADDR srcAddr, ODMRP_AT_Node *mcast);

ODMRP_AT_Snode *RoutingOdmrpInsertAckSource(
                  NODE_ADDR srcAddr, NODE_ADDR nextAddr, ODMRP_AT_Node *mcast);

ODMRP_AT_Snode *RoutingOdmrpInsertASInOrder(NODE_ADDR srcAddr,
                 NODE_ADDR nextAddr, ODMRP_AT_Snode *old, ODMRP_AT_Snode *last);

void RoutingOdmrpInsertRouteTable(NODE_ADDR destAddr,
                                  NODE_ADDR nextAddr,
                                  int hopCount,
                                  ODMRP_RT *routeTable);

ODMRP_RT_Node *RoutingOdmrpInsertRTInOrder(
    NODE_ADDR destAddr, NODE_ADDR nextAddr, int hopCount, ODMRP_RT_Node *old);

BOOL RoutingOdmrpCheckRouteExist(NODE_ADDR destAddr, ODMRP_RT *routeTable);

void RoutingOdmrpInsertMessageCache(GlomoNode *node,
                               NODE_ADDR srcAddr,
                               int seqNumber,
                               ODMRP_MC *messageCache);

int RoutingOdmrpGetSeq(GlomoNode *node);

NODE_ADDR RoutingOdmrpGetNextNode(NODE_ADDR destAddr, ODMRP_RT *routeTable);

int RoutingOdmrpGetTempCount(NODE_ADDR mcastAddr, ODMRP_TT *tempTable);

int RoutingOdmrpGetMemberCount(NODE_ADDR mcastAddr, ODMRP_MT *memberTable);

int RoutingOdmrpGetAckCount(NODE_ADDR mcastAddr, ODMRP_AT *ackTable);

void RoutingOdmrpJoinGroup(GlomoNode *node, NODE_ADDR mcastAddr);

void RoutingOdmrpLeaveGroup(GlomoNode *node, NODE_ADDR mcastAddr);

BOOL RoutingOdmrpCheckLastSent(NODE_ADDR mcastAddr,
                               ODMRP_MT *memberTable);

void RoutingOdmrpUpdateLastSent(NODE_ADDR mcastAddr,
                                ODMRP_MT *memberTable);

BOOL RoutingOdmrpCheckAckTable(NODE_ADDR mcastAddr, ODMRP_AT *ackTable);

void RoutingOdmrpDeleteAckTable(NODE_ADDR mcastAddr, NODE_ADDR srcAddr, 
                                NODE_ADDR lastAddr, ODMRP_AT *ackTable);

void RoutingOdmrpInitAckTable(ODMRP_AT *ackTable);

void RoutingOdmrpDeleteMemberTable(NODE_ADDR mcastAddr, ODMRP_MT *memberTable);

void RoutingOdmrpDeleteTempTable(NODE_ADDR mcastAddr, ODMRP_TT *tempTable);

void RoutingOdmrpDeleteResponseTable(
                               NODE_ADDR mcastAddr, ODMRP_RPT *rspnsTable);

BOOL RoutingOdmrpCheckResponseMatch(
                NODE_ADDR mcastAddr, NODE_ADDR srcAddr, ODMRP_RPT *rspnsTable);

BOOL RoutingOdmrpCheckMinExpTime(NODE_ADDR mcastAddr, ODMRP_SS *sentTable);

BOOL RoutingOdmrpCheckCongestionTime(
                               NODE_ADDR mcastAddr, ODMRP_MT *memberTable);

BOOL RoutingOdmrpCheckSendQuery(NODE_ADDR mcastAddr, ODMRP_SS *sentTable);

void RoutingOdmrpSetSendQuery(NODE_ADDR mcastAddr, ODMRP_SS *sentTable);

void RoutingOdmrpUnsetSendQuery(NODE_ADDR mcastAddr, ODMRP_SS *sentTable);

void RoutingOdmrpSetMinExpireTime(NODE_ADDR mcastAddr, ODMRP_SS *sentTable);

BOOL RoutingOdmrpCheckTempSent(NODE_ADDR mcastAddr, ODMRP_TT *tempTable);

void RoutingOdmrpSetTempSent(NODE_ADDR mcastAddr, ODMRP_TT *tempTable);

void RoutingOdmrpUnsetTempSent(NODE_ADDR mcastAddr, ODMRP_TT *tempTable);

void RoutingOdmrpSetMemberSent(NODE_ADDR mcastAddr, ODMRP_MT *memberTable);

void RoutingOdmrpSetTimer(
    GlomoNode *node, long eventType, NODE_ADDR mcastAddr, clocktype delay);

void RoutingOdmrpSendReply(GlomoNode *node, NODE_ADDR mcastAddr, 
                           ODMRP_MT *memberTable, ODMRP_TT *tempTable);

void RoutingOdmrpRetxReply(
                    GlomoNode *node, NODE_ADDR mcastAddr, ODMRP_AT *ackTable);

void RoutingOdmrpSendData(GlomoNode *node, Message *msg, NODE_ADDR mcastAddr);

void RoutingOdmrpSendQuery(GlomoNode *node, Message *msg, NODE_ADDR mcastAddr);

void AddCustomOdmrpIpOptionFields(GlomoNode* node, Message* msg);

OdmrpIpOptionType GetOdmrpIpOptionField(const Message* msg);

void SetOdmrpIpOptionField(
        Message* msg, const OdmrpIpOptionType* OdmrpIpOption);

#endif /* _ODMRP_H_ */

