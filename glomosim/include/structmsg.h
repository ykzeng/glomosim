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
 * $Id: structmsg.h,v 1.37 2001/04/14 03:37:14 jmartin Exp $
 *
 * Message Type Enumerations and API declarations between layers.
 */

#ifndef _STRUCTMSG_H_
#define _STRUCTMSG_H_

#include "main.h"
#include "application.h"
#include "network.h"

/*
 * Event/message types exchanged in the simulation.
 */
enum {
    /* Special message types used for internal design. */
    MSG_SPECIAL_Broadcast,
    MSG_SPECIAL_Timer,

    /* Message Types for Channel layer */
    MSG_CHANNEL_FromChannel,
    MSG_CHANNEL_FromRadio,

    /* Message Types for Radio layer */
    MSG_RADIO_FromChannelBegin,     
    MSG_RADIO_FromChannelEnd,
    MSG_RADIO_FromMac,
    MSG_RADIO_StartPropagation,
    MSG_RADIO_SwitchToIdle,
    MSG_RADIO_CheckChannelStatus,    

    /* Message Types for MAC layer */
    MSG_MAC_FromRadio,             /* 10 */
    MSG_MAC_FromNetwork,
    MSG_MAC_ReportChannelStatus,
    MSG_MAC_TransmissionFinished,
    MSG_MAC_TimerExpired,
    MSG_MAC_SlotFront,
    MSG_MAC_WiredToWired,

    /* Message Types for Network layer */
    MSG_NETWORK_FromApp,           /* 15 */
    MSG_NETWORK_FromMac,
    MSG_NETWORK_FromTransportOrRoutingProtocol,
    MSG_NETWORK_DelayedSendToMac, 
    MSG_NETWORK_RTBroadcastAlarm,
    MSG_NETWORK_CheckTimeoutAlarm,   /* 20 */
    MSG_NETWORK_TriggerUpdateAlarm,  
    MSG_NETWORK_InitiateSend,
    MSG_NETWORK_FlushTables,
    MSG_NETWORK_CheckAcked,
    MSG_NETWORK_CheckReplied,       /* 25 */

    MSG_NETWORK_JoinGroup,
    MSG_NETWORK_LeaveGroup,
    MSG_NETWORK_SendData,                       /* 30 */
    MSG_NETWORK_SendRequest,
    MSG_NETWORK_SendReply,
    MSG_NETWORK_CheckFg,

    MSG_NETWORK_Retx,
    
    MSG_NETWORK_PacketDropped,      
    MSG_NETWORK_CheckRouteTimeout,
    MSG_NETWORK_CheckNeighborTimeout,

    /* Messages Types special for IP */
    MSG_NETWORK_BuffTimerExpired,   

    /* Message Types for Transport layer */
    MSG_TRANSPORT_FromNetwork,
    MSG_TRANSPORT_FromAppListen,
    MSG_TRANSPORT_FromAppOpen,      /* 30 */
    MSG_TRANSPORT_FromAppSend,      
    MSG_TRANSPORT_FromAppClose,     
    MSG_TRANSPORT_TCP_TIMER_FAST,
    MSG_TRANSPORT_TCP_TIMER_SLOW,
    MSG_TRANSPORT_Tcp_CheckTcpOutputTimer,

    /* Messages Types for Transport layer with NS TCP */
    MSG_TCP_SetupConnection, 
        
    /* Message Types for Appliation layer */
    MSG_APP_FromTransListenResult,
    MSG_APP_FromTransOpenResult,    
    MSG_APP_FromTransDataSent,      
    MSG_APP_FromTransDataReceived,   
    MSG_APP_FromTransCloseResult,
    MSG_APP_TimerExpired,
 
    /* Messages Types for Application layer with UDP */
    MSG_APP_FromTransport,

    /* Messages Types for Application layer with NS TCP */
    MSG_APP_NextPkt,
    MSG_APP_SetupConnection,
    
    /* Messages Type for Application layer directly on top of IP */  
    MSG_APP_FromNetwork,

    /* Message Types for Promiscuous Routing Algorithms */
    MSG_ROUTE_FromTransport,
    MSG_ROUTE_FromNetwork,

    /* Message Types for Routing - OSPF */
    MSG_OspfScheduleHello,
    MSG_OspfInitiateHello,
    MSG_OspfScheduleLSA,
    MSG_OspfOriginateLSA,
    MSG_OspfRetransLSA,
    MSG_OspfInactivityNeighFired,

    /* Message types for rumor */
    MSG_RUMOR_Timeout,
    MSG_RUMOR_ReconInitiate,
    MSG_RUMOR_FileReference,
    MSG_APP_FromRumor,
    MSG_APP_FromRumorKillOut,
    MSG_APP_FromRumorKillIn,

    /* Message types for routing - Bellmanford. */
    MSG_APP_RTBroadcastAlarm,
    MSG_APP_CheckTimeoutAlarm,
    MSG_APP_TriggerUpdateAlarm,

    /* Message types for routing - Fisheye */
    MSG_APP_FisheyeNeighborTimeout,
    MSG_APP_FisheyeIntraUpdate,
    MSG_APP_FisheyeInterUpdate,

    /* Message Types for Application Layer CBR */
    MSG_APP_CBR_NEXT_PKT,

    /* Message Types for Setting Timers */
    MSG_TRANSPORT_TCP_TIMER, 
 
    /*
     * Any other message types which have to be added should be added before
     * MSG_DEFAULT. Otherwise the program will not work correctly.
     */
    MSG_DEFAULT
};



/*
 * FUNCTION    GLOMO_*Init
 * PURPOSE     Initialization function for various layers.

 * Parameters:
 *     node:      node being initialized.
 *     nodeInput: structure containing contents of input file
 */
void GLOMO_ChannelInit(GlomoNode *node, const GlomoNodeInput *nodeInput);
void GLOMO_RadioInit(GlomoNode *node, const GlomoNodeInput *nodeInput);
void GLOMO_MacInit(GlomoNode *node, const GlomoNodeInput *nodeInput);
void GLOMO_NetworkPreInit(GlomoNode *node, const GlomoNodeInput *nodeInput);
void GLOMO_NetworkInit(GlomoNode *node, const GlomoNodeInput *nodeInput);
void GLOMO_TransportInit(GlomoNode *node, const GlomoNodeInput *nodeInput);
void GLOMO_AppInit(GlomoNode *node, const GlomoNodeInput *nodeInput);


/*
 * FUNCTION    GLOMO_*Finalize
 * PURPOSE     Called at the end of simulation to collect the results of 
 *             the simulation of the various layers.
 *
 * Parameter:
 *     node:     node for which results are to be collected.
 */
void GLOMO_ChannelFinalize(GlomoNode *node);
void GLOMO_RadioFinalize(GlomoNode *node);
void GLOMO_MacFinalize(GlomoNode *node);
void GLOMO_NetworkFinalize(GlomoNode *node);
void GLOMO_TransportFinalize(GlomoNode *node);
void GLOMO_AppFinalize(GlomoNode *node);


/*
 * FUNCTION    GLOMO_*Layer
 * PURPOSE     Models the behaviour of the various layers on receiving 
 *             message enclosed in msgHdr.
 *
 * Parameters:
 *     node:     node which received the message
 *     msgHdr:   message received by the layer
 */
void GLOMO_ChannelLayer(GlomoNode *node, Message *msg);
void GLOMO_RadioLayer(GlomoNode *node, Message *msg);
void GLOMO_MacLayer(GlomoNode *node, Message *msg);
void GLOMO_NetworkLayer(GlomoNode *node, Message *msg);
void GLOMO_TransportLayer(GlomoNode *node, Message *msg);
void GLOMO_AppLayer(GlomoNode *node, Message *msg);


//typedef struct pkt_net_to_mac {
//    NODE_ADDR destAddr;      /* next hop */
//    NetworkQueueingPriorityType priority;
//} PacketNetworkToMac;

//typedef struct pkt_mac_to_net {
//    NODE_ADDR sourceAddr;    /* previous hop */
//    NetworkQueueingPriorityType priority;
//} PacketMacToNetwork;


typedef struct pkt_net_to_app {
    NODE_ADDR sourceAddr;    /* previous hop */
} PacketNetworkToApp;

typedef struct {
    NODE_ADDR sourceAddr;
    NODE_ADDR destinationAddr;
    NetworkQueueingPriorityType priority;
} NetworkToTransportInfo;

typedef struct pkt_nstcp_to_network {
    NODE_ADDR sourceId;
    NODE_ADDR destId;
    long  packetSize;
    long  agenttype;
    short sourcePort;
    short destPort;
    
    NetworkQueueingPriorityType priority;
    void *pkt;
} PacketTransportNetwork;

typedef struct tcp_timer__ {
    int timerId;
    int timerType;
    int connectionId;
} TcpTimerPacket;

typedef struct app_to_udp_send {
    NODE_ADDR sourceAddr;
    short sourcePort;
    NODE_ADDR destAddr;
    short destPort;
    NetworkQueueingPriorityType priority;
} AppToUdpSend;

typedef struct udp_to_app_send {
    NODE_ADDR sourceAddr;
    short sourcePort;
    NODE_ADDR destAddr;
    short destPort;
} UdpToAppRecv;

/*
 * Report the result of application's listen request.
 */
typedef struct transport_to_app_listen_result {
    NODE_ADDR localAddr;
    short localPort;
    int connectionId;     /* -1 - listen failed, >=0 - connection id */
} TransportToAppListenResult;

/*
 * Report the result of opening a connection.
 */
typedef struct transport_to_app_open_result {
    int type;             /* 1 - active open, 2 - passive open */
    NODE_ADDR localAddr;
    short localPort;
    NODE_ADDR remoteAddr;
    short remotePort; 
    int connectionId;     /* -1 - open failed, >=0 - connection id */

    long uniqueId;
} TransportToAppOpenResult;

/*
 * Report the result of sending application data.
 */
typedef struct transport_to_app_data_sent {
    int connectionId;
    long length;               /* length of data sent */
} TransportToAppDataSent;

/*
 * Deliver data to application.
 */
typedef struct transport_to_app_data_received {
    int connectionId;
} TransportToAppDataReceived;

/*
 * Report the result of closing a connection.
 */ 
typedef struct tcp_to_app_close_result {
    int type;                /* 1 - active close, 2 - passive close */
    int connectionId;
} TransportToAppCloseResult;

/*
 * Application announces willingness to accept connections on given port.
 */
typedef struct app_to_tcp_listen {
    APP_TYPE appType;
    NODE_ADDR localAddr;
    short localPort;
    NetworkQueueingPriorityType priority;
} AppToTcpListen;

/*
 * Application attempts to establish a connection.
 */
typedef struct app_to_tcp_open{
    APP_TYPE appType;
    NODE_ADDR localAddr; 
    short localPort;
    NODE_ADDR remoteAddr;
    short remotePort;

    long uniqueId;
    NetworkQueueingPriorityType priority;
} AppToTcpOpen;

/*
 * Application wants to send some data over the connection.
 */
typedef struct app_to_tcp_send{
    int connectionId;
} AppToTcpSend;

/*
 * Application wants to release the connection.
 */
typedef struct app_to_tcp_close{
    int connectionId;
} AppToTcpClose;     

/* Application sets up connection at the local end
 * Needed for NS TCP to fake connection setup
 */
typedef struct app_to_tcp_conn_setup {
    NODE_ADDR localAddr;
    int       localPort;
    NODE_ADDR remoteAddr;
    int       remotePort;
    int       connectionId;
    int       agentType;
} AppToTcpConnSetup;

#endif /* _STRUCTMSG_H_ */

