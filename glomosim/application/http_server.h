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
 * $Id: http_server.h,v 1.2 2000/01/10 20:51:12 gandy Exp $
 *
 * This file contains data structure used by http server and 
 * prototypes of functions defined in http_server.pc.
 */

#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_

#include "structmsg.h"

typedef struct glomo_app_http_server_str 
{
    int connectionId;
    NODE_ADDR localAddr; 
    NODE_ADDR remoteAddr;
    clocktype sessionStart;
    clocktype sessionFinish;
    BOOL sessionIsClosed;
    long numBytesSent;
    long numBytesRecvd;
	long pagesSent;
	long bytesRemaining;
} GlomoAppHttpServer;



/*
 * NAME:        AppLayerHttpServer.
 * PURPOSE:     Models the behaviour of Http Server on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerHttpServer(GlomoNode *nodePtr, Message *msg);

/*
 * NAME:        AppHttpServerInit.
 * PURPOSE:     listen on Http server port.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETURN:      none.
 */
void
AppHttpServerInit(GlomoNode *nodePtr);

/*
 * NAME:        AppHttpServerPrintStats.
 * PURPOSE:     Prints statistics of a Http session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the http server data structure.
 * RETURN:      none.
 */
static void
AppHttpServerPrintStats(GlomoNode *nodePtr, GlomoAppHttpServer *serverPtr);

/*
 * NAME:        AppHttpServerFinalize.
 * PURPOSE:     Collect statistics of a Http session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the http server data structure.
 * RETURN:      none.
 */
void
AppHttpServerFinalize(GlomoNode *nodePtr, GlomoAppHttpServer *serverPtr);

/*
 * NAME:        AppHttpServerGetHttpServer.
 * PURPOSE:     search for a http server data structure.
 * PARAMETERS:  appList - link list of applications,
 *              connId - connection ID of the http server.
 * RETURN:      the pointer to the http server data structure,
 *              NULL if nothing found.
 */
static GlomoAppHttpServer *
AppHttpServerGetHttpServer(GlomoNode *nodePtr, int connId);

/*
 * NAME:        AppHttpServerRemoveHttpServer.
 * PURPOSE:     Remove an HTTP server process that corresponds to the 
 *              given connectionId 
 * PARAMETERS:  nodePtr - pointer to the node.
 *              closeRes - the close connection results from TCP
 * RETURN:      none.
 */
static void AppHttpServerRemoveHttpServer(GlomoNode *nodePtr,
                                          TransportToAppCloseResult *closeRes);

/*
 * NAME:        AppHttpServerNewHttpServer.
 * PURPOSE:     create a new http server data structure, place it
 *              at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              openResult - result of the open request.
 * RETRUN:      the pointer to the created http server data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppHttpServer *
AppHttpServerNewHttpServer(GlomoNode *nodePtr,
                         TransportToAppOpenResult *openResult);

/*
 * NAME:        AppHttpServerSendCtrlPkt.
 * PURPOSE:     call AppHttpCtrlPktSize() to get the response packet
 *              size, and send the packet.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              serverPtr - pointer to the server data structure.
 * RETRUN:      none.
 */
static void
AppHttpServerSendCtrlPkt(GlomoNode *nodePtr, GlomoAppHttpServer *serverPtr);

/*
 * NAME:        AppHttpClientDeterminePrimaryReplyLength.
 * PURPOSE:     Return the number of bytes in the primary reply
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      the number of bytes.
 */
long AppHttpServerDeterminePrimaryReplyLength(GlomoNode *node);

/*
 * NAME:        AppHttpClientDetermineSecondaryReplyLength.
 * PURPOSE:     Return the number of bytes in the secondary reply
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      the number of bytes.
 */
long AppHttpServerDetermineSecondaryReplyLength(GlomoNode *node);

/*
 * NAME:        AppHttpServerSendSecondaryReply.
 * PURPOSE:     Send the secondary reply to the client.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the server's data structure.
 *              secondaryReplyLength - the length in bytes of the reply.
 * RETURN:      none.
 */
static void AppHttpServerSendSecondaryReply(GlomoNode *node,
                                          GlomoAppHttpServer *serverPtr,
                                          long secondaryReplyLength);

/*
 * NAME:        AppHttpServerSendPrimaryReply.
 * PURPOSE:     Send the primary reply to the client.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the server's data structure.
 *              primaryReplyLength - the length in bytes of the reply.
 * RETURN:      none.
 */
static void AppHttpServerSendPrimaryReply(GlomoNode *node,
				                         GlomoAppHttpServer *serverPtr,
									     long primaryReplyLength);

#endif /* _HTTP_SERVER_H_ */

