#!/bin/bash
gcc client.cpp -ldbus-1 -I/usr/include/dbus-1.0 -o client
gcc service.cpp -ldbus-1 -I/usr/include/dbus-1.0 -o service
