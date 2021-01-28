# ESP32 CastleLinkLive
A functional telemetry communication for getting live stats from your Castle ESC to your phone via two Heltec ESP32 LoRa modules.

>*_It should be noted that while this is functional it still has a list of things to do to fully round it out._*

### Things To Do
* Create android app for a beautiful dashboard
* Optimize code to get rid of +/- 20 RPM reporting
* Output the telemetry to the OLED as well
* Build into a library so that it can be used for other projects/boards
* Possibly act a a castle link for on the fly adjustments

### Whats Done
* Inverts the PWM signal from the receiver for the ESC to understand in Link Live mode
* Creates a buffer of the telemetry then sends it as one package over LoRa
* Receives data via LoRa and resends it over Bluetooth via Serial for your phone to see.
---
## Build it yourself
#### Required Parts
* https://www.amazon.com/gp/product/B086ZG25DZ/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1
* https://www.amazon.com/gp/product/B01HXU1NQY/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1 (only if your esc is supply high voltage to your receiver for high voltage servos)
* https://www.amazon.com/DIYmall-10PCS-Servo-Extension-Cable/dp/B016RJ8S42/ref=sr_1_3?dchild=1&keywords=servo+plugs&qid=1611800982&sr=8-3 (for splicing)
#### Circuit
Using this PDF Pinout https://resource.heltec.cn/download/WiFi_LoRa_32/WIFI_LoRa_32_V2.pdf
* Connect receiver signal to pin 12
* Connect esc signal to pin 13
* Connect GND to the ESP32, Receiver, and the 3v regulator if you are using it.
* Connect ESC Power to the Receiver and ESP32 5v pin if your are not running high voltage. Otherwise connect the ESC Power to the 3v regulator in and the ESP32 3v pin the 3v regulator out pin.
#### Upload the Code
* Install the Arduino IDE
* Follow this guide on adding support for ESP32 modules in the IDE https://heltec-automation-docs.readthedocs.io/en/latest/esp32/quick_start.html
* Castle_Link_Live_V1 goes to the sender which is the ESP32 module on the RC Car
* Telemetry_Receiver goes to the receiver which is the ESP32 module that should be by your phone
* Install this app on your phone to receive the telemetry on it https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en_US&gl=US
#### Putting it all Together
* Power both modules up and they should star working
* Go to your phones bluetooth setting and pair to "CastleLinkLive"
* Go into the Serial Bluetooth Terminal app and choose the "CastleLinkLive" device and hit connect
* If for some reason it's not working go ahead and hit the reset button on both ESP32 modules to restart them
