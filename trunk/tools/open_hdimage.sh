#!/bin/sh
#sudo /sbin/losetup /dev/loop0 hd.img
#sudo mount -t ext2 /dev/loop0 /mnt-seaos
loop=`losetup -f`
echo -n "$loop" > .loop
sudo mount -text2 -oloop=$loop,offset=1048576 hd.img
