# ULP - LoraWan
This repo has examples and setup for off-the-shelf boards that support Ultra Low Power (< 1 ma)

| Board                           | sleep mA  | Cost| CPU   |  Comments | 
| ------------------------------- | ---- | ----|-------| --------- |
| Seeeduino-Lorawan               | 100  | £37 |SAMD21 | GPS, separate prosessor for Lora in module RHF76-052 | 
| Adafruit Feather M0 LoRa (RFM95)| 400  | £27 |SAMD21 | Soldering required to get Lora and I2C to work       | 

## Seeeduino-Lorawan
Firmware and example code to get LoraWan to work


| Name                                                | Version                  | Link                                                  | 
| ------------------------------------------  | ----------------------- | -------------------------------------------------------------  |
|  Arduino   IDE                                  |            1.8.8            |                                                        |
| Seeed SAMD Boards  definition   |           1.3                 |                                                                                      |
|  Lora Library                                     |           N/A               | [InRepo,](/ExtraPuTTY) [Original](http://www.extraputty.com/)  |
| ExtraPuTTY                                       |        v0.29-RC2       | [InRepo](/LoraLibrary) [Original](https://github.com/toddkrein/OTAA-LoRaWAN-Seeed)   | 
| RHF76-052 firmware                      |          2.1.19            | [InRepo](/Firmware_RHF76-052/rhf76-052am-v2.1.19-20180525.ebin.bin) |
| TinyGPS++                                        | ???                           |                                                                                       |

## Adafruit Feather M0 LoRa
### Soldering 


## Low-Power
http://www.rocketscream.com/blog/docs-item/using-mini-ultra-pro-with-the-things-network-ttn/#tab-id-8
https://www.mysensors.org/apidocs/group__RFM95grp.html#gga58a50f630651a28661637aa416c58d90a8ffa5b5410e8dd723486d70c8fad986d
https://mariozwiers.de/2018/04/04/arduino-lmic-library-with-low-power-mode/


## Libraries
https://github.com/rocketscream/Low-Power

## Antenas 
| Antenna Model  | Link | Gain | Type  | Form | Bands | Connector |
| ---------------| ---- | ---- | ----- | -----|-------| ----------|
| ANT-PCB8121-FL |[link](https://uk.farnell.com/webapp/wcs/stores/servlet/ProductDisplay?catalogId=15001&langId=44&productSeoURL=rf-solutions&storeId=10151&partNumber=2133450&krypto=8Y%2BQ3CEGuS1osvCczkwFp4hRPmKmItLCfFJZZ8ThPtn6PuD5q%2BOL7DZnbWIQkMDXgAy%2FLvuFS6WkbR9W0neNEQ%3D%3D&ddkey=https%3Aen-GB%2FElement14_United_Kingdom%2Frf-solutions%2Fant-pcb8121-fl%2Fant-pcb-gsm-pentaband-81x21-coax%2Fdp%2F2133450) | 2 Db | Omni Directional 1/2 Wave|  PCB | 800/900/1800/1900/2100MHz| iPex |

