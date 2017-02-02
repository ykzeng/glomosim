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
 * $Id: main.h,v 1.26 2001/02/15 03:11:11 mineo Exp $
 *
 * FILENAME: main.h
 * PURPOSE:  This header file contains some common definitions.
 */

#ifndef _MAIN_H_
#define _MAIN_H_

typedef unsigned int NODE_ADDR;
typedef unsigned int InterfaceIdType;

/* for broadcasting address */
#define ANY_DEST 0xfffffff
#define INVALID_ADDRESS 987654321

typedef enum {
    FALSE = 0,
    TRUE = 1
} BOOL;


/* The maximum length of any string in the input file. */
#define GLOMO_MAX_STRING_LENGTH 200
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define SQUARE(x) ((x) * (x))
#define IN_DB(x)  (10.0 * log10(x))
#define NON_DB(x) (pow(10.0, (x) / 10.0))

void* checked_pc_malloc(size_t size);


/* IP will fragment packet into this unit, has to be multiple of 8 
 * right now, it is set to be the same as maximum application data unit 
 * MAX_APP_DATA_UNIT in ../include/application.h
 * so no fragmentation right now.
 */
#define NETWORK_IP_FRAG_UNIT       2048   

#define NW_PKT_HEADER_SIZE            20
#define MAX_NW_PKT_SIZE               NETWORK_IP_FRAG_UNIT 
#define MAX_NW_PAYLOAD_SIZE           (MAX_NW_PKT_SIZE - NW_PKT_HEADER_SIZE) 
#define MAX_NW_BROADCAST_RT_SIZE      MAX_NW_PKT_SIZE

/* MAC layer */
#define MAC_FRAME_HEADER_SIZE 100
#define MAX_MAC_FRAME_SIZE    (MAX_NW_PKT_SIZE + MAC_FRAME_HEADER_SIZE )

/*
 * The various layers in Glomo. As a new layer is added
 * to the simulation it should be added here as well.
 * Used to direct messages to the right layer/module.
 */
enum {
    /* Special control information */
    GLOMO_MOBILITY_SPECIAL,

    /* Various layers */
    GLOMO_CHANNEL_LAYER,
    GLOMO_RADIO_LAYER,
    GLOMO_MAC_LAYER,
    GLOMO_NETWORK_LAYER,
    GLOMO_TRANSPORT_LAYER,
    GLOMO_APP_LAYER, 

    /*
     * Any other layers which have to be added should be added before
     * GLOMO_DEFAULT_LAYER. Otherwise the program will not work correctly.
     */
    GLOMO_DEFAULT_LAYER
};



/* The maximum neighbors that a partition can have. */
#define GLOMO_MAX_NEIGHBOR_PARTITIONS 8

/*
 * The various directions for neighboring partitions. These are
 * also used to identify the direction in which a signal is travelling.
 * The last enumeration is a default one to indicate that the signal
 * is not coming from any specific direction.
 * (i.e it orignated in this partition)
 */
enum {
    SIGNAL_DIR_EAST = 0,
    SIGNAL_DIR_WEST,
    SIGNAL_DIR_NORTH,
    SIGNAL_DIR_SOUTH,
    SIGNAL_DIR_NORTHWEST,
    SIGNAL_DIR_NORTHEAST,
    SIGNAL_DIR_SOUTHWEST,
    SIGNAL_DIR_SOUTHEAST
};

#define NANO_SECOND              ((clocktype) 1)
#define MICRO_SECOND             (1000 * NANO_SECOND)
#define MILLI_SECOND             (1000 * MICRO_SECOND)
#define SECOND                   (1000 * MILLI_SECOND)
#define MINUTE                   (60 * SECOND)
#define HOUR                     (60 * MINUTE)
#define DAY                      (24 * HOUR)

#define PROCESS_IMMEDIATELY 0


typedef struct message_str Message;

typedef struct glomo_node_input_str GlomoNodeInput;
typedef struct glomo_mobility_str GlomoMobility;
typedef struct glomo_timer_str GlomoTimer;

typedef struct glomo_node_str GlomoNode;

typedef struct glomo_prop_str GlomoProp;
typedef struct glomo_channel_str GlomoChannel;
typedef struct glomo_radio_str GlomoRadio;
typedef struct glomo_mac_str GlomoMac;
typedef struct glomo_network_str GlomoNetwork;
typedef struct glomo_transport_str GlomoTransport;
typedef struct glomo_app_str GlomoApp;

typedef struct glomo_partition_str     GlomoPartition;
typedef struct glomo_area_str          GlomoAreaInfo;
typedef struct glomo_area_nearest_str  GlomoAreaNearestInfo;
typedef struct glomo_remote_link_str   GlomoRemoteLink;

typedef struct glomo_coordinates_str   GlomoCoordinates;
#endif /* _MAIN_H_ */

