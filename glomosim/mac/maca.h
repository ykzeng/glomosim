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
 * $Id: maca.h,v 1.13 2000/10/20 16:55:59 jmartin Exp $
 */

#ifndef _MACA_H_
#define _MACA_H_

#include "main.h"
#include "message.h"
#include "fileio.h"

#include "mac.h"

#define MACA_EXTRA_DELAY 100

/* This vacation only applies to broadcasted packets. */
#define MACA_VACATION   100

#define MACA_BO_MIN     (20 * MICRO_SECOND)
#define MACA_BO_MAX     (16 * MACA_BO_MIN)

typedef enum
{
    MACA_RTS,
    MACA_CTS,
    MACA_UNICAST,
    MACA_BROADCAST
} MacaFrameType;


typedef enum
{
    MACA_S_PASSIVE,
    MACA_S_RTS,
    MACA_S_BACKOFF,
    MACA_S_REMOTE,
    MACA_S_XMIT,
    MACA_S_YIELD,
    MACA_S_IN_XMITING_RTS,
    MACA_S_IN_XMITING_CTS,
    MACA_S_IN_XMITING_UNICAST,
    MACA_S_IN_XMITING_BROADCAST
} MacaStateType;


#define MACA_TIMER_SWITCH       0x1     /* bit 0000 0001 is used for ON/OFF*/ 
#define MACA_TIMER_ON           0x1
#define MACA_TIMER_OFF          0x0

#define MACA_TIMER_TYPE 0xE     /* bit 0000 1110 is used for Timer type */
#define MACA_T_RTS      0x0     /* bit 0000 0000 */
#define MACA_T_BACKOFF  0x2     /* bit 0000 0010 */
#define MACA_T_XMIT     0x4     /* bit 0000 0100 */
#define MACA_T_REMOTE   0x6     /* bit 0000 0110 */
#define MACA_T_YIELD    0x8     /* bit 0000 1000 */
#define MACA_T_UNDEFINED 0xE    /* bit 0000 1110 */ 

typedef struct _maca_timer 
{
    int            seq;
    unsigned char   flag;
} MacaTimer;

typedef struct maca_header_str {
    NODE_ADDR sourceAddr;
    NODE_ADDR destAddr;
    int payloadSize;
    int frameType;  /* RTS, CTS, MAC_DATA */
    int priority;
} MacaHeader;

typedef struct glomo_mac_maca_str 
{
    GlomoMac* myGlomoMac;
    int state;         

    int BOmin;          /* minimum backoff */
    int BOmax;          /* maximum backoff */
    int BOtimes;        /* how many times has it backed off? */

    MacaTimer timer;

    int payloadSizeExpected;

    int pktsToSend;
    int pktsLostOverflow;

    int pktsSentUnicast;
    int pktsSentBroadcast;

    int pktsGotUnicast;
    int pktsGotBroadcast;

    int RtsPacketSent;
    int CtsPacketSent;

    int RtsPacketGot;
    int CtsPacketGot;

    int NoisyPacketGot;

    NetworkQueueingPriorityType currentPriority;
} GlomoMacMaca;


/*
 * FUNCTION    MacMacaLayer.
 * PURPOSE     Models the behaviour of the MAC layer with the MACA protocol
 *             on receiving the message enclosed in msg.
 *
 * Parameters:
 *     node:     node which received the message.
 *     msg:      message received by the layer.
 */

void MacMacaLayer(
   GlomoNode *node, int InterfaceIndex, Message *msg);


/*
 * FUNCTION    MacMacaInit.
 * PURPOSE     Initialization function for Maca protocol of MAC layer.
 *
 * Parameters:
 *     node:      node being initialized.
 *     nodeInput: structure containing contents of input file.
 */

void MacMacaInit(
   GlomoNode *node, int interfaceIndex, const GlomoNodeInput *nodeInput);


/*
 * FUNCTION    MacMacaFinalize.
 * PURPOSE     Called at the end of simulation to collect the results of
 *             the simulation of MACA protocol of the MAC Layer.
 *
 * Parameter:
 *     node:     node for which results are to be collected.
 */

void MacMacaFinalize(GlomoNode *node, int interfaceIndex);

/*
 * FUNCTION    MacMacaNetworkLayerHasPacketToSend.
 * PURPOSE     For notifying MACA that a new packet at the network layer
 *             is ready to be sent.
 */

void MacMacaNetworkLayerHasPacketToSend(GlomoNode* node, GlomoMacMaca* maca);


void MacMacaReceivePacketFromRadio(
    GlomoNode* node, GlomoMacMaca* maca, Message* msg);
    
    
void MacMacaReceiveRadioStatusChangeNotification(
   GlomoNode* node,
   GlomoMacMaca* maca,
   RadioStatusType oldRadioStatus,
   RadioStatusType newRadioStatus);


#endif


