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
 * $Id: app_util.h,v 1.12 2000/02/24 02:14:36 jmartin Exp $
 * This file contains prototypes of the functions defined
 * in app_util.pc.
 */

#ifndef _APP_UTIL_H_
#define _APP_UTIL_H_

#include "main.h"
#include "network.h"


/*
 * FUNCTION: AppUdpSendNewData
 * PURPOSE:    allocate a new GLOMO message and send to UDP.
 * PARAMETERS: node - node that is sending the data.
 *             appType - application type, to be used as destination port.
 *             destAddr - the destination node Id data is sent to.
 *             payload  - pointer to the data.
 *             payloadSize - size of the data in bytes.
 *             delay - send the data after this delay.
 */
void
AppUdpSendNewData(GlomoNode *node, APP_TYPE appType, NODE_ADDR destAddr,
                  char *payload, long payloadSize, clocktype delay);


/*
 * FUNCTION: AppUdpSendNewDataWithPriority
 * PURPOSE:    allocate a new GLOMO message and send to UDP.
 * PARAMETERS: node - node that is sending the data.
 *             appType - application type, to be used as destination port.
 *             destAddr - the destination node Id data is sent to.
 *             payload  - pointer to the data.
 *             payloadSize - size of the data in bytes.
 *             priority - priority of data.
 *             delay - send the data after this delay.
 */
void
AppUdpSendNewDataWithPriority(GlomoNode *node,
                              APP_TYPE appType,
                              NODE_ADDR destAddr,
                              char *payload,
                              long payloadSize,
                              NetworkQueueingPriorityType priority,
                              clocktype delay);


/*
 * FUNCTION: AppUdpSendNewHeaderData
 * PURPOSE:    allocate a new GLOMO message and send to UDP.
 * PARAMETERS: node - node that is sending the data.
 *             appType - application type, to be used as destination port.
 *             destAddr - the destination node Id data is sent to.
 *             header - header of the payload.
 *             headerSize - size of the header.q
 *             payload  - pointer to the data.
 *             payloadSize - size of the data in bytes.
 *             delay - send the data after this delay.
 */

void
AppUdpSendNewHeaderData(GlomoNode *node, APP_TYPE appType, NODE_ADDR destAddr,
                        char *header, long headerSize, char *payload,
                        long payloadSize, clocktype delay);


/*
 * FUNCTION: AppUdpSendNewHeaderDataWithPriority
 * PURPOSE:    allocate a new GLOMO message and send to UDP.
 * PARAMETERS: node - node that is sending the data.
 *             appType - application type, to be used as destination port.
 *             destAddr - the destination node Id data is sent to.
 *             header - header of the payload.
 *             headerSize - size of the header.q
 *             payload  - pointer to the data.
 *             payloadSize - size of the data in bytes.
 *             priority - priority of data.
 *             delay - send the data after this delay.
 */
void
AppUdpSendNewHeaderDataWithPriority(GlomoNode *node,
                                    APP_TYPE appType,
                                    NODE_ADDR destAddr,
                                    char *header,
                                    long headerSize,
                                    char *payload,
                                    long payloadSize,
                                    NetworkQueueingPriorityType priority,
                                    clocktype delay);


/*
 * NAME:        AppTcpServerListen.
 * PURPOSE:     listen on a server port.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              transProtocolType - which transport protocol to use.
 *              appType - which application initiates this request.
 *              serverAddr - server address.
 *              serverPort - server port number.
 * RETURN:      none.
 */
void
AppTcpServerListen(GlomoNode *nodePtr,
                   TRANSPORT_PROTOCOL transProtocolType,
                   APP_TYPE appType,
                   NODE_ADDR serverAddr,
                   short serverPort);


/*
 * NAME:        AppTcpServerListenWithPriority.
 * PURPOSE:     listen on a server port.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              transProtocolType - which transport protocol to use.
 *              appType - which application initiates this request.
 *              serverAddr - server address.
 *              serverPort - server port number.
 *              priority - priority of this data for this session.
 * RETURN:      none.
 */
void
AppTcpServerListenWithPriority(GlomoNode *nodePtr,
                               TRANSPORT_PROTOCOL transProtocolType,
                               APP_TYPE appType,
                               NODE_ADDR serverAddr,
                               short serverPort,
                               NetworkQueueingPriorityType priority);


/*
 * NAME:        AppTcpOpenConnection.
 * PURPOSE:     Open a connection.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              transProtocolType - which transport protocol to use.
 *              appType - which application initiates this request.
 *              remoteAddr - address of the remote node.
 *              remotePort - port number on the remote node (server port).
 *              uniqueId - used to determine which client is requesting
 *                         connection.
 *              waitTime - time until the session starts.
 * RETURN:      none.
 */
void
AppTcpOpenConnection(GlomoNode *nodePtr, TRANSPORT_PROTOCOL transProtocolType,
                     APP_TYPE appType, NODE_ADDR remoteAddr,
                     short remotePort, long uniqueId, clocktype waitTime);



/*
 * NAME:        AppTcpOpenConnectionWithPriority.
 * PURPOSE:     Open a connection.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              transProtocolType - which transport protocol to use.
 *              appType - which application initiates this request.
 *              remoteAddr - address of the remote node.
 *              remotePort - port number on the remote node (server port).
 *              uniqueId - used to determine which client is requesting
 *                         connection.
 *              waitTime - time until the session starts.
 *              priority - priority of the data.
 * RETURN:      none.
 */
void
AppTcpOpenConnectionWithPriority(GlomoNode *nodePtr,
                                 TRANSPORT_PROTOCOL transProtocolType,
                                 APP_TYPE appType,
                                 NODE_ADDR remoteAddr,
                                 short remotePort,
                                 long uniqueId,
                                 clocktype waitTime,
                                 NetworkQueueingPriorityType priority);


/*
 * NAME:        AppTcpSendData.
 * PURPOSE:     send an application data unit.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              protocolType - which transport protocol to use.
 *              connId - connection id.
 *              payload - data to send.
 *              length - length of the data to send.
 * RETRUN:      none.
 */
void
AppTcpSendData(GlomoNode *nodePtr, TRANSPORT_PROTOCOL protocolType, int connId,
               char *payload, int length);


/*
 * NAME:        AppTcpCloseConnection.
 * PURPOSE:     close the connection.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              protocolType - which transport protocol to use.
 *              connId - connection id.
 * RETRUN:      none.
 */
void
AppTcpCloseConnection(GlomoNode *nodePtr, TRANSPORT_PROTOCOL protocolType,
                      int connId);




#endif /* _APP_UTIL_H_ */

