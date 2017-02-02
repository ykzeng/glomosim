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
 * $Id: telnet_server.h,v 1.4 1999/09/05 04:31:51 jmartin Exp $
 *
 * This file contains data structure used by telnet server and 
 * prototypes of functions defined in telnet_server.pc.
 */

#ifndef _TELNET_SERVER_H_
#define _TELNET_SERVER_H_

#include "message.h"

typedef struct glomo_app_telnet_server_str {
    int connectionId;
    NODE_ADDR localAddr; 
    NODE_ADDR remoteAddr;
    clocktype sessionStart;
    clocktype sessionFinish;
    BOOL sessionIsClosed;
    long numBytesSent;
    long numBytesRecvd;
} GlomoAppTelnetServer;



/*
 * NAME:        AppLayerTelnetServer.
 * PURPOSE:     Models the behaviour of Telnet server on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerTelnetServer(GlomoNode *nodePtr, Message *msg);



/*
 * NAME:        AppTelnetServerInit.
 * PURPOSE:     listen on Telnet server port.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETURN:      none.
 */
void
AppTelnetServerInit(GlomoNode *nodePtr);



/*
 * NAME:        AppTelnetServerFinalize.
 * PURPOSE:     Collect statistics of a Telnet session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the telnet server data structure.
 * RETURN:      none.
 */
void
AppTelnetServerFinalize(GlomoNode *nodePtr, GlomoAppTelnetServer *serverPtr);



/*
 * NAME:        AppTelnetServerGetTelnetServer.
 * PURPOSE:     search for a telnet server data structure.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              connId - connection ID of the telnet server.
 * RETURN:      the pointer to the telnet server data structure,
 *              NULL if nothing found.
 */
static GlomoAppTelnetServer *
AppTelnetServerGetTelnetServer(GlomoNode *nodePtr, int connId);



/*
 * NAME:        AppTelnetServerNewTelnetServer.
 * PURPOSE:     create a new telnet server data structure, place it
                at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              openResult - result of the open request.
 * RETRUN:      the pointer to the created telnet server data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppTelnetServer *
AppTelnetServerNewTelnetServer(GlomoNode *nodePtr,
                               TransportToAppOpenResult *openResult);



/*
 * NAME:        AppTelnetServerSendResponse.
 * PURPOSE:     call AppTelnetServerRespPktSize() to get the
 *              response packet size,
                and send the packet.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              serverPtr - pointer to the server data structure.
 * RETRUN:      none.
 */
static void
AppTelnetServerSendResponse(GlomoNode *nodePtr, 
                            GlomoAppTelnetServer *serverPtr);



/*
 * NAME:        AppTelnetServerRespPktSize.
 * PURPOSE:     call tcplib function telnet_pktsize().
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETRUN:      telnet control packet size.
 */
static int
AppTelnetServerRespPktSize(GlomoNode *nodePtr);


#endif /* _TELNET_SERVER_H_ */

