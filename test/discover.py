#!/usr/bin/python -tt

import logging
# disable warnings
logging.getLogger("scapy").setLevel(logging.ERROR)
logging.getLogger("scapy.loading").setLevel(logging.ERROR)
from scapy.all import conf,send,sniff,IP,UDP,Raw
from threading import Thread
from time import sleep

conf.verb = 0
conf.sniff_promisc = 0
conf.L2listen(iface="br0")

addp_port = 2362

addp = IP(dst="224.0.5.128")/UDP(sport=addp_port, dport=addp_port)
discover_request = addp/"DIGI\x00\x01\x00\x06\xff\xff\xff\xff\xff\xff"

def print_packet(x):
    #print x.display()

    switch(
            str(x[Raw])[5] ,

    return '{0}: type: {1}, raw:'.format(
            x.sprintf("%IP.src%:"),
            repr(x[Raw].load)
            )

class sniffer(Thread):
    def __init__ (self):
        Thread.__init__(self)

    def run(self):
        response = sniff(
                filter="udp and port " + str(addp_port),
                timeout=2,
                prn=lambda x: print_packet(x))

sniffer().start()
sleep(0.1)
send(discover_request)
