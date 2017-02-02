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
 * $Id: tcp.h,v 1.7 2001/02/16 04:28:21 jmartin Exp $
 * This file contains simulation related definitions for TCP.
 */

#ifndef _TCP_H_
#define _TCP_H_

#include "fileio.h"
#include "main.h"
#include "message.h"

#include "in_pcb.h"
#include "tcp_seq.h"
#include "tcp_var.h"
#include "ip.h"

/*
 * Connection opening and closing status, used in messages
 * sent to application.
 */
#define TCP_CONN_ACTIVE_OPEN            0 
#define TCP_CONN_PASSIVE_OPEN           1 
#define TCP_CONN_ACTIVE_CLOSE           0
#define TCP_CONN_PASSIVE_CLOSE          1 


// Typedef GlomoTransportTcp;

struct GlomoTransportTcpStruct {
    struct inpcb head;       /* head of queue of active inpcb's */
    tcp_seq tcpIss;          /* initial sequence number */
    unsigned long tcpNow;    /* current time in ticks, 1 tick = 500 ms */
    BOOL tcpIsStarted;       /* whether TCP timers are going */
    BOOL tcpStatsEnabled;    /* whether to collect stats */
    struct tcpstat *tcpStat; /* statistics */
    struct tcpcb *tp;
};

/*
 * FUNCTION    TransportTcpInit
 * PURPOSE     Initialization function for TCP.
 *
 * Parameters:
 *     node:      node being initialized.
 *     nodeInput: structure containing contents of input file
 */
void TransportTcpInit(GlomoNode *node, const GlomoNodeInput *nodeInput); 


/*
 * FUNCTION    TransportTcpLayer.
 * PURPOSE     Models the behaviour of TCP on receiving the
 *             message encapsulated in msgHdr
 *
 * Parameters:
 *     node:     node which received the message
 *     msgHdr:   message received by the layer
 */
void TransportTcpLayer(GlomoNode *node, Message *msg);


/*
 * FUNCTION    TransportTcpFinalize
 * PURPOSE     Called at the end of simulation to collect the results of
 *             the simulation of the TCP protocol of Transport Layer.
 *
 * Parameter:
 *     node:     node for which results are to be collected.
 */
void TransportTcpFinalize(GlomoNode *node);

#endif /* _TCP_H_ */

