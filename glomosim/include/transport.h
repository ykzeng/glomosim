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
 * $Id: transport.h,v 1.10 2001/02/16 04:00:29 jmartin Exp $
 * This file contains definitions common to transport layer protocols.
 */

#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_


#define TRANSPORT_DELAY (1 * MICRO_SECOND)

typedef enum {
    TRANSPORT_PROTOCOL_UDP, 
    TRANSPORT_PROTOCOL_TCP 
}TRANSPORT_PROTOCOL;


typedef struct GlomoTransportUdpStruct GlomoTransportUdp;
typedef struct GlomoTransportTcpStruct GlomoTransportTcp;


/*
 * Structure for transport layer.
 *
 * typedef to GlomoTransport in main.h
 */
struct glomo_transport_str {
    GlomoTransportUdp* udp;
    GlomoTransportTcp* tcp;
};
 
#endif /* _TRANSPORT_H_ */

