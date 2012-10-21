#!/bin/sh

sudo umount `cat .loop` 2> /dev/null
rm .loop
