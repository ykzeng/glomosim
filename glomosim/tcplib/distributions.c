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
 * $Id: distributions.c,v 1.4 1999/09/05 05:20:38 jmartin Exp $
 *
 * Ported from TCPLIB.  This file contains gam_dist(). 
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

#include <stdlib.h>
#include <math.h>
#include "distributions.h"

extern double pc_erand(unsigned short seed[3]);

/* Numerical Recipes in C, p. 220. */
float gam_dist(float n, float n2, float s, unsigned short seed[3])
{
    int i, r;
    double g, rm, rs, v1, v2, y, e;

		if (!s) return 0.0;

 		r = (int)((double) n2/s + 0.5); /* Kleinrock, p. 124 */
    if (r < 1) { 
			perror("gam_dist: bad r\n");
			exit(1);
		}

    if (r < 6) { 
      g = 1.0;
      for (i = 0; i <= r; i++)  {
				g *= (float) pc_erand(seed);
			}
      g = -log((double) g);
    } else {
      do {
        do {
          do {
						v1 = 2.0*pc_erand(seed)-1.0;
            v2 = 2.0*pc_erand(seed)-1.0;
          } while (v1*v2+v1*v2 > 1.0);
          y = v2/v1;
          rm = r - 1;
          rs = sqrt(2.0*rm+1.0);
          g = rs*y+rm;
        } while (g <= 0.0);
        e = (1.0+y*y)*exp(rm*log((double) g/rm)-rs*y);
      } while (pc_erand(seed) > e);
    }
    g = (double) ((g*(double)n)/(double)r);
		return((float) g);
} 

