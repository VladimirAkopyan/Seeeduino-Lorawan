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
