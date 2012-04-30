#echo -n Starting auto-synchronization...
lmod /sys/modules/sync
rm /config/run/status/autosync > /dev/null
echo -n "up" > /config/run/status/autosync
