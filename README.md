# ESP8266 ESP01 Relay module fix

**Original  info**

5V or 12V WiFi relay module carried a ESP8266 WiFi module and microcontroller.
It will send the serial port instructions to the cell phone APP and Implementation within the local area network (LAN) for wireless control relay.

**Vendor materials**

Product site: [http://www.chinalctech.com/cpzx/1/332.html](http://www.chinalctech.com/cpzx/1/332.html) 
More tools and docs under [vendor materials](vendor_materials) directory

<img src='vendor_materials/orig_153P013S-1.jpg' alt="Orig Relay" width='30%'> <img src='vendor_materials/orig_153P02519-2.jpg ' alt="Orig Relay" width='30%'> 

# The issues

Realay **cannot switch** but the code running fine in esp8266 wifi module and GPIO send high signal

## Tha fix

**Test code**

[Arduino ino](test_code/esp01_relay_test.ino)  and [header with wifi login infor](test_code/relayExample_my_ssid_password.h)  all file available in ['test_code' ](test_code)  folder

* **The modified schematic** 
<img src='circuit_mod/ESP01_relay_fix.png' alt="Schematic" width="50%">

* **Modified circuit**
<img src='circuit_mod/ESP01_relay_fix_on_board.png' alt="Circuit board" width="50%">

# At work
<img src='circuit_mod/relay_on.jpg'  alt="Switch On" width="50%">

<img src='circuit_mod/relay_off.jpg'  alt="Switch On" width="50%">

* **Relay test video**

[<img src="circuit_mod/play.png" width="50%">](circuit_mod/relay_test.mp4  "Test")

*Modifcation by Charles K Barcza - <kbarcza@blackpantehr.hu>*
