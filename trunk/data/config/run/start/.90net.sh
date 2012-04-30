#echo Initializing network...
lmod /sys/modules/rtl8139
lmod /sys/modules/i825xx
lmod /sys/modules/ipv4
rm /config/run/status/net > /dev/null
echo -n "up" > /config/run/status/net
