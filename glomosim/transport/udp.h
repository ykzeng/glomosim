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
 * $Id: udp.h,v 1.5 2001/02/16 04:27:01 jmartin Exp $
 *
 * File: udp.h
 * Author: Teresa Yan (tyan@cs.ucla.edu)
 * Objective: UDP 
 * Reference: Computer Networks by Tannebaum      
 * Date: 2/26/1999.
 */

#ifndef _UDP_H_
#define _UDP_H_

#include "main.h"

typedef struct TransportUdpHeader_ {  /* UDP header */
    short sourcePort;                 /* source port */
    short destPort;                   /* destination port */
    short length;                     /* length of the packet */
    short checksum;                   /* checksum */
} TransportUdpHeader;


typedef struct TransprotUdpStat_ {
    int numPktFromApp; 
    int numPktToApp;
} TransportUdpStat;

struct GlomoTransportUdpStruct {
    BOOL udpStatsEnabled;    /* whether to collect stats */
    TransportUdpStat *statistics; /*statistics */
};


/*
 * FUNCTION    TransportUdpInit
 * PURPOSE     Initialization function for UDP.
 *
 * Parameters:
 *     node:      node being initialized.
 *     nodeInput: structure containing contents of input file
 */
void TransportUdpInit(GlomoNode *node, const GlomoNodeInput *nodeInput); 


/*
 * FUNCTION    TransportLayerUdp.
 * PURPOSE     Models the behaviour of UDP on receiving the
 *             message encapsulated in msgHdr
 *
 * Parameters:
 *     node:     node which received the message
 *     msg:   message received by the layer
 */
void TransportUdpLayer(GlomoNode *node, Message *msg);


/*
 * FUNCTION    TransportUdpFinalize
 * PURPOSE     Called at the end of simulation to collect the results of
 *             the simulation of the UDP protocol of Transport Layer.
 *
 * Parameter:
 *     node:     node for which results are to be collected.
 */
void TransportUdpFinalize(GlomoNode *node);


void TransportUdpSendToApp(GlomoNode *node, Message *msg);
void TransportUdpSendToNetwork(GlomoNode *node, Message *msg);

#endif /* _UDP_H_ */

