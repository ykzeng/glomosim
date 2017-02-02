#ifndef CLOCKTYPE_H
#define CLOCKTYPE_H
/* =========================================================================
   clocktype.h - clocktype definition.
   $Id: clocktype.h,v 1.10 1998/10/26 08:46:04 jmartin Exp $
   ========================================================================= */

/* -------------------------------------------------------------------------
   CLOCKTYPE_MAX is the maximum value of clocktype.
   This value can be anything as long as it is less than or equal to the
   maximum value of the type which is typedefed to clocktype.
   Users can simulate the model up to CLOCKTYPE_MAX - 1.
   ------------------------------------------------------------------------- */

#ifdef __sgi
   #define SGI_UINT_MAX 4294967295U
   #ifndef ONLY_INCLUDE_DEFINES
      #include<limits.h>
      #if (SGI_UINT_MAX != UINT_MAX)
         Incorrect Constant For UINT_MAX. (Crashing Compiler)
      #endif
   #else
      #define UINT_MAX SGI_UINT_MAX
   #endif
#else
   #include <limits.h>
#endif
                                                    

#ifdef CLOCK_LONGLONG
    #ifndef _WIN32
        #ifndef ONLY_INCLUDE_DEFINES
           typedef long long clocktype;
           /*
            * Since long long is not in ANSI standard, some OS's
            * do not have a definition of maximum value for
            * long long in limits.h
            */
        #endif  
          
        #define CLOCKTYPE_MAX 0x7fffffffffffffffLL
    #else
        #ifndef ONLY_INCLUDE_DEFINES
           typedef __int64 clocktype;
        #endif
        
        #define CLOCKTYPE_MAX _I64_MAX
    #endif
#elif  CLOCK_DOUBLE
    #ifndef ONLY_INCLUDE_DEFINES
        typedef double clocktype;
    #endif
    /*
     * This number is 2^48
     */
    #define CLOCKTYPE_MAX 281474976710656.0
#else
    #ifndef ONLY_INCLUDE_DEFINES
        typedef unsigned int clocktype;
    #endif

    #define CLOCKTYPE_MAX UINT_MAX
#endif

#ifdef CLOCK_LONGLONG
    #define ctoa(clock, string) sprintf(string, "%lld", clock)
    #define atoc(string, clock) sscanf(string, "%lld", clock)
#elif  CLOCK_DOUBLE
    #define ctoa(clock, string) sprintf(string, "%.0lf", clock)
    #define atoc(string, clock) sscanf(string, "%.0lf", clock)
#else
    #define ctoa(clock, string) sprintf(string, "%u", clock)
    #define atoc(string, clock) sscanf(string, "%u", clock)
#endif

#endif
