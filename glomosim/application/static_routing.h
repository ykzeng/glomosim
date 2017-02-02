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
 * $Id: static_routing.h,v 1.1 1999/06/08 23:07:13 lokesh Exp $
 *
 * NAME:            static_routing.h.
 *
 * WRITTEN BY:      Ken Tang.
 *
 * PURPOSE:         Static routing.
 */

#ifndef _STATIC_ROUTING_H_
#define _STATIC_ROUTING_H_


/*
 * NAME:        RoutingStaticLayer.
 *
 * PURPOSE:     Handles all messages sent to bellmandford.
 *
 * PARAMETERS:  node, node receiving message.
 *              msg, message for node to interpret.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingStaticLayer(GlomoNode *node, const Message *msg);


/*
 * NAME:        RoutingStaticInit.
 *
 * PURPOSE:     Handling all initializations needed by static routing.
 *
 * PARAMETERS:  node, node doing the initialization.
 *              nodeInput, input from configuration file.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingStaticInit(GlomoNode *node, const GlomoNodeInput *nodeInput);


/*
 * NAME:        RoutingStaticFinalize.
 *
 * PURPOSE:     Handling all finalization needed by static routing.
 *
 * PARAMETERS:  node, node doing the finalization.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void RoutingStaticFinalize(GlomoNode *node);


#endif /* _STATIC_ROUTING_H_ */

