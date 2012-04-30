#!/bin/sh
#sudo /sbin/losetup /dev/loop0 hd.img
#sudo mount -t ext2 /dev/loop0 /mnt
sudo mount -text2 -oloop=/dev/loop1,offset=1048576 hd.img /mnt
