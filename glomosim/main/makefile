# Glomosim is COPYRIGHTED software.  It is freely available without fee for
# education, or research, or to non-profit agencies. No cost evaluation
# licenses are available for commercial users. By obtaining copies of this
# and other files that comprise GloMoSim, you, the Licensee, agree to abide
# by the following conditions and understandings with respect to the
# copyrighted software:
#
# 1.Permission to use, copy, and modify this software and its documentation
#   for education, research, and non-profit purposes is hereby granted to
#   Licensee, provided that the copyright notice, the original author's names
#   and unit identification, and this permission notice appear on all such
#   copies, and that no charge be made for such copies. Any entity desiring
#   permission to incorporate this software into commercial products or to use
#   it for commercial purposes should contact: 
#
#   Professor Rajive Bagrodia 
#   University of California, Los Angeles 
#   Department of Computer Science 
#   Box 951596 
#   3532 Boelter Hall 
#   Los Angeles, CA 90095-1596 
#   rajive@cs.ucla.edu
#
# 2.NO REPRESENTATIONS ARE MADE ABOUT THE SUITABILITY OF THE SOFTWARE FOR ANY
#   PURPOSE. IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
#
# 3.Neither the software developers, the Parallel Computing Lab, UCLA, or any
#   affiliate of the UC system shall be liable for any damages suffered by
#   Licensee from the use of this software.
#
# $Id: makefile,v 1.86 2001/02/16 04:19:05 jmartin Exp $
#
# Makefile used for compiling GloMoSim
#
# Add Parsec Suffix
#.SUFFIXES:
.SUFFIXES: .pc .cpp .c $(SUFFIXES)

# Program Files 
GUI = Run

SIM_HDRS =  ../main/glomo.h ../main/driver.h \
            ../main/mobility_trace.h \
            ../main/mobility_waypoint.h ../main/heap.h \
            ../main/lookahead.h \
            ../include/mobility.h ../include/queue.h ../include/message.h \
            ../include/structmsg.h ../include/api.h ../include/fileio.h \
            ../include/main.h ../include/splaytree.h \
            ../include/radio.h ../include/mac.h \
            ../include/network.h ../include/nwcommon.h ../include/ip.h \
            ../include/transport.h ../include/application.h \
            ../include/propagation.h \
            ../include/pathloss_matrix.h \
            ../radio/radio_accnoise.h ../radio/radio_nonoise.h \
            ../mac/csma.h ../mac/maca.h \
            ../mac/tsma.h ../mac/wiredlink.h \
            ../network/ipqueue.h ../network/fifoqueue.h \
            ../network/nwip.h ../network/nwlar1.h ../network/odmrp.h \
            ../network/aodv.h ../network/dsr.h ../network/zrp.h \
            ../transport/udp.h  ../transport/in_pcb.h \
            ../transport/tcp/tcp_config.h ../transport/tcp/tcp_var.h \
            ../transport/tcp/tcp_fsm.h ../transport/tcp/tcp_proto.h \
            ../transport/tcp/tcp_timer.h ../transport/tcp/tcpip.h \
            ../transport/tcp/tcp.h \
            ../application/fisheye.h \
            ../application/wrp.h  ../application/static_routing.h \
            ../application/bellmanford.h  \
            ../application/app_util.h ../application/telnet_client.h \
            ../application/telnet_server.h \
            ../application/ftp_client.h ../application/ftp_server.h \
            ../application/http_distribution.h ../application/http_client.h \
            ../application/http_server.h \
            ../application/gen_ftp_client.h ../application/gen_ftp_server.h \
            ../application/cbr_client.h ../application/cbr_server.h \
            ../application/nsdsdv.h \
            ../include/java_gui.h



#            ../application/nsdsdvinterface.h \
#            ../application/nsdsdv/config.h  ../application/nsdsdv/datastructures.h \
#            ../application/nsdsdv/dsdv.h ../application/nsdsdv/fakens.h \
#            ../application/nsdsdv/hdrcmn.h ../application/nsdsdv/ip.h \
#            ../application/nsdsdv/rtable.h ../application/nsdsdv/smart.h \


TCPLIBAPP_HDRS = ../tcplib/telnet.h ../tcplib/ftp.h ../tcplib/nntp.h \
                 ../tcplib/smtp.h ../tcplib/phone.h ../include/tcpapps.h \
                 ../include/brkdn_dist.h

HDRS = $(SIM_HDRS) $(TCPLIBAPP_HDRS)

TCPLIBAPP_SRCS = ../tcplib/telnet.c ../tcplib/ftp.c ../tcplib/nntp.c \
                 ../tcplib/smtp.c ../tcplib/phone.c ../tcplib/tcplib.c \
                 ../tcplib/brkdn_dist.c ../tcplib/distributions.c

C_SRCS = $(TCPLIBAPP_SRCS) ../java_gui/java_gui.c \
                           ../application/http_distribution.c

C++_SRCS =


#            ../application/nsdsdvinterface.cpp \
#            ../application/nsdsdv/dsdv.cpp \
#            ../application/nsdsdv/rtable.cpp


DRIVER_FILE = ../main/driver.pc

PAR_FILES = ../main/glomo.pc ../main/mobility.pc \
            ../main/mobility_waypoint.pc \
            ../main/mobility_trace.pc \
            ../main/message.pc ../main/splaytree.pc ../main/heap.pc \
            ../main/queue.pc ../main/nodes.pc \
            ../main/fileio.pc \
            ../main/lookahead.pc \
            ../radio/radio.pc \
            ../radio/radio_accnoise.pc \
            ../radio/radio_nonoise.pc \
            ../radio/propagation.pc \
            ../radio/pathloss_free_space.pc \
            ../radio/pathloss_two_ray.pc \
            ../radio/pathloss_matrix.pc \
            ../mac/csma.pc \
            ../mac/maca.pc \
            ../mac/802_11.pc \
            ../mac/tsma.pc \
            ../mac/user_mac.pc \
            ../mac/mac.pc \
            ../network/network.pc ../network/nwcommon.pc ../network/nwip.pc \
            ../network/user_nwip.pc ../network/fifoqueue.pc \
            ../network/nwlar1.pc ../network/odmrp.pc ../network/aodv.pc \
            ../network/dsr.pc ../network/zrp.pc \
            ../transport/transport.pc ../transport/in_pcb.pc \
            ../transport/udp.pc \
            ../transport/tcp/tcp.pc ../transport/tcp/tcp_subr.pc \
            ../transport/tcp/tcp_output.pc ../transport/tcp/tcp_usrreq.pc \
            ../transport/tcp/tcp_timer.pc ../transport/tcp/tcp_input.pc \
            ../application/fisheye.pc \
            ../application/wrp.pc ../application/static_routing.pc \
            ../application/bellmanford.pc ../application/user_application.pc \
            ../application/application.pc ../application/app_util.pc \
            ../application/telnet_server.pc ../application/telnet_client.pc \
            ../application/ftp_client.pc ../application/ftp_server.pc \
            ../application/http_client.pc ../application/http_server.pc \
            ../application/gen_ftp_client.pc ../application/gen_ftp_server.pc \
            ../application/cbr_client.pc ../application/cbr_server.pc \
            ../mac/wiredlink.pc

ALLFILES = $(HDRS) $(C_SRCS) $(C++_SRCS) $(PAR_FILES) Makefile

PAR_OBJECTS = $(PAR_FILES:.pc=.o)
DRIVER_OBJECT = $(DRIVER_FILE:.pc=.o)
SIM_OBJECTS = $(PAR_OBJECTS) $(C++_SRCS:.cpp=.o) $(C_SRCS:.c=.o)
RADIO_RANGE_OBJS = ../radio/radiorange.o
OBJECTS = $(DRIVER_OBJECT) $(SIM_OBJECTS) $(RADIO_RANGE_OBJS)

SIM_EXEC = ../bin/glomosim
RADIO_RANGE = ../bin/radio_range
TSMA_CODE = tsma_code_gen
TSMA_PARAM = tsma_param_gen

#
#
COMFLAG = -g -O3 -I../include/ -I../transport -I../transport/tcp -I../application -I../mac -I../main -I../network -I../radio

#
# C Compiler
CC = gcc
CTX = g++
CFLAGS = $(COMFLAG)

# Parsec
PAR = pcc

## By putting this "pcc" script in your path you can
## put the Parsec compiler files wherever you want.
##
## #!/bin/csh
## setenv PCC_DIRECTORY "/Your Parsec Dir"
## echo Using Parsec in ${PCC_DIRECTORY}
## ${PCC_DIRECTORY}/bin/parsecc $*
##

PARFLAG = $(COMFLAG) -clock longlong
# -sync cons

PARLIB = -lm

# Dependencies
all:  $(SIM_EXEC) $(TSMA_CODE) $(TSMA_PARAM) $(RADIO_RANGE)

.cpp.o:
	$(CTX) $(CFLAGS) -c $*.cpp -o $*.o

.pc.o:
	$(PAR) $(PARFLAG) $(PARLIB) -c $*.pc
#	$(PAR) $(PARFLAG) $(PARLIB) -E $*.pc

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

$(SIM_EXEC): $(SIM_OBJECTS) $(DRIVER_OBJECT)
	$(PAR) $(PARFLAG) -user_main $(SIM_OBJECTS) $(DRIVER_OBJECT) $(PARLIB) -o $(SIM_EXEC)

$(TSMA_CODE): 
	$(CC) ../mac/$(TSMA_CODE).c -o ../bin/$(TSMA_CODE)

$(TSMA_PARAM): 
	$(CC) ../mac/$(TSMA_PARAM).c -o ../bin/$(TSMA_PARAM)

$(RADIO_RANGE): $(RADIO_RANGE_OBJS)
	$(PAR) $(PARFLAG) $(SIM_OBJECTS) $(RADIO_RANGE_OBJS) -o $(RADIO_RANGE)

# Commonly Used Commands
clean:
	rm -f $(OBJECTS) $(SIM_EXEC) $(TSMA_CODE) $(TSMA_PARAM) $(RADIO_RANGE) core ../*/*~ ../*/*/*~ ../*/*.pi ../*/*/*.pi
wc:
	wc $(ALLFILES)
