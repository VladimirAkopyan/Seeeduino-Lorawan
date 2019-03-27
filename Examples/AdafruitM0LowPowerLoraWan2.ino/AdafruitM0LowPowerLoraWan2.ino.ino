/*******************************************************************************
 * Copyright (c) 2015 Thomas Telkamp and Matthijs Kooijman
 * Adapted for Adafruit feather m0 LoRa by Stefan Huber
 *
 * Permission is hereby granted, free of charge, to anyone
 * obtaining a copy of this document and accompanying files,
 * to do whatever they want with them without any restriction,
 * including, but not limited to, copying, modification and redistribution.
 * NO WARRANTY OF ANY KIND IS PROVIDED.
 *
 * This example sends the actual battery voltage, using frequency and 
 * encryption settings matching those of the The Things Network.
 *
 * This uses OTAA (Over-the-air activation), where where a DevEUI and
 * application key is configured, which are used in an over-the-air
 * activation procedure where a DevAddr and session keys are
 * assigned/generated for use with all further communication.
 *
 * Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in
 * g1, 0.1% in g2), but not the TTN fair usage policy (which is probably
 * violated by this sketch when left running for longer)!
 * To use this sketch, first register your application and device with
 * the things network, to set or generate an AppEUI, DevEUI and AppKey.
 * Multiple devices can use the same AppEUI, but each device has its own
 * DevEUI and AppKey.
 *
 * Do not forget to define the radio type correctly in config.h.
 *
 *******************************************************************************/

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <avr/dtostrf.h>
#include <RTCZero.h>
#include <Adafruit_SleepyDog.h>
#include <I2CSoilMoistureSensor.h>
#include <Wire.h>
//#include <stdlib.h>

#define VBATPIN A7
#define I2C_PULLUP 12
#define SoilMoisutePower1 A0
#define SoilMoisutePower2 A1

/* Create an RTC object */
RTCZero rtc;

// This EUI must be in little-endian format, so least-significant-byte
// first. When copying an EUI from ttnctl output, this means to reverse
// the bytes. For TTN issued EUIs the last bytes should be 0xD5, 0xB3,
// 0x70.
static const u1_t PROGMEM APPEUI[8]={ 0x5E, 0x45, 0x00, 0xF0, 0x7E, 0xD5, 0xB3, 0x70 };
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}

// This should also be in little endian format, see above.
static const u1_t PROGMEM DEVEUI[8]={ 0x0C, 0x4F, 0xC2, 0x20, 0xAF, 0xAA, 0xF8, 0x00 };
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}

// This key should be in big endian format (or, since it is not really a
// number but a block of memory, endianness does not really apply). In
// practice, a key taken from ttnctl can be copied as-is.
// The key shown here is the semtech default key.
static const u1_t PROGMEM APPKEY[16] = { 0x0E, 0xD0, 0xE7, 0xCA, 0xEC, 0x8D, 0x04, 0x58, 0x3A, 0x67, 0xC1, 0xB2, 0xF2, 0x20, 0x94, 0xB4 };
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}


char mydata[16];
static osjob_t sendjob;

const unsigned int Interval_Transmit_Max = 40; //How long is a maximum transmission period -> any longer and the device will cancell what it's doign and sleep
const unsigned int Interval_Sleep = 60; //How long device will sleep for
const unsigned int Interval_SleepSingle = 10;  //How long is a single sleep period, they are kept small to avoid watchdog trigger
const unsigned int Interval_Watchdog = 16000; //How often watchdog kicks in, MILLISECONDS!

volatile bool timeToSleep = false; //Whether the time to sleep has come
volatile uint32_t lastSleep = 0; //When was the last time device slept? 

I2CSoilMoistureSensor sensor;

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = 8,  
    .rxtx = LMIC_UNUSED_PIN,
    .rst = LMIC_UNUSED_PIN,
    .dio = {3,6,LMIC_UNUSED_PIN},
};

void onEvent (ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    Serial.println();
    
    
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            Serial.println(F("EV_SCAN_TIMEOUT"));
            timeToSleep = true;
            break;            
        case EV_BEACON_FOUND:
            Serial.println(F("EV_BEACON_FOUND"));
            break;
        case EV_BEACON_MISSED:
            Serial.println(F("EV_BEACON_MISSED"));
            break;
        case EV_BEACON_TRACKED:
            Serial.println(F("EV_BEACON_TRACKED"));
            break;
        case EV_JOINING:
            Serial.println(F("EV_JOINING"));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED"));

            // Disable link check validation (automatically enabled
            // during join, but not supported by TTN at this time).
            LMIC_setLinkCheckMode(0);
            break;
        case EV_RFU1:
            Serial.println(F("EV_RFU1"));
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            timeToSleep = true; 
            break;
        case EV_REJOIN_FAILED:
            Serial.println(F("EV_REJOIN_FAILED"));
            break;
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            if (LMIC.txrxFlags & TXRX_ACK)
              Serial.println(F("Received ack"));
            if (LMIC.dataLen) {
              Serial.println(F("Received "));
              Serial.println(LMIC.dataLen);
              Serial.println(F(" bytes of payload"));
            }
            timeToSleep = true; 
            break;
        case EV_LOST_TSYNC:
            Serial.println(F("EV_LOST_TSYNC"));
            break;
        case EV_RESET:
            Serial.println(F("EV_RESET"));
            break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            Serial.println(F("EV_RXCOMPLETE"));
            break;
        case EV_LINK_DEAD:
            Serial.println(F("EV_LINK_DEAD"));
            break;
        case EV_LINK_ALIVE:
            Serial.println(F("EV_LINK_ALIVE"));
            break;
         default:
            Serial.println(F("Unknown event"));
            break;
    }
}

void readValues(unsigned char *vals) {
    // Payload format Bytes: [(Bat-Voltage - 2) * 100]
    double measuredvbat = analogRead(VBATPIN);
    measuredvbat *= 2;    // we divided by 2, so multiply back
    measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
    measuredvbat /= 1024; // convert to voltage
    Serial.print("VBat: " ); Serial.println(measuredvbat);
    measuredvbat -= 2; // offset by -2
    measuredvbat *= 100; //make it centi volts
    Serial.print("VBat in CVolts-2: " ); Serial.println(measuredvbat);
    vals[0] = (unsigned char)measuredvbat; //we're unsigned

    //uint capacitance = sensor.getCapacitance(); 
    //vals[1] = map(capacitance, 300, 800, 0, 255);

    //Serial.print(", Temperature: ");
    //Serial.println(sensor.getTemperature()/(float)10); //temperature register
}

void do_send(osjob_t* j){
    digitalWrite(SoilMoisutePower1, HIGH);
    digitalWrite(SoilMoisutePower2, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(I2C_PULLUP, HIGH);
    
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND, not sending"));
    } else {
        // Prepare upstream data transmission at the next possible time.
        unsigned char payload;
        readValues(&payload);
        LMIC_setTxData2(1, &payload, 1, 0);
        Serial.println(F("Packet queued"));
    }
    
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(SoilMoisutePower1, LOW);
    digitalWrite(SoilMoisutePower2, LOW);
    digitalWrite(I2C_PULLUP, LOW);
}


void setup() {
//Delay to make re-programming easier
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    
    delay(15000);
    //USBDevice.detach();
    Serial.begin(115200);
    while (! Serial) ;
    Serial.println("Starting"); 

    //Turn off unused pins
    pinMode(0, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A4, INPUT_PULLUP);
    pinMode(A5, INPUT_PULLUP);

    //Set pinds for powering soil sensor
    pinMode(SoilMoisutePower1, OUTPUT); //Power
    pinMode(SoilMoisutePower2, OUTPUT); //Power
    pinMode(I2C_PULLUP, OUTPUT); //I2C pullup

     //Initialise r
    rtc.begin();
    // Use rtc as a second timer instead of calendar
    rtc.setEpoch(0);
    rtc.enableAlarm(rtc.MATCH_YYMMDDHHMMSS);
        
    // LMIC init
    os_init();

    // Reset the MAC state. Session and pending data transfers will be discarded.
    
    LMIC_reset();
    LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100);
    
    lastSleep = rtc.getEpoch();
    //Watchdog.enable(Interval_Watchdog);
    
    // Start job (sending automatically starts OTAA too)
    os_setCallback(&sendjob, do_send); 
   
    // Show on device LED that we are ready
    digitalWrite(LED_BUILTIN, LOW);
    
}

void loop() {
    //Watchdog.reset();
    TransmissionTimeoutCheck();
    if(timeToSleep)
    {
        Serial.println("Time to sleep");
        timeToSleep = false;        

        int sleepTime = 0;
        while( sleepTime < Interval_Sleep)
        {
            //Watchdog.reset();
            rtc.setAlarmEpoch(rtc.getEpoch() + Interval_SleepSingle);
            rtc.standbyMode();    // Sleep until next alarm match
            sleepTime += Interval_SleepSingle;
            digitalWrite(LED_BUILTIN, HIGH);
            delay(50);
            digitalWrite(LED_BUILTIN, LOW);
        }      
        lastSleep = rtc.getEpoch();
        os_setCallback(&sendjob, do_send);            
    }
    os_runloop_once();
}

//Determines if the device was awake for too long and should stop what it's doing and go sleep immediately. 
void TransmissionTimeoutCheck(){
    uint32_t awakePeriod = rtc.getEpoch() - lastSleep;
    if(awakePeriod > Interval_Transmit_Max)
    {
       Serial.print("Exceeded send time, awake period is: ");
       Serial.println(awakePeriod);
       timeToSleep = true; 
       os_clearCallback(&sendjob);
    }
}
