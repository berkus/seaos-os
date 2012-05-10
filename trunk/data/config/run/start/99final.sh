login </dev/tty2 >/dev/tty2 2>/dev/tty2 &
mon </dev/tty8 >/dev/tty8 2>/dev/tty8 &

if [ -e /tmp ]; then
	chmod a+w /tmp
else
	mkdir /tmp
	chmod a+w /tmp
fi
echo -n "down" > /config/run/status/autosync &
echo -n "down" > /config/run/status/net &
lmod /sys/modules/loop /sys/modules/rand
if [ -e /dev/rand ]; then
	ioctl /dev/rand 0 8 &
fi
echo -n "up" > /config/run/status/rand &
echo -n "up" > /config/run/status/loop &
