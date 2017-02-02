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
 * $Id: fileio.h,v 1.14 1999/12/10 05:32:57 jmartin Exp $
 *
 * Header file for strucutres and functions used for
 * reading from the input file.
 */

#ifndef _FILEIO_H_
#define _FILEIO_H_

#include "main.h"


#define DEFAULT_NO_INSTANCE_NUMBER -1


/*
 * typedef to GlomoNodeInput in main.h
 */
struct glomo_node_input_str {
    int  numLines;
    char **inputStrings;
};


void GLOMO_FreeNodeInput(GlomoNodeInput *nodeInput);
void GLOMO_ReadFile(GlomoNodeInput *nodeInput, const char *filename);
BOOL GLOMO_ReadCachedFile(const GlomoNodeInput *nodeInput,
                          char *index, GlomoNodeInput *readVal);

/*
 * FUNCTION     GLOMO_Read{String,Int,Double}
 * PURPOSE      This function is used for reading an integer value from
 *              the strucutre which contains input file information.
 *
 * Parameters:
 *     nodeAddr:    Node Address for which the info is required
 *     nodeInput:   Structure containing contents of input file.
 *     index:       String used to match a string from the file.
 *     readVal:     If a matching string is found, the corresponding
 *                  value is placed in readVal.
 *
 * TRUE is returned if a match is made correctly.
 * Otherwise FALSE is returned.
 */

BOOL GLOMO_ReadString(const NODE_ADDR nodeAddr, 
                      const GlomoNodeInput *nodeInput, 
                      const char *index, 
                      char *readVal);

BOOL GLOMO_ReadInt(const NODE_ADDR nodeAddr, 
                   const GlomoNodeInput *nodeInput, 
                   const char *index, 
                   int *readVal);

BOOL GLOMO_ReadDouble(const NODE_ADDR nodeAddr, 
                      const GlomoNodeInput *nodeInput, 
                      const char *index, 
                      double *readVal);

BOOL GLOMO_ReadTime(const NODE_ADDR nodeAddr, 
                    const GlomoNodeInput *nodeInput, 
                    const char *index, 
                    clocktype *readVal);




/*
 * FUNCTION     GLOMO_Read{String|Int|Double|Time}Instance
 * PURPOSE      This function is used for reading a string(etc) paramerter
 *              values from the configuration file data structure.
 *              This version of the function can also select different
 *              parameter instances instead of the default (0) instance.
 *              For example in the configuration file:
 *                 MAC-PROTOCOL[3] 802.11
 *              specifies that "instance 3" is "802.11".
 *
 *
 *              
 *              
 * Parameters:
 *   nodeAddr:       Node Address for which the info is required
 *   nodeInput:      Strcture containing contents of input file.
 *   parameterName:  GloMoSim parameter name string.
 *   parameterInstanceNumber: 
 *                   The retrieve parameter with this "instance number" 
 *   
 *   parameterFound : TRUE if the parameter was found.
 *   parameterValue: The value writen here if the parameter was found.
 *                  value is placed in readVal.
 *
 *
 */

void GLOMO_ReadStringInstance(
    const NODE_ADDR nodeAddr,
    const GlomoNodeInput *nodeInput, 
    const char parameterName[],
    const int parameterInstanceNumber, 
    const BOOL fallbackToDefault, 
    BOOL* WasFound,
    char  parameterValue[]);

void GLOMO_ReadIntInstance(
    const NODE_ADDR nodeAddr,
    const GlomoNodeInput *nodeInput, 
    const char parameterName[],
    const int parameterInstanceNumber, 
    const BOOL fallbackToDefault, 
    BOOL* WasFound,
    int*  parameterValue);

void GLOMO_ReadDoubleInstance(
    const NODE_ADDR nodeAddr,
    const GlomoNodeInput *nodeInput, 
    const char parameterName[],
    const int parameterInstanceNumber, 
    const BOOL fallbackToDefault, 
    BOOL* WasFound,
    double* parameterValue);

void GLOMO_ReadTimeInstance(
    const NODE_ADDR nodeAddr,
    const GlomoNodeInput *nodeInput, 
    const char parameterName[],
    const int parameterInstanceNumber, 
    const BOOL fallbackToDefault, 
    BOOL* WasFound,
    clocktype* parameterValue);
                      
#endif /* _FILEIO_H_ */







