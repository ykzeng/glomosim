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
 * $Id: wiredlink.h,v 1.5 2000/09/15 21:53:47 mineo Exp $
 */

#ifndef _WIREDLINK_H_
#define _WIREDLINK_H_

#include "main.h"
#include "message.h"
#include "api.h"
#include "structmsg.h"
#include "fileio.h"

enum {
    IDLE,
    BUSY
};

//
// MacWiredFrameHeader
// It is similar to the 802.3 header, but is 28 bytes
// (2 bytes longer than the 802.3 header and no padding for short packets)
//
typedef struct mac_wired_frame_header_str {
    char      framePreamble[8];
    NODE_ADDR sourceAddr;
    char      sourceAddrPadding[6 - sizeof(NODE_ADDR)];
    NODE_ADDR destAddr;
    char      destAddrPadding[6 - sizeof(NODE_ADDR)];
    char      length[2];
    char      checksum[4];
} MacWiredFrameHeader;

typedef struct glomo_wired_link_stats_str {
    int packetsSent;
} GlomoWiredLinkStats;

typedef struct glomo_wired_if_str {
    GlomoMac *myGlomoMac;

    int status;
    GlomoNode *dest;
    NODE_ADDR destAddr;
    int destInterfaceId;

    int partitionIndex; // for multiple partitions

    GlomoWiredLinkStats stats;
} GlomoWiredLink;

void WiredLinkInit(GlomoNode * node, const GlomoNodeInput * nodeInput);
void WiredLinkLayer(GlomoNode * node, int interfaceIndex, Message * msg);
void WiredLinkFinalize(GlomoNode * node, int interfaceIndex);

void WiredLinkNetworkLayerHasPacketToSend(GlomoNode * node,
                                          GlomoWiredLink * wiredlink);
void WiredLinkMessageFromWire(GlomoNode *node, int interfaceIndex,
                                Message *msg);
void WiredLinkTransmissionFinished(GlomoNode *node, int interfaceIndex,
                                   Message *msg);

int WiredLinkInterfaceIdForThisDest(GlomoNode *node, NODE_ADDR destAddr);
#endif /* _WIREDLINK_H_ */

