echo -n "Shutting down auto-synchronization..."
dmod sync 2> /dev/null
echo done
rm /config/run/status/autosync > /dev/null
echo -n "down" > /config/run/status/autosync
