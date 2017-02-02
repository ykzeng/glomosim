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
 * $Id: tcpip.h,v 1.2 1999/09/05 05:25:02 jmartin Exp $
 *
 * Ported from FreeBSD 2.2.2.
 * This file contains TCP plus IP header structure after ip options removed.
 */

#ifndef _TCPIP_H_
#define _TCPIP_H_

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
 *  @(#)tcpip.h 8.1 (Berkeley) 6/10/93
 * $Id: tcpip.h,v 1.2 1999/09/05 05:25:02 jmartin Exp $
 */

/*
 * Overlay for ip header used by other protocols (tcp, udp).
 */
struct ipovly {
    char *ih_next, *ih_prev;     /* for protocol sequence q's */
    unsigned char  ih_x1;        /* (unused) */
    unsigned char  ih_pr;        /* protocol */
    short    ih_len;             /* protocol length */
    long     ih_src;             /* source internet address */
    long     ih_dst;             /* destination internet address */
};


/*
 * Tcp+ip header, after ip options removed.
 */
struct tcpiphdr {
    struct  ipovly ti_i;        /* overlaid ip structure */
    struct  tcphdr ti_t;        /* tcp header */
};
#define ti_next     ti_i.ih_next
#define ti_prev     ti_i.ih_prev
#define ti_x1       ti_i.ih_x1
#define ti_pr       ti_i.ih_pr
#define ti_len      ti_i.ih_len
#define ti_src      ti_i.ih_src
#define ti_dst      ti_i.ih_dst
#define ti_sport    ti_t.th_sport
#define ti_dport    ti_t.th_dport
#define ti_seq      ti_t.th_seq
#define ti_ack      ti_t.th_ack
#define ti_x2       ti_t.th_x2
#define ti_off      ti_t.th_off
#define ti_flags    ti_t.th_flags
#define ti_win      ti_t.th_win
#define ti_sum      ti_t.th_sum
#define ti_urp      ti_t.th_urp

#endif /* _TCPIP_H_ */

