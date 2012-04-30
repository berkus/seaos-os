echo "Shutting down network..."
dmod rtl8139 2> /dev/null
dmod i825xx 2> /dev/null
dmod ipv4 2> /dev/null
dmod ethernet 2> /dev/null
rm /config/run/status/net > /dev/null
echo -n "down" > /config/run/status/net
