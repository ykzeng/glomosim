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
 * $Id: cbr_server.h,v 1.8 2000/01/25 23:00:17 mineo Exp $
 */



#ifndef _CBR_SERVER_H_
#define _CBR_SERVER_H_

#include "structmsg.h"


#define APP_CBR_SERVER_FILE     "CBR_SERVER.EXCEL"


/* Structure containing cbr related information. */
typedef struct glomo_app_cbr_server_str {
    NODE_ADDR localAddr;
    NODE_ADDR remoteAddr;
    int uniqueId;
    clocktype sessionStart;
    clocktype sessionFinish;
    clocktype sessionLastReceived;
    BOOL sessionIsClosed;
    long numBytesRecvd;
    long numPktsRecvd;
    clocktype totalEndToEndDelay;
    long seqNo;
} GlomoAppCbrServer;


/*
 * NAME:        AppLayerCbrServer.
 * PURPOSE:     Models the behaviour of CbrServer Server on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerCbrServer(GlomoNode *nodePtr, Message *msg);


/*
 * NAME:        AppCbrServerInit.
 * PURPOSE:     listen on CbrServer server port.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETURN:      none.
 */
void
AppCbrServerInit(GlomoNode *nodePtr);


/*
 * NAME:        AppCbrServerPrintStats.
 * PURPOSE:     Prints statistics of a CbrServer session.
 * PARAMETERS:  nodePtr - pointer to this node.
 *              serverPtr - pointer to the cbr server data structure.
 * RETURN:      none.
 */
void
AppCbrServerPrintStats(GlomoNode *nodePtr, GlomoAppCbrServer *serverPtr);


/*
 * NAME:        AppCbrServerFinalize.
 * PURPOSE:     Collect statistics of a CbrServer session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the cbr server data structure.
 * RETURN:      none.
 */
void
AppCbrServerFinalize(GlomoNode *nodePtr, GlomoAppCbrServer *serverPtr);


/*
 * NAME:        AppCbrServerGetCbrServer.
 * PURPOSE:     search for a cbr server data structure.
 * PARAMETERS:  nodePtr - cbr server.
 *              uniqueId - uniqueId of cbr client/server pair.
 *              remoteAddr - cbr client sending the data.
 * RETURN:      the pointer to the cbr server data structure,
 *              NULL if nothing found.
 */
static GlomoAppCbrServer *
AppCbrServerGetCbrServer(GlomoNode *nodePtr, 
                         NODE_ADDR remoteAddr, 
                         int uniqueId);


/*
 * NAME:        AppCbrServerNewCbrServer.
 * PURPOSE:     create a new cbr server data structure, place it
 *              at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              remoteAddr - remote address.
 *              uniqueId - uniqueId of cbr client/server pair.
 * RETRUN:      the pointer to the created cbr server data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppCbrServer *
AppCbrServerNewCbrServer(GlomoNode *nodePtr, 
                         NODE_ADDR remoteAddr, 
                         int uniqueId);


#endif /* _CBR_SERVER_H_ */

