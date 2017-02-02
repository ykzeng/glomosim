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
 * $Id: ftp_client.h,v 1.5 2000/10/20 19:17:23 jmartin Exp $
 *
 * This file contains data structure used by ftp client and 
 * prototypes of functions defined in ftp_client.pc.
 */
#ifndef _FTP_CLIENT_H_
#define _FTP_CLIENT_H_

#include "structmsg.h"

typedef struct glomo_app_ftp_client_str 
{
    int connectionId;
    NODE_ADDR localAddr; 
    NODE_ADDR remoteAddr;
    clocktype sessionStart;
    clocktype sessionFinish;
    BOOL sessionIsClosed;
    int itemsToSend;
    int itemSizeLeft;
    int numBytesSent;
    int numBytesRecvd;

    int uniqueId;
    unsigned short seed[3];
} GlomoAppFtpClient;



/*
 * NAME:        AppLayerFtpClient.
 * PURPOSE:     Models the behaviour of Ftp Client on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerFtpClient(GlomoNode *nodePtr, Message *msg);



/*
 * NAME:        AppFtpClientInit.
 * PURPOSE:     Initialize a Ftp session.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              serverAddr - address of the server,
 *              itemsToSend - number of items to send,
 *              waitTime - time until the session starts.
 * RETURN:      none.
 */
void
AppFtpClientInit(GlomoNode *nodePtr, NODE_ADDR serverAddr,
                 int itemsToSend, clocktype waitTime);



/*
 * NAME:        AppFtpClientPrintStats.
 * PURPOSE:     Prints statistics of a Ftp session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              clientPtr - pointer to the ftp client data structure.
 * RETURN:      none.
 */
static void
AppFtpClientPrintStats(GlomoNode *nodePtr, GlomoAppFtpClient *clientPtr);


/*
 * NAME:        AppFtpClientFinalize.
 * PURPOSE:     Collect statistics of a Ftp session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              clientPtr - pointer to the ftp client data structure.
 * RETURN:      none.
 */
void
AppFtpClientFinalize(GlomoNode *nodePtr, GlomoAppFtpClient *clientPtr);





/*
 * NAME:        AppFtpClientGetFtpClient.
 * PURPOSE:     search for a ftp client data structure.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              connId - connection ID of the ftp client.
 * RETURN:      the pointer to the ftp client data structure,
 *              NULL if nothing found.
 */
static GlomoAppFtpClient *
AppFtpClientGetFtpClient(GlomoNode *nodePtr, int connId);


/*
 * NAME:        AppFtpClientUpdateFtpClient.
 * PURPOSE:     update existing ftp client data structure by including 
 *              connection id.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              openResult - result of the open request.
 * RETRUN:      the pointer to the created ftp client data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppFtpClient *
AppFtpClientUpdateFtpClient(GlomoNode *nodePtr,
                            TransportToAppOpenResult *openResult);



/*
 * NAME:        AppFtpClientNewFtpClient.
 * PURPOSE:     create a new ftp client data structure, place it
 *              at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverAddr - ftp server to this client.
 *              itemsToSend - number of ftp items to send in simulation.
 * RETRUN:      the pointer to the created ftp client data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppFtpClient *
AppFtpClientNewFtpClient(GlomoNode *nodePtr,
                         NODE_ADDR serverAddr,
                         int itemsToSend);



/*
 * NAME:        AppFtpClientSendNextItem.
 * PURPOSE:     Send the next item.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              clientPtr - pointer to the ftp client data structure.
 * RETRUN:      none.
 */
static void
AppFtpClientSendNextItem(GlomoNode *nodePtr, GlomoAppFtpClient *clientPtr);



/*
 * NAME:        AppFtpClientSendNextPacket.
 * PURPOSE:     Send the remaining data.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              clientPtr - pointer to the ftp client data structure.
 * RETRUN:      none.
 */
static void
AppFtpClientSendNextPacket(GlomoNode *nodePtr, GlomoAppFtpClient *clientPtr);



/*
 * NAME:        AppFtpClientItemsToSend.
 * PURPOSE:     call tcplib function ftp_nitems() to get the
 *              number of items to send in an ftp session.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETRUN:      amount of items to send.
 */
static int
AppFtpClientItemsToSend(GlomoAppFtpClient *clientPtr);




/*
 * NAME:        AppFtpClientItemSize.
 * PURPOSE:     call tcplib function ftp_itemsize() to get the size
 *              of each item.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETRUN:      size of an item.
 */
static int
AppFtpClientItemSize(GlomoAppFtpClient *clientPtr);


/*
 * NAME:        AppFtpServerCtrlPktSize.
 * PURPOSE:     call tcplib function ftp_ctlsize().
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETRUN:      ftp control packet size.
 */
int
AppFtpClientCtrlPktSize(GlomoAppFtpClient *clientPtr);



#endif /* _FTP_CLIENT_H_ */

