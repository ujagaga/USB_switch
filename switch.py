#!/usr/bin/env python3

import socket
import time
import sys

WEB_PORT = 60010
USB_PORT = 0

if len(sys.argv) > 1:
    try:
        USB_PORT = int(sys.argv[1])
    except Exception as e:
        sys.exit("ERROR: {}. Please specify the USB port to use (0 or 1)".format(e))

message = "20{}".format(USB_PORT).encode('utf-8')

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
server.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

# UDP is not guaranteed to arrive so broadcast few times
server.sendto(message, ("192.168.0.255", WEB_PORT))
time.sleep(0.1)
server.sendto(message, ("192.168.0.255", WEB_PORT))

print("Sent: {}".format(message), flush=True)

server.close()
