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
 * $Id: telnet_client.h,v 1.4 1999/09/05 04:31:41 jmartin Exp $
 *
 * This file contains data structure used by telnet client and 
 * prototypes of functions defined in telnet_client.pc.
 */
#ifndef _TELNET_CLIENT_H_
#define _TELNET_CLIENT_H_

#include "message.h"

typedef struct glomo_app_telnet_client_str {
    int connectionId;
    NODE_ADDR localAddr; 
    NODE_ADDR remoteAddr;
    clocktype sessionStart;
    clocktype sessionFinish;
    clocktype sessDuration;
    BOOL sessionIsClosed;
    long numBytesSent;
    long numBytesRecvd;

    long uniqueId;
} GlomoAppTelnetClient;



/*
 * NAME:        AppLayerTelnetClient.
 * PURPOSE:     Models the behaviour of TelnetClient Client on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerTelnetClient(GlomoNode *nodePtr, Message *msg);


/*
 * NAME:        AppTelnetClientInit.
 * PURPOSE:     Initialize a TelnetClient session.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              serverAddr - address of the server,
 *              sessDuration - length of telnet session.
 *              waitTime - time until the session starts.
 * RETURN:      none.
 */
void
AppTelnetClientInit(GlomoNode *nodePtr, NODE_ADDR serverAddr,
                    clocktype sessDuration, clocktype waitTime);



/*
 * NAME:        AppTelnetClientFinalize.
 * PURPOSE:     Collect statistics of a TelnetClient session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              clientPtr - pointer to the telnet client data structure.
 * RETURN:      none.
 */
void
AppTelnetClientFinalize(GlomoNode *nodePtr, GlomoAppTelnetClient *clientPtr);



/*
 * NAME:        AppTelnetClientGetTelnetClient.
 * PURPOSE:     search for a telnet client data structure.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              connId - connection ID of the telnet client.
 * RETURN:      the pointer to the telnet client data structure,
 *              NULL if nothing found.
 */
static GlomoAppTelnetClient *
AppTelnetClientGetTelnetClient(GlomoNode *nodePtr, int connId);




/*
 * NAME:        AppTelnetClientUpdateTelnetClient.
 * PURPOSE:     create a new telnet client data structure, place it
                at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              openResult - result of the open request.
 * RETRUN:      the pointer to the created telnet client data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppTelnetClient *
AppTelnetClientUpdateTelnetClient(GlomoNode *nodePtr,
                                  TransportToAppOpenResult *openResult);



/*
 * NAME:        AppTelnetClientNewTelnetClient.
 * PURPOSE:     create a new telnet client data structure, place it
                at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              serverAddr - server node of this telnet session.
 *              sessDuration - length of telnet session.
 * RETRUN:      the pointer to the created telnet client data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppTelnetClient *
AppTelnetClientNewTelnetClient(GlomoNode *nodePtr,
                               NODE_ADDR serverAddr,
                               clocktype sessDuration);


/*
 * NAME:        AppTelnetClientScheduleNextPkt.
 * PURPOSE:     schedule the next packet the client will send.  If next packet
 *              won't arrive until the finish deadline, schedule a close.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              clientPtr - pointer to the telnet client data structure.
 * RETRUN:      none.
 */
static void
AppTelnetClientScheduleNextPkt(GlomoNode *nodePtr, 
                               GlomoAppTelnetClient *clientPtr);



/*
 * NAME:        AppTelnetClientSessDuration.
 * PURPOSE:     call tcplib function telnet_duration to get the duration
 *              of this session.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETRUN:      session duration in clocktype.
 */
static clocktype
AppTelnetClientSessDuration(GlomoNode *nodePtr);


/*
 * NAME:        AppTelnetClientPktInterval.
 * PURPOSE:     call tcplib function telnet_interarrival to get the
 *              between the arrival of the next packet and the current one.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETRUN:      interarrival time in clocktype.
 */
static clocktype
AppTelnetClientPktInterval(GlomoNode *nodePtr);




#endif /* _TELNET_CLIENT_H_ */

