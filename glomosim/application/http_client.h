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
#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_

#include "structmsg.h"

typedef enum {
	IDLE,
    XMIT_PRIMARY_REQUEST,
	XMIT_SECONDARY_REQUEST,
	WAIT_PRIMARY_RESPONSE,
	WAIT_SECONDARY_RESPONSE
} HttpClientState;

typedef enum {
    THINK_TIMER,
	WAIT_PRIMARY_REPLY_TIMER,
	WAIT_SECONDARY_REPLY_TIMER
} HttpClientTimerType;

typedef struct http_client_timer_str {
    HttpClientTimerType timerType;
	long clientId;
} HttpClientTimer;

typedef struct http_client_stats_str {
    int itemRequestBytes;   // number of bytes this item
    int pageItems;      // number of items this page
} HttpClientStats;

typedef struct glomo_app_http_client_str 
{
    int connectionId;
    NODE_ADDR localAddr; 
    NODE_ADDR remoteAddr;
    clocktype sessionStart;         // start time of current session
    clocktype sessionFinish;        // end time of current session
	clocktype avgSessionLength;     // average session length
	long numSessions;               // total number of sessions
	long numPages;                  // total num of pages recvd
	NODE_ADDR *servers;
	long num_servers;
	double Zipf_constant;
	clocktype threshhold;
	clocktype lastReceiveTime;
	HttpClientStats stats;
	unsigned short *seed;
	HttpClientState state;
    BOOL sessionIsClosed;
    long documentsOnCurrentServer;
    int itemSizeLeft;
    long numBytesSent;
    long numBytesRecvd;

    long uniqueId;
} GlomoAppHttpClient;

/*
 * NAME:        AppLayerHttpClient.
 * PURPOSE:     Models the behaviour of Http Client on receiving the
 *              message encapsulated in msg.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              msg - message received by the layer
 * RETURN:      none.
 */
void
AppLayerHttpClient(GlomoNode *nodePtr, Message *msg);

/*
 * NAME:        AppHttpClientInit.
 * PURPOSE:     Initialize a Http session.
 * PARAMETERS:  nodePtr - pointer to the node,
 *              serverAddrs - addresses of the servers to choose from,
 *              numServerAddrs - number of addresses in above array,
 *              startTime - the time to start the first connection
 *              thresh - maximum time before deciding the connection is
 *       		done .
 * RETURN:      none.
 */
void
AppHttpClientInit(GlomoNode *nodePtr, NODE_ADDR *serverAddrs,
				  long numServerAddrs, clocktype startTime,
				  clocktype thresh);

/*
 * NAME:        AppHttpClientFinalize.
 * PURPOSE:     Collect statistics of a Http session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              clientPtr - pointer to the http client data structure.
 * RETURN:      none.
 */

void
AppHttpClientFinalize(GlomoNode *nodePtr, GlomoAppHttpClient *clientPtr);


/*
 * NAME:        AppHttpClientNewHttpClient.
 * PURPOSE:     create a new http client data structure, place it
 *              at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETURN:      the pointer to the created http client data structure,
 *
 */
static GlomoAppHttpClient *
AppHttpClientNewHttpClient(GlomoNode *nodePtr);

/*
 * NAME:        AppHttpClientSendThinkTimer.
 * PURPOSE:     Send a Timeout to itself at the end of the determined
 *              thinking period.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              clientPtr - pointer to the client's data structure
 *              thinkTime - determined thinking period
 * RETURN:      none.
 */
void AppHttpClientSendThinkTimer(GlomoNode *nodePtr,
                                 GlomoAppHttpClient *clientPtr,
                                 clocktype thinkTime);

/*
 * NAME:        AppHttpClientSendWaitReplyTimer.
 * PURPOSE:     Send a Timeout to itself just in case the server never replies
 *              to a page request.  Times out at the maximum think threshhold
 *              parameter.
 * PARAMETERS:  nodePtr - pointer to the node which received the message.
 *              clientPtr - pointer to the client's data structure
 *              timerType - either WAIT_PRIMARY_RESPONSE or 
 *                                 WAIT_SECONDARY_RESPONSE
 * RETURN:      none.
 */
void AppHttpClientSendWaitReplyTimer(GlomoNode *nodePtr,
                                     GlomoAppHttpClient *clientPtr,
                                     HttpClientTimerType timerType);

/*
 * NAME:        AppHttpClientProcessDoneThinking.
 * PURPOSE:     After waiting the think period, either request the next
 *              document, or select a new http server and start over.
 * PARAMETERS:  node - pointer to the node which received the message.
 *              clientPtr - pointer to the client's data structure
 * RETURN:      none.
 */
void AppHttpClientProcessDoneThinking(GlomoNode *node,
                                      GlomoAppHttpClient *clientPtr);

/*
 * NAME:        AppHttpClientProcessWaitReplyTimer.
 * PURPOSE:     Do nothing if the packet reception was successful,
 *              otherwise, check if the server has not responded within
 *              the allotted threshhold.  If not, request the next 
 *              document.  If so, reset the timer.
 * PARAMETERS:  node - pointer to the node which received the message.
 *              clientPtr - pointer to the client's data structure
 * RETURN:      none.
 */
void AppHttpClientProcessWaitReplyTimer(GlomoNode *node,
                                   GlomoAppHttpClient *clientPtr);

/*
 * NAME:        AppHttpClientProcessReplyPacket.
 * PURPOSE:     Process a Reply Packet from the server.  This packet is marked
 *              as the last one corresponding to a specific request.
 * PARAMETERS:  node - pointer to the node which received the message.
 *              clientPtr - pointer to the client's data structure
 * RETURN:      none.
 */
void AppHttpClientProcessReplyPacket(GlomoNode *node,
                                     GlomoAppHttpClient *clientPtr);

/*
 * NAME:        AppHttpClientConsecutiveDocumentRetrievals.
 * PURPOSE:     Return the number of consecutive document retrievals for the
 *              current server.
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      the number of consecutive document retrievals.
 */
long AppHttpClientConsecutiveDocumentRetrievals(GlomoAppHttpClient *clientPtr);

/*
 * NAME:        AppHttpClientSelectNewServer.
 * PURPOSE:     Return the address for the next selected server
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      the node address for the next server to communicate with.
 */
NODE_ADDR AppHttpClientSelectNewServer(GlomoAppHttpClient *clientPtr);

/*
 * NAME:        AppHttpClientDetermineThinkTime.
 * PURPOSE:     Return the amount of time to think for, before the next
 *              request.
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      the amount of time to wait.
 */
double AppHttpClientDetermineThinkTime(GlomoAppHttpClient *clientPtr);


/*
 * NAME:        AppHttpClientDetermineItemCount.
 * PURPOSE:     Return the number of items on this particular page.
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      the number of items.
 */
long AppHttpClientDetermineItemCount(GlomoAppHttpClient *clientPtr);

/*
 * NAME:        AppHttpClientDetermineSecondaryRequestLength.
 * PURPOSE:     Return the number of bytes in the secondary request
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      the number of bytes.
 */
long AppHttpClientDetermineSecondaryRequestLength(
				    GlomoAppHttpClient *clientPtr);

/*
 * NAME:        AppHttpClientDeterminePrimaryRequestLength.
 * PURPOSE:     Return the number of bytes in the primary request
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      the number of bytes.
 */
long AppHttpClientDeterminePrimaryRequestLength(
				    GlomoAppHttpClient *clientPtr);

/*
 * NAME:        AppHttpClientSendPrimaryRequest.
 * PURPOSE:     Send the primary request of the given size to the server.
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      none.
 */
void AppHttpClientSendPrimaryRequest(GlomoNode *node,
				                     GlomoAppHttpClient *clientPtr,
									 long primaryRequestLength);

/*
 * NAME:        AppHttpClientSendSecondaryRequest.
 * PURPOSE:     Send the secondary request of the given size to the server.
 * PARAMETERS:  clientPtr - pointer to the client's data structure
 * RETURN:      none.
 */
void AppHttpClientSendSecondaryRequest(GlomoNode *node,
				                       GlomoAppHttpClient *clientPtr,
									   long secondaryRequestLength);


/*
 * NAME:        AppHttpClientPrintStats.
 * PURPOSE:     Prints statistics of a Http session.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              clientPtr - pointer to the http client data structure.
 * RETURN:      none.
 */
static void
AppHttpClientPrintStats(GlomoNode *nodePtr, GlomoAppHttpClient *clientPtr);

/*
 * NAME:        AppHttpClientGetHttpClient.
 * PURPOSE:     search for a http client data structure.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              connId - connection ID of the http client.
 * RETURN:      the pointer to the http client data structure,
 *              NULL if nothing found.
 */
static GlomoAppHttpClient *
AppHttpClientGetHttpClient(GlomoNode *nodePtr, int connId);

/*
 * NAME:        AppHttpClientUpdateHttpClient.
 * PURPOSE:     update existing http client data structure by including
 *              connection id.
 * PARAMETERS:  nodePtr - pointer to the node.
 *              openResult - result of the open request.
 * RETRUN:      the pointer to the created http client data structure,
 *              NULL if no data structure allocated.
 */
static GlomoAppHttpClient *
AppHttpClientUpdateHttpClient(GlomoNode *nodePtr,
				              TransportToAppOpenResult *openResult);

/*
 * NAME:        AppHttpClientNewHttpClient.
 * PURPOSE:     create a new http client data structure, place it
 *              at the beginning of the application list.
 * PARAMETERS:  nodePtr - pointer to the node.
 * RETURN:      the pointer to the created http client data structure,
 *
 */
static GlomoAppHttpClient *
AppHttpClientNewHttpClient(GlomoNode *nodePtr);


#endif /* _HTTP_CLIENT_H_ */

