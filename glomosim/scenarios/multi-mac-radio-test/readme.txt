A very simple test case demonstrating the still 
very rough capability of multiple independent
radios with associated independent MAC layers.  

The following test merely creates 3 nodes: 0, 1 and 2
with two radio and two corresponding MAC layers.  See "config.in".
It uses static routes from the "routes.in" file to connect 0 and 1
using radio number 1 and 0 and 2 with radio number 2.  The
traffic in "app.conf" simply sets up ftp sessions between 
each node pair (both directions).


Multiple radio's and MAC layers are specified
in the configuration file with an "[]" array notation:

NODE-ADDRESS[0:0] RADIO-TYPE[0]       RADIO-ACCNOISE
NODE-ADDRESS[0:0] RADIO-FREQUENCY[0]  2.4e9

NODE-ADDRESS[0:0] RADIO-TYPE[1]       RADIO-ACCNOISE
NODE-ADDRESS[0:0] RADIO-FREQUENCY[1]  2.41e9

This specifies that there will be a
radio number (index) "0" and a radio number 1.
On node 0.


NODE-ADDRESS[1:1] RADIO-TYPE          RADIO-ACCNOISE
NODE-ADDRESS[1:1] RADIO-FREQUENCY     2.4e9

NODE-ADDRESS[2:2] RADIO-TYPE          RADIO-ACCNOISE
NODE-ADDRESS[2:2] RADIO-FREQUENCY     2.41e9

These lines specify that nodes 1 and 2 each have one radio
and the radio's frequencies.  Frequencies must
match for the radio to pick up the signal.

MAC-PROTOCOL    802.11
NODE-ADDRESS[0:0] MAC-PROTOCOL[0] 802.11
NODE-ADDRESS[0:0] MAC-PROTOCOL[1] 802.11

This specifies the default MAC layer protocol
is 802.11.  The second two lines allow the radio's
on node 0 to have different protocols.

Currently the only routing protocol that has been
modified to work with multiple radios is static routing.  An extra
optional "network interface number" field in the static routing file
specifies which radio (interface) to use for the next hop.  






