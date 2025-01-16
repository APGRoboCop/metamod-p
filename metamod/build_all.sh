#!/bin/sh

make OPT=opt-fast
make TARGET=amd64 OPT=opt-fast
make
make TARGET=amd64