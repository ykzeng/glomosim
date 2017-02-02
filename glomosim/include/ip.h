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
 * $Id: ip.h,v 1.16 2000/02/23 00:17:44 jmartin Exp $
 *
 * Ported from FreeBSD 2.2.2. 
 * This file contains ip header structure definition, etc.
 */

#ifndef _IP_H_
#define _IP_H_

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
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)ip.h    8.2 (Berkeley) 6/1/94
 *  $Id: ip.h,v 1.16 2000/02/23 00:17:44 jmartin Exp $
 */

/*
 * Definitions for internet protocol version 4.
 * Per RFC 791, September 1981.
 */

#define IP_MIN_MULTICAST_ADDRESS 0xE0000000

#define IPVERSION       4

/*
 * Structure of an internet header, naked of options.
 *
 * We declare ip_len and ip_off to be short, rather than unsigned short
 * pragmatically since otherwise unsigned comparisons can result
 * against negative integers quite easily, and fail in subtle ways.
 */

/****
 ****   *** Non-Standard IP Protocol Hack ***
 ****   New IP Version "13" (Heh).  IP header length is extended into
 ****   the version field to give it an extra bit allowing for 
 ****   up to 124 byte headers for long source routes.   Headers of size
 ****   64-124 are designated by a "1" in low bit of the official IP
 ****   version field making long header packets version "5" or if the
 ****   top bit is also set version "13" (version # not "simulated").
 ****/

typedef struct ip {
    unsigned int ip_v:3,        /* version */
                 ip_hl:5,       /* header length */
                 ip_tos:8,      /* type of service */
                 ip_len:16;     /* total length */
    
    unsigned int ip_id:16,
                 ip_reserved:1,
                 ip_dont_fragment:1,
                 ip_more_fragments:1,
                 ip_fragment_offset:13;
                 
    unsigned char  ip_ttl;      /* time to live */
    unsigned char  ip_p;        /* protocol */
    unsigned short ip_sum;      /* checksum */
    long    ip_src,ip_dst;      /* source and dest address */
    
} IpHeaderType;


#define IP_MAXPACKET    65535       /* maximum packet size */

#define IP_MIN_HEADER_SIZE 20
#define IP_MAX_HEADER_SIZE 124

#define IP_SOURCE_ROUTE_OPTION_PADDING 1


#define SetIpHeaderSize(IpHeader, Size) \
   IpHeader->ip_hl = (Size) / 4; \
   assert(((Size) % 4 == 0) && \
          (Size >= IP_MIN_HEADER_SIZE) && (Size <= IP_MAX_HEADER_SIZE));

#define IpHeaderSize(IpHeader) ((IpHeader)->ip_hl * 4)


#define FragmentOffset(ipHeader) (((ipHeader)->ip_fragment_offset) * 8)
#define SetFragmentOffset(ipHeader, offset) \
   assert(((offset) % 8 == 0) && ((offset) < IP_MAXPACKET)); \
   (ipHeader)->ip_fragment_offset = ((offset)/8);   



//
// FUNCTION    ExtractIpSourceAndRecordedRoute() 
// PURPOSE     Retrieves a copy of the source and recorded route from
//             the options field in the header.
// 
//   msg - The message with an IP header with a source/recorded route.
//   RouteAddress - An array for the returned addresses.
//   NumAddresses - The returned size of this array.
//   RouteAddressIndex - The index of the first address of the source
//                       route, before this index is the recorded route.


void ExtractIpSourceAndRecordedRoute(
   Message* msg, 
   NODE_ADDR RouteAddresses[],
   int*  NumAddresses,
   int*  RouteAddressIndex);


/*
 * Definitions for IP type of service (ip_tos)
 */

#define IPTOS_LOWDELAY      0x10
#define IPTOS_THROUGHPUT    0x08
#define IPTOS_RELIABILITY   0x04
#define IPTOS_MINCOST       0x02

/*
 * Definitions for IP precedence (also in ip_tos) (hopefully unused)
 */
#define IPTOS_PREC_NETCONTROL       0xe0
#define IPTOS_PREC_INTERNETCONTROL  0xc0
#define IPTOS_PREC_CRITIC_ECP       0xa0
#define IPTOS_PREC_FLASHOVERRIDE    0x80
#define IPTOS_PREC_FLASH            0x60
#define IPTOS_PREC_IMMEDIATE        0x40
#define IPTOS_PREC_PRIORITY         0x20
#define IPTOS_PREC_ROUTINE          0x00

/*
 * Definitions for options.
 */
#define IPOPT_COPIED(o)     ((o)&0x80)
#define IPOPT_CLASS(o)      ((o)&0x60)
#define IPOPT_NUMBER(o)     ((o)&0x1f)

#define IPOPT_CONTROL       0x00
#define IPOPT_RESERVED1     0x20
#define IPOPT_DEBMEAS       0x40
#define IPOPT_RESERVED2     0x60

#define IPOPT_EOL       0       /* end of option list */
#define IPOPT_NOP       1       /* no operation */

#define IPOPT_RR        7       /* record packet route */
#define IPOPT_TS        68      /* timestamp */
#define IPOPT_SECURITY  130     /* provide s,c,h,tcc */
#define IPOPT_LSRR      131     /* loose source route */
#define IPOPT_SATID     136     /* satnet id */
#define IPOPT_SSRR      137     /* strict source route */

/*
 * Offsets to fields in options other than EOL and NOP.
 */
#define IPOPT_OPTVAL        0       /* option ID */
#define IPOPT_OLEN          1       /* option length */
#define IPOPT_OFFSET        2       /* offset within option */
#define IPOPT_MINOFF        4       /* min value of above */

/*
 * Time stamp option structure.
 */
struct  ip_timestamp {
    unsigned int ipt_code:8,       /* IPOPT_TS */
                 ipt_len:8,        /* size of structure (variable) */
                 ipt_ptr:8,        /* index of current entry */
                 ipt_flg:4,        /* flags, see below */
                 ipt_oflw:4;       /* overflow counter */
    union ipt_timestamp {
        unsigned long  ipt_time[1];
        struct  ipt_ta {
            NODE_ADDR ipt_addr;
            unsigned long ipt_time;
        } ipt_ta[1];
    } ipt_timestamp;
};

/* flag bits for ipt_flg */
#define IPOPT_TS_TSONLY     0       /* timestamps only */
#define IPOPT_TS_TSANDADDR  1       /* timestamps and addresses */
#define IPOPT_TS_PRESPEC    3       /* specified modules only */
 
/* bits for security (not byte swapped) */
#define IPOPT_SECUR_UNCLASS 0x0000
#define IPOPT_SECUR_CONFID  0xf135
#define IPOPT_SECUR_EFTO    0x789a
#define IPOPT_SECUR_MMMM    0xbc4d
#define IPOPT_SECUR_RESTR   0xaf13
#define IPOPT_SECUR_SECRET  0xd788
#define IPOPT_SECUR_TOPSECRET   0x6bc5

/*
 * Internet implementation parameters.
 */
#define MAXTTL      255     /* maximum time to live (seconds) */
#define IPDEFTTL    64      /* default ttl, from RFC 1340 */
#define IPFRAGTTL   60      /* time to live for frags, slowhz */
#define IPTTLDEC    1       /* subtracted when forwarding */
#define IPDEFTOS    0x10    /* default TOS */
 
#define IP_MSS      576     /* default maximum segment size */

struct ip_options {         /* options header */
    unsigned char code;
    unsigned char len;
    unsigned char ptr;
};


typedef struct ip_options IpOptionsHeaderType;


//
// FindAnIpOptionField : Searches the IP header for the 
// option field that matches the "OptionCode" parameter and
// returns a pointer to that option field.
//

static
IpOptionsHeaderType* FindAnIpOptionField(
   const IpHeaderType* ipHeader, 
   const int OptionCode)
{
   IpOptionsHeaderType* ipOption;

   if (IpHeaderSize(ipHeader) == sizeof(IpHeaderType)) {
      return NULL;
   }
   
   ipOption = (IpOptionsHeaderType*)((char*)ipHeader + sizeof(IpHeaderType));

   while (ipOption->code != OptionCode) {
      ipOption = 
         (IpOptionsHeaderType*)((char*)ipOption + ipOption->len);
      if (((char*)ipOption) >= ((char*)ipHeader + IpHeaderSize(ipHeader))) {
         ipOption = NULL;
         break;
      }/*if*/
   }/*while*/
   return ipOption;
}



#endif /* _IP_H_ */

