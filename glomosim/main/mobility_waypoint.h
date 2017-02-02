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
 * $Id: mobility_waypoint.h,v 1.9 2001/02/15 03:06:06 mineo Exp $
 */

#ifndef _MOBILITY_WAYPOINT_H_
#define _MOBILITY_WAYPOINT_H_

#include "driver.h"
#include "fileio.h"

typedef struct glomo_mobility_random_waypoint_str {
    clocktype mobilityPause;
    double MaxSpeed;
    double MinSpeed;

    GlomoCoordinates dest;
    int number_moves_left;
    clocktype move_interval;

    GlomoCoordinates move_step;

} GlomoMobilityRandomWaypoint;


/*
 * FUNCTION     GLOMO_MobilityRandomWaypointInit
 * PURPOSE      Initialization function for random drunken waypoint model.
 *
 * Parameters:
 *     node:      node being initialized.
 *     nodeInput: structure containing contents of input file
 */
void GLOMO_MobilityRandomWaypointInit (GlomoNode *node,
                                       GlomoNodeInput *nodeInput);


/*
 * FUNCTION    GLOMO_MobilityRandomWaypoint
 * PURPOSE     Models the behaviour of the random drunken waypoint model
 *             on receiving a message.
 *
 * Parameters:
 *     node:     node which received the message
 *     msg:      message received by the layer
 */
void GLOMO_MobilityRandomWaypoint (GlomoNode *node);

#endif /* _MOBILITY_DEST_H_ */








