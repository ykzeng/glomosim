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
 * $Id: csma.h,v 1.14 2000/08/01 00:17:23 jmartin Exp $
 */
#ifndef _CSMA_H_
#define _CSMA_H_

#include "main.h"
#include "message.h"
#include "fileio.h"

#include "mac.h"

enum 
{
    CSMA_STATUS_PASSIVE,
    CSMA_STATUS_CARRIER_SENSE,
    CSMA_STATUS_BACKOFF,
    CSMA_STATUS_XMIT,
    CSMA_STATUS_IN_XMITING,
    CSMA_STATUS_YIELD
};


#define CSMA_TX_DATA_YIELD_TIME         (20 * MICRO_SECOND)

/* Used to experiment with CSMA timers only. */
#define CSMA_LOCAL_DATA_YIELD_TIME      (0)
#define CSMA_REMOTE_DATA_YIELD_TIME     (0)

#define CSMA_BO_MIN          (20 * MICRO_SECOND)
#define CSMA_BO_MAX          (16 * CSMA_BO_MIN)

#define CSMA_TIMER_SWITCH    0x1  /* bit 0000 0001 is used for ON/OFF*/ 
#define CSMA_TIMER_ON        0x1
#define CSMA_TIMER_OFF       0x0

#define CSMA_TIMER_TYPE      0xE  /* bit 0000 1110 is used for Timer type */
#define CSMA_TIMER_BACKOFF   0x0
#define CSMA_TIMER_YIELD     0x2
#define CSMA_TIMER_UNDEFINED 0xE


typedef struct csma_timer 
{
    long seq;
    unsigned char flag;
} CsmaTimer;

typedef struct csma_header_str {
    NODE_ADDR sourceAddr;
    NODE_ADDR destAddr;
    int priority;
} CsmaHeader;

typedef struct glomo_mac_csma_str 
{
    GlomoMac* myGlomoMac;
    
    long status;           /* status of layer CSMA_STATUS_* */
    long BOmin;            /* minimum backoff */
    long BOmax;            /* maximum backoff */
    long BOtimes;          /* how many times has it backoff ? */

    long pktsToSend;
    long pktsLostOverflow;

    long pktsSentUnicast;
    long pktsSentBroadcast;

    long pktsGotUnicast;
    long pktsGotBroadcast;

    CsmaTimer timer;
} GlomoMacCsma;



/*
 * FUNCTION    MacCsmaInit
 * PURPOSE     Initialization function for CSMA protocol of MAC layer.
 *
 * Parameters:
 *     node:      node being initialized.
 *     nodeInput: structure containing contents of input file
 */
void MacCsmaInit(
    GlomoNode *node, int interfaceIndex, const GlomoNodeInput *nodeInput);


/*
 * FUNCTION    MacCsmaLayer
 * PURPOSE     Models the behaviour of the MAC layer with the CSMA protocol
 *             on receiving the message enclosed in msgHdr.
 *
 * Parameters:
 *     node:     node which received the message
 *     msgHdr:   message received by the layer
 */
void MacCsmaLayer(
    GlomoNode *node, int interfaceIndex, Message *msg);


/*
 * FUNCTION    MacCsmaFinalize
 * PURPOSE     Called at the end of simulation to collect the results of 
 *             the simulation of CSMA protocol of the MAC Layer.
 *
 * Parameter:
 *     node:     node for which results are to be collected.
 */
void MacCsmaFinalize(GlomoNode *node, int interfaceIndex);

/*
 * FUNCTION    MacCsmaNetworkLayerHasPacketToSend
 * PURPOSE     To tell CSMA that the network layer has a packet to send.
 */

void MacCsmaNetworkLayerHasPacketToSend(GlomoNode *node, GlomoMacCsma *csma);


void MacCsmaReceivePacketFromRadio(
    GlomoNode* node, GlomoMacCsma* csma, Message* msg);
    
    
void MacCsmaReceiveRadioStatusChangeNotification(
   GlomoNode* node,
   GlomoMacCsma* csma,
   RadioStatusType oldRadioStatus,
   RadioStatusType newRadioStatus);

#endif /* _CSMA_H_ */

