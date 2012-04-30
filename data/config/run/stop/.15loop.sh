echo -n Shutting down loopback devices...
dmod loop
rm /config/run/status/loop > /dev/null
echo -n "down" > /config/run/status/loop
echo done
