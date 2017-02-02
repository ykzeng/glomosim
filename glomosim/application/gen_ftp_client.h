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
 * $Id: gen_ftp_client.h,v 1.4 2001/02/15 03:17:26 mineo Exp $
 *
 * This file contains data structure used by ftp client and 
 * prototypes of functions defined in ftp_client.pc.
 */
#ifndef _GEN_FTP_CLIENT_H_
#define _GEN_FTP_CLIENT_H_

#include "structmsg.h"

#define APP_GEN_FTP_CLIENT_FILE    "GEN_FTP_CLIENT.EXCEL"


typedef struct glomo_app_gen_ftp_client_str 
{
    int connectionId;
    NODE_ADDR localAddr; 
    NODE_ADDR remoteAddr;
    clocktype sessionStart;
    clocktype sessionFinish;
    BOOL sessionIsClosed;
    int itemSize;
    long itemsToSend;
    long numBytesSent;
    clocktype endTime;

    long uniqueId;
} GlomoAppGenFtpClient;


/*
 * NAME:        AppLayerGenFtpClient.
 * PURPOSE:     Models the behaviour of ftp client on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerGenFtpClient(GlomoNode *nodePtr, Message *msg);


/*
 * NAME:        AppGenFtpClientInit.
 * PURPOSE:     Initialize a ftp session.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              serverAddr - address of the server,
 *              itemsToSend - number of items to send,
 *              itemSize - size of each item.
 *              startTime - time until the session starts.
 *              endTime - time when session is over.
 * RETURN:      none.
 */
void
AppGenFtpClientInit(GlomoNode *nodePtr,
                    NODE_ADDR serverAddr,
                    long itemsToSend,
                    long itemSize,
                    clocktype startTime,
                    clocktype endTime);



/*
 * NAME:        AppGenFtpClientPrintStats.
 * PURPOSE:     Prints statistics of a ftp session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              clientPtr - pointer to the ftp client data structure.
 * RETURN:      none.
 */
static void
AppGenFtpClientPrintStats(GlomoNode *nodePtr, GlomoAppGenFtpClient *clientPtr);



/*
 * NAME:        AppGenFtpClientFinalize.
 * PURPOSE:     Collect statistics of a ftp session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              clientPtr - pointer to the ftp client data structure.
 * RETURN:      none.
 */
void
AppGenFtpClientFinalize(GlomoNode *nodePtr, GlomoAppGenFtpClient *clientPtr);



/*
 * NAME:        AppGenFtpClientGetGenFtpClient.
 * PURPOSE:     search for a ftp client data structure.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              connId - connection ID of the ftp client.
 * RETURN:      the pointer to the ftp client data structure,
 *              NULL if nothing found.
 */
static GlomoAppGenFtpClient *
AppGenFtpClientGetGenFtpClient(GlomoNode *nodePtr, int connId);



/*
 * NAME:        AppGenFtpClientUpdateGenFtpClient.
 * PURPOSE:     update existing ftp client data structure by including 
 *              connection id.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              openResult - result of the open request.
 * RETRUN:      the pointer to the created ftp client data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppGenFtpClient *
AppGenFtpClientUpdateGenFtpClient(GlomoNode *nodePtr,
                                  TransportToAppOpenResult *openResult);


/*
 * NAME:        AppGenFtpClientNewGenFtpClient.
 * PURPOSE:     create a new ftp client data structure, place it
 *              at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverAddr - ftp server to this client.
 *              itemsToSend - number of ftp items to send in simulation.
 *              itemSize - size of each item.
 *              endTime - when simulation of ftp ends.
 * RETRUN:      the pointer to the created ftp client data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppGenFtpClient *
AppGenFtpClientNewGenFtpClient(GlomoNode *nodePtr,
                               NODE_ADDR serverAddr,
                               long itemsToSend,
                               long itemSize,
                               clocktype endTime);



/*
 * NAME:        AppGenFtpClientSendNextItem.
 * PURPOSE:     Send the next item.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              clientPtr - pointer to the ftp client data structure.
 * RETRUN:      none.
 */
static void
AppGenFtpClientSendNextItem(GlomoNode *nodePtr, 
                            GlomoAppGenFtpClient *clientPtr);



/*
 * NAME:        AppGenFtpClientSendPacket.
 * PURPOSE:     Send the remaining data.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              clientPtr - pointer to the ftp client data structure.
 *              end - end of session.
 * RETRUN:      none.
 */
static void
AppGenFtpClientSendPacket(GlomoNode *nodePtr,
                          GlomoAppGenFtpClient *clientPtr,
                          BOOL end);



#endif /* _GEN_FTP_CLIENT_H_ */

