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
 * $Id: propagation.h,v 1.9 2001/08/31 19:07:36 jmartin Exp $
 */

#ifndef _PROPAGATION_H_
#define _PROPAGATION_H_

#include "main.h"

#define PI 3.14159265358979323846
#define SPEED_OF_LIGHT 3.0e8
#define BOLTZMANN_CONSTANT 1.379e-23

#define DEFAULT_NOISE_FIGURE 10.0

#define MAX_NUM_CHANNELS 10

/*
 * Macro to compute the propagation delay for "dist" for
 * the specified range unit.
 * Assuming that simulation clock is in nano-seconds
 */
#define ChannelPropagationDelay(dist) ((clocktype)((dist) * 10.0 / 3.0 + 0.5))


#define GLOMO_PropBackgroundNoise_mW(node, channelBandwidth) \
            ((node)->propData->backgroundNoise_mW * channelBandwidth)

#define GLOMO_PropBackgroundNoise_dBm(node, channelBandwidth) \
            ((node)->propData->backgroundNoise_dBm * channelBandwidth)


typedef enum {
    FREE_SPACE = 0,
    TWO_RAY,
    PATHLOSS_MATRIX
} PATHLOSS_MODEL;

typedef enum {
    NONE,
    RAYLEIGH,
    RICIAN
} FADING_MODEL;

typedef struct {
    double snr;
    double ber;
} GlomoPropBerTable;



/*
 * typedef to GlomoProp in main.h
 */
struct glomo_prop_str {
    GlomoChannel *channelData[MAX_NUM_CHANNELS];
    int numberChannels;
    double backgroundNoise_mW;
    double backgroundNoise_dBm;
    double propLimit_dBm;
    PATHLOSS_MODEL pathlossModel;
    FADING_MODEL fadingModel;
    double ricianKFactor;
    double ricianStandardDeviation;
    void           *pathlossVar;
    int             numBerDataItems;
    GlomoPropBerTable *berTable;
};



/*
 * This structure is used for fields related to channel layer information
 * that need to be sent with a message.
 */
typedef struct propagation_info_str {
    GlomoCoordinates txPosition;
    clocktype txStartTime; // transmit starting time at the transmitter
    clocktype txDuration;  // transmiting duration time
    NODE_ADDR txAddr;      // address of node that is sending message
    float txPower_dBm;   /* transmit power */
    float txAntennaGain_dB;
    float txAntennaHeight;
    float wavelength;    /* Channel wavelength */
    double rxPower_mW;    /* the received power of the signal */
    float correlatedFastFading_dB; // Frame sequences can have same fast fade.
    NODE_ADDR correlatedFastFadingDestinationNode; 
} PropInfo;

/*
 * Structure to keep information about neighboring partitions.
 * Used by the Channel layer.
 *
 * typdef to GlomoNeighbor in main.h
 */
typedef struct glomo_neighbor_str {
    ename partitionEname; /* The ename used for sending message */
    BOOL status;          /* Used to indicate if neighbor exists.
                             If this field is FALSE, neighbor doesn't exist.*/
    double start_x;     /* The Starting X Position  */
    double start_y;     /* The Starting Y Position */
    double end_x;       /* The Ending X Position    */
    double end_y;       /* The Ending Y Position    */
} GlomoNeighbor;

/*
 * FUNCTION     GLOMO_GlobalPropagateInit
 * PURPOSE      Initialization function for propagation functions
 *
 * Parameters:
 *     propagateData: structure shared among nodes
 *     nodeInput: structure containing contents of input file
 */
void GLOMO_GlobalPropInit(GlomoProp *propData,
                          const GlomoNodeInput *nodeInput);

void GLOMO_PropInit(GlomoNode *node, GlomoProp *propData);

void GLOMO_PropBroadcast(GlomoPartition *partitionData, Message *msg);


double GLOMO_PropBER(const GlomoNode *node,
                     const double signalPower,
                     const double noisePower);



#endif /* _PROPAGATE_H_ */

