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
 * $Id: tcp_proto.h,v 1.5 1999/09/28 05:25:47 ktang Exp $
 *
 * Ported from FreeBSD 2.2.2.
 * This file contains TCP function prototypes.
 */

#ifndef _TCP_PROTO_H_
#define _TCP_PROTO_H_

#include "main.h"
#include "transport.h"

#include "in_pcb.h"
#include "tcpip.h"
#include "tcp_seq.h"
#include "tcp_var.h"

extern int get_conid(struct inpcb *);

extern void insque_ti(struct tcpiphdr *, struct tcpiphdr *);

extern int in_cksum(unsigned short *, int);

extern int myrand(int, int, unsigned short *);

extern void remque_ti(struct tcpiphdr *);

extern struct inpcb *tcp_attach(struct inpcb *, APP_TYPE, NODE_ADDR, short,
                                NODE_ADDR, short, long, int);

extern void tcp_canceltimers(struct tcpcb *);

extern struct tcpcb *tcp_close(GlomoNode *, struct tcpcb *, struct tcpstat *);

extern void tcp_connect(GlomoNode *, struct inpcb *, APP_TYPE, 
                        NODE_ADDR, short, NODE_ADDR, short,
                        unsigned long, tcp_seq *, struct tcpstat *,
                        long, int);

extern void tcp_disconnect(GlomoNode *, struct inpcb *, int,
                           unsigned long, struct tcpstat *);

extern struct tcpcb *tcp_drop(GlomoNode *, struct tcpcb *, unsigned long,
                              struct tcpstat *);

extern void tcp_fasttimo(GlomoNode *, struct inpcb *, unsigned long,
                         struct tcpstat *);

extern void tcp_input(GlomoNode *, unsigned char *, int, int,
                      struct inpcb *, tcp_seq *, unsigned long,
                      struct tcpstat *);

extern void tcp_listen(GlomoNode *, struct inpcb *, APP_TYPE, NODE_ADDR,
                       short, int);

extern int tcp_mssopt();

extern struct tcpcb *tcp_newtcpcb(struct inpcb *);

extern void tcp_output(GlomoNode *, struct tcpcb *, unsigned long,
                       struct tcpstat *);

extern void tcp_respond(GlomoNode *, struct tcpcb *, struct tcpiphdr *,
                        int, tcp_seq, tcp_seq,
                        int, struct tcpstat *);
 
extern void tcp_send(GlomoNode *, struct inpcb *, int, 
                     unsigned char *, int, unsigned long,
                     struct tcpstat *);

extern void tcp_setpersist(struct tcpcb *);

extern void tcp_slowtimo(GlomoNode *, struct inpcb *, tcp_seq *,
                         unsigned long *, struct tcpstat *);

extern struct tcpiphdr * tcp_template(struct tcpcb *);

#endif /* _TCP_PROTO_H_ */

