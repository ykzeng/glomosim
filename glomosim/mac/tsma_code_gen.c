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
 * $Id: tsma_code_gen.c,v 1.2 1999/09/14 03:39:54 ktang Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#define POLY int*
#define TSMA_CODE int*
#define INT unsigned int
#define OUTFILE "../mac/tsmacodes.dat"
#define WRITE "wb"

/*
 * For some odd reason, I was not able 
 * to use the pow function defined in
 * the math.h header file. So I simply
 * wrote some code to perform the same
 * function.
 */


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

int MacTsmaPower(int base, int exp);



/*
 * NAME:        MacTsmaPrintPoly.
 *
 * PURPOSE:     Print the poly.
 *
 * PARAMETERS:  poly, the poly to be printed.
 *              size, size of the poly.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void MacTsmaPrintPoly(POLY poly, INT size);


/*
 * NAME:        MacTsmaGeneratePolys.
 *
 * PURPOSE:     Generate the polys.
 *
 * PARAMETERS:  poly, the poly to be generated.
 *              Q, q value of poly.
 *              K, k value of poly.
 *              pos, position of poly.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void MacTsmaGeneratePolys(POLY poly, INT Q, INT K, INT pos);


/*
 * NAME:        MacTsmaEvaluatePoly.
 *
 * PURPOSE:     Evaluate the poly.
 *
 * PARAMETERS:  poly, the poly to be evaluated.
 *              degree, degree of the poly.
 *              x, k value of poly.
 *
 * RETURN:      Sum of the poly.
 *
 * ASSUMPTION:  None.
 */

INT MacTsmaEvaluatePoly(POLY poly, INT degree, INT x);


/*
 * NAME:        MacTsmaSlotAssignment.
 *
 * PURPOSE:     Determine slot assignment.
 *
 * PARAMETERS:  Q, q value of poly.
 *              K, k value of poly.
 *              slotNumber, slot number.
 *
 * RETURN:      slot number being assigned.
 *
 * ASSUMPTION:  None.
 */

INT MacTsmaSlotAssignment(POLY poly, INT Q, INT K, INT slotNumber);


/*
 * NAME:        MacTsmaBuildCode.
 *
 * PURPOSE:     Build code for node.
 *
 * PARAMETERS:  poly, the poly used to build code.
 *              Q, q value of poly.
 *              K, k value of poly.
 *
 * RETURN:      TSMA code.
 *
 * ASSUMPTION:  None.
 */

TSMA_CODE MacTsmaBuildCode(POLY poly, INT Q, INT K);


/*
 * NAME:        main.
 *
 * PURPOSE:     Computs the TSMA codes for the given q and k parameters
 *              from tsmaparam.c.
 *
 * PARAMETERS:  argc, number of arguments to program.
 *              argv, agruments to program.
 *
 * RETURN:      0
 *
 * ASSUMPTION:  None.
 *
 * NOTE:        Will be compiled into binary called TsmaCodeGen.
 */

int main(int argc, char* argv[])
{
    POLY polynomial;
    FILE* ofile;
    INT Q;
    INT K;

    if (argc != 3)
    {
        printf("Error: Invalid number of args present!\n");
        return 1;
    }

    Q = atoi(argv[1]);
    K = atoi(argv[2]);
    polynomial = malloc((K + 1) * sizeof(int));
    MacTsmaGeneratePolys(polynomial, Q, K, 0);

    return 0;
}


/*
 * NAME:        MacTsmaPrintPoly.
 *
 * PURPOSE:     Print the poly.
 *
 * PARAMETERS:  poly, the poly to be printed.
 *              size, size of the poly.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void MacTsmaPrintPoly(POLY poly, INT size)
{
    INT pos;

    for (pos = 0; pos < size; pos++)
    {
        printf("%d", poly[pos]);
    }

    printf("\n");
}


/*
 * NAME:        MacTsmaGeneratePolys.
 *
 * PURPOSE:     Generate the polys.
 *
 * PARAMETERS:  poly, the poly to be generated.
 *              Q, q value of poly.
 *              K, k value of poly.
 *              pos, position of poly.
 *
 * RETURN:      None.
 *
 * ASSUMPTION:  None.
 */

void MacTsmaGeneratePolys(POLY poly, INT Q, INT K, INT pos)
{
    TSMA_CODE code;
    INT k, q;
  
    for(k = pos; k <= K; k++)
    {
        for(q = 0; q < Q; q++)
        {
            poly[k] = q;
            MacTsmaGeneratePolys(poly, Q, K, pos + 1);
        }

        return;
    }
/*  MacTsmaPrintPoly(poly, K + 1); */

    code = MacTsmaBuildCode(poly, Q, K);
    MacTsmaPrintPoly(code, Q * Q);
    free(code);
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


/*
 * NAME:        MacTsmaEvaluatePoly.
 *
 * PURPOSE:     Evaluate the poly.
 *
 * PARAMETERS:  poly, the poly to be evaluated.
 *              degree, degree of the poly.
 *              x, k value of poly.
 *
 * RETURN:      Sum of the poly.
 *
 * ASSUMPTION:  None.
 */

INT MacTsmaEvaluatePoly(POLY poly, INT degree, INT x)
{
    INT pos, var, sum = 0;

    for (pos = 0; pos <= degree; pos++)
    {
        var = MacTsmaPower(x, pos);
        sum += poly[pos] * var;
    }

    return sum;
}


/*
 * NAME:        MacTsmaSlotAssignment.
 *
 * PURPOSE:     Determine slot assignment.
 *
 * PARAMETERS:  Q, q value of poly.
 *              K, k value of poly.
 *              slotNumber, slot number.
 *
 * RETURN:      slot number being assigned.
 *
 * ASSUMPTION:  None.
 */

INT MacTsmaSlotAssignment(POLY poly, INT Q, INT K, INT slotNumber)
{
    INT sModQ = slotNumber % Q;
    INT sDivQ = slotNumber / Q;
    INT result = MacTsmaEvaluatePoly(poly, K, sDivQ);
    result %= Q;
    return sModQ == result;
}


/*
 * NAME:        MacTsmaBuildCode.
 *
 * PURPOSE:     Build code for node.
 *
 * PARAMETERS:  poly, the poly used to build code.
 *              Q, q value of poly.
 *              K, k value of poly.
 *
 * RETURN:      TSMA code.
 *
 * ASSUMPTION:  None.
 */

TSMA_CODE MacTsmaBuildCode(POLY poly, INT Q, INT K)
{
    INT slot, size = Q * Q;
    TSMA_CODE code;
    code = malloc(size * sizeof(INT));

    for (slot = 0; slot < size; slot++)
    {
        code[slot] = MacTsmaSlotAssignment(poly, Q, K, slot);
    }

    return code;
}

