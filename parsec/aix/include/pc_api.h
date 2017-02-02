/* =========================================================================
   pc_api.h - APIs to the runtime system
   $Id: pc_api.h,v 1.10 1998/12/07 19:16:39 jmartin Exp $
  ========================================================================== */

#ifndef PC_API_H
#define PC_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "clocktype.h"

/* -------------------------------------------------------------------------
   Default stack size.  Note this is a "#define" because C (unlike C++)
   does not allow:
      "static const int DEFAULT_STACK = 200000;"
   to be used as a initial value of global variable.  
   ------------------------------------------------------------------------- */

#define DEFAULT_STACK 200000


#ifdef ONLY_INCLUDE_DEFINES 
/* -------------------------------------------------------------------------
   For setjmp() on Windows NT.
   This may have to be changed if the user program itself includes setjmp*.h.
   ------------------------------------------------------------------------- */
  #ifdef _WIN32 
     #define setjmp(x) _setjmp(x)
  #endif
#else 

#include <stdio.h>
#include <setjmp.h>

/* -------------------------------------------------------------------------
   Define the entity name type.   
   
   Note that the pid is currently goes up to 65K entities and may wrap
   with simulations that create and delete entities continuously. 
   Currently it seems to be only used by ISP which is limited to an
   even lower number of entities.
   ------------------------------------------------------------------------- */

struct MC_ename {
    short                   node;   /* which node it is on */
    unsigned short          pid;    /* pid of the entity on that node */
    struct MC_entity_state* entity_state; 
};

typedef struct MC_ename ename;

/*  For optimistic runtime written in C++,  this type is not really
*   used but is overlayed by the C++ entity name object (the type
*   could not be compiled as C).  Of course, the actual C++ entity
*   name type must be smaller or equal in size and there is an assert
*   to check this requirement.  The justification for this hack is so
*   there are not two versions of generated C code. The below type name
*   is to call attention to this evil hack.
*/

typedef ename OverlayedBogusEntityNameType;


extern const ename ENULL;

#define ename_cmp(e1, e2) ((e1).node == (e2).node && (e1).pid == (e2).pid)
#define ename_valid(e)    ((e).pid)

/* -------------------------------------------------------------------------
   Maximum number of Parsec message types.
   ------------------------------------------------------------------------- */

#define MAX_MSG_TYPES 128

static const int MCMN_timeout_first = 0;
static const int MCMN_timeout_last = 1;


/* -------------------------------------------------------------------------
   Drivers stack size.
   ------------------------------------------------------------------------- */
                      
extern const unsigned int MCEN_driver_stacksize;


/* -------------------------------------------------------------------------
   Definition of struct MCS_driver_args.
   Passed to the driver entity as parameter.
   ------------------------------------------------------------------------- */

struct MCS_driver_args {
    int   argc;
    char  **argv;
};



/* -------------------------------------------------------------------------
   Pointers to the entity thread execution functions.
   ------------------------------------------------------------------------- */
   
typedef void (*MC_entity_function)(void *);

extern MC_entity_function EntityFunctionPtr[];

void MC_entity_ptr_init(void);

static const int ParsecDriverEntityTypeID = 0;
   
/* -------------------------------------------------------------------------
   Prototypes of API functions.
   ------------------------------------------------------------------------- */

/* For entity startup */
void  MC_initialize(ename *, jmp_buf);
void  MC_examine_current_stacksize(void);
void  MC_my_ename(ename *);


/* For "new" statement */
void  MC_prepare_arg(ename, void **, int);
void  MC_create(ename, ename *, int, unsigned int, int);

/* For "send" statement */
void  MC_prepare_msg(ename, void **, int, int, ename, clocktype);
void  MC_invoke_msg(ename);

/* For "receive" statement */
void  MC_build_mset(ename, int, const int[]);
int   MC_check_msg(ename, void **, clocktype);
void *MC_remove_msg(ename, int);

/* For users */
long   pc_nrand(unsigned short [3]);
long   pc_jrand(unsigned short [3]);
double pc_erand(unsigned short [3]);

void   pc_printf(char *, ...);
void   pc_fprintf(FILE *, char *, ...);
FILE*  pc_fopen(const char*, const char*);
void   pc_fclose(FILE*);
       
int    pc_num_nodes(void);
void   pc_print_runtime(void);
void   pc_exit(int);

clocktype simclock(ename);
void      setmaxclock(clocktype);
void      hold(ename, clocktype);
void      entity_yield(ename);
void     *qhead(ename, int);
int       qlength(ename, int);
int       qposition(ename, void *);
int       qempty(ename, int);

/* For conservative runtime */
void      add_source(ename);
void      del_source(ename);
void      add_dest(ename);
void      del_dest(ename);
void      setlookahead(ename, clocktype, clocktype);

/* For special purpose runtimes */
void      add_path_source(ename, int);
void      del_path_source(ename, int);
void      add_path_dest(ename, int);
void      del_path_dest(ename, int);
void      setpathlookahead(ename, clocktype, clocktype, int);
void      setdestlookahead(ename, clocktype, clocktype, ename);

/* For optimistic runtime */

void * pc_malloc(size_t size);
void   pc_free(void* ptr);

void set_gvt_calculation_interval(int EventInterval, double MinRealTime);
void set_state_saving_interval(int EventInterval);
void set_event_throttle_window(int MaxNumberOptimisticEvents);


typedef unsigned int EventNumberType;

typedef void (*RollbackCallbackFunctionType)(
   void * DataStructurePtr, 
   EventNumberType RollbackedEventNumber);
   
typedef void (*DeadwoodCollectCallbackFunctionType)(
   void * DataStructurePtr, 
   EventNumberType WillNeverBeRolledbackEventNumber);
        
   
void register_rollbackable_datastructure(
   void* DataStructurePtr,
   RollbackCallbackFunctionType RollbackCallbackFunction,
   DeadwoodCollectCallbackFunctionType DeadwoodCollectCallbackFunction);

EventNumberType current_event_number(ename);


/* -------------------------------------------------------------------------
   Function to call to start the simulation if the user
   wants to write his own main().
   ------------------------------------------------------------------------- */

int parsec_main(int argc, char **argv);

#endif

#ifdef __cplusplus
}
#endif

#endif
