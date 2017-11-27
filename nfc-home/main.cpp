/*
Project:	nfc-home
Board:
MCU:
FRENQUENCY:	16000000

Created using QtCreator
*/

#include <Arduino.h>
#include <MFRC522.h> // Include of the RC522 Library
#include <SPI.h> // Used for communication via SPI with the Module

#define SDAPIN 10 // RFID Module SDA Pin is connected to the UNO 10 Pin
#define RESETPIN 8 // RFID Module RST Pin is connected to the UNO 8 Pin

static const int LED_PIN = 5; // Pin 5 connected to DIN of RGB Stick
static const int BUZZER_PIN = 3; // Pin 3 connected to + pin of the Buzzer
static bool ARMED = false;

byte FoundTag; // Variable used to check if Tag was found
byte ReadTag; // Variable used to store anti-collision value to read Tag information
byte TagData[MAX_LEN]; // Variable used to store Full Tag Data
byte TagSerialNumber[5]; // Variable used to store only Tag Serial Number
byte GoodTagSerialNumber[2][5] = {
    {0x88, 0x04, 0xDF, 0xDE},
    {0x08, 0xF8, 0x64, 0xE2}
    }; // The Tag Serial number we are looking for

int armSecurity(MFRC522& nfc)
{
    bool GoodTag = false; // Variable used to confirm good Tag Detected

    // Check to see if a Tag was detected
    // If yes, then the variable FoundTag will contain "MI_OK"
    FoundTag = nfc.requestTag(MF1_REQIDL, TagData);
    delay(1);

    if (FoundTag != MI_OK)
        return 0;

    // Get anti-collision value to properly read information from the Tag
    ReadTag = nfc.antiCollision(TagData);
    memcpy(TagSerialNumber, TagData, 4); // Write the Tag information in the TagSerialNumber variable

    for (int i = 0; i < 4; i++) { // Loop to print serial number to serial monitor
        Serial.print(TagSerialNumber[i], HEX);
        Serial.print(", ");
    }

    // Check if detected Tag has the right Serial number we are looking for
    for(int i=0; i < 5; i++)
    {
        if (GoodTagSerialNumber[0][i] != TagSerialNumber[i]) {
            continue; // if not equal, then break out of the "for" loop
        }

        if (i == 3) { // if we made it to 4 loops then the Tag Serial numbers are matching
            GoodTag = true;
        }
    }


    if (!GoodTag)
        return 0;

    digitalWrite (BUZZER_PIN, HIGH) ;// Buzzer On
    delay (1000) ;// Delay 1ms
    digitalWrite (BUZZER_PIN, LOW) ;// Buzzer Off

    ARMED = !ARMED;

    if(ARMED)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }

    delay (5000) ;
    //send armed to rpi

    return 0;
}


int main() {
    init();

    MFRC522 nfc(SDAPIN, RESETPIN); // Init of the library using the UNO pins declared above

    pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin to an Output pin
    digitalWrite(BUZZER_PIN, LOW); // Buzzer Off at startup

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    SPI.begin();
    Serial.begin(115200);

    // Start to find an RFID Module
    Serial.println("Looking for RFID Reader");
    nfc.begin();
    byte version = nfc.getFirmwareVersion(); // Variable to store Firmware version of the Module

    // If can't find an RFID Module
    if (!version) {
        Serial.print("Didn't find RC522 board.");
        while(1); //Wait until a RFID Module is found
    }

    // If found, print the information about the RFID Module
    Serial.print("Found chip RC522 ");
    Serial.print("Firmware version: 0x");
    Serial.println(version, HEX);
    Serial.println();

    while(1)
        armSecurity(nfc);

}
