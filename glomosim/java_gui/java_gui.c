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
 * Glomosim is COPYRIGHTED software.  It is freely available without fee for
 * education, or research, or to non-profit agencies. No cost evaluation
 * licenses are available for commercial users. By obtaining copies of this
 * and other files that comprise GloMoSim, you, the Licensee, agree to abide
 * by the following conditions and understandings with respect to the
 * copyrighted software:
 *
 * 1.Permission to use, copy, and modify this software and its documentation
 *   for education, research, and non-profit purposes is hereby granted to
 *   Licensee, provided that the copyright notice, the original author's names
 *   and unit identification, and this permission notice appear on all such
 *   copies, and that no charge be made for such copies. Any entity desiring
 *   permission to incorporate this software into commercial products or to use
 *   it for commercial purposes should contact: 
 *
 *   Professor Rajive Bagrodia 
 *   University of California, Los Angeles 
 *   Department of Computer Science 
 *   Box 951596 
 *   3532 Boelter Hall 
 *   Los Angeles, CA 90095-1596 
 *   rajive@cs.ucla.edu
 */
#include<stdio.h>
#include "java_gui.h"

enum {
    JGUI_INITIALIZE = 0,
    JGUI_MOVE_NODE = 1,
    JGUI_DRAW_BROADCAST = 2,
    JGUI_DRAW_LINE = 3,
    JGUI_DRAW_THICKLINE = 4,
    JGUI_DRAW_LINK = 5,
    JGUI_ERASE_LINK = 6
};

void JGUI_InitNode (int numGuiNodes, int id, int positionX, int positionY,
                    int txRange, JGUI_COLOR node, JGUI_COLOR connection) { 
    printf("%d %d %d %d %d %d %d %d\n", JGUI_INITIALIZE, numGuiNodes,
            id, positionX, positionY, txRange, node, connection);
}

void JGUI_DrawLink(int srcId, int destId, char *simTime,
                   JGUI_COLOR color) {
    printf("%d %s %d %d %d\n", JGUI_DRAW_LINK, simTime, srcId, destId, color);
}

void JGUI_EraseLink(int srcId, int destId, char *simTime) {
    printf("%d %s %d %d\n", JGUI_ERASE_LINK, simTime, srcId, destId);
}  

void JGUI_DrawBroadcast(int id, char *simTime, JGUI_COLOR color) {
    printf("%d %s %d %d\n", JGUI_DRAW_BROADCAST, simTime, id, color);
}

void JGUI_DrawLine(int srcId, int destId, char *simTime,
                   JGUI_COLOR color) {
    printf("%d %s %d %d %d\n", JGUI_DRAW_LINE, simTime, srcId, destId, color);
}

void JGUI_DrawThickLine(int srcId, int destId, int thickness,
                        char *simTime, JGUI_COLOR color) {
    printf("%d %s %d %d %d %d\n", JGUI_DRAW_THICKLINE, simTime, srcId, destId,
                                  thickness, color);
}

void JGUI_MoveNode(int id, int x, int y, char *simTime) {
    printf("%d %s %d %d %d\n", JGUI_MOVE_NODE, simTime, id, x, y);
}


