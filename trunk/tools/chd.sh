#!/bin/sh
sudo /sbin/losetup -d /dev/loop1 2> /dev/null
sudo umount /mnt 2> /dev/null

rm hd.img 2>/dev/null
echo -n "processing hd.img..."
dd if=/dev/zero of=hd.img bs=1024 count=1 2> /dev/null
dd if=/dev/zero of=hd.img bs=1024 count=1 seek=999999 2> /dev/null
echo -n "partition..."
(echo -e "o\nn\np\n1\n2048\n\na\n1\nw\n" | fdisk -u -S63 -H16 hd.img) > /dev/null 2>/dev/null

sudo /sbin/losetup -o1048576 /dev/loop1 hd.img
echo -n "format..."
sudo mke2fs -q -I128 -b1024 /dev/loop1  > /dev/null
echo -n "install grub..."
sudo mount /dev/loop1 /mnt-seaos
sudo mkdir -p /mnt-seaos/boot/grub
sudo cp -r data/boot/grub/* /mnt-seaos/boot/grub/
sudo umount /mnt-seaos

sudo /sbin/losetup -d /dev/loop1
sudo /sbin/losetup /dev/loop1 hd.img

(echo -e "device (hd0) /dev/loop1\nroot (hd0,0)\nembed /boot/grub/e2fs_stage1_5 (hd0)\ninstall --stage2=data/boot/grub/stage2 /boot/grub/stage1 (hd0) (hd0)1+17 p (hd0,0)/boot/grub/stage2 /boot/grub/menu.lst\nquit" | grub --device-map data/boot/grub/device.map --batch) > /dev/null
sudo /sbin/losetup -d /dev/loop1
echo ok
echo processing hd2.img..
dd if=/dev/zero of=hd2.img bs=1024 count=1 2> /dev/null
dd if=/dev/zero of=hd2.img bs=1024 count=1 seek=100000 2> /dev/null
yes | (sudo /sbin/mke2fs -q -I128 -b1024 hd2.img) > /dev/null
echo copying data/ to hd.img...
sh ./tools/open_hdimage.sh
sudo cp -f -r data/* /mnt-seaos/
sudo cp -f -r doc/man/* /mnt-seaos/usr/man/
echo copying apps/data/ to hd.img...
sudo cp -f -r apps/data/* /mnt-seaos/
sudo rm -rf `sudo find /mnt-seaos -name .svn`
sudo rm -f `sudo find /mnt-seaos -name .directory`
sudo rm -rf `sudo find /mnt-seaos -name man`
echo copying documentation to hd.img...
sudo mkdir -p /mnt-seaos/usr/man
sudo cp -rf tools/man_gen_tmp/text/* /mnt-seaos/usr/man/
sh ./tools/close_hdimage.sh
