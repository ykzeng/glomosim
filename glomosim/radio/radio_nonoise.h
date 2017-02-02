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
 * $Id: radio_nonoise.h,v 1.3 2000/12/05 03:22:46 mineo Exp $
 */

#ifndef _RADIO_NONOISE_H_
#define _RADIO_NONOISE_H_

#include "main.h"

#define NONOISE_SNR_THRESHOLD_dB 10.0

/*
 * Structure for radio statistics variables
 */
typedef struct radio_nonoise_stats_str {
    int totalTxSignals;
    int totalRxSignalsAboveRX;
    int totalRxSignalsAboveCS;
    int totalRxSignalsToMac;
    int totalCollisions;
    double energyConsumed;
    clocktype turnOnTime;
} RadioNonoiseStats;


/*
 * Structure for Radio.
 */
typedef struct glomo_radio_nonoise_str {
    double           radioRxSnrThreshold;
    double           radioRxSnrThreshold_dB;

    Message   *rxMsg;
    double     rxMsgPower_mW;
    clocktype  rxMsgTxDuration;
    clocktype  rxStartTime;

    int numSignals;
    RadioStatusType mode;
    RadioStatusType previousMode;

    RadioNonoiseStats    stats; /* Stores statistical results */
} GlomoRadioNonoise;


/*
 * FUNCTION    RadioNonoiseLayer
 * PURPOSE     Models the behaviour of the Radio with capture on receiving
 *             the message enclosed in msgHdr.
 *
 * Parameters:
 *     node:     node which received the message
 *     msgHdr:   message received by the layer
 */
void RadioNonoiseLayer(GlomoNode *node, const int radioNum, Message *msgHdr);

void RadioNonoiseInit(GlomoNode *node, const int radioNum, 
                 const GlomoNodeInput *nodeInput);

void RadioNonoiseFinalize(GlomoNode *node, const int radioNum);

static /*inline*/
RadioStatusType RadioNonoiseGetStatus(GlomoNode *node, int radioNum) {
    GlomoRadioNonoise* radioNonoise = 
       (GlomoRadioNonoise *)node->radioData[radioNum]->radioVar;
    return (radioNonoise->mode);
}

void RadioNonoiseStartTransmittingPacket(
   GlomoNode* node, int radioNum, Message* packet,
   BOOL useMacLayerSpecifiedDelay,
   clocktype delayUntilAirborne);

#endif /* _RADIO_NONOISE_H_ */

