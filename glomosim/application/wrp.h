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
 * $Id: wrp.h,v 1.3 1999/09/05 04:32:00 jmartin Exp $
 *
 * PURPOSE:         Simulate the WRP routing protocol in the
 *                  application layer.
 */

#ifndef _WRP_H_
#define _WRP_H_

#define WRP_DATA        0
#define WRP_RT           1
#define WRP_UPDATE      0
#define WRP_ACK         1
#define WRP_COST        1
#define WRP_INFINITY    10000
#define WRP_RETX_TIMER  1
#define WRP_HELO_TIMER  2
#define WRP_INIT_TIMER  3
#define WRP_XMIT_TIMER   4
#define WRP_HOP_LIMIT   15
#define WRP_MAX_SEQ_NUM 128
#define WRP_MRL_RETX_CONST 3 

typedef struct DistEntry_t {
    NODE_ADDR via;  /* of "through" node */
    int dist;
    NODE_ADDR pred;
    int valid;
} DistEntry;

typedef struct DistTable_t
{
   NODE_ADDR dest;  /* of destination node */
   DistEntry *dat;
} DistTable;

typedef struct RouteTable_t
{
   NODE_ADDR dest, /* id of dest node */
       succ,       /* id of successor node */
       pred;       /* id of predecessor node */
   int dist,       /* distance to dest node */
       tag;        /* tag marker: NULL=unmarked, 1=correct, -1=error/loop */
} RouteTable;

typedef struct LCTable_t
{
   NODE_ADDR dest;       /* id of neighbor node */
   int dist,             /* distance to neighbor node */
       HelloCount;       /* number of un'ACKd helo messages outstanding */
   clocktype HelloTimer, /* Sim Time at which HelloTimer expires */
             RetxTimer;  /* Sim Time at which to Retx an unACK'd message */
   int RetxCount,        /* number of un'ACKd messages outstanding */
       seqno;            /* sequence number in use for this link */
   clocktype x;          /* retx time */
   int y,                /* max HelloCount before link failed */
       z;                /* max retx before link failed */
} LCTable;

typedef struct wirp_tpl {
    int u;                         /* ACK or UPDATE */
    NODE_ADDR j;           /* destination node */
    int RDkj;              /* distance to j */
    NODE_ADDR rpkj;        /* predecessor node to j */
} WrpTuple;

typedef struct wirp_mrl_tpl {
    WrpTuple entry;
    struct wirp_mrl_tpl *next;
} WrpMrlTuple;

typedef struct wirp_mrl_entry_t
{
   int retx_counter;    /* when 0, retransmit the update list */
   int retx_count;      /* when retx too many times, need to remove neighbor */
   int MRLsize;         /* number of update entries in linked list */
   NODE_ADDR *bitmap;   /* nodes that still need to ACK */
   WrpTuple *dat;       /* actual routing table update entries */
} WrpMrlEntry;

typedef struct wirp_pkt_hdr_str {
    int msgType;                  /* DATA or RT */
    NODE_ADDR k;
    NODE_ADDR destId;
    int seqNum;            /* Sequence Number assigned by WRP */
    int valid;                     /* Number of update entries in msg */
    int packetSize;               /* payload in bytes */
    int hopCount;
    clocktype timestamp;
} WrpPacketHeader;

#define WRP_PKT_PAYLOAD_SIZE MAX_NW_PAYLOAD_SIZE 

typedef struct wirp_pkt_str {
    WrpPacketHeader hdr;
    char payload[MAX_NW_BROADCAST_RT_SIZE-sizeof(WrpPacketHeader)];
} WrpPacket;

typedef struct wirp_timer_str {
    int timerType;
    NODE_ADDR k;
} WrpTimer;

typedef struct network_wirp_stats_str {
    /* Total number of RT packets sent */
    int numRTsent;

    /* Total number of packets received from Transport Layer. */
    int numFromTransport;

} WrpStats;

typedef struct glomo_routing_wrp_str {
    DistTable *DTable;
    RouteTable *RTable;
    LCTable *LTable;
    int *N,
        *Ni;

    int LISTmax;
    WrpTuple *LIST;
    int LISTct;
    WrpTuple *V;
    int Vct;
    int *responseList;
    int ACKthis;
    WrpPacket *wpkt;

    WrpMrlEntry *MRL;
    int SEQNO;
    WrpStats stats;
} GlomoRoutingWrp;

#define MAX_WRP_PKT_SIZE MAX_NW_BROADCAST_RT_SIZE - sizeof(WrpPacketHeader)
#define MAX_WRP_UPD_SIZE MAX_WRP_PKT_SIZE - (sizeof(NODE_ADDR)*node->numNodes)

void RoutingWrpInit(GlomoNode *node, const GlomoNodeInput *nodeInput);
void RoutingWrpLayer(GlomoNode *node, Message *msgHdr);
void RoutingWrpFinalize(GlomoNode *node);

#endif /* _WRP_H_ */

