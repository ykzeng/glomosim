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
 * TSMA Model in GloMoSim - version 1.0
 *
 * The TSMA model in GloMoSim is COPYRIGHTED software.  It is freely available 
 * without fee for education, or research, or to non-profit agencies. By 
 * obtaining copies of this and other files that comprise the TSMA model in
 * GloMoSim, you, the Licensee, agree to abide by the following conditions 
 * and understandings with respect to the copyrighted software:
 *
 * 1. Permission to use, copy, and modify this software and its documentation
 *    for education, research, and non-profit purposes is hereby granted to
 *    Licensee, provided that the copyright notice, the original author's names
 *    and unit identification, and this permission notice appear on all such
 *    copies, and that no charge be made for such copies. Any entity desiring
 *    permission to incorporate this software into commercial products or to 
 *    use it for commercial purposes should contact: 
 *
 *    Professor Imrich Chlamtac
 *    Distinguished Chair in Telecommunications
 *    Director, Center for Advanced Telecommunications Systems and Services
 *    Erik Jonsson School of Engineering and Computer Science
 *    The University of Texas at Dallas
 *    P.O. Box 830688, EC 33
 *    Richardson, TX 75083-0688
 *    e-mail: chlamtac@utdallas.edu
 *
 * 2. NO REPRESENTATIONS ARE MADE ABOUT THE SUITABILITY OF THE SOFTWARE FOR ANY
 *    PURPOSE. IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 *
 * 3. Neither the software developers, the Center for Advanced Tele-
 *    communications Systems and Services (CATSS), UTD, or any affiliate 
 *    of the UT system shall be liable for any damages suffered by
 *    Licensee from the use of this software.
 */


/*
 * $Id: tsma_param_gen.c,v 1.4 1999/10/08 10:23:05 ktang Exp $
 */

#include <stdio.h>
#include <math.h>

#define MAX_NUM_PRIMES 170

const int TsmaPrimes[] =
    {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,
    71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,
    149,151,157,163,167,173,179,181,191,193,197,199,211,223,
    227,229,233,239,241,251,257,263,269,271,277,281,283,293,
    307,311,313,317,331,337,347,349,353,359,367,373,379,383,
    389,397,401,409,419,421,431,433,439,443,449,457,461,463,
    467,479,487,491,499,503,509,521,523,541,547,557,563,569,
    571,577,587,593,599,601,607,613,617,619,631,641,643,647,
    653,659,661,673,677,683,691,701,709,719,727,733,739,743,
    751,757,761,769,773,787,797,809,811,821,823,827,829,839,
    853,857,859,863,877,881,883,887,907,911,919,929,937,941,
    947,953,967,971,977,983,991,997,1009,1013};


/*
 * NAME:        MacTsmaPower.
 *
 * PURPOSE:     Caculates power of a given number.
 *
 * PARAMETERS:  base, base of the exponent.
 *              exp, exponent.
 *
 * RETURN:      Result of power function.
 *
 * ASSUMPTION:  None.
 */

int MacTsmaPower (int base, int exp);


/*
 * NAME:        main.
 *
 * PURPOSE:     Computes the minimum TSMA parameters (q and k)
 *              necessary for the current number of nodes and specified
 *              node degree.
 *
 * PARAMETERS:  argc, number of arguments to program.
 *              argv, arguments to program.
 *
 * RETURN:      0.
 *
 * ASSUMPTION:  None.
 *
 * NOTE:  Will be compiled into binary named TsmaParamGen.
 */

int main(int argc, char* argv[])
{
    int i, q, k, D, N;

    if (argc != 3)
    {
        printf("Error: invalid number of args!\n");
        return 1;
    }

    N = atoi(argv[1]);
    D = atoi(argv[2]);

    if ((N < 2) || (D < 1))
    {
        printf("Error: bad args!\n");
        return 1;
    }

    for (i = 0; i < MAX_NUM_PRIMES; i++)
    {
        q = TsmaPrimes[i];
        k = (q - 1) / D;

        if ((k >= 0) && (MacTsmaPower(q, k + 1) >= N) && (q >= (k * D) + 1))
        {
            printf("%d\n%d\n", q, k);
            break;
        }
    }

    return 0;
}


/*
 * NAME:        MacTsmaPower.
 *
 * PURPOSE:     Caculates power of a given number.
 *
 * PARAMETERS:  base, base of the exponent.
 *              exp, exponent.
 *
 * RETURN:      Result of power function.
 *
 * ASSUMPTION:  None.
 */

int MacTsmaPower (int base, int exp)
{
    int pow,
    sum = base;

    if (exp == 0)
    {
        return 1;
    }

    for (pow = 1; pow < exp; pow++)
    {
        sum *= base;
    }

    return sum;
}

