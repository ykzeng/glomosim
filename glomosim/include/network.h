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
 * $Id: network.h,v 1.26 2001/12/19 22:31:15 jmartin Exp $
 */

#ifndef _NETWORK_H_
#define _NETWORK_H_

typedef unsigned int NetworkQueueingPriorityType;

#define CONTROL 0
#define REAL_TIME 1
#define NON_REAL_TIME 2
#define IP_QUEUE_NUM_OF_PRIORITIES 3
#define INVALID_PRIORITY IP_QUEUE_NUM_OF_PRIORITIES

#define DEFAULT_NETWORK_OUTPUT_QUEUE_SIZE 100



#define NETWORK_IP_DELAY             1 * MICRO_SECOND

typedef enum {
    NETWORK_PROTOCOL_IP = 0,
    ROUTING_PROTOCOL_AODV,
    ROUTING_PROTOCOL_DSR,
    ROUTING_PROTOCOL_LAR1,
    ROUTING_PROTOCOL_ODMRP,
    ROUTING_PROTOCOL_OSPF,
    ROUTING_PROTOCOL_ZRP,
    ROUTING_PROTOCOL_ALL,
    ROUTING_PROTOCOL_NONE
} NetworkRoutingProtocolType;


struct glomo_network_ip_struct;

/*
 * typedef to GlomoNetwork in main.h
 */

struct glomo_network_str 
{
    //NETWORK_PROTOCOL networkProtocol;
    BOOL networkStats;
    BOOL guiOption;

    struct glomo_network_ip_struct* networkVar;
    void *routingVar;
};



void NetworkIpReceivePacketFromTransportLayer(
   GlomoNode* node, 
   Message* msg, 
   NODE_ADDR destAddr,
   NetworkQueueingPriorityType priority,
   unsigned char protocol,
   clocktype delay);

void NetworkIpReceivePacketFromMacLayer(
   GlomoNode* node, 
   Message* msg, 
   NODE_ADDR lastHopAddress);

void NetworkIpNotifyOfPacketDrop(
   GlomoNode* node, 
   Message* msg,
   NODE_ADDR nextHop);

void NetworkIpSneakPeekAtMacPacket(GlomoNode *node,  const Message *msg);


void NetworkIpAddNewInterfaceWithOutputQueue(
   GlomoNode* node, 
   InterfaceIdType interfaceId,
   const GlomoNodeInput* nodeInput);

BOOL NetworkIpOutputQueueIsEmpty(
   GlomoNode* node, 
   InterfaceIdType interfaceId);

int NetworkIpOutputQueueNumberInQueue(
   GlomoNode* node, 
   InterfaceIdType interfaceId,
   NetworkQueueingPriorityType priority);

void NetworkIpOutputQueueDequeuePacket(
   GlomoNode* node,
   InterfaceIdType interfaceId, 
   Message** msg,
   NODE_ADDR* nextHopAddress,
   NetworkQueueingPriorityType* priority);
   
void NetworkIpOutputQueueDequeuePacketForAPriority(
   GlomoNode* node,
   InterfaceIdType interfaceId, 
   NetworkQueueingPriorityType priority,
   Message** msg,
   NODE_ADDR* nextHopAddress);

void NetworkIpOutputQueueTopPacket(
   GlomoNode* node,
   InterfaceIdType interfaceId, 
   Message** msg,
   NODE_ADDR* nextHopAddress,
   NetworkQueueingPriorityType* priority);
   
void NetworkIpOutputQueueTopPacketForAPriority(
   GlomoNode* node,
   InterfaceIdType interfaceId, 
   NetworkQueueingPriorityType priority,
   Message** msg,
   NODE_ADDR* nextHopAddress);


#endif /* _NETWORK_H_ */

