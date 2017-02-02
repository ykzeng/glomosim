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
 * $Id: driver.h,v 1.14 2001/02/15 03:06:06 mineo Exp $
 *
 * Structure declarations needed by the driver entity.
 */

#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "main.h"
#include "message.h"

/*
 * FUNCTION     DriverSendNeighborInfo
 * PURPOSE      Send neighbor information between the two partitions.
 *
 * Parameters:
 *     to_x:      x index of first partition
 *     to_y:      y index of first partition
 *     channel:   pointer to channel information
 *     from_x:    x index of second partition
 *     from_y:    y index of second partition
 *     dir1:      position of 2nd partition with respect to 1st partition
 *     dir2:      position of 1st partition with respect to 2nd partition
 */
void DriverSendNeighborInfo(int to_x, int to_y,
                            GlomoAreaInfo **channel,
                            int from_x, int from_y, int dir1, int dir2);

/*
 * Map entities to processors. Current empty.
 */
void DriverMapEntities(int **mapping,
                       int partitionNum_x, int partitionNum_y,
                       int  numProcessorsX, int  numProcessorsY);

/*
 * The following functions are for generating nodes in the simulation.
 * These were copied directly from old framework. The one for generating
 * random nodes looks okay. I have not gone into the others in detail.
 * We need to make sure that they work correctly.
 */
/*
 * Function for generating random nodes in the simulation.
 */
int DriverGenerateRandomNodes(GlomoNodePositionInfo *nodeData, int nodeNum,
                              GlomoCoordinates terrainDimensions,
                              unsigned short seed[3]);
/*
 * Function for generating uniform nodes in the simulation.
 */
int DriverGenerateUniformNodes(GlomoNodePositionInfo *nodeData, int nodeNum,
                               GlomoCoordinates terrainDimensions,
                               unsigned short seed[3]);

/*
 * Function for generating nodes in a grid topology.
 */
int DriverGenerateGridNodes(GlomoNodePositionInfo *nodeData, int nodeNum,
                            int gridUnit, GlomoCoordinates terrainDimensions);

/*
 * Function for generating nodes based on input file.
 */
int DriverGenerateInputNodes(GlomoNodePositionInfo *nodeData, int nodeNum,
                             GlomoCoordinates terrainDimensions,
                             GlomoNodeInput *nodeInput);

#endif /* _DRIVER_H_ */

