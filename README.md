# OSOYOO GROUND ROBOT

## gnd_firmware ##
### Connect hc02 bluetooth module to laptop serial monitor ###
Usually, the bot is configured with Hc02 as a virutal serial, which means that hc02's tx/rx are hardwired to the arduino's tx/rx. Note: this configuration as a virtual serial can be changed by moving the 'UART select' pin headers on the shield; the bot will probably be configured as a virtual serial rather than not.

**Arduino uses these same pins to upload code, so always unplug the hc02 module before uploading**, then replug the hc02 into the board.
<br>
<br>
<br>
**Linux:**

**1. Launch bluetoothctl**

bluetoothctl is just the default command-line utility for managing bluetooth connections on Linux. 
```bash
bluetoothctl
```

**2. Discover/pair hc02**

power on just turns on your computer's bluetooth; scan on sets your computer's bluetooth into scan mode to find discoverable devices. You will see the MAC address of the hc02 module pop up eventually; if not, then reset the arduino to force the hc02 to scan for connectable devices.
```bash
power on
scan on
```

Once your see the mac address of the hc02,
```bash
scan off
pair 00:0C:BF:13:51:3D
# enter PIN: 1234
trust 00:0C:BF:13:51:3D
exit
```
The mac address above is not the same as your module unless you're using the same exact one. Obtain the mac address of the hc02 before doing this. The default pin for all hc02 modules is '1234'

**3. Bind the module to a serial port**

Since the module is configured as a virtual serial, your computer will treat it as a normal serial port, but now you need to 'bind' it to any of your ports.
```bash
sudo rfcomm bind 0 00:0C:BF:13:51:3D
```
Done, now the port is ready to be used as a serial in vscode or anything else.
