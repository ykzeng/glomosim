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
 * $Id: tcp_hdr.h,v 1.2 1999/09/05 05:24:21 jmartin Exp $
 *
 * Ported from FreeBSD 2.2.2.
 * This file contains TCP header structure definition.
 */

#ifndef _TCP_HDR_H_
#define _TCP_HDR_H_

/*
 * Copyright (c) 1982, 1986, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)tcp.h   8.1 (Berkeley) 6/10/93
 * $Id: tcp_hdr.h,v 1.2 1999/09/05 05:24:21 jmartin Exp $
 */

typedef unsigned long  tcp_seq;

/*
 * TCP header.
 * Per RFC 793, September, 1981.
 */
struct tcphdr {
    unsigned short th_sport;       /* source port */
    unsigned short th_dport;       /* destination port */
    tcp_seq th_seq;                /* sequence number */
    tcp_seq th_ack;                /* acknowledgement number */
    unsigned int  th_x2:4,         /* (unused) */
                  th_off:4,        /* data offset */
                  th_flags:8,
                  th_win:16;       /* window */
    unsigned short th_sum;         /* checksum */
    unsigned short th_urp;         /* urgent pointer */
};

/* 
 * value of th_flags
 */
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG)

/*
 * value of TCP options and length of the options
 */
#define TCPOPT_EOL              0
#define TCPOPT_NOP              1
#define TCPOPT_MAXSEG           2
#define TCPOLEN_MAXSEG          4
#define TCPOPT_WINDOW           3
#define TCPOLEN_WINDOW          3
#define TCPOPT_SACK_PERMITTED   4       /* Experimental */
#define TCPOLEN_SACK_PERMITTED  2
#define TCPOPT_SACK             5       /* Experimental */
#define TCPOPT_TIMESTAMP        8
#define TCPOLEN_TIMESTAMP       10
#define TCPOLEN_TSTAMP_APPA     (TCPOLEN_TIMESTAMP+2) /* appendix A */
#define TCPOPT_TSTAMP_HDR       \
    (TCPOPT_NOP<<24|TCPOPT_NOP<<16|TCPOPT_TIMESTAMP<<8|TCPOLEN_TIMESTAMP)

#define TCPOPT_CC               11      /* CC options: RFC-1644 */
#define TCPOPT_CCNEW            12
#define TCPOPT_CCECHO           13
#define TCPOLEN_CC              6
#define TCPOLEN_CC_APPA         (TCPOLEN_CC+2)
#define TCPOPT_CC_HDR(ccopt)    \
    (TCPOPT_NOP<<24|TCPOPT_NOP<<16|(ccopt)<<8|TCPOLEN_CC)

#define TCP_MAXWIN 65535            /* largest value for (unscaled) window */
#define TTCP_CLIENT_SND_WND 4096    /* dflt send window for T/TCP client */

#define TCP_MAX_WINSHIFT 14         /* maximum window shift */

#define TCP_MAXHLEN (0xf<<2)        /* max length of header in bytes */
#define TCP_MAXOLEN (TCP_MAXHLEN - sizeof(struct tcphdr))
                                    /* max space left for options */

#endif /* _TCP_HDR_H_ */ 

