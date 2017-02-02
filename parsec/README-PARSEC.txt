/*
 * PARSEC is COPYRIGHTED software.  Release 1.1 of PARSEC is available 
 * at no cost to educational users only.
 *
 * Commercial use of this software requires a separate license.  No cost,
 * evaluation licenses are available for such purposes; please contact
 * info@scalable-networks.com
 *
 * By obtaining copies of this and any other files that comprise PARSEC 1.1,
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

-------------------------------------------------------------------------------
1. PARSEC Installation requirements
PARSEC/GloMoSim requires a C compiler to run. While it works
with most C/C++ compilers on many common platforms, we only
include pre-compiled PARSEC runtime libraries for the
following operating systems:
./parsec/aix/                : IBM AIX with xlc compiler
./parsec/windowsnt-4.0-vc6/  : MS Windows NT or 2000
                               with Visual C++ ver. 6.0
./parsec/freebsd-3.3/        : FreeBSD 3.3
./parsec/redhat-6.0/         : Red Hat 6.0 or higher
./parsec/solaris-2.5.1/      : Sun SPARC Solaris 2.5.1 or higher
                               with gcc/g++
./parsec/solaris-2.5.1-cc/   : Sun SPARC Solaris 2.5.1 or higher
                               with Sun C compiler
./parsec/x86-solaris-2.5.1/  : Sun X86 Solaris 2.5.1 or higher
                               with gcc/g++
./parsec/irix-6.4/           : SGI IRIX 6.4 or higher
                               with gcc/g++
Please contact us if you need PARSEC on other platforms.

2. PARSEC Installation
(For UNIX based machines)
If you have permission to create /usr/local/parsec, the
installation is easy; just copy the whole subdirectory with
the name of target platform under /usr/local/parsec. If you
do not have permission to create a directory under
/usr/local, create a directory anywhere you like, and set
the designated directory to an environment variable
"PCC_DIRECTORY." For instance, you can set the variable by
typing "setenv PCC_DIRECTORY /home/foo/parsec" if you are
using (t)csh.
(For Windows)
The default path is c:\parsec. You can change the directory
in the same way as UNIX based machines.

3. PARSEC environment variables and compiler options
pcc checks the following environment variables when
executed:
  PCC_DIRECTORY      : Directory that pcc looks up
  PCC_CC             : C compiler used for preprocessing and compiling
  PCC_LINKER         : Linker used for linking
  PCC_PP_OPTIONS     : Options for preprocessing
  PCC_CC_OPTIONS     : Options for compiling
  PCC_LINKER_OPTIONS : Options for linking
These variables do not usually need to change. PARSEC also
has the command line options each of which corresponds to
the environment variable above:
  -pcc_directory
  -pcc_cc
  -pcc_linker
  -pcc_pp_optoins
  -pcc_cc_options
  -pcc_linker_options
These command line options can override the environment
variables and are useful when changing options temporarily.
There are other command line options besides those. You can
see brief descriptions of those options by typing "pcc -help"
For detailed descriptions, you can read the manual for
PARSEC on the web:
    http://pcl.cs.ucla.edu/projects/parsec
-------------------------------------------------------------------------------
