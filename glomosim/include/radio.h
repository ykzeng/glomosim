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
 * $Id: radio.h,v 1.24 2001/08/31 18:21:47 jmartin Exp $
 */


#ifndef _RADIO_H_
#define _RADIO_H_

#include <stdlib.h>
#include "main.h"

/*
 * synchronization time for 802.11 DSSS PHY
 */
#define SYNCHRONIZATION_TIME         (192 * MICRO_SECOND)

/*
 * This is an aggregated delay at the radio PHY.
 * The value should be reduced as we define more detailed delay times.
 */

#define RADIO_RX_TX_TURNAROUND_TIME  (5 * MICRO_SECOND)
#define RADIO_PHY_DELAY RADIO_RX_TX_TURNAROUND_TIME

#define RADIO_DEFAULT_TX_POWER 15.0
#define RADIO_DEFAULT_ANTENNA_GAIN 0.0
#define RADIO_DEFAULT_ANTENNA_HEIGHT 1.5
#define RADIO_DEFAULT_RX_SENSITIVITY -91.0
#define RADIO_DEFAULT_RX_THRESHOLD   -81.0

/* 
 * Different radio types supported. 
 */
typedef enum {
    RADIO_ACCNOISE,
    RADIO_FOR_SIRCIM,
    RADIO_NONOISE
} RADIO_TYPE;


/*
 * Structure for radio layer.
 * Can be used for radio with and without capture ability.
 *
 * typedef to GlomoRadio in main.h
 */
struct glomo_radio_str {
    RADIO_TYPE radioType;
    int        radioNumber;
    int        macInterfaceIndex;
    double     txPower_mW;
    double     txPower_dBm;
    double     rxSensitivity_mW;
    double     rxSensitivity_dBm;
    double     rxThreshold_mW;
    double     rxThreshold_dBm;
    float      antennaGain_dB;
    float      antennaHeight;
    int        bandwidth;
    double     backgroundNoise_mW;   // Pre-calculated to include bandwidth.
    double     backgroundNoise_dBm;  // 
    float      wavelength;
    
    BOOL       radioStats;
    BOOL       guiOption;

    /*
     * The following varialbe will be interpreted differently
     * by different radio layers.
     */
    void *radioVar;
};


/*
 * Status of the radio: idle, transmitting, or receiving
 */

typedef enum {
    RADIO_IDLE,
    RADIO_SENSING,
    RADIO_RECEIVING,
    RADIO_TRANSMITTING
} RadioStatusType;


/*
 * Used by Radio layer to report channel status to mac layer.
 */
typedef struct radio_status_pkt_str {
    RadioStatusType status;
    clocktype receiveDuration;
    const Message* thePacketIfItGetsThrough;
} PacketRadioStatus;

//
// Radio power consumption rate in mW.
// Note:
// BATTERY_SLEEP_POWER is not used at this point for the following reasons:
// * Monitoring the channel is assumed to consume as much power as receiving
//   signals, thus the radio mode is either TX or RX in ad hoc networks.
// * Power management between APs and stations needs to be modeled in order to
//   simulate the effect of the sleep (or doze) mode for WLAN environment.
// Also, the power consumption for transmitting signals is calculated as
// (BATTERY_TX_POWER_COEFFICIENT * txPower_mW + BATTERY_TX_POWER_OFFSET).
//
// The values below are set based on these assumptions and the WaveLAN
// specifications.
// 
// *** There is no guarantee that the assumptions above are correct! ***
//
#define BATTERY_SLEEP_POWER          (50.0 / SECOND)
#define BATTERY_RX_POWER             (900.0 / SECOND)
#define BATTERY_TX_POWER_OFFSET      BATTERY_RX_POWER
#define BATTERY_TX_POWER_COEFFICIENT (16.0 / SECOND)


void GLOMO_RadioCreateARadioForMacLayer(
    GlomoNode *node, 
    const GlomoNodeInput *nodeInput,
    const int interfaceIndex,
    int* radioNumber);



#define GLOMO_RadioAntennaGain_dB(node, radioNum) \
            ((node)->radioData[(radioNum)]->antennaGain_dB)

#define GLOMO_RadioAntennaHeight(node, radioNum) \
            ((node)->radioData[(radioNum)]->antennaHeight)

BOOL GLOMO_RadioCanReceive(GlomoNode* node, int radioNum, double rxPower_dBm);

RadioStatusType GLOMO_RadioGetStatus(GlomoNode *node, int radioNum);

void GLOMO_RadioStartTransmittingPacket(
   GlomoNode* node, 
   int radioNum, 
   Message* msg,
   NODE_ADDR destinationNode,
   BOOL macLayerSpecifiesTheDelay,
   clocktype delayUntilAirborne);
   

// This routine finds which radio is tuned is tuned to a certain
// frequency. (Returns INVALID_RADIO_NUMBER  when can't find one).

#define INVALID_RADIO_NUMBER -1

int GLOMO_RadioGetRadioNumberForWavelength(GlomoNode* node, double wavelength);


int GLOMO_RadioGetBandwidthBits(GlomoNode* node, int radioNum);
                             

#endif /* _RADIO_H_ */

