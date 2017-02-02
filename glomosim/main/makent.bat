@setlocal
@set prompt=$g

@set cppflags=-Ox 
@rem -DPARALLEL

@set parsecflags=%cppflags% 

@rem -sync cons

@set linkflags=

@rem /F400000000
@rem /F is for setting the maximum stacksize (sequential).

@if ""=="%1" goto All

@if M==%1 goto Main
@if MAC==%1 goto Mac
@if T==%1 goto Transport
@if N==%1 goto Network
@if A==%1 goto Application
@if L==%1 goto Link
@if R==%1 goto Radio
echo Bad parmeter.
goto End
    

:All

@del /s ..\*.obj 1>nul  2>nul

call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\java_gui\java_gui.c /Fo..\java_gui\java_gui.obj
call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\tcplib\telnet.c /Fo..\tcplib\telnet.obj
call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\tcplib\ftp.c /Fo..\tcplib\ftp.obj
call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\tcplib\nntp.c /Fo..\tcplib\nntp.obj
call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\tcplib\smtp.c /Fo..\tcplib\smtp.obj
call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\tcplib\phone.c /Fo..\tcplib\phone.obj
call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\tcplib\tcplib.c /Fo..\tcplib\tcplib.obj
call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\tcplib\brkdn_dist.c /Fo..\tcplib\brkdn_dist.obj
call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\tcplib\distributions.c /Fo..\tcplib\distributions.obj


:Main
@del ..\main\*.obj 1>nul 2>nul
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\glomo.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\mobility.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\mobility_waypoint.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\mobility_trace.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\message.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\splayTree.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\heap.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\queue.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\nodes.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\fileio.pc
call pcc %parsecflags% -I..\include\ -clock longlong -c ..\main\lookahead.pc

@if M==%1 goto Link

:Radio
@del ..\radio\*.obj 1>nul 2>nul
call pcc %parsecflags% -I..\include\ -I..\radio\ -clock longlong -c ..\radio\propagation.pc
call pcc %parsecflags% -I..\include\ -I..\radio\ -clock longlong -c ..\radio\pathloss_free_space.pc
call pcc %parsecflags% -I..\include\ -I..\radio\ -clock longlong -c ..\radio\pathloss_two_ray.pc
call pcc %parsecflags% -I..\include\ -I..\radio\ -clock longlong -c ..\radio\pathloss_matrix.pc
call pcc %parsecflags% -I..\include\ -I..\radio\ -clock longlong -c ..\radio\radio.pc
call pcc %parsecflags% -I..\include\ -I..\radio\ -clock longlong -c ..\radio\radio_accnoise.pc
call pcc %parsecflags% -I..\include\ -I..\radio\ -clock longlong -c ..\radio\radio_nonoise.pc

@if R==%1 goto Link

:Mac
@del ..\mac\*.obj 1>nul 2>nul

call pcc %parsecflags% -I..\include\ -I..\mac\ -clock longlong -c ..\mac\802_11.pc
call pcc %parsecflags% -I..\include\ -I..\mac\ -clock longlong -c ..\mac\csma.pc
call pcc %parsecflags% -I..\include\ -I..\mac\ -clock longlong -c ..\mac\maca.pc
call pcc %parsecflags% -I..\include\ -I..\mac\ -clock longlong -c ..\mac\tsma.pc
call pcc %parsecflags% -I..\include\ -I..\mac\ -clock longlong -c ..\mac\mac.pc
call pcc %parsecflags% -I..\include\ -I..\mac\ -clock longlong -c ..\mac\user_mac.pc
call pcc %parsecflags% -I..\include\ -I..\mac\ -clock longlong -c ..\mac\wiredlink.pc

@if MAC==%1 goto Link

                                                    
:Network
@del ..\network\*.obj 1>nul  2>nul
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\network.pc
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\nwCommon.pc
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\nwip.pc
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\user_nwip.pc
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\nwlar1.pc
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\dsr.pc
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\aodv.pc
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\zrp.pc
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\fifoqueue.pc
call pcc %parsecflags% -I..\include\ -I..\network\ -clock longlong -c ..\network\odmrp.pc

@if N==%1 goto Link

:Transport
@del /s ..\transport\*.obj 1>nul  2>nul
call pcc %parsecflags% -I..\include\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\transport\transport.pc
call pcc %parsecflags% -I..\include\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\transport\in_pcb.pc
call pcc %parsecflags% -I..\include\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\transport\udp.pc
call pcc %parsecflags% -I..\include\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\transport\tcp\tcp.pc
call pcc %parsecflags% -I..\include\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\transport\tcp\tcp_subr.pc
call pcc %parsecflags% -I..\include\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\transport\tcp\tcp_output.pc
call pcc %parsecflags% -I..\include\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\transport\tcp\tcp_usrreq.pc
call pcc %parsecflags% -I..\include\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\transport\tcp\tcp_timer.pc
call pcc %parsecflags% -I..\include\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\transport\tcp\tcp_input.pc
@if T==%1 goto Link

:Application
@del ..\application\*.obj 1>nul  2>nul
call pcc %parsecflags% -I..\include\ -I..\application\ -clock longlong -c ..\application\application.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -clock longlong -c ..\application\user_application.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -clock longlong -c ..\application\app_util.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\telnet_server.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\telnet_client.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\ftp_client.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\ftp_server.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\gen_ftp_client.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\gen_ftp_server.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\cbr_client.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\cbr_server.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\http_client.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -I..\transport\ -I..\transport\tcp\ -clock longlong -c ..\application\http_server.pc

call pcc %parsecflags% -I..\include\ -I..\application\ -clock longlong -c ..\application\bellmanford.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -clock longlong -c ..\application\fisheye.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -clock longlong -c ..\application\wrp.pc
call pcc %parsecflags% -I..\include\ -I..\application\ -clock longlong -c ..\application\static_routing.pc

call cl %cppflags% -MT -Zi -Za -nologo -I..\include\ -c ..\application\http_distribution.c /Fo..\application\http_distribution.obj

rem call pcc %parsecflags% -I..\include -I..\application -clock longlong -c ..\application\nsdsdv.pc 
rem call cl %cppflags% -MT -Zi -Za -nologo -I..\include -c ..\application\nsdsdvinterface.cpp /Fo..\application\nsdsdvinterface.obj
rem @pushd ..\application\nsdsdv
rem @cd
rem call cl %cppflags% -MT -Zi -Za -nologo -c dsdv.cpp rtable.cpp
rem @popd

:Link

del temp.lib driver.obj radio_range.obj 1>nul 2>nul
call lib /nologo /out:temp.lib ..\radio\*.obj ..\tcplib\*.obj ^
..\java_gui\*.obj ..\main\*.obj ..\network\*.obj ..\transport\*.obj ^
..\transport\tcp\*.obj ..\application\*.obj ..\application\nsdsdv\*obj ^
..\mac\*.obj

call pcc -user_main -Zi  %parsecflags% %linkflags% -I..\include\ -clock longlong ^
-o ..\bin\glomosim driver.pc temp.lib

call pcc -Zi %parsecflags% %linkflags% -I..\include\ -I..\radio\ -clock longlong ^
-o ..\bin\radio_range ..\radio\radiorange.pc temp.lib

del temp.lib 1>nul 2>nul

call cl %cppflags% -MT -Zi -Za -nologo ..\mac\tsma_code_gen.c /Fe..\bin\tsma_code_gen.exe
call cl %cppflags% -MT -Zi -Za -nologo ..\mac\tsma_param_gen.c /Fe..\bin\tsma_param_gen.exe
@del tsma_code_gen.obj tsma_param_gen.obj 1> nul 1> nul


:End
@endlocal




