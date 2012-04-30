#echo "Initializing random number generator..."
lmod /sys/modules/rand
ioctl /dev/rand 0 8
echo -n "up" > /config/run/status/rand
