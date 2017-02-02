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
 * TSMA Model in GloMoSim - version 2.0
 *
 * The TSMA model in GloMoSim is COPYRIGHTED software.  It is freely available
 * without fee for education, or research, or to non-profit agencies. By
 * obtaining copies of this and other files that comprise the TSMA model in
 * GloMoSim, you, the Licensee, agree to abide by the following conditions
 * and understandings with respect to the copyrighted software:
 *
 * 1. Permission to use, copy, and modify this software and its documentation
 *    for education, research, and non-profit purposes is hereby granted to
 *    Licensee, provided that the copyright notice, the original author's names
 *    and unit identification, and this permission notice appear on all such
 *    copies, and that no charge be made for such copies. Any entity desiring
 *    permission to incorporate this software into commercial products or to
 *    use it for commercial purposes should contact:
 *
 *    Professor Imrich Chlamtac
 *    Distinguished Chair in Telecommunications
 *    Director, Center for Advanced Telecommunications Systems and Services
 *    Erik Jonsson School of Engineering and Computer Science
 *    The University of Texas at Dallas
 *    P.O. Box 830688, EC 33
 *    Richardson, TX 75083-0688
 *    e-mail: chlamtac@utdallas.edu
 *
 * 2. NO REPRESENTATIONS ARE MADE ABOUT THE SUITABILITY OF THE SOFTWARE FOR ANY
 *    PURPOSE. IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *
 * 3. Neither the software developers, the Center for Advanced Tele-
 *    communications Systems and Services (CATSS), UTD, or any affiliate
 *    of the UT system shall be liable for any damages suffered by
 *    Licensee from the use of this software.
 */


#ifndef _TSMA_H_
#define _TSMA_H_


#include "main.h"
#include "message.h"
#include "fileio.h"
#include "mac.h"


typedef enum 
{ 
  TSMA_BPKT, 
  TSMA_UPKT, 
  TSMA_ACK 
} MacTsmaPktType;


typedef enum 
{
  MAC_TSMA_READY,
  MAC_TSMA_WF_USLOT,
  MAC_TSMA_WF_BSLOT,
  MAC_TSMA_XMT_UPKT,
  MAC_TSMA_XMT_BPKT,
  MAC_TSMA_XMT_UACK,
  MAC_TSMA_WF_UACK
} MacTsmaState;


typedef struct mac_tsma_hdr_str
{
  NODE_ADDR sourceAddr;
  NODE_ADDR destAddr;
  
  MacTsmaPktType type;

  int seqNum;

  //int priority;
} MacTsmaHeader;


typedef struct glomo_mac_tsma_str
{
  GlomoMac *myGlomoMac;

  Message* currentOutgoingFrame;
  NODE_ADDR currentOutgoingFrameNextHopAddress;
  //MacPacketQueue queue;

  /* MAC frame management. */
  int *pktIds;
  int seqNum;
  int maxReps;
  int pktReps;

  /* MAC states. */
  MacTsmaState currentState;
  MacTsmaState prevState;

  /* MAC TSMA parameters. */
  char *schedule;
  int frameLength;
  int currentSlot;

  /* MAC frame counters. */
  int pktsToSend;
  int pktsLostOverflow;
  int pktsSentUnicast;
  int pktsSentBroadcast;
  int pktsGotUnicast;
  int pktsGotBroadcast;
} GlomoMacTsma;


typedef struct mac_tsma_synch_pkt_str
{
  clocktype slotInterval;
} MacTsmaSynchPkt;

/*
 * NAME:        MacTsmaInit
 *
 * PURPOSE:     Initialization function for the TSMA protocol.
 *
 * PARAMETERS:  node, node being initialized
 *              input, structure containing contents of input file
 *
 * RETURN:      None
 *
 * ASSUMPTIONS: None
 */

void MacTsmaInit(GlomoNode *node, int index, const GlomoNodeInput* input);

/*
 * NAME:        MacTsmaLayer
 *
 * PURPOSE:     Models the behavior of the MAC layer with the TSMA protocol
 *              on receiving a message.
 *
 * PARAMETERS:  node, node which received the message
 *              msg, message received
 *
 * RETURN:      None
 *
 * ASSUMPTIONS: None
 */

void MacTsmaLayer(GlomoNode *node, int index, Message *msg);

/*
 * NAME:        MacTsmaFinalize
 * 
 * PURPOSE:     Called at the end of simulation to collect statisitcs
 *              associated with MAC layer performance.
 *
 * PARAMETERS:  node, node for which stats are to be collected
 *
 * RETURN:      None
 *
 * ASSUMPTIONS: None
 */

void MacTsmaFinalize(GlomoNode *node, int index);

/*
 * FUNCTION    MacTsmaNetworkLayerHasPacketToSend.
 * PURPOSE     For notifying TCMA that a new packet at the network layer
 *             is ready to be sent.
*/

void MacTsmaNetworkLayerHasPacketToSend(GlomoNode *node, GlomoMacTsma *tsma);


/*
 * NAME:        MacTsmaReceivePacketFromRadio
 *              (Was:MacTsmaProcRadioPkt).
 *
 * PURPOSE:     Process frames sent up from radio layer.
 *
 * PARAMETERS:  node, node receiving radio frame
 *              msg, contains radio frame
 *
 * RETURN:      None
 *
 * ASSUMPTIONS: None
 */


void MacTsmaReceivePacketFromRadio(
  GlomoNode* node, GlomoMacTsma* tsma, Message* msg);

    
void MacTsmaReceiveRadioStatusChangeNotification(
   GlomoNode* node,
   GlomoMacTsma* tsma,
   RadioStatusType oldRadioStatus,
   RadioStatusType newRadioStatus);


#endif

