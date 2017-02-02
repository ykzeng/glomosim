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
 * $Id: in_pcb.h,v 1.5 1999/09/28 05:54:07 ktang Exp $
 *
 * Ported from FreeBSD 2.2.2.
 * This file contains common pcb structure for internet protocol 
 * implementation.
 */

#ifndef _IN_PCB_H_
#define _IN_PCB_H_

/*
 * Copyright (c) 1982, 1986, 1990, 1993
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
 *  @(#)in_pcb.h    8.1 (Berkeley) 6/10/93
 * $Id: in_pcb.h,v 1.5 1999/09/28 05:54:07 ktang Exp $
 */
 
#include "main.h"
#include "application.h"

#include "tcp_var.h"

#define INPCB_WILDCARD     0
#define INPCB_NO_WILDCARD  1

#define sbspace(inp) ((inp)->inp_rcv_hiwat) 

struct inp_buf {
    unsigned long cc;              /* actual chars in buffer */
    unsigned long hiwat;           /* max actual char count */
    unsigned char *buffer;         /* buffer content */
};

/*
 * Data structure for blocked user data.
 */
struct pending_buf{
    unsigned long cc;              /* number of bytes moved to send buffer */
    unsigned long hiwat;           /* length of the payload */ 
    unsigned char *buffer;   /* payload of the blocked packet */
};

struct inpcb {
    struct inpcb *inp_next, *inp_prev; /* doubly linked list of inpcb */
    struct inpcb *inp_head;            /* pointer back to chain of inpcb's 
                                          for this protocol */
    APP_TYPE app_proto_type;           /* app this connection belongs to */
    /* four-tuple used to identify a connection */
    NODE_ADDR inp_remote_addr;           /* remote address    */
    short     inp_remote_port;           /* remote port       */
    NODE_ADDR inp_local_addr;            /* local address     */
    short     inp_local_port;            /* local port        */

    char    *inp_ppcb;                 /* pointer to per protocol PCB */
    int     con_id;                    /* connection id #    */
    unsigned long inp_rcv_hiwat;       /* receive buffer size */
    struct inp_buf inp_snd;            /* send buffer */  
    struct pending_buf blocked_pkt;    /* data blocked to send */
    int     usrreq;                    /* user request */ 
   
    long unique_id; 
    int priority;
};
 
/* 
 * Possible values of usrreq.
 */
#define INPCB_USRREQ_NONE         0
#define INPCB_USRREQ_OPEN         1
#define INPCB_USRREQ_CONNECTED    2
#define INPCB_USRREQ_CLOSE        3

extern int append_buf(GlomoNode *, struct inpcb *, unsigned char *,
                      int);
extern void del_buf(GlomoNode *, struct inpcb *, int);
extern struct inpcb *in_pcballoc(struct inpcb *, int, int);
extern void in_pcbdetach(struct inpcb *);
extern struct inpcb *in_pcblookup(struct inpcb *, NODE_ADDR, short,
                                  NODE_ADDR, short, int);
extern struct inpcb *in_pcbsearch(struct inpcb *, int);

#endif /* _IN_PCB_H_ */

