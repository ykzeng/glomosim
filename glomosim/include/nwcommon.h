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
 * $Id: nwcommon.h,v 1.19 2000/11/10 06:04:50 mineo Exp $
 *
 * File: nwCommon.h
 * By: Teresa Yan (tyan@cs.ucla.edu)
 * Objective: for routing protocol to update IP forwarding table and
 *            layer on top of IP to encapsulate IP header by setting
 *            certain fields in IP.
 * Date: 2/22/1999.
 */

#ifndef _NWCOMMON_H_
#define _NWCOMMON_H_

#include "message.h"
 
/* protocol number for IP */
#define IPPROTO_TCP  6
#define IPPROTO_UDP  17
#define IPPROTO_OSPF 87
#define IPPROTO_BELLMANFORD 520
#define IPPROTO_FISHEYE 530
#define IPPROTO_AODV 123
#define IPPROTO_DSR 135
#define IPPROTO_ODMRP 145
#define IPPROTO_LAR1 110
#define IPPROTO_ZRP 133
#define NETWORK_UNREACHABLE   -2
#define DEFAULT_INTERFACE 0


/*  FUNCTION    NetworkInitForwardingTable
 *  PURPOSE     initialize the fowarding table, allocate enough memory for
 *              number of rows, used by ip
 *  PARAMETER   node
 *  RETURN      None.
 */
void NetworkInitForwardingTable(GlomoNode *node);

/*  FUNCTION    NetworkEmptyFowardingTable
 *  PURPOSE     empty out all the entries in the routing table 
 *              basically set the size of table back to 0.
 *  PARAMETER   node
 *  RETURN      None. 
 */

void NetworkEmptyForwardingTable(GlomoNode *node);

                                  
/*  FUNCTION    NetworkGetInterfaceAndNextHopFromForwardingTable
 *  PURPOSE     get the interface Id node that lead to destId. 
 *  PARAMETER   node - its own node.
 *              destId - destination Id.
 *              interfaceId - Interface to send packet.
 *              nextHopAddress - Next hop address for the packet.
 *                               Returns NETWORK_UNREACHABLE when the next
 *                               hop cannot be found in the table.
 */
 
void NetworkGetInterfaceAndNextHopFromForwardingTable(
    GlomoNode *node,
    NODE_ADDR destId,
    InterfaceIdType* interfaceId,
    NODE_ADDR* nextHopAddress);

                                        

/*  FUNCTION    NetworkUpdateForwardingTable 
 *  PURPOSE     update entry with destId,
 *              search for the row with destId, update its interfaceId.
 *               if no row is found, add a new row and increase table size.
 *  PARAMETER   node   - its own node.
 *              destId - destination Id to match in the table
 *              interfaceId - interface to send the packet.
 *              nextHopAddress - The next node on the route.
 *  RETURN      TRUE,  if new row is added.
 *              FALSE, if original row existed (only update).
 */

void NetworkUpdateForwardingTable(
    GlomoNode *node, 
    NODE_ADDR destId,
    InterfaceIdType interfaceId,
    NODE_ADDR nextHopAddress);


/*  FUNCTION    NetworkPrintForwardingTable
 *  PURPOSE     display all entries in routing table of the node.
 *  PARAMETER   node
 *  RETURN      None.
 */
void NetworkPrintForwardingTable(GlomoNode *node);


/*  FUNCTION    NetworkPrintIpHeader
 *  PURPOSE     for application (run directly on top of IP) with source routing
 *              to print the ip header when received packet from network.
 *              particularly to look at the recorded routes of the packet.
 *              note: network will not remove IP header.
 *              fields in Ip Header are not totally right when handed to top,
 *              fields that are correct: 
 *              totalLength, headerLength, protocol number, sourceId, 
 *              destinationId, and recorded strict source routing fields.
 *  PARAMETER   msg - message encapsulated by IP header.
 *  RETURN      None.
 */
void NetworkPrintIpHeader(Message *msg);


#endif /* _NWCOMMON_H_ */

