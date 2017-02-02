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
 * $Id: application.h,v 1.25 2001/02/15 03:11:11 mineo Exp $
 *
 * This file contains definitions common to application layer protocols
 * and application data structure in node structure.
 */

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "nwcommon.h"

#define MAX_APP_DATA_UNIT 2048

typedef enum {
    APP_FTP_SERVER = 21,
    APP_FTP_CLIENT,
    APP_TELNET_SERVER = 23,
    APP_TELNET_CLIENT,
    APP_NSTELNET_CLIENT,
    APP_GEN_FTP_SERVER,
    APP_GEN_FTP_CLIENT,
    APP_CBR_SERVER = 59,
    APP_CBR_CLIENT = 60,
    APP_HTTP_CLIENT,
    APP_HTTP_SERVER,
    /* Rumorsim */
    APP_RUMOR,

    /* Routing Protocols */
    APP_ROUTING_BELLMANFORD = IPPROTO_BELLMANFORD,
    ROUTING_PROTOCOL_FISHEYE = IPPROTO_FISHEYE,
    APP_ROUTING_WRP,
    APP_ROUTING_NS_DSDV,
    APP_ROUTING_STATIC
} APP_TYPE;

/*
 * Protocol specific information.
 */
typedef struct app_info {
    APP_TYPE appType;         /* type of application */
    void *appDetail;          /* statistics of the application */ 
    struct app_info *appNext; /* link to the next app of the node */
} AppInfo;

/*
 * Application data structure in node structure.
 *
 * typedef to GlomoApp in main.h
 */
struct glomo_app_str {
    AppInfo *appPtr;         /* pointer to the list of app info */
    short    nextPortNum;    /* next available port number */
    BOOL     appStats;       /* whether app stat is enabled */
    APP_TYPE routingProtocol;
    BOOL routingStats;
    void *routingVar;
    void* userApplicationData;

    /*
     * Application statistics for the node using TCP.
     */
    long numAppTcpFailure;     /* # of apps terminated due to failure */

    /* Used to determine unique client/server pair. */
    long uniqueId;
    
    /*
     * User specified session parameters.
     */
    clocktype telnetSessTime;/* duration of a telnet session */
};

/*
 * Application timer types. 
 */
typedef enum {
    APP_TIMER_SEND_PKT,      /* for sending a packet */
    APP_TIMER_CLOSE_SESS     /* for closing a session */
} AppTimerType;

/*
 * Timer structure used by applications.
 */
typedef struct app_timer {
    AppTimerType type;        /* timer type */
    int connectionId;         /* which connection this timer is meant for */
    long uniqueId;            /* which cbr session this timer is meant for */
} AppTimer;


/*
 * Data item structure used by cbr.
 */
typedef struct glomo_app_cbr_data
{
    long uniqueId;
    char type;
    long seqNo;
    clocktype txTime;
} GlomoAppCbrData;



/*
 * NAME:        GLOMO_AppInitApplications.
 * PURPOSE:     start applications on nodes according to user's
 *              specification.
 * PARAMETERS:  node - pointer to the node,
 *              nodeInput - configuration information.
 * RETURN:      none.
 */
void
GLOMO_AppInitApplications(GlomoNode *node, const GlomoNodeInput *nodeInput);


//--------------------------------------------------------------------

// GloMoSim User modified functions defined in "user_application.pc".


void AppLayerInitUserApplications(
   GlomoNode *node,
   const GlomoNodeInput *nodeInput,
   void** userApplicationData);
      
void AppLayerHandleUserAppEvent(
   GlomoNode* node, 
   void* userApplicationData,
   Message* msg);

void AppLayerFinalizeUserApps(
   GlomoNode* node,
   void* userApplicationData);


#endif /* _APPLICATION_H_ */

