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
 * $Id: ftp_server.h,v 1.5 2000/10/20 19:17:23 jmartin Exp $
 *
 * This file contains data structure used by ftp server and 
 * prototypes of functions defined in ftp_server.pc.
 */

#ifndef _FTP_SERVER_H_
#define _FTP_SERVER_H_

#include "structmsg.h"

typedef struct glomo_app_ftp_server_str 
{
    int connectionId;
    NODE_ADDR localAddr; 
    NODE_ADDR remoteAddr;
    clocktype sessionStart;
    clocktype sessionFinish;
    BOOL sessionIsClosed;
    long numBytesSent;
    long numBytesRecvd;
    unsigned short seed[3];
} GlomoAppFtpServer;



/*
 * NAME:        AppLayerFtpServer.
 * PURPOSE:     Models the behaviour of Ftp Server on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerFtpServer(GlomoNode *nodePtr, Message *msg);



/*
 * NAME:        AppFtpServerInit.
 * PURPOSE:     listen on Ftp server port.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETURN:      none.
 */
void
AppFtpServerInit(GlomoNode *nodePtr);




/*
 * NAME:        AppFtpServerPrintStats.
 * PURPOSE:     Prints statistics of a Ftp session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the ftp server data structure.
 * RETURN:      none.
 */
static void
AppFtpServerPrintStats(GlomoNode *nodePtr, GlomoAppFtpServer *serverPtr);



/*
 * NAME:        AppFtpServerFinalize.
 * PURPOSE:     Collect statistics of a Ftp session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the ftp server data structure.
 * RETURN:      none.
 */
void
AppFtpServerFinalize(GlomoNode *nodePtr, GlomoAppFtpServer *serverPtr);



/*
 * NAME:        AppFtpServerGetFtpServer.
 * PURPOSE:     search for a ftp server data structure.
 * PARAMETERS:  appList - link list of applications,
 *              connId - connection ID of the ftp server.
 * RETURN:      the pointer to the ftp server data structure,
 *              NULL if nothing found.
 */
static GlomoAppFtpServer *
AppFtpServerGetFtpServer(GlomoNode *nodePtr, int connId);



/*
 * NAME:        AppFtpServerNewFtpServer.
 * PURPOSE:     create a new ftp server data structure, place it
 *              at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              openResult - result of the open request.
 * RETRUN:      the pointer to the created ftp server data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppFtpServer *
AppFtpServerNewFtpServer(GlomoNode *nodePtr,
                         TransportToAppOpenResult *openResult);



/*
 * NAME:        AppFtpServerSendCtrlPkt.
 * PURPOSE:     call AppFtpCtrlPktSize() to get the response packet
 *              size, and send the packet.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              serverPtr - pointer to the server data structure.
 * RETRUN:      none.
 */
static void
AppFtpServerSendCtrlPkt(GlomoNode *nodePtr, GlomoAppFtpServer *serverPtr);



/*
 * NAME:        AppFtpServerCtrlPktSize.
 * PURPOSE:     call tcplib function ftp_ctlsize().
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETRUN:      ftp control packet size.
 */
int
AppFtpServerCtrlPktSize(GlomoAppFtpServer *serverPtr);



#endif /* _FTP_SERVER_H_ */

