#!/bin/bash
gcc client.c -ldbus-1 -I/usr/include/dbus-1.0 -o client
 gcc service.c -ldbus-1 -I/usr/include/dbus-1.0 -o service
