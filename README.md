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
| Antenna Model  | Manufacturer | dBi| Type                    | Form | MHz                       |Contact |
| ---------------| ------------ | -- | ----------------------- | -----| ------------------------- | ------ |
| ANT-PCB8121-FL | Rf-Solutions | 2 ?|Omni Directional 1/2 Wave|  PCB | 800/900/1800/1900/2100    | iPex   |
| 105262-0003    | MoLex        | 0.2|                         |Sticky|  868/915                  | iPex   |
|ECHO14/200M/UFL | Siretta      |1.44| ----------------------- | PCB  |800/900/1800/1900/2100/2600| iPex   |
| ECHO1A         | Siretta      |-1.9|    ¼ wave dipole        | PCB  |800/900/1800/1900/2100/2600| iPex   |
| TANGO33        | Siretta      | 5  |                         |Whip  |850/900/1800/1900/2100     | SMA    |
| TANGO18        | Siretta      | 4  |1/2 wave omni directional|Whip  | 850/900/1800/1900/2100    | SMA    |
| TANGO45        | Siretta      | 2  |                         |Whip  |734-960/1710-2170/2300-2700| iPex   |
|ISPC.86A.09.0092E | Taoglas    | 5  |                         |Whip  | 868                       | MMCX   |
| True-MOX       | TrueRC       | 5.4|                         |PCB   | 868                       | SMA    |
| GP 868 C       | Sirio Antenne| 5.2| 1/4 λ + 1/2 λ colinear  | Pole | 868                       |N-female|
| OMNI 900       | Sirio Antenne| 6.0|                         | Pole | 868-960                   |SMA-male|
|650200599 GP    |Aurel Wireless| 2.1| Spiky Mast type         | Pole | 868                       | F-Type |
|                | RAK Wireless | 6.0| Fiberglass Antenna      | Pole | 433/570/868/915           | N Male |
|Barracuda OMB.868.05F21|Taoglas| 5  | Fiberglass Antenna      | Pole | 868                       |N Female|
|Barracuda OMB.868.08F21|Taoglas| 8  |Fiberglass Antenna       | Pole | 868                       |N Female|
|Barracuda OMB.868.B10F21|Taoglas| 10|Fiberglass Antenna       | Pole | 868                       |N Female|
|Barracuda OMB.868.B12F21|Taoglas| 12|Fiberglass Antenna       | Pole | 868                       |N Female|
