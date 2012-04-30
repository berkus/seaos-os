# echo -n "Creating loopback devices..."
lmod /sys/modules/loop
echo -n "up" > /config/run/status/loop
