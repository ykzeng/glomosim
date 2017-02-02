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
 * pathloss_matrix.h -- drive glomosim with pathloss matrix traces
 */

/* rcsid = "$Id: pathloss_matrix.h,v 1.2 2001/02/15 02:57:57 mineo Exp $" */

#ifndef PATHLOSS_MATRIX_H
#define PATHLOSS_MATRIX_H

#include "main.h"
#include "propagation.h"

#define PATHLOSS_MATRIX_DEFAULT_THRESHOLD  1000
#define PATHLOSS_MATRIX_DEFAULT_TRACEFILE  "pathloss.input"

/*
 * GlomoPropagatePathlossMatrix -- per partition info
 */
typedef struct glomo_propagate_pathloss_matrix_str {
    GlomoNode  *master;        /* control partition's trace */
    FILE       *tracein;       /* trace file */
    int        *threshold;     /* attenuation error thresh */
    int       **range;         /* range map */
    int       **attenuation;   /* attenuation map */
} GlomoPropPathlossMatrix;

void GLOMO_MobilityPathlossMatrixInit(GlomoNode *, GlomoNodeInput *);
void GLOMO_MobilityPathlossMatrixFinalize(GlomoNode *);
void GLOMO_MobilityPathlossMatrix(GlomoNode *);

void PathlossMatrixInit(GlomoProp *propData,
                        const GlomoNodeInput *nodeInput);

double PathlossMatrix(NODE_ADDR txAddr,
                      NODE_ADDR rxAddr,
                      float txAntennaGain,
                      float rxAntennaGain,
                      GlomoPropPathlossMatrix *pathlossVar,
                      double *distance);

#endif /* PATHLOSS_MATRIX_H */

/* Local Variables: */
/* c-basic-offset: 4 */
/* indent-tabs-mode: nil */
/* End: */

