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
 * $Id: tcp_var.h,v 1.2 1999/09/05 05:24:58 jmartin Exp $
 *
 * Ported from FreeBSD 2.2.2.
 * This file contains definition of TCP control block and statistics structure.
 */

/*
 * Copyright (c) 1982, 1986, 1993, 1994, 1995
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
 *  @(#)tcp_var.h   8.4 (Berkeley) 5/24/95
 *  $Id: tcp_var.h,v 1.2 1999/09/05 05:24:58 jmartin Exp $
 */

/*
 * tcp_var.h
 * Lan Wang, Xiang Zeng
 * modified: 8/5/98
 */ 
 
#ifndef _TCP_VAR_H_
#define _TCP_VAR_H_

/*
 * Kernel variables for tcp.
 */

#include "tcp_hdr.h"
#include "tcp_timer.h"

/*
 * Tcp control block, one per tcp; fields:
 */
struct tcpcb {
    struct  tcpiphdr *seg_next;     /* sequencing queue */
    struct  tcpiphdr *seg_prev;
    int     t_state;                /* state of this connection */
    int     t_timer[TCPT_NTIMERS];  /* tcp timers */
    int     t_rxtshift;             /* log(2) of rexmt exp. backoff */
    int     t_rxtcur;               /* current retransmit value */
    int     t_dupacks;              /* consecutive dup acks recd */
    unsigned int   t_maxseg;        /* maximum segment size */
    unsigned int   t_maxopd;        /* mss plus options */
    int     t_force;                /* 1 if forcing out a byte */
    unsigned int   t_flags;
#define TF_ACKNOW       0x0001      /* ack peer immediately */
#define TF_DELACK       0x0002      /* ack, but try to delay it */
#define TF_NODELAY      0x0004      /* don't delay packets to coalesce */
#define TF_NOOPT        0x0008      /* don't use tcp options */
#define TF_SENTFIN      0x0010      /* have sent FIN */
#define TF_REQ_SCALE    0x0020      /* have/will request window scaling */
#define TF_RCVD_SCALE   0x0040      /* other side has requested scaling */
#define TF_REQ_TSTMP    0x0080      /* have/will request timestamps */
#define TF_RCVD_TSTMP   0x0100      /* a timestamp was received in SYN */
#define TF_SACK_PERMIT  0x0200      /* other side said I could SACK */
#define TF_NEEDSYN      0x0400      /* send SYN (implicit state) */
#define TF_NEEDFIN      0x0800      /* send FIN (implicit state) */
#define TF_NOPUSH       0x1000      /* don't push */
#define TF_REQ_CC       0x2000      /* have/will request CC */
#define TF_RCVD_CC      0x4000      /* a CC was received in SYN */
#define TF_SENDCCNEW    0x8000      /* send CCnew instead of CC in SYN */

    struct  tcpiphdr *t_template;   /* skeletal packet for transmit */
    struct  inpcb *t_inpcb;         /* back pointer to internet pcb */
/*
 * The following fields are used as in the protocol specification.
 * See RFC793, Dec. 1981, page 21.
 */
/* send sequence variables */
    tcp_seq snd_una;                /* send unacknowledged */
    tcp_seq snd_nxt;                /* send next */
    tcp_seq snd_up;                 /* send urgent pointer */
    tcp_seq snd_wl1;                /* window update seg seq number */
    tcp_seq snd_wl2;                /* window update seg ack number */
    tcp_seq iss;                    /* initial send sequence number */
    unsigned long  snd_wnd;         /* send window */
/* receive sequence variables */
    unsigned long  rcv_wnd;         /* receive window */
    tcp_seq rcv_nxt;                /* receive next */
    tcp_seq rcv_up;                 /* receive urgent pointer */
    tcp_seq irs;                    /* initial receive sequence number */
/*
 * Additional variables for this implementation.
 */
/* receive variables */
    tcp_seq rcv_adv;                /* advertised window */
/* retransmit variables */
    tcp_seq snd_max;                /* highest sequence number sent;
                                     * used to recognize retransmits
                                     */
/* congestion control (for slow start, source quench, retransmit after loss) */
    unsigned long  snd_cwnd;        /* congestion-controlled window */
    unsigned long  snd_ssthresh;    /* snd_cwnd size threshold for
                                     * for slow start exponential to
                                     * linear switch
                                     */
/*
 * transmit timing stuff.  See below for scale of srtt and rttvar.
 * "Variance" is actually smoothed difference.
 */
    unsigned int   t_idle;          /* inactivity time */
    int t_rtt;                      /* round trip time */
    tcp_seq t_rtseq;                /* sequence number being timed */
    int t_srtt;                     /* smoothed round-trip time */
    int t_rttvar;                   /* variance in round-trip time */
    unsigned int   t_rttmin;        /* minimum rtt allowed */
    unsigned long  max_sndwnd;      /* largest window peer has offered */

/* out-of-band data */
    char    t_oobflags;             /* have some */
    char    t_iobc;                 /* input character */
#define TCPOOB_HAVEDATA 0x01
#define TCPOOB_HADDATA  0x02
    int t_softerror;                /* possible error not yet reported */

/* RFC 1323 variables */
    unsigned char  snd_scale;       /* window scaling for send window */
    unsigned char  rcv_scale;       /* window scaling for recv window */
    unsigned char  request_r_scale; /* pending window scaling */
    unsigned char  requested_s_scale;
    unsigned long  ts_recent;       /* timestamp echo data */
    unsigned long  ts_recent_age;   /* when last updated */
    tcp_seq last_ack_sent;
    unsigned long  t_duration;      /* connection duration */

/* TUBA stuff */
     char * t_tuba_pcb;             /* next level down pcb for TCP over z */
/* More RTT stuff */
    unsigned long  t_rttupdated;    /* number of times rtt sampled */
};

/*
 * Structure to hold TCP options that are only used during segment
 * processing (in tcp_input), but not held in the tcpcb.
 * It's basically used to reduce the number of parameters
 * to tcp_dooptions.
 */
struct tcpopt {
    unsigned long  to_flag;        /* which options are present */
#define TOF_TS      0x0001         /* timestamp */
#define TOF_CC      0x0002         /* CC and CCnew are exclusive */
#define TOF_CCNEW   0x0004
#define TOF_CCECHO  0x0008
    unsigned long  to_tsval;
    unsigned long  to_tsecr;
};

#define intotcpcb(ip)   ((struct tcpcb *)(ip)->inp_ppcb)

/*
 * The smoothed round-trip time and estimated variance
 * are stored as fixed point numbers scaled by the values below.
 * For convenience, these scales are also used in smoothing the average
 * (smoothed = (1/scale)sample + ((scale-1)/scale)smoothed).
 * With these scales, srtt has 3 bits to the right of the binary point,
 * and thus an "ALPHA" of 0.875.  rttvar has 2 bits to the right of the
 * binary point, and is smoothed with an ALPHA of 0.75.
 */
#define TCP_RTT_SCALE       32  /* multiplier for srtt; 3 bits frac. */
#define TCP_RTT_SHIFT       5   /* shift for srtt; 3 bits frac. */
#define TCP_RTTVAR_SCALE    16  /* multiplier for rttvar; 2 bits */
#define TCP_RTTVAR_SHIFT    4   /* shift for rttvar; 2 bits */
#define TCP_DELTA_SHIFT     2   /* see tcp_input.c */

/*
 * The initial retransmission should happen at rtt + 4 * rttvar.
 * Because of the way we do the smoothing, srtt and rttvar
 * will each average +1/2 tick of bias.  When we compute
 * the retransmit timer, we want 1/2 tick of rounding and
 * 1 extra tick because of +-1/2 tick uncertainty in the
 * firing of the timer.  The bias will give us exactly the
 * 1.5 tick we need.  But, because the bias is
 * statistical, we have to test that we don't drop below
 * the minimum feasible timer (which is 2 ticks).
 * This version of the macro adapted from a paper by Lawrence
 * Brakmo and Larry Peterson which outlines a problem caused
 * by insufficient precision in the original implementation,
 * which results in inappropriately large RTO values for very
 * fast networks.
 */
#define TCP_REXMTVAL(tp) \
    ((((tp)->t_srtt >> (TCP_RTT_SHIFT - TCP_DELTA_SHIFT))  \
      + (tp)->t_rttvar) >> TCP_DELTA_SHIFT)

/* Statistics.
 * Many of these should be kept per connection,
 * but that's inconvenient at the moment.
 */
struct  tcpstat {
    unsigned long  tcps_connattempt;     /* connections initiated */
    unsigned long  tcps_accepts;         /* connections accepted */
    unsigned long  tcps_connects;        /* connections established */
    unsigned long  tcps_drops;           /* connections dropped */
    unsigned long  tcps_conndrops;       /* embryonic connections dropped */
    unsigned long  tcps_closed;          /* conn. closed (includes drops) */
    unsigned long  tcps_segstimed;       /* segs where we tried to get rtt */
    unsigned long  tcps_rttupdated;      /* times we succeeded */
    unsigned long  tcps_delack;          /* delayed acks sent */
    unsigned long  tcps_timeoutdrop;     /* conn. dropped in rxmt timeout */
    unsigned long  tcps_rexmttimeo;      /* retransmit timeouts */
    unsigned long  tcps_persisttimeo;    /* persist timeouts */
    unsigned long  tcps_keeptimeo;       /* keepalive timeouts */
    unsigned long  tcps_keepprobe;       /* keepalive probes sent */
    unsigned long  tcps_keepdrops;       /* connections dropped in keepalive */
 
    unsigned long  tcps_sndtotal;        /* total packets sent */
    unsigned long  tcps_sndpack;         /* data packets sent */
    unsigned long  tcps_sndbyte;         /* data bytes sent */
    unsigned long  tcps_sndrexmitpack;   /* data packets retransmitted */
    unsigned long  tcps_sndrexmitbyte;   /* data bytes retransmitted */ 
    unsigned long  tcps_sndacks;         /* ack-only packets sent */
    unsigned long  tcps_sndprobe;        /* window probes sent */
    unsigned long  tcps_sndurg;          /* packets sent with URG only */
    unsigned long  tcps_sndwinup;        /* window update-only packets sent */
    unsigned long  tcps_sndctrl;         /* control (SYN|FIN|RST) packets sent*/
 
    unsigned long  tcps_rcvtotal;        /* total packets received */
    unsigned long  tcps_rcvpack;         /* packets received in sequence */
    unsigned long  tcps_rcvbyte;         /* bytes received in sequence */
    unsigned long  tcps_rcvbadsum;       /* packets received with ccksum errs */
    unsigned long  tcps_rcvbadoff;       /* packets received with bad offset */
    unsigned long  tcps_rcvshort;        /* packets received too short */
    unsigned long  tcps_rcvctrl;         /* control packets received */
    unsigned long  tcps_rcvduppack;      /* duplicate-only packets received */
    unsigned long  tcps_rcvdupbyte;      /* duplicate-only bytes received */
    unsigned long  tcps_rcvpartduppack;  /* packets with some duplicate data */
    unsigned long  tcps_rcvpartdupbyte;  /* dup. bytes in part-dup. packets */
    unsigned long  tcps_rcvoopack;       /* out-of-order packets received */
    unsigned long  tcps_rcvoobyte;       /* out-of-order bytes received */
    unsigned long  tcps_rcvpackafterwin; /* packets with data after window */
    unsigned long  tcps_rcvbyteafterwin; /* bytes rcvd after window */
    unsigned long  tcps_rcvafterclose;   /* packets rcvd after "close" */
    unsigned long  tcps_rcvwinprobe;     /* rcvd window probe packets */
    unsigned long  tcps_rcvdupack;       /* rcvd duplicate acks */
    unsigned long  tcps_rcvackpack;      /* rcvd in sequence ack packets */
    unsigned long  tcps_rcvackbyte;      /* bytes acked by rcvd acks */
    unsigned long  tcps_rcvacktoomuch;   /* rcvd acks for unsent data */
    unsigned long  tcps_rcvwinupd;       /* rcvd window update packets */
    unsigned long  tcps_pawsdrop;        /* segments dropped due to PAWS */
    unsigned long  tcps_predack;         /* times hdr predict ok for acks */
    unsigned long  tcps_preddat;         /* times hdr predict ok for data pkts*/
    unsigned long  tcps_persistdrop;     /* timeout in persist state */
    unsigned long  tcps_badsyn;          /* bogus SYN, e.g. premature ACK */

};

#endif /* _TCP_VAR_H_ */

