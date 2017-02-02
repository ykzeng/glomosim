/*
 * PARSEC is COPYRIGHTED software.  Release 1.1 of PARSEC is available 
 * at no cost to educational users only.
 *
 * Commercial use of this software requires a separate license.  No cost,
 * evaluation licenses are available for such purposes; please contact
 * info@scalable-networks.com
 *
 * By obtaining copies of this and any other files that comprise PARSEC 1.1,
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

-------------------------------------------------------------------------------
GloMoSim is a scalable wireless and wired network simulator
that has been built on top of PARSEC simulation
environment. When refrencing this software, please refer to
the following paper:

Lokesh Bajaj, Mineo Takai, Rajat Ahuja, Ken Tang, Rajive
Bagrodia, and Mario Gerla, "GloMoSim: A Scalable Network
Simulation Environment," Technical Report, UCLA Computer
Science Department - 990027.

This paper can be found in ./glomosim/doc/glomo-tech.ps. For
more references to GloMoSim/PARSEC, check the following web
page:

http://pcl.cs.ucla.edu/papers/


1. Contents
2. Installation requirements
3. PARSEC Installation
4. PARSEC environment variables and compiler options
5. GloMoSim Installation
6. List of models included in this version

-------------------------------------------------------------------------------

1. Contents
./LICENCE.txt: License agreement
./README.txt : This file
./parsec/    : PARSEC compiler and runtime libraries
./glomosim/  : GloMoSim

2. Installation requirements
PARSEC/GloMoSim requires a C compiler to run. While it works
with most C/C++ compilers on many common platforms, we only
include pre-compiled PARSEC runtime libraries for the
following operating systems:
./parsec/aix/                : IBM AIX with xlc compiler
./parsec/windowsnt-4.0-vc6/  : MS Windows NT or 2000
                               with Visual C++ ver. 6.0
./parsec/freebsd-3.3/        : FreeBSD 3.3
./parsec/redhat-6.0/         : Red Hat 6.0 or higher
./parsec/solaris-2.5.1/      : Sun SPARC Solaris 2.5.1 or higher
                               with gcc/g++
./parsec/solaris-2.5.1-cc/   : Sun SPARC Solaris 2.5.1 or higher
                               with Sun C compiler
./parsec/x86-solaris-2.5.1/  : Sun X86 Solaris 2.5.1 or higher
                               with gcc/g++
./parsec/irix-6.4/           : SGI IRIX 6.4 or higher
                               with gcc/g++
Please contact us if you need PARSEC on other platforms.

3. PARSEC Installation
(For UNIX based machines)
If you have permission to create /usr/local/parsec, the
installation is easy; just copy the whole subdirectory with
the name of target platform under /usr/local/parsec. If you
do not have permission to create a directory under
/usr/local, create a directory anywhere you like, and set
the designated directory to an environment variable
"PCC_DIRECTORY." For instance, you can set the variable by
typing "setenv PCC_DIRECTORY /home/foo/parsec" if you are
using (t)csh.
(For Windows)
The default path is c:\parsec. You can change the directory
in the same way as UNIX based machines.

4. PARSEC environment variables and compiler options
pcc checks the following environment variables when
executed:
  PCC_DIRECTORY      : Directory that pcc looks up
  PCC_CC             : C compiler used for preprocessing and compiling
  PCC_LINKER         : Linker used for linking
  PCC_PP_OPTIONS     : Options for preprocessing
  PCC_CC_OPTIONS     : Options for compiling
  PCC_LINKER_OPTIONS : Options for linking
These variables do not usually need to change. PARSEC also
has the command line options each of which corresponds to
the environment variable above:
  -pcc_directory
  -pcc_cc
  -pcc_linker
  -pcc_pp_optoins
  -pcc_cc_options
  -pcc_linker_options
These command line options can override the environment
variables and are useful when changing options temporarily.
There are other command line options besides those. You can
see brief descriptions of those options by typing "pcc -help"
For detailed descriptions, you can read the manual for
PARSEC on the web:
    http://pcl.cs.ucla.edu/projects/parsec

5. GloMoSim Installation
Once PARSEC is installed and pcc is recognizable from the
command line, go to ./glomosim/main and type "make" for UNIX
based systems and "makent" for Windows based systems. When
the compilation is successful, you will see the GloMoSim
executable "glomosim" under ./glomosim/bin. To check if
GloMoSim is installed correctly, run "./glomosim config.in"
and you will get an output file "glomo.stat." Compare
"glomo.stat" with "glomo.stat.sample" under the same
directory to ensure that the executable generates the
expected output. The sample scenario file "config.in"
includes descriptions how to set up the network and
protocols to simulate. You will also find "radiorange"
program under the same directory, which shows the radio
range under no interference condition.

6. List of models included in this version

Mobility Models:
- Random waypoint
Each network node with the random waypoint mobility moves
straight towards a randomly determined destination. Once the
node arrives at the destination, it stays for a specified
pause time, and starts moving towards another destination.

- Random drunken
Each network node with the random drunken mobility chooses
a direction out of four randomly, and moves for a certain
time towards it. This model is included as a template to
develop a new mobility model and is not for use to configure
realistic scenarios.

- Trace based
This model reads in user provided trace of mobility, and
moves network nodes as specified.

Propagation Models:
- Free space
- Two ray
The implementation of these two propagation models is based
on the description in T. S. Rappaport "Wireless
Communications: Principles & Practice."

Radio (noise calculation) Models:
- Accumulated noise
Radio with accumulated noise calculates the noise level as
the sum of the thermal noise and the power of all the
signals on the same channel. It works with both SNR bounded
and BER based packet reception models.

- No noise
Radio with no noise does not have a notion of noise, but
regards a single co-existing signal with the signal being
received as the noise in order to calculate SNR. This model
emulates the current ns-2 radio model (2.1b6) and should
yield the same results for the same scenario when the
necessary parameters are set appropriately. This model
only works with the SNR bounded packet reception model.

Packet Reception Models:
- SNR bounded
SNR bounded packet reception model determines sucessful
packet receptions by comparing the yielded SNR with the
threshold set in the configuration. This comparison is
performed every time the noise level changes. Once the
signal being received is determined to be failed, it will
not be forwarded to the upper layers.

- BER based with BPSK/QPSK modulation
BER based packet reception model looks up a user specified
table to retrieve BER for the current level of noise, and
determines successful packet reception
probablistically. As BER for a signal can constantly change
with the noise power, the evaluation of signal is performed
every time SNR changes.

MAC Models:
- CSMA (Carrier Sense Multiple Access)
- MACA (Multiple Access with Collision Avoidance)

- 802.11
This model is only for DCF (Distributed Coordination
Function) of the IEEE 802.11 standard.

- TSMA (Time-Spread Multiple-Access)
This model is a contribution from University of Texas,
Dallas. The implementation of this model is based on "Making
Transmission Schedules Immune to Topology Changes in
Multi-hop Packet Radio Networks", I. Chlamtac and A. Farago,
IEEE/ACM Transactions on Networking, vol. 2, no. 1,
Feb. 1994.

- Wiredlink
This model simulates a simple wired link between two network
nodes. The data rate, propagation delay and other parameters
of each link are specified by users.

Routing Protocol Models:
- Bellman-Ford

- Fisheye Routing Protocol
The implementation of this protocol is based on "Scalable
Routing Strategies for Ad-hoc Wireless Networks," A. Iwata,
C.-C. Chiang, G. Pei, M. Gerla, and T.-W. Chen, IEEE Journal
on Selected Areas in Communications, Special Issue on Ad-Hoc
Networks, Aug. 1999.

- WRP
This implementation of WRP is based upon the pseudocode in:
S. Murthy and J.J. Garcia-Luna-Aceves, "An Efficient Routing
Protocol for Wireless Networks", ACM Mobile Networks and
Applications Journal, Special issue on Routing in Mobile
Communication Networks, 1996.

- AODV
The implementation of AODV followed the specification of
AODV Internet Draft (draft-ietf-manet-aodv-03.txt).
 * This implements only unicast functionality of AODV.
 * It assumes the MAC protocol sends a signal to the routing
 protocol when it detects link breaks. MAC protocols such as
 IEEE 802.11 and MACAW has this functionality. In IEEE
 802.11, when no CTS is received after RTS, and no ACK is
 received after retransmissions of unicasted packet, it
 sends the signal to the routing protocol.
 * If users want to use MAC protocols other than IEEE
 802.11, they must implement schemes to detect link
 breaks. A way to do this is, for example, using HELLO
 packets, as specified in AODV documents.
 * No Precursors (Implemented other mechanism so that the
 protocol can still function the same as when precursors are
 used.
 * Unsolicited RREPs are broadcasted and forwarded only if
 the node is part of the broken route and not the source of
 that route.
 * If more than one route uses the broken link, send RREP
 multiple times (this should be fixed based on new
 specification by C. Perkins, E. Royer, and S. Das).
 * Rev route of RREQ overwrites the one in the route table
 * May need slight modifications when
 draft-ietf-manet-aodv-04.txt comes out.

- DSR
The implementation of DSR followed the specification of DSR
Internet Draft (draft-ietf-manet-dsr-03.txt).
 * Assumes the MAC protocol sends a signal to the routing
 protocol when it detects link breaks. MAC protocols such as
 IEEE 802.11 and MACAW has this functionality. In IEEE
 802.11, when no CTS is received after RTS, and no ACK is
 received after retransmissions of unicasted packet, it
 sends the signal to the routing protocol
 * If users want to use MAC protocols other than IEEE
 802.11, they must implement schemes to detect link
 breaks. A way to do this is, for example, using passive
 acknowledgments, as specified in DSR documents.
 * Destination sends Route Replies to ALL Route Requests it
 receives, as was done in CMU's NS2 implementation.
 * Most, but not all, optimization features of DSR are
 implemented. Implemented optimizations are:
   + Promiscuous learning of source routes
   + Discovering shorter routes
   + Rate limiting the route discovery process
   + All nodes process all of the Route Error messages the receive 
     (when the node is the destination of the packet, is the forwarder,
     or overhears the packet promiscuously) 
   + Nonpropagating Route Requests
   + Replying from cache
   + Gratuitous Route Replies
   + Salvaging (for data and Route Errors)
   + Tapping
 Optimizations not implemented are:
   + Preventing Route Reply Storms
   + Path state and flow state mechanisms
   + Piggybacking on Route Discoveries
   + Gratuitous Route Errors

- LAR scheme 1
Implementation of LAR followed the specification of
"Location-Aided Routing (LAR) in Mobile Ad Hoc Networks,"
Y.-B. Ko and N. H. Vaidya, Mobicom'98, October 1998. Other
details followed based on discussions with Mr. Youngbae Ko
of Texas A & M. We assume that underlying MAC protocol sends
a signal when the packet cannot be reached to the next hop
(after retransmissions). MAC protocols such as IEEE 802.11
and MACAW have these functionality. Nodes detect link breaks
by receiving a signal from the IEEE 802.11 MAC Protocol. If
other MAC protocol is used, users need to modify the LAR
code so that it can detect link breaks.

- ODMRP (On-Demand Multicast Routing Protocol)
The implementation of ODMRP followed the latest
specification in the Internet Draft
(draft-ietf-manet-odmrp-02.txt). The mobility prediction
using GPS is not included in this implementation.

Transport Layer Models:
- FreeBSD TCP
- UDP

Application Models:
- CBR (Constant Bit Rate) traffic generator
- HTTP
- TELNET
- FTP
-------------------------------------------------------------------------------
