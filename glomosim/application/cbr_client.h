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
 * $Id: cbr_client.h,v 1.7 2000/01/25 23:00:17 mineo Exp $
 */


#ifndef _CBR_CLIENT_H_
#define _CBR_CLIENT_H_

#include "structmsg.h"


#define APP_CBR_CLIENT_FILE     "CBR_CLIENT.EXCEL"



/* Structure containing cbr client information. */
typedef struct glomo_app_cbr_client_str
{
    NODE_ADDR   localAddr;
    NODE_ADDR   remoteAddr;
    clocktype interval;
    clocktype sessionStart;
    clocktype sessionFinish;
    clocktype sessionLastSent;
    clocktype endTime;
    BOOL sessionIsClosed;
    long numBytesSent;
    long numPktsSent;
    long itemsToSend;
    long itemSize;
    long uniqueId;
    long seqNo;
} GlomoAppCbrClient;


/*
 * NAME:        AppLayerCbrClient.
 * PURPOSE:     Models the behaviour of CbrClient Client on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerCbrClient(GlomoNode *nodePtr, Message *msg);


/*
 * NAME:        AppCbrClientInit.
 * PURPOSE:     Initialize a CbrClient session.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              serverAddr - address of the server,
 *              itemsToSend - number of items to send,
 *              itemSize - size of each packet,
 *              interval - interval of packet transmission rate.
 *              startTime - time until the session starts.
 *              endTime - time until the session end.
 * RETURN:      none.
 */
void
AppCbrClientInit(GlomoNode *nodePtr,
                 NODE_ADDR serverAddr,
                 long itemsToSend,
                 long itemSize,
                 clocktype interval,
                 clocktype startTime,
                 clocktype endTime);

/*
 * NAME:        AppCbrClientPrintStats.
 * PURPOSE:     Prints statistics of a CbrClient session.
 * PARAMETERS:  nodePtr - pointer to the this node.
 *              clientPtr - pointer to the cbr client data structure.
 * RETURN:      none.
 */
void
AppCbrClientPrintStats(GlomoNode *nodePtr, GlomoAppCbrClient *clientPtr);


/*
 * NAME:        AppCbrClientFinalize.
 * PURPOSE:     Collect statistics of a CbrClient session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              clientPtr - pointer to the cbr client data structure.
 * RETURN:      none.
 */
void
AppCbrClientFinalize(GlomoNode *nodePtr, GlomoAppCbrClient *clientPtr);


/*
 * NAME:        AppCbrClientGetCbrClient.
 * PURPOSE:     search for a cbr client data structure.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              uniqueId - connection ID of the cbr client.
 * RETURN:      the pointer to the cbr client data structure,
 *              NULL if nothing found.
 */
static GlomoAppCbrClient *
AppCbrClientGetCbrClient(GlomoNode *nodePtr, int uniqueId);


/*
 * NAME:        AppCbrClientNewCbrClient.
 * PURPOSE:     create a new cbr client data structure, place it
 *              at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              remoteAddr - remote address.
 *              itemsToSend - number of items to send,
 *              itemSize - size of data packets.
 *              interval - interdeparture time of packets.
 *              startTime - time when session is started.
 *              endTime - time when session is ended.
 * RETURN:      the pointer to the created cbr client data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppCbrClient *
AppCbrClientNewCbrClient(GlomoNode *nodePtr, 
                         NODE_ADDR remoteAddr,
                         long itemsToSend,
                         long itemSize,
                         clocktype interval,
                         clocktype startTime,
                         clocktype endTime);


/*
 * NAME:        AppCbrClientScheduleNextPkt.
 * PURPOSE:     schedule the next packet the client will send.  If next packet
 *              won't arrive until the finish deadline, schedule a close.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              clientPtr - pointer to the cbr client data structure.
 * RETRUN:      none.
 */
static void
AppCbrClientScheduleNextPkt(GlomoNode *nodePtr, GlomoAppCbrClient *clientPtr);





#endif /* _CBR_CLIENT_H_ */

