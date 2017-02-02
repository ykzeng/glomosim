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
 * $Id: gen_ftp_server.h,v 1.3 1999/10/07 05:05:42 ktang Exp $
 *
 * This file contains data structure used by ftp server and 
 * prototypes of functions defined in ftp_server.pc.
 */

#ifndef _GEN_FTP_SERVER_H_
#define _GEN_FTP_SERVER_H_

#include "structmsg.h"

#define APP_GEN_FTP_SERVER_FILE    "GEN_FTP_SERVER.EXCEL"


typedef struct glomo_app_gen_ftp_server_str 
{
    int connectionId;
    NODE_ADDR localAddr; 
    NODE_ADDR remoteAddr;
    clocktype sessionStart;
    clocktype sessionFinish;
    BOOL sessionIsClosed;
    long numBytesRecvd;
} GlomoAppGenFtpServer;



/*
 * NAME:        AppLayerGenFtpServer.
 * PURPOSE:     Models the behaviour of ftp Server on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerGenFtpServer(GlomoNode *nodePtr, Message *msg);



/*
 * NAME:        AppGenFtpServerInit.
 * PURPOSE:     listen on ftp server port.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETURN:      none.
 */
void
AppGenFtpServerInit(GlomoNode *nodePtr);



/*
 * NAME:        AppGenFtpServerPrintStats.
 * PURPOSE:     Prints statistics of a ftp session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the ftp server data structure.
 * RETURN:      none.
 */
static void
AppGenFtpServerPrintStats(GlomoNode *nodePtr, GlomoAppGenFtpServer *serverPtr);



/*
 * NAME:        AppGenFtpServerFinalize.
 * PURPOSE:     Collect statistics of a ftp session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              serverPtr - pointer to the ftp server data structure.
 * RETURN:      none.
 */
void
AppGenFtpServerFinalize(GlomoNode *nodePtr, GlomoAppGenFtpServer *serverPtr);



/*
 * NAME:        AppGenFtpServerGetGenFtpServer.
 * PURPOSE:     search for a ftp server data structure.
 * PARAMETERS:  appList - link list of applications,
 *              connId - connection ID of the ftp server.
 * RETURN:      the pointer to the ftp server data structure,
 *              NULL if nothing found.
 */
static GlomoAppGenFtpServer *
AppGenFtpServerGetGenFtpServer(GlomoNode *nodePtr, int connId);



/*
 * NAME:        AppGenFtpServerNewGenFtpServer.
 * PURPOSE:     create a new ftp server data structure, place it
 *              at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              openResult - result of the open request.
 * RETRUN:      the pointer to the created ftp server data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppGenFtpServer *
AppGenFtpServerNewGenFtpServer(GlomoNode *nodePtr,
                               TransportToAppOpenResult *openResult);











#endif /* _GEN_FTP_SERVER_H_ */

