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
 * $Id: mobility.h,v 1.24 2001/02/15 03:11:11 mineo Exp $
 */

#ifndef _MOBILITY_H_
#define _MOBILITY_H_

#include "main.h"
#include "message.h"

#define UPPER_BOUND_ON_MOBILITY_VELOCITY 50


typedef enum {
    MOBILITY_NONE = 20,
    MOBILITY_RANDOM_WAYPOINT,
    MOBILITY_TRACE,
    MOBILITY_PATHLOSS_MATRIX
} MOBILITY_TYPE;


/*
 * typedef to GlomoMobility in main.h
 */
struct glomo_mobility_str {
    MOBILITY_TYPE mobilityType;
    GlomoCoordinates next;

    double distance_granularity;

    clocktype nextMoveTime;
    
    unsigned short seed[3];
    void *mobilityVar;
    double avgSpeed;
    int totalMoves;
    BOOL mobilityStats;
    BOOL guiOption;
};


/*
 * FUNCTION     GLOMO_MobilityInit
 * PURPOSE      Initialization function for mobility models.
 *
 * Parameters:
 *     node:      node being initialized.
 *     nodeInput: structure containing contents of input file
 */
void GLOMO_MobilityInit(GlomoNode *node, GlomoNodeInput *nodeInput);


/*
 * FUNCTION    GLOMO_MobilityFinalize
 * PURPOSE     Called at the end of simulation to collect the results of 
 *             the simulation of the mobility data.
 *
 * Parameter:
 *     node:     node for which results are to be collected.
 */
void GLOMO_MobilityFinalize(GlomoNode *node);


/*
 * FUNCTION    GLOMO_Mobility
 * PURPOSE     Models the behaviour of the mobility models on receiving
 *             a message.
 *
 * Parameters:
 *     node:     node which received the message
 *     msg:      message received by the layer
 */
void GLOMO_Mobility(GlomoNode *node);


/*
 * FUNCTION    GLOMO_MobilityReturnAvgSpd
 * PURPOSE     Returns the Average Speed of a node 
 *
 * Parameters:
 *     node:     node needs to report the average speed
 */
double GLOMO_MobilityReturnAvgSpd(GlomoNode *node);


/*
 * FUNCTION    GLOMO_MobilityReturnPositionX
 * PURPOSE     Returns the X coordinate of a node
 *
 * Parameters:
 *     node:      node needs to report its x coord (GPS)
 */
double GLOMO_MobilityReturnPositionX(GlomoNode *node);

/*
 * FUNCTION    GLOMO_MobilityReturnPositionY
 * PURPOSE     Returns the Y coordinate of a node
 *
 * Parameters:
 *     node:      node needs to report its y coord (GPS)
 */
double GLOMO_MobilityReturnPositionY(GlomoNode *node);

#endif /* _MOBILITY_H_ */

