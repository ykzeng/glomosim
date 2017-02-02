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
 * $Id: 802_11.h,v 1.35 2001/08/31 18:23:49 jmartin Exp $
 */


#ifndef _802_11_H_
#define _802_11_H_

#define M802_11_SHORT_CTRL_FRAME_SIZE     14
#define M802_11_LONG_CTRL_FRAME_SIZE      20
#define M802_11_DATA_FRAME_HDR_SIZE       28


/*
 * #define DSSS - use the DSSS physical spec definitions.
 * #define FHSS - use the FHSS physical spec definitions.
 */

#define DSSS

/*
 * #define FHSS
 */

#include "main.h"
#include "message.h"
#include "fileio.h"

#define M802_11_RADIO_IDLE      1
#define M802_11_RADIO_BUSY      0

/* MAC states */
typedef enum
{
    M802_11_S_IDLE,                 // 0
    M802_11_S_WFNAV,                // 1
    M802_11_S_WF_DIFS_OR_EIFS,      // 2
    M802_11_S_BO,                   // 3
    M802_11_S_NAV_RTS_CHECK_MODE,   // 4

    // Waiting For Response States
    // Make consistent with Mac802_11InWaitingForResponseState()
    
    M802_11_S_WFCTS,            // 5 First State in range
    M802_11_S_WFDATA,           // 6
    M802_11_S_WFACK,            // 7 
    M802_11_S_WFFRAGACK,        // 8 Last State in range
   
    // Transmission States:
    // Make consistent with Mac802_11InTransmittingState().
    
    M802_11_X_RTS,              //  9  First State in range
    M802_11_X_CTS,              // 10
    M802_11_X_UNICAST,          // 11
    M802_11_X_BROADCAST,        // 12
    M802_11_X_FRAGMENT,         // 13
    M802_11_X_ACK,              // 14  
    M802_11_X_FRAGACK           // 15  Last State in range
} M802_11_MacStates;


static //inline//
BOOL Mac802_11IsWaitingForResponseState(M802_11_MacStates state)
{
   return((M802_11_S_WFCTS <= state) &&
          (state <= M802_11_S_WFFRAGACK));
}          

static //inline//
BOOL Mac802_11IsTransmittingState(M802_11_MacStates state)
{
   return((state >= M802_11_X_RTS) &&
          (state <= M802_11_X_FRAGACK));
}          
          


/* Type of MAC frame */

typedef enum
{
    M802_11_UNICAST,      // 0
    M802_11_BROADCAST,    // 1
    M802_11_ACK,          // 2
    M802_11_DATA,         // 3
    M802_11_RTS,          // 4
    M802_11_CTS,          // 5
    M802_11_FRAGMENT      // 6
} M802_11_MacFrameType;


/*
 * Physical layer specification for Direct Sequence Spread Spectrum.
 */
#ifdef DSSS
    /* Binary expon backoff lower bound and upper bound */
    #define M802_11_CW_MIN          31
    #define M802_11_CW_MAX          1023
    #define M802_11_SLOT_TIME       (20*MICRO_SECOND)
    #define M802_11_SIFS            (10*MICRO_SECOND)
    #define M802_11_DELAY_UNTIL_SIGNAL_AIRBORN (5 * MICRO_SECOND)
    #define M802_11_TX_SIFS (M802_11_SIFS - M802_11_DELAY_UNTIL_SIGNAL_AIRBORN)
    
#endif


/*
 * Physical layer specification for Frequency Hopping Spread Spectrum.
 */
#ifdef FHSS
    #define M802_11_CW_MIN          15
    #define M802_11_CW_MAX          1023
    #define M802_11_SLOT_TIME       (50*MICRO_SECOND)
    #define M802_11_SIFS            (28*MICRO_SECOND)
#endif


#define M802_11_PROPAGATION_DELAY  (1*MICRO_SECOND)

#define M802_11_DIFS  (M802_11_SIFS + (2*M802_11_SLOT_TIME))
#define M802_11_TX_DIFS  (M802_11_TX_SIFS + (2*M802_11_SLOT_TIME))


#define M802_11_MAX_ACK_TRANSMIT_TIME \
    (SYNCHRONIZATION_TIME + (160*MICRO_SECOND))

#define M802_11_MIN_PACKET_TRANSMIT_TIME \
    (SYNCHRONIZATION_TIME + (56*MICRO_SECOND))

#define M802_11_EXTENDED_IFS_DELAY \
    (M802_11_SIFS + M802_11_DIFS + M802_11_MAX_ACK_TRANSMIT_TIME)


// Min Delay to get a local packet out the door from the network
// layer.

#define M802_11_MIN_SEND_DELAY_WHEN_IDLE \
    (M802_11_TX_DIFS + M802_11_DELAY_UNTIL_SIGNAL_AIRBORN)
    
#define M802_11_MIN_PACKET_DURATION_PLUS_REPLY_DELAY \
   (M802_11_MIN_PACKET_TRANSMIT_TIME + M802_11_SIFS)    


// This is the minimum time that a packet will be in the air
// for the purpose of computing (parallel simulation) lookahead.
// It also can include the SIFS delay for the time it takes 
// the ACK to get in the air (small).  This is the minimum delay
// that a blindsiding packet can jump on the channel and demand
// an ACK.
//    ONLY need for NULL message protocol with incomplete 
//    topology. Otherwise we can lie on lookahead.
//
// #define M802_11_MIN_PACKET_RECEIVE_DURATION (???*MICRO_SECOND)


/* 
 * RTS_THRESH defaults to 3000.  If packet size (bytes) of network layer is
 * larger than this threshold, RTS-CTS method is used.  0 means always
 * use RTS-CTS method.  Broadcast packets NEVER use RTS-CTS method.
 */
#define M802_11_RTS_THRESH          0 

/* Retransmission limits. */
#define M802_11_SHORT_RETRY_LIMIT   7
#define M802_11_LONG_RETRY_LIMIT    4

/*
 * FRAG_THRESH defaults to 2346.  If packet size (bytes) network layer is
 * smaller than this threshold, no fragmentation is used.  Broadcast
 * packets are NEVER fragmented.
 `*/

#define M802_11_FRAG_THRESH         2346



/* Keeps track of sequence numbers of frames. */
typedef struct seqno_list_t
{
    int fromSeqNo;
    int toSeqNo;
} SeqNoList;

typedef struct seqno_entry_t
{
    NODE_ADDR nodeAddr;
    int fromSeqNo;
    int toSeqNo;
    struct seqno_entry_t *next;
} SeqNoEntry;


/*
 * CTS and ACK frames.
 * Note: All frames types must match the short control (this one)
 *       exactly for its first four (universal) fields.
 */
 
typedef struct _Mac802_11SCtrlFrame
{                               //  Should Be  Actually
    unsigned short frameType;   //      2         2
    char Padding[2];            //      0         2
    int duration;               //      2         4
    NODE_ADDR destAddr;         //      6         4
    // char FCS;                //      4         0
} M802_11ShortControlFrame;     //---------------------
                                //     14        12
       
       
/* RTS frames. */

typedef struct _Mac802_11LCtrlFrame
{                               //  Should Be  Actually
    unsigned short frameType;   //      2         2
    char Padding[2];            //      0         2
    int duration;               //      2         4 
    NODE_ADDR destAddr;         //      6         4
    
    NODE_ADDR sourceAddr;       //      6         4
    char FCS[4];                //      4         4
} M802_11LongControlFrame;      //----------------------
                                //     20        20


/*
 * Data frame header. 
 */
typedef struct _Mac802_11FrameHdr
{                               //  Should Be  Actually
    unsigned short frameType;   //      2         2
    char Padding1[2];           //      0         2
    int duration;               //      2         4
    NODE_ADDR destAddr;         //      6         4
    
    NODE_ADDR sourceAddr;       //      6         4    
    //NODE_ADDR Address3        //      6         0   
    unsigned short seqNo;       //      -         -          
    unsigned char  fragId;      //      2         3
    char Padding2[5];           //      0         5
    char FCS[4];                //      4         4    
} M802_11FrameHdr;              //---------------------
                                //     28        28


static /*inline*/
void M802_11_CheckHeaderSizes() {
    assert(sizeof(M802_11ShortControlFrame) <= M802_11_SHORT_CTRL_FRAME_SIZE);
    assert(sizeof(M802_11LongControlFrame) == M802_11_LONG_CTRL_FRAME_SIZE);
    assert(sizeof(M802_11FrameHdr) == M802_11_DATA_FRAME_HDR_SIZE);
}



/* Data frames. */
typedef struct M802_mac_frame
{
    M802_11FrameHdr hdr;
    char payload[ MAX_NW_PKT_SIZE];
} M802_11_MacFrame;


/* 802.11 data structure. */
typedef struct glomo_mac_802_11_str 
{
    GlomoMac* myGlomoMac;
    
    /* Mac states. */
    int state;

    int prevState;
    
    BOOL IsInExtendedIfsMode;
    
    clocktype noResponseTimeoutDuration;

    /* Backoff value at this station. */
    clocktype CW;
    clocktype BO;
    clocktype lastBOTimeStamp;

    unsigned int timerSequenceNumber;

    char PartialFrame[MAX_NW_PKT_SIZE];

    SeqNoEntry *seqNoHead;

    int currentFrag;
    clocktype NAV;
    int SSRC;
    int SLRC;
    NODE_ADDR waitingForAckOrCtsFromAddress;

    long bandwidth;
    clocktype extraPropDelay;
    
    clocktype ctsOrAckTransmissionDuration;

    /* Statistics collection variables. */
    long pktsToSend;
    long pktsLostOverflow;

    long pktsSentUnicast;
    long pktsSentBroadcast;

    long pktsGotUnicast;
    long pktsGotBroadcast;

    long retxDueToCts;
    long retxDueToAck;
    long retxDueToFragAck;

    long pktsDropped;
    long fragsDropped;
    
    int rtsPacketsIgnoredDueToBusyChannel;
    int rtsPacketsIgnoredDueToNAV;

    NetworkQueueingPriorityType currentPriority;
    
    
    
    
} GlomoMac802_11;


/*
 * FUNCTION    Mac802_11Layer
 * PURPOSE     Models the behaviour of the MAC layer with the FAMA protocol
 *             on receiving the message enclosed in msgHdr.
 *
 * Parameters:
 *     node:     node which received the message
 *     msgHdr:   message received by the layer
 */
void Mac802_11Layer(GlomoNode *node, int interfaceIndex, Message *msg);


/*
 * FUNCTION    Mac802_11Init
 * PURPOSE     Initialization function for 802_11 protocol of MAC layer.

 * Parameters:
 *     node:      node being initialized.
 *     nodeInput: structure containing contents of input file
 */
void Mac802_11Init(
   GlomoNode *node, int interfaceIndex, const GlomoNodeInput *nodeInput);

/*
 * FUNCTION    Mac802_11Finalize
 * PURPOSE     Called at the end of simulation to collect the results of
 *             the simulation of FAMA protocol of the MAC Layer.
 *
 * Parameter:
 *     node:     node for which results are to be collected.
 */
void Mac802_11Finalize(GlomoNode *node, int interfaceIndex);

/*
 * NAME:        Mac802_11NetworkLayerHasPacketToSend.
 *
 * PURPOSE:     To notify 802_11 that network has something to send.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void Mac802_11NetworkLayerHasPacketToSend(
   GlomoNode* node, GlomoMac802_11* M802);
   
void Mac802_11ReceivePacketFromRadio(
   GlomoNode* node, GlomoMac802_11* M802, Message* msg);
   
void Mac802_11ReceiveRadioStatusChangeNotification(
   GlomoNode* node,
   GlomoMac802_11* M802,
   RadioStatusType oldRadioStatus,
   RadioStatusType newRadioStatus,
   clocktype receiveDuration,
   const Message* potentialIncomingPacket);





#endif


