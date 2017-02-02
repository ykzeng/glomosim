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
 * $Id: api.h,v 1.23 2001/02/16 04:00:29 jmartin Exp $
 *
 * API header file.
 */

#ifndef _API_H_
#define _API_H_

#include "main.h"
#include "coordinates.h"
#include "splaytree.h"
#include "mobility.h"
#include "propagation.h"
#include "radio.h"
#include "mac.h"
#include "network.h"
#include "transport.h"
#include "application.h"


#define MAX_NUM_RADIOS 5
#define MAX_NUM_INTERFACES 30


struct EventTimeHeapStruct;


/*
 * The Node Structure.
 * This strucutre will include all the information related to a particular 
 * node. The data structure for each layer should be added to this structure.
 *
 * typedef to GlomoNode in main.h
 */
struct glomo_node_str {
    /* Common Information  about each node. */
    /* This field represents the simulation id of the node. It is used
       only for simulation purposes and should not be used by the protocol
       code at any layer. For the network address of the node use the next
       field, which is called nodeAddr. */
    unsigned       id;

    NODE_ADDR      nodeAddr;      /* the network address of the node */
    unsigned short seed[3];       /* seed for random number generator */
    unsigned short initialSeedValue[3]; /* First seed value for a node */
    long           numNodes;      /* number of nodes in the simulation */

    GlomoCoordinates position;

    SplayTree splayTree;
    
    
    

    GlomoPartition *partitionData;

    GlomoMobility  mobilityData;

    /* Information about partition nodes */
    GlomoNode      *prevNodeData;
    GlomoNode      *nextNodeData;

    /* Layer specific information about each node. */
    GlomoProp      *propData; /* propagation information */
    GlomoRadio*     radioData[MAX_NUM_RADIOS]; /* radio layer information   */
    int             numberRadios;
    GlomoMac*       macData[MAX_NUM_INTERFACES];  /* mac layer information */
    int             numberInterfaces;
    GlomoNetwork    networkData;   /* network layer information */
    GlomoTransport  transportData; /* transport layer information */
    GlomoApp        appData;       /* application layer information */
    
    // For Parallel Lookahead Calculation
    
    int eotCalculatorBackPtrIndex;
    
};



/*
 * FUNCTION      GLOMO_ConvertToClock
 * PURPOSE       Read the string in "buf" and provide the corresponding
 *               coordinates for the string.
 */
void GLOMO_ConvertToCoordinates(char *buf, GlomoCoordinates *coordinates);

/*
 * FUNCTION      GLOMO_ConvertToClock
 * PURPOSE       Read the string in "buf" and provide the corresponding
 *               clocktype value for the string. Use the following conversions:
 *               NS - nano-seconds
 *               MS - milli-seconds
 *               S  - seconds (default if no specification)
 *               H  - hours
 *               D  - days
 */
clocktype GLOMO_ConvertToClock(char *buf);

/*
 * FUNCTION      GLOMO_PrintClockInSecond
 * PURPOSE       Print a clocktype value in second.
 *               The result is copied to stringInSecond
 */
void GLOMO_PrintClockInSecond(clocktype clock, char stringInSecond[]);

/*
 * FUNCTION      GLOMO_PrintStat
 * PURPOSE       Print out the relevant stat in "buf", along with the
 *               node id and the layer type generating this stat.
 *               
 * Paramters:
 *     node         the node generating the stat
 *     layer        the layer generating the stat
 *     buf          string which has the statistic to be printed out
 */
void GLOMO_PrintStat(GlomoNode *node, char *layer, char *buf);

#endif /* _API_H_ */

