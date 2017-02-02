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
 * File: fisheye.h
 * By: Guangyu Gary Pei (pei@cs.ucla.edu)
 * Date: 12/22/1998.
 */

#ifndef _FISHEYE_H_
#define _FISHEYE_H_

#include "fileio.h"

#define FisheyeInfinity 16 

/* We use UDP and IP for the control packet */
#define MAX_TT_SIZE (MAX_NW_PKT_SIZE - 20 - 8 - sizeof(RoutingFisheyeHeader))

/* Used to avoid synchronization of TT updates. */
#define FisheyeRandomTimer                (100 * MILLI_SECOND)

/* Timer */
typedef struct fisheye_timer_
{
  long seq;
  unsigned char type;
} FisheyeTimer;

/* describe one neighoring information */
typedef struct fisheye_neighbor_info_ FisheyeNeighborInfo;
struct fisheye_neighbor_info_
{
  NODE_ADDR nodeAddr;
  FisheyeNeighborInfo *next;
} ;

typedef struct fisheye_heard_neighbor_info_
{
  NODE_ADDR nodeAddr;
  clocktype lastHeardTime;
  struct fisheye_heard_neighbor_info_ *next;
} FisheyeHeardNeighborInfo;

/* decribe one entry of the topology table  indexed by nodeAddr*/
typedef struct fisheye_tt_row_
{
  /* Node id of next hop node */
  NODE_ADDR nextHop;

  /* Node id of the prev node to this node */
  NODE_ADDR prevHop;

  /* distance could be anything, but here let be the hop distance*/
  int distance;

  /* timestamp of the entry be revised*/
  clocktype lastModifyTime;

  /* sequence number of the neigboring list */
  int sequenceNumber;

  /* neighbor number of the destionation node*/
  short neighborNumber;

  /* one information per neighbor */
  FisheyeNeighborInfo *neighborInfo;

} FisheyeTTRow;

typedef struct fisheye_tt_
{
  /* one row for each destination */
  FisheyeTTRow *row;

} FisheyeTT;

typedef struct fisheye_stats_
{
  
  /* Total number of TT updates In the scope */
  int intraScopeUpdate;

  /* Total number of TT updates out the scope*/
  int interScopeUpdate;

  /* Total number of fisheye control pkts got from transport Udp */
  int pktNumFromUdp;

  /* Total Control OH in bytes */
  int controlOH;

}FisheyeStats;


typedef struct routing_fisheye_header_
{
  /* Source address*/
  NODE_ADDR sourceAddr;

  /* destination address */
  NODE_ADDR destinationAddr;
  
  /* size of the payload in bytes */
  int payloadSize;

}RoutingFisheyeHeader;

typedef struct fisheye_parameter_
{
  /* Fisheye scope */
  short Scope;
  /* neighbor time out interval*/
  clocktype NeighborTOInterval;
  /* update hop < Scope interval */
  clocktype IntraUpdateInterval;
  /* update hop > Scope interval */
  clocktype InterUpdateInterval;

}FisheyeParameter;

typedef struct glomo_network_fisheye_str 
{
  /*keep track of topology table for every node */
  FisheyeTT topologyTable;

  /* Keep track of the heardd neighbor */
  FisheyeHeardNeighborInfo *heardNeighborInfo;
  
  /*keep track of different network statistics*/
  FisheyeStats stats;

  /* Keep track of the parameters of Fisheye protocol*/
  FisheyeParameter parameter;

  /* Timer */
  FisheyeTimer timer;

} GlomoRoutingFisheye;


void RoutingFisheyeInit(GlomoNode *node,const GlomoNodeInput *nodeInput);
void RoutingFisheyeFinalize(GlomoNode *node);
void RoutingFisheyeLayer(GlomoNode *node, Message *msg);
void RoutingFisheyeInitTT(GlomoNode *node,GlomoRoutingFisheye *fisheye);
void RoutingFisheyeInitStats(GlomoNode *node,GlomoRoutingFisheye *fisheye);
RoutingFisheyeHeader RoutingFisheyeCreateHeader(NODE_ADDR sourceAddr,
						NODE_ADDR destinationAddr,
						int payloadSize);
void RoutingFisheyeUpdateNeighborInfo(GlomoNode *node,
				      GlomoRoutingFisheye *fisheye,
				      RoutingFisheyeHeader *header);
void RoutingFisheyePrintNeighborInfo(GlomoNode *node,
				     GlomoRoutingFisheye *fisheye);
void RoutingFisheyeHandleIntraUpdateMsg(GlomoNode *node,
					GlomoRoutingFisheye *fisheye);
void RoutingFisheyeHandleInterUpdateMsg(GlomoNode *node,
					GlomoRoutingFisheye *fisheye);
void RoutingFisheyeSendScopeTT(GlomoNode *node,
			       GlomoRoutingFisheye *fisheye, 
			       short lower, short upper);
void RoutingFisheyeUpdateTT(GlomoNode *node,
			    GlomoRoutingFisheye *fisheye,
			    RoutingFisheyeHeader *header,
			    char *payload);
void RoutingFisheyeFindSP(GlomoNode *node);
void RoutingFisheyePrintTT(GlomoNode *node,GlomoRoutingFisheye *fisheye);
void RoutingFisheyePrintTTPkt(RoutingFisheyeHeader *header, char *payload);
void RoutingFisheyeHandleNeighborTOMsg(GlomoNode *node,
				       GlomoRoutingFisheye *fisheye);
void RoutingFisheyeCopyHeardToTable(GlomoNode *node,
				    GlomoRoutingFisheye *fisheye);
void RoutingFisheyeHandleControlPacket(GlomoNode *node,
				       GlomoRoutingFisheye *fisheye,
				       RoutingFisheyeHeader *header,
				       char *payload);
void RoutingFisheyePrintRoutingStats(GlomoNode *node);
#endif  /* _FISHEYE_H_ */

