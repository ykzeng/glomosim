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
 * $Id: tcp_config.h,v 1.2 1999/09/05 05:24:13 jmartin Exp $
 *
 * This file contains configurable options and constants.  
 * Users can set these values for their particular needs.
 */

#ifndef _TCP_CONFIG_H_
#define _TCP_CONFIG_H_

/*
 * keepalive option
 * if 1, always send probes when keepalive timer times out.
 * if 0, remain silent
 * Originally always_keepalive in tcp_timer.c
 */
#define TCP_ALWAYS_KEEPALIVE 1

/*
 * Whether to include TCP Options defined in RFC 1323:
 * window scaling and timestamp
 * if 1, include these options in tcp header
 * if 0, do not include these options
 * Originally tcp_do_rfc1232 in tcp_subr.c.
 */ 
#define TCP_DO_RFC1323 0

/*
 * Nagle algorithm: delay send to coalesce packets.
 * If 1, disable Nagle. If 0, enable Nagle (default).
 */ 
#define TCP_NODELAY 0

/*
 * Don't use TCP option.
 * If 1, shouldn't include options in TCP header.
 * If 0, options are allowed.
 */ 
#define TCP_NOOPT   0

/*
 * Don't push last block of write.
 * If 1, do not push.
 * If 0, push. 
 */
#define TCP_NOPUSH  0

/*
 * Whether to delay ACK
 * If 1, do not delay ACK if the received packet is a short packet.
 * If 0, delay ACK of all packets.
 */ 
#define TCP_ACK_HACK 1

/*
 * Default maximum segment size for TCP.
 * With an IP MSS of 576, this is 536,
 * but 512 is probably more convenient.
 * This should be defined as MIN(512, IP_MSS - sizeof (struct tcpiphdr)).
 * Originally defined in tcp.h 
 */
#define TCP_MSS 512 

/*
 * TCP_SENDSPACE and TCP_RECVSPACE are the default send and
 * receiver buffer size.
 * Both of them should be defined as 1024*16.
 * Originally tcp_sendspace and tcp_recvspace in tcp_usrreq.c.
 */
#define TCP_SENDSPACE 1024*16 
#define TCP_RECVSPACE 1024*16 

#endif /* _TCP_CONFIG_H_ */

