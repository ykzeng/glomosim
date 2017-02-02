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
 * $Id: mac.h,v 1.18 2001/02/23 05:35:05 jmartin Exp $
 */

#ifndef _MAC_H_
#define _MAC_H_

#include "radio.h"


#define MAC_DELAY                     (2 * MICRO_SECOND)
#define MAC_PROPAGATION_DELAY         (1 * MICRO_SECOND)

/*
 * Different MAC layers supported
 */

typedef enum 
{
    MAC_PROTOCOL_CSMA,
    MAC_PROTOCOL_MACA,
    MAC_PROTOCOL_FAMA,
    MAC_PROTOCOL_802_11,
    MAC_PROTOCOL_TSMA,
    MAC_PROTOCOL_WIRED
} MAC_PROTOCOL;

/*
 * typedef to GlomoMac in main.h
 */
struct glomo_mac_str 
{
    MAC_PROTOCOL macProtocol;
    int          interfaceIndex;
    BOOL         macStats;

    BOOL         promiscuousMode;
    int          bandwidth;   // In bytes.
    clocktype    propDelay;
    
    int radioNumber;
    
    void         *macVar;
};


void GLOMO_MacNetworkLayerHasPacketToSend(
   GlomoNode *node, InterfaceIdType interfaceIndex);

void GLOMO_MacReceivePacketFromRadio(
   GlomoNode *node, 
   InterfaceIdType interfaceIndex,
   Message* packet);

void GLOMO_MacReceiveRadioStatusChangeNotification(
   GlomoNode *node, 
   InterfaceIdType interfaceIndex,
   RadioStatusType oldRadioStatus,
   RadioStatusType newRadioStatus,
   clocktype receiveDuration,
   const Message* potentialIncomingPacket);




typedef struct {
    clocktype theDelayUntilAirborn;
} MacToRadioPacketDelayInfoType; 


void MacInitUserMacProtocol(
   GlomoNode* node,
   const GlomoNodeInput* nodeInput,
   const char* macProtocolName,
   int interfaceIndex);

void MacFinalizeUserMacProtocol(GlomoNode* node, int interfaceIndex);
   

void MacHandleUserMacProtocolEvent(
   GlomoNode* node, int interfaceIndex, Message* packet);



#endif /* _MAC_H_ */

