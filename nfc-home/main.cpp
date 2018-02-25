#include <Arduino.h>
#include <MFRC522.h> // Include of the RC522 Library
#include <SPI.h> // Used for communication via SPI with the Module

#define SDAPIN 10 // RFID Module SDA Pin is connected to the UNO 10 Pin
#define RESETPIN 8 // RFID Module RST Pin is connected to the UNO 8 Pin

static const int LED_PIN = 5; // Pin 5 connected to DIN of RGB Stick
static const int BUZZER_PIN = 3; // Pin 3 connected to + pin of the Buzzer

byte foundTag; // Variable used to check if Tag was found
byte readTag; // Variable used to store anti-collision value to read Tag information
byte tagData[MAX_LEN]; // Variable used to store Full Tag Data
byte tagSerialNumber[4]; // Variable used to store only Tag Serial Number
byte goodTagSerialNumber[2][4] = {
    {0x88, 0x04, 0xDF, 0xDE},
    {0x08, 0xF8, 0x64, 0xE2}
    }; // The Tag Serial numbers we are looking for

int armSecurity(MFRC522& nfc)
{
    bool goodTag = false; // Variable used to confirm good Tag Detected

    // Check to see if a Tag was detected
    // If yes, then the variable foundTag will contain "MI_OK"
    foundTag = nfc.requestTag(MF1_REQIDL, tagData);
    delay(1);

    if (foundTag != MI_OK)
        return 0;

    // Get anti-collision value to properly read information from the Tag
    readTag = nfc.antiCollision(tagData);
    memcpy(tagSerialNumber, tagData, 4); // Write the Tag information in the tagSerialNumber variable

    // Check if detected Tag has the right Serial number we are looking for
    for(int i = 0; i < 4; i++)
    {
        if (goodTagSerialNumber[0][i] != tagSerialNumber[i]) {
            continue; // if not equal, then break out of the "for" loop
        }

        if (i == 3) { // if we made it to 4 loops then the Tag Serial numbers are matching
            goodTag = true;
        }
    }


    if (!goodTag)
        return 0;

    digitalWrite(LED_PIN, HIGH);
    digitalWrite (BUZZER_PIN, HIGH) ;// Buzzer On
    delay (1000) ;// Delay 1ms
    digitalWrite(LED_PIN, LOW);
    digitalWrite (BUZZER_PIN, LOW) ;// Buzzer Off

    Serial.print("<");
    
    for (int i = 0; i < 4; i++) 
    { // Loop to print serial number to serial monitor
        Serial.print(tagSerialNumber[i], HEX);
    }

    Serial.print(">");
    delay (5000) ;
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
    nfc.begin();

    byte version = nfc.getFirmwareVersion(); // Variable to store Firmware version of the Module

    // If can't find an RFID Module don't do anything
    if (!version) {
        while(1);
    }

    while(1)
        armSecurity(nfc);

}
