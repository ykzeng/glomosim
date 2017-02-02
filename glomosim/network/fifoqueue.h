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
 * $Id: fifoqueue.h,v 1.2 2001/04/12 18:28:31 jmartin Exp $
 */
/* FILENAME: fifoqueue.h
 * PURPOSE:  header for file FifoQueue.pc(FIFO queuing utilities)
 */

#ifndef _FIFOQUEUE_H_
#define _FIFOQUEUE_H_

#include "main.h"
#include "structmsg.h"
#include "ipqueue.h"


typedef struct {
   int         maxPackets;
   Message**   packetArray;
   int         numPackets;
   int         headIndex;
   int         tailIndex;
} FifoPacketQueueType;


typedef struct {
   double QueueWeight;
   int MinThresholdForQueue;
   int MaxThresholdForQueue;
   double MaxPacketMarkingProbability;

   double AverageQueueSize;
   clocktype StartOfQueueIdleTime;
   clocktype TypicalPacketTransmissionTime;
   
   int PacketsSinceLastMarkedPacket;
   
   unsigned short seed[3];
   NODE_ADDR nodeAddress;
} RedInformationType;


typedef struct multi_fifo_packet_queue_struct {
   FifoPacketQueueType fifoqueues[IP_QUEUE_NUM_OF_PRIORITIES]; 
   RedInformationType* RedInformationPtrs[IP_QUEUE_NUM_OF_PRIORITIES];
} MultiFifoPacketQueueType;


void MultiFifoPacketQueue_Insert(
   IpQueuesUnion queue, 
   Message* msg,
   NetworkQueueingPriorityType priority,
   BOOL* QueueIsFull);


void MultiFifoPacketQueue_RetrieveTopAndMaybeDequeue(
   IpQueuesUnion queue,
   BOOL specificPriorityOnly,
   NetworkQueueingPriorityType priority,
   Message** msg,
   NetworkQueueingPriorityType* msgpriority,
   BOOL dequeueTheMessage);


BOOL MultiFifoPacketQueue_IsEmpty(IpQueuesUnion queue);


void MultiFifoPacketQueue_Initialize(
   IpOutputQueueType* queue,
   GlomoNode* node,
   int interfaceId,
   const GlomoNodeInput* nodeInput);

#endif /* _FIFOQUEUE_H_ */


