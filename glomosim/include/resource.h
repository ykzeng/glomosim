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
 * $Id: resource.h,v 1.5 1999/12/08 17:24:41 jmartin Exp $
 *
 * Function declarations for resource sharing.
 */

#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "main.h"
#include "queue.h"

enum {
    RESOURCE_CPU,
    RESOURCE_NIC,

    /*
     * Any other resources which have to be added should be added before
     * RESOURCE_DEFAULT. Otherwise the program will not work correctly.
     */
    RESOURCE_DEFAULT
};


/*
 * typedef to GlomoResource in main.h
 */
struct glomo_resource_str {
    BOOL    isBusy;
    Queue   queue;

    unsigned char layerField[GLOMO_DEFAULT_LAYER];
};


/*
 * FUNCTION     GLOMO_ResourceShareLayer
 * PURPOSE      Set the specified layerType for sharing the specified resource.
 *              Any messages received by "layerType" while the resource is
 *              being utilized will be buffered automatically.
 *
 * Parameters:
 *     node:          The node for which resource sharing is being set.
 *     layerType:     The layer type which will utilize the resource.
 *     resourceType:  The resource for which we are setting.
 */
void GLOMO_ResourceShareLayer (GlomoNode *node, int layerType,
                               int resourceType);


/*
 * FUNCTION     GLOMO_UtilizeResource
 * PURPOSE      Mark the resource as busy until the specified delay.
 *
 * Parameters:
 *     node:          The node for which the resource is being set to busy.
 *     delay:         The time duration during which the resource is busy.
 *     resourceType:  The resource which will be utilized.
 */
void GLOMO_UtilizeResource(GlomoNode *node, clocktype delay,
                           int resourceType);



/*
 * FUNCTION     GLOMO_ResourceBuffer
 * PURPOSE      A new message has been received. Check if it needs
 *              to be buffered.
 *
 * Parameters:
 *     msgHdr:       The message which we are considering.
 *     node:         The node for which the message has arrived.
 */
BOOL GLOMO_ResourceBuffer (Message *msg, GlomoNode *node);


/*
 * FUNCTION     GLOMO_ResourceFree
 * PURPOSE      A message type has been received to free the resource.
 *              Check if any messages are waiting for this resource to
 *              be freed. If a message is available process it.
 *
 * Parameters:
 *     msgHdr:       The message for freeing resource.
 *     node:         The node for which resource is being freed.
 */
void GLOMO_ResourceFree (Message *msg, GlomoNode *node);

#endif /* _RESOURCE_H_ */

