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
 * $Id: brkdn_dist.c,v 1.4 1999/09/05 05:20:34 jmartin Exp $
 *
 * Ported from TCPLIB.  This file contains functions to get the
 * next application randomly.
 */ 

/*
 * Copyright (c) 1991 University of Southern California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of Southern California. The name of the University 
 * may not be used to endorse or promote products derived from this 
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*/
#ifndef lint
static char rcsid[] =
"@(#) $Id: brkdn_dist.c,v 1.4 1999/09/05 05:20:34 jmartin Exp $ (USC)";
#endif

#include <stdlib.h>
#include <math.h>
#include "distributions.h"

struct app_brkdn {
	char *appname;
	float mean;
	float mean_sqr;
	float var;
};

#include "app_brkdn.h"
#include "brkdn_dist.h"
#include "distributions.h"

extern double pc_erand(unsigned short seed[3]);

struct brkdn_dist *
brkdn_dist(unsigned short seed[3])
{
	int i;
	struct brkdn_dist *apps = (struct brkdn_dist *) malloc(NUMAPP*sizeof(struct brkdn_dist));
	float normalizer = 0.0;

	for (i = 0; i < NUMAPP; i++) {
		apps[i].appname = apps_brkdn[i].appname;
		apps[i].cdf = gam_dist(apps_brkdn[i].mean, apps_brkdn[i].mean_sqr, apps_brkdn[i].var, seed);
		normalizer += apps[i].cdf;
	}

	apps[0].cdf /= normalizer;
	for (i = 1; i < NUMAPP; i++) {
		apps[i].cdf /= normalizer;
		apps[i].cdf += apps[i-1].cdf;
	}

	return apps;
}


char *next_app(struct brkdn_dist brkdn[], unsigned short seed[3])
{
	int i = 0;
	float prob = (float) pc_erand(seed);

	while (i < NUMAPP && brkdn[i].cdf < prob) i++;
	if (i == NUMAPP)
		perror("next_app: bad prob");
	return brkdn[i].appname;
}

