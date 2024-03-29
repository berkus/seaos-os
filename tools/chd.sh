#!/bin/sh
loop=`cat .loop`

rm hd.img 2>/dev/null
echo -n "processing hd.img..."
dd if=/dev/zero of=hd.img bs=1024 count=1 2> /dev/null
dd if=/dev/zero of=hd.img bs=1024 count=1 seek=999999 2> /dev/null
echo -n "partition..."
(echo "o\nn\np\n1\n2048\n\na\n1\nw\n" | fdisk -u -S63 -H16 hd.img) &>/dev/null

losetup -o1048576 $loop hd.img
echo -n "format..."
mke2fs -q -I128 -b1024 $loop  > /dev/null
losetup -d $loop

echo -n "install grub..."
sh ./tools/open_hdimage.sh
mkdir -p ./mnt/boot/grub
cp -r data/boot/grub/* ./mnt/boot/grub/
sh ./tools/close_hdimage.sh

(echo "device (hd0) hd.img\nroot (hd0,0)\nembed /boot/grub/e2fs_stage1_5 (hd0)\ninstall --stage2=data/boot/grub/stage2 /boot/grub/stage1 (hd0) (hd0)1+17 p (hd0,0)/boot/grub/stage2 /boot/grub/menu.lst\nquit" | grub --device-map data/boot/grub/device.map --batch) > /dev/null

echo ok
echo processing hd2.img..
dd if=/dev/zero of=hd2.img bs=1024 count=1 2> /dev/null
dd if=/dev/zero of=hd2.img bs=1024 count=1 seek=100000 2> /dev/null
yes | (/sbin/mke2fs -q -I128 -b1024 hd2.img) > /dev/null
sh ./tools/open_hdimage.sh
echo copying apps/data/ to hd.img...
cp -f -r apps/data/* ./mnt
rm -rf `find ./mnt -name man`
echo copying data/ to hd.img...
cp -f -r data/* ./mnt/
mkdir -p ./mnt/usr/man
cp -rf tools/man_gen_tmp/text/* ./mnt/usr/man/
echo copying source code to hd.img...
mkdir -p ./mnt/usr/src
cp -rf system ./mnt/usr/src/sea
cp -rf apps/seaos-util ./mnt/usr/src/seaos-util
make -C ./mnt/usr/src/sea clean
rm ./mnt/usr/src/sea/tools/confed ./mnt/usr/src/sea/tools/mkird
rm -rf `find ./mnt -name .svn`
rm -f `find ./mnt -name .directory`

sh ./tools/close_hdimage.sh
