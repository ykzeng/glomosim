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
 * $Id: nwip.h,v 1.39 2001/12/19 21:56:59 jmartin Exp $
 *
 * File: nwip.h
 * By: Teresa Yan (tyan@cs.ucla.edu)
 * Objective: IP Network Layer.
 * Reference: RFC 791
 * Date: 2/25/1999.
 */

#ifndef NWIP_H
#define NWIP_H

#include "ip.h"
#include "nwcommon.h"
#include "main.h"
#include "network.h"
#include "ipqueue.h"


//  Modifying the network code to add a routing protocol. 
//
//  Routing protocol packets with its specific "IP protocol number"
//  can be handled by making a case in the switch in 
//  "ProcessPacketForMeFromMac" and calling the routing protocol
//  routine that handles that packet.
//
//  Routing protcols can send events to themselves (such as 
//  timer timeout events) and can field them by modifying
//  the by modifying the switch statement in 
//  "HandleRoutingProtocolEvent". 

// 
// NetworkIpSetRouterFunction routine allows a routing protocol to 
// define the routing function.  The routing function is called
// by the network layer to ask the routing protocol to 
// route the packet.  The routing function is given the 
// packet and its destination.  The routing protocol can
// route the packet and return "PacketWasRouted" as TRUE.
// Or not route the packet and return FALSE.  If the packet,
// was not routed, then the network layer will try to use the
// forwarding table or the source route the source route in
// the IP header.  This function will also be given packets
// for the local node the routing protocols can look at packets
// for protocol reasons. In this case, the message should not
// be modified and the PacketWasRouted must return FALSE.
//

typedef void (*RouterFunctionType)(
   GlomoNode* node,
   Message* msg,
   NODE_ADDR destAddr,
   BOOL *PacketWasRouted); 


void NetworkIpSetRouterFunction(
   GlomoNode* node,
   RouterFunctionType RouterFunctionPtr);


#define GET_INTERFACE_FROM_TABLE  0xFFFF


//
// NetworkIpSetPacketDropNotificationFunction allows a routing protocol
// to be notified when the network fails to deliver a packet to
// the next hop.  This usual signifies a link break. 
//

typedef void (*PacketDropNotificationFunctionType)(
   GlomoNode* node, 
   const Message * msg,
   const NODE_ADDR triedNextHop);

void NetworkIpSetPacketDropNotificationFunction(
   GlomoNode* node, 
   PacketDropNotificationFunctionType PacketDropHandlerPtr);

//
//  NetworkIpSendPacketToMacLayer is for the routing protocol defined
//  "Routing Function" to send the IP packet down specifying the
//  next hop address and interfaceId. Packets are fragmented
//  if necessary as they exit the network layer.
//


void NetworkIpSendPacketToMacLayer(     
   GlomoNode* node, 
   Message* msg, 
   InterfaceIdType interfaceId,
   NODE_ADDR nextHop);


void NetworkIpSendPacketToMacLayerWithDelay(     
   GlomoNode* node, 
   Message* msg, 
   InterfaceIdType interfaceId,
   NODE_ADDR nextHop,
   clocktype delay);



//
//  NetworkIpSendRawGlomoMessageToMacLayer is for the routing protocols
//  to directly (bypassing routing) send a routing protocol packet
//  down to the Mac layer specifying the next hop address and
//  interfaceId. The packet receives an IP header and is fragmented
//  if necessary as it exits the network layer.
//

void NetworkIpSendRawGlomoMessageToMacLayer(     
   GlomoNode* node,
   Message* rawMsg, 
   NODE_ADDR destAddr,
   NetworkQueueingPriorityType priority,
   unsigned char protocol,
   unsigned int ttl,
   InterfaceIdType interfaceId,
   NODE_ADDR nextHop);
   
//
//  NetworkIpSendRawGlomoMessageToMacLayer is just like
//  NetworkIpSendRawGlomoMessageToMacLayer except that the
//  action is delayed in simulation time.
//

void NetworkIpSendRawGlomoMessageToMacLayerWithDelay(     
   GlomoNode* node,
   Message* rawMsg, 
   NODE_ADDR destAddr,
   NetworkQueueingPriorityType priority,
   unsigned char protocol,
   unsigned int ttl,
   InterfaceIdType interfaceId,
   NODE_ADDR nextHop,
   clocktype delay);

//
//  NetworkIpSendPacketToMacLayerWithNewStrictSourceRoute
//  is for the routing protocol defined
//  "Routing Function" to send the IP packet down specifying
//  a new source route. Packets are fragmented
//  if necessary as they exit the network layer.
//


void NetworkIpSendPacketToMacLayerWithNewStrictSourceRoute(
   GlomoNode *node,
   Message *msg, 
   NODE_ADDR newRouteAddresses[],
   int numNewRouteAddresses,
   BOOL removeExistingRecordedRoute);


//
// NetworkIpSendNewPacket allows for the routing protocols in the
// network layer to send a new routing protocol packet.
// The packet follows the usual code path through the network
// layer where it is routed and possibly fragmented.
// If ttl (time to live) is 0, then it is set to the default TTL value.
//


void NetworkIpSendNewPacket(
   GlomoNode* node, 
   NODE_ADDR destAddr,
   NetworkQueueingPriorityType priority,
   unsigned char protocol,
   unsigned int ttl,
   char* payload, int payloadSize);


//
// NetworkIpSendNewPacketWithDelay allows for the routing protocols 
// in the network layer to send a new routing protocol packet with
// a time delay. 
// The packet follows the usual code path through the network
// layer where it is routed and possibly fragmented.
// If ttl (time to live) is 0, then it is set to the default TTL value.
//

void NetworkIpSendNewPacketWithDelay(
   GlomoNode* node, 
   NODE_ADDR destAddr,
   NetworkQueueingPriorityType priority,
   unsigned char protocol,
   unsigned int ttl,
   char* payload, int payloadSize,
   clocktype delay);

//
// NetworkIpSendRawGlomoMessage allows for the routing protocols in the
// network layer to send a new routing protocol packet.
// The message sent is a raw GloMoSim WITHOUT an IP header.
// The packet follows the usual code path through the network
// layer where it is routed and possibly fragmented.
// If ttl (time to live) is 0, then it is set to the default TTL value.
//

void NetworkIpSendRawGlomoMessage(
   GlomoNode* node,
   Message* rawMsg, 
   NODE_ADDR destAddr,
   NetworkQueueingPriorityType priority,
   unsigned char protocol,
   unsigned int ttl);

//
// NetworkIpSendRawGlomoMessageWithDelay allows for the routing
// protocols in the network layer to send a new routing protocol packet
// with a time delay. The message sent is a raw GloMoSim WITHOUT an 
// IP header. The packet follows the usual code path through the network
// layer where it is routed and possibly fragmented.
// If ttl (time to live) is 0, then it is set to the default TTL value.
//

void NetworkIpSendRawGlomoMessageWithDelay(
   GlomoNode* node,
   Message* rawMsg, 
   NODE_ADDR destAddr,
   NetworkQueueingPriorityType priority,
   unsigned char protocol,
   unsigned int ttl,
   clocktype delay);


// NetworkIpDeleteOutboundPacketsToANode removes all packets in the
// queue that are going to the nextHopAddress (for broken links).
// if returnToRoutingProtocol flag is true the packets are returned
// to the routing protocol via the callback mechanism, otherwise
// they are just dropped.

void NetworkIpDeleteOutboundPacketsToANode(
   GlomoNode* node,
   const NODE_ADDR nextHopAddress,
   const NODE_ADDR destinationAddress,
   const BOOL returnPacketsToRoutingProtocol);
                        
                        
//***
//*** Mode obsolete by an explicit packet drop function interface.
//***
// NetworkIpSetMacLayerStatusEventHandlerFunction allows a routing protocol
// to receive special MAC Layer status messages sent to the network
// layer for the sole purpose of routing protocols that use that 
// information for routing optimization. 
// The "Status Event Handler Function" must not write or free the message.
//
//
//typedef void (*MacLayerStatusEventHandlerFunctionType)(
//   GlomoNode* node, 
//   const Message * msg);
//
//void NetworkIpSetMacLayerStatusEventHandlerFunction(
//   GlomoNode* node, 
//   MacLayerStatusEventHandlerFunctionType StatusEventHandlerPtr);


//
// NetworkIpSetPromiscuousMessagePeekFunction allows a routing protocol
// to set the function that will be used by the routing protocol
// to sneak a "Peek" or "Tap" packets in the MAC layer when
// executing in promiscuous mode.  The "Peek Function" must not write
// to the message.
//

typedef void (*PromiscuousMessagePeekFunctionType)(
   GlomoNode* node, 
   const Message * msg);

void NetworkIpSetPromiscuousMessagePeekFunction(
   GlomoNode* node, 
   PromiscuousMessagePeekFunctionType PeekFunctionPtr);



void NetworkIpRemoveIpHeader(
   GlomoNode *node, 
   Message *msg, 
   NODE_ADDR* sourceAddress,
   NODE_ADDR* destinationAddress,
   NetworkQueueingPriorityType* priority,
   unsigned char* protocol,
   unsigned int* ttl);

void SendToUdp(
   GlomoNode *node,
   Message *msg,
   NetworkQueueingPriorityType priority,
   NODE_ADDR sourceAddress,
   NODE_ADDR destinationAddress);


//
// AddIpOptionField tacks on a custom "IP option" field to an IP
// packet (WARNING: Must be IP packet.).  The option code
// that identifies the custom option must not conflict with
// standard ones, most notably the source routing code.  The
// option size specifies the extra space beyond the standard
// 3 byte IP option header.  Currently this value must
// satisfy (Size+3 % 4 == 0).  The header fields are moved
// by this operation, so watch out for lingering pointers into
// the message.


void AddIpOptionField(
   GlomoNode* node, 
   Message* msg,
   int OptionCode, 
   int OptionSize); 

void AddIpHeader(
   GlomoNode *node,
   Message *msg,
   NODE_ADDR destinationAddress,
   NetworkQueueingPriorityType priority,
   unsigned char protocol,
   unsigned int ttl);
//---------------------------------------------------------------------------
   

typedef struct {
    NODE_ADDR destAddress;       /* destination address */
    InterfaceIdType interfaceId;    /* right now interface Id */
    NODE_ADDR nextHopAddress;    /* next hop. */
} NetworkForwardingTableRow;


typedef struct {
    int size;  /* number of entries */
    int allocatedSize;
    NetworkForwardingTableRow *row;  /* allocation in Init function in Ip */
} NetworkForwardingTable;


//---------------------------------------------------------------------------

/* max. time data can stored in assembly buffer */

#define NETWORK_IP_REASS_BUFF_TIMER (15 * SECOND)

#define MAX_IP_FRAGMENTS_SIMPLE_CASE        64

#define SMALL_REASSEMBLY_BUFFER_SIZE  2048
#define REASSEMBLY_BUFFER_EXPANSION_MULTIPLIER  8

       
//---------------------------------------------------------------------------
/* data structure used for assembling fragments */


typedef struct { 
   Message* packetUnderConstruction;
   int sizeLimit;
   clocktype expirationDate;
   unsigned short totalPacketLength;
   unsigned short fragmentationSize;
   unsigned char  fragmentIsHereBitTable[MAX_IP_FRAGMENTS_SIMPLE_CASE/8];
   BOOL endFragmentHasArrived;
   unsigned short endFragmentOffset;
} IpReassemblyBufferType;



typedef struct IpReassemblyBufferListCellStruct {
   struct IpReassemblyBufferListCellStruct* nextPtr;
   IpReassemblyBufferType reassemblyBuffer;
} IpReassemblyBufferListCellType;


typedef struct {
   IpReassemblyBufferListCellType* firstPtr;
   IpReassemblyBufferListCellType* freeListPtr;
} IpReassemblyBufferListType;


//---------------------------------------------------------------------------

typedef struct {
    int numPacketsSentToMac;
    int numPacketsRoutedForOtherNodes;
    
    int numPacketsDeliveredToThisNode;
    int deliveredPacketTtlTotal;
    
    int numNetworkUnreachableDrops;
    int numTtlExpirationDrops;
} NetworkIpStatsType;



typedef struct {
    unsigned short              packetIdCounter; // Used for identifying datagram 
    NetworkForwardingTable      forwardTable;
    NetworkRoutingProtocolType  routingProtocolChoice;    
    void*                       routingProtocol; 
    
    RouterFunctionType                     routerFunction;
    PacketDropNotificationFunctionType     packetDropHandlerFunction;
    
    PromiscuousMessagePeekFunctionType     promiscuousMessagePeekFunction;
    
    int maxPacketLength;
    
    IpReassemblyBufferListType reassemblyBufferList;
    
    IpOutputQueueType* interfaceQueues[MAX_NUM_INTERFACES];
    
    NetworkIpStatsType stats;
} GlomoNetworkIp;
    
//---------------------------------------------------------------------------
       
       
/* functions called by network.pc */

void NetworkIpPreInit(GlomoNode *node);
void NetworkIpInit(GlomoNode *node, const GlomoNodeInput *nodeInput);
void NetworkIpFinalize(GlomoNode *node);
void NetworkIpLayer(GlomoNode *node, Message *msg);

//---------------------------------------------------------------------------

// GloMoSim User modified functions defined in "user_nwip.pc".

void NetworkIpUserProtocolInit(
   GlomoNode *node,
   const GlomoNodeInput *nodeInput,
   const char* routingProtocolString, 
   NetworkRoutingProtocolType* routingProtocolChoice,
   void** routingProtocolData);
      
void NetworkIpUserHandleProtocolEvent(GlomoNode* node, Message* msg);

void NetworkIpUserHandleProtocolPacket(
   GlomoNode* node, 
   Message* msg, 
   unsigned char ipProtocol,
   NODE_ADDR sourceAddress,
   NODE_ADDR destinationAddress, 
   int ttl);

void NetworkIpUserProtocolFinalize(
   GlomoNode* node, 
   int userProtocolNumber);


#endif



