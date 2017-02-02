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
 * $Id: message.h,v 1.44 2001/08/03 21:23:42 jmartin Exp $
 *
 * Declaration of Parsec message types used in simulation
 */

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "main.h"
#include "fileio.h"
#include "coordinates.h"

#define SMALL_INFO_SPACE_SIZE 80


/*
 * Generic Message received/sent by any layer in GloMoSim
 * typedef to Message in main.h
 */
struct message_str {
    /*
     * The following fields are simulation related information.
     */
    short layerType;    // Layer which will receive the message
    short protocolType; // Protocol which will receive the message in the layer.
    short instanceId;   // Which instance to give message to (for multiple
                        // copies of a protocol or application). 
    short eventType;    // Message's Event type. 
    
    BOOL error;         // Does the packet contain errors?

    /*
     * This field carries any information that needs to be transported
     * between layers.
     * It can be used for carrying data for messages which are not packets.
     * It can also be used to carry additional information for messages
     * which are packets.
     */
    char* info;
    /* size of buffer pointer to by "info" variable */
    int infoSize;
    double smallInfoSpace[SMALL_INFO_SPACE_SIZE / sizeof(double)];


    /*
     * The following two fields are only used when the message is being
     * used to simulate an actual packt.
     */
    /*
     * packetSize field will indicate the simulated packet size. As a
     * packet moves up or down between the various layers, this field
     * will be updated to reflect the addition or deletion of the various
     * layer headers. For most purposes this does not have to be modified
     * by the users as it will be controlled through the following functions:
     * GLOMO_MsgAllocPacket, GLOMO_MsgAddHeader, GLOMO_MsgRemoveHeader
     */
    int packetSize;

    /*
     * The "packet" as seen by a particular layer for messages which are used
     * to simulate packets.
     */
    char* packet;

    /*
     * This field is used for messages used to send packets. It is
     * used for internal error checking and should not be used by users.
     */
    char* payLoad;
    /*
     * Size of the buffer pointed to by payLoad.
     * This field should never be changed by the user.
     */
    int payLoadSize;

    // If this is a packet, its the creation time.

    clocktype packetCreationTime;  
};



/*
 * FUNCTION     GLOMO_MsgSend
 * PURPOSE      Function call used to send a message within GlomoSim. When
 *              a message is sent using this mechanism, only the pointer to
 *              the message is actually sent through the system. So the user
 *              has to be careful not to do anything with the content of the
 *              pointer once GLOMO_MsgSend has been called.
 *
 * Parameters:
 *    node:       node which is sending message
 *    msg:        message to be delivered
 *    delay:      delay suffered by this message.
 */
void GLOMO_MsgSend(GlomoNode *node, Message *msg, clocktype delay);

/*
 * FUNCTION     GLOMO_MsgCancelSelfMsg
 * PURPOSE      Function call used to cancel a event message in the
 *              GloMoSim scheduler.  The Message must be a self message
 *              (timer) .i.e. a message a node sent to itself.  The
 *              msgToCancelPtr must a pointer to the original message
 *              that needs to be canceled.
 *
 * Parameters:
 *    node:       node which is sending message
 *    msg:        message to be delivered
 *    delay:      delay suffered by this message.
 */
void GLOMO_MsgCancelSelfMsg(GlomoNode *node, Message *msgToCancelPtr);


/*
 * FUNCTION     GLOMO_MsgAlloc
 * PURPOSE      Allocate a new Message structure. This is called when a new
 *              message has to be sent through the system. The last three
 *              parameters indicate the nodeId, layerType, and eventType
 *              that will be set for this message.
 *
 * Parameters:
 *    node:       node which is allocating message
 *    layerType:  Layer type to be set for this message
 *    protocol:   Protocol to be set for this message
 *    eventType:  event type to be set for this message
 */
Message* GLOMO_MsgAlloc (GlomoNode *node, int layerType,
                         int protocol, int eventType);


/*
 * FUNCTION     GLOMO_MsgInfoAlloc
 * PURPOSE      Allocate the "info" field for the message. This function
 *              is used for the delivery of data for messages which are NOT
 *              packets as well as the delivery of extra information for
 *              messages which are packets.
 *              If the "info" field has previously been allocated for
 *              the message, it will be replaced by a new "info" field with
 *              the specified size.
 *              Once this function has been called the "info" variable in
 *              the message structure can be used to acces this space.
 *
 * Parameters:
 *    node:         node which is allocating payLoad
 *    msg:          message for which "info" field has to be allocated
 *    infoSize:     size of the "info" field to be allocated
 */
void GLOMO_MsgInfoAlloc (GlomoNode *node, Message *msg, int infoSize);



/*
 * FUNCTION     GLOMO_MsgPacketAlloc
 * PURPOSE      Allocate the "payLoad" field for the packet to be delivered.
 *              Add additional free space in front of the packet for headers
 *              that might be added to the packet.
 *              This function can be called from the application layer or
 *              anywhere else (e.g TCP, IP) that a packet may originiate from.
 *              The "packetSize" variable will be set to the "packetSize"
 *              parameter specified in the function call.
 *              Once this function has been called the "packet" variable in
 *              the message structure can be used to access this space.
 *
 * Parameters:
 *    node:         node which is allocating message
 *    msg:          message for which data has to be allocated
 *    payLoadSize:  size of the payLoad to be allocated
 */
void GLOMO_MsgPacketAlloc(GlomoNode *node, Message *msg, int packetSize);


/*
 * FUNCTION     GLOMO_MsgAddHeader
 * PURPOSE      This function is called to reserve additional space for a
 *              header of size "hdrSize" for the packet enclosed in the
 *              message. The "packetSize" variable in the message structure
 *              will be increased by "hdrSize".
 *              Since the header has to be prepended to the current packet,
 *              after this function is called the "packet" variable in the
 *              message structure will point the space occupied by this new
 *              header.
 *
 * Parameters:
 *    node:         node which is adding header
 *    msg:          message for which header has to be added
 *    hdrSize:      size of the header to be added
 */
void GLOMO_MsgAddHeader(GlomoNode *node, Message *msg, int hdrSize);


/*
 * FUNCTION     GLOMO_MsgRemoveHeader
 * PURPOSE      This function is called to remove a header from the packet
 *              enclosed in the message. The "packetSize" variable in the
 *              message will be decreased by "hdrSize".
 *
 * Parameters:
 *    node:         node which is removing the header
 *    msg:          message for which header is being removed
 *    hdrSize:      size of the header being removed
 */
void GLOMO_MsgRemoveHeader(GlomoNode *node, Message *msg, int hdrSize);


/*
 * FUNCTION     GLOMO_MsgFree
 * PURPOSE      When the message is no longer needed it can be freed. Firstly,
 *              the "payLoad" and "info" fields of the message are freed. Than
 *              the message itself is freed. It is important to remember
 *              to free the message. Otherwise there will nasty memory leaks
 *              in the program.
 *
 * Parameters:
 *    node:       node which is freeing the message
 *    msg:        message which has to be freed
 */
void GLOMO_MsgFree (GlomoNode *node, Message *msg);


/*
 * FUNCTION     GLOMO_MsgCopy
 * PURPOSE      Create a new message which is an exact duplicate of the message
 *              supplied as the parameter to the function and return the new
 *              message.
 *
 * Parameters:
 *    node:       node which is calling message copy
 *    msg:        message for which duplicate has to be made
 */
Message* GLOMO_MsgCopy (GlomoNode *node, const Message *msg);


#define GLOMO_MsgReturnPacket(msg) (msg->packet)
#define GLOMO_MsgReturnPacketSize(msg) (msg->packetSize)
#define GLOMO_MsgReturnInfo(msg) (msg->info)

/*
 * Given the layer and protocol fields,  this macro will
 * form the a layerType field of the Message structure.
 */

#define GLOMO_MsgSetLayer(msg, layer, protocol) \
        (msg)->layerType = (layer); \
        (msg)->protocolType = (protocol); 
/*
 * The following two functions will retrieve the actual layer and
 * protocol type fileds from the layerType variable
 */
#define GLOMO_MsgGetLayer(msg) ((msg)->layerType)
#define GLOMO_MsgGetProtocol(msg) ((msg)->protocolType)

#define GLOMO_MsgSetEvent(msg, event) (msg->eventType = (event))
#define GLOMO_MsgGetEvent(msg) (msg->eventType)

#define GLOMO_MsgSetInstanceId(msg, instance) \
   (msg)->instanceId = (instance);

#define GLOMO_MsgGetInstanceId(msg) ((msg)->instanceId)

#define GLOMO_MsgGetPacketCreationTime(msg) ((msg)->packetCreationTime)



message RemoteMessage {
    GlomoNode *node;
    Message   *msg;
};

message MovingSoon {
    /* Nothing */
};

message MovingNow {
    GlomoNode *node;
    clocktype currentEarliestCommunicationTime;  // For Parallel.
    BOOL currentEotIsBoundedByLowerLayer;        // For Parallel 
};

/*
 * Message sent to inform entity partition of 
 * neighboring partitions.
 */
message NeighborInfoMsg {
    ename  partitionEname;
    double start_x;
    double start_y;
    double end_x;
    double end_y;
    int  dir;
};


/*
 * Message send to inform partitions about
 * various information.
 */
message PartitionInfoMsg {
    GlomoAreaInfo **area;
    int numPartitionsX;
    int numPartitionsY;
    int  partitionConnectivityDistance;
    int indexX;
    int indexY;
    unsigned short seedVal;
    int numNodes;
    GlomoNodeInput nodeInput;
    GlomoCoordinates terrainDimensions;
};


typedef struct node_position_info_str {
    NODE_ADDR nodeAddr;
    GlomoCoordinates position;
} GlomoNodePositionInfo;

/*
 * Message sent to inform entity that the driver has finished
 * doing node initialization.
 */
message NodePositionMsg { GlomoNodePositionInfo *nodePos; };

message WiredPartitionMsg {
    int              numLinks;
    GlomoRemoteLink *link;
};

/* Message indicating that partition is ready */
message Ready { };

/* Message indicating that partition can start simulation */
message StartSim { };


#endif /* _MESSAGE_H_ */

