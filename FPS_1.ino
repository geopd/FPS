#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM800(7, 8); // gsm module connected here
String textForSMS;

int pirsensor = 2;
int alarm = A1;
int led = A2;

int calibrationTime = 5;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);        // Create MFRC522 instance.
 
void setup() {
        Serial.begin(9600);        // Nodemcu is connected over here
        randomSeed(analogRead(0));
        SIM800.begin(9600); // enter 9600 for sim800A
        delay(100);
        Serial.println("SYSTEM GETTING READY!");
        SPI.begin();                // Init SPI bus
        pinMode(pirsensor, INPUT); 
        pinMode(led, OUTPUT);
        pinMode(alarm, OUTPUT);
        digitalWrite(led, LOW); 
        digitalWrite(alarm, LOW);
        Serial.print("calibrating sensor ");
        for(int i = 0; i < calibrationTime; i++){
          Serial.print(".");
          delay(1000);
          }
          Serial.println(" done");
          Serial.println("SENSOR ACTIVE");
          delay(50);
        mfrc522.PCD_Init();        // Init MFRC522 card
        Serial.println("***SYSTEM READY***");
}
 
void loop() {
  

     MAIN:if ( digitalRead(pirsensor) == HIGH) {
      delay(2000);

        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        MFRC522::MIFARE_Key key;
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) {
          delay(2000);
              Serial.println("***INTRUDER ALERT***");
              digitalWrite(A1, HIGH);
              delay(500);
              digitalWrite(A1, LOW);
              delay(150);
              digitalWrite(A1, HIGH);
              delay(250);
              digitalWrite(A1,LOW);
              delay(150);
              digitalWrite(A1, HIGH);
              delay(500);
              digitalWrite(A1, LOW);
              delay(150);
              digitalWrite(A1, HIGH);
              delay(250);
              digitalWrite(A1,LOW);
              delay(150);
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2, LOW);
              delay(150);
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2,LOW);
              delay(150);
              sendSMS("INTRUDER ALERT");
              Serial.println("message sent."); 
              digitalWrite(A1, HIGH);
              delay(500);
              digitalWrite(A1, LOW);
              delay(150);
              digitalWrite(A1, HIGH);
              delay(250);
              digitalWrite(A1,LOW);
              delay(150);
              digitalWrite(A1, HIGH);
              delay(500);
              digitalWrite(A1, LOW);
              delay(150);
              digitalWrite(A1, HIGH);
              delay(250);
              digitalWrite(A1,LOW);
              delay(150);
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2, LOW);
              delay(150);
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2,LOW);
              delay(150);
        }
 
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) {
                return;
        }
        // Now a card is selected. The UID and SAK is in mfrc522.uid.
        
        // Dump UID
        Serial.print("Card UID:");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], DEC);
        } 
        Serial.println();
 
        // Dump PICC type
        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
        Serial.print("PICC type: ");
        Serial.println(mfrc522.PICC_GetTypeName(piccType));
        if (        piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_1K
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
                Serial.println("This sample only works with MIFARE Classic cards.");
                return;
        }
                
              if ( (mfrc522.uid.uidByte[0] == 153) && (mfrc522.uid.uidByte[1] == 112) && (mfrc522.uid.uidByte[2] == 129) && (mfrc522.uid.uidByte[3] == 156) ) {
              Serial.println("WORKER 1");
              digitalWrite(A1, HIGH);
              delay(150);
              digitalWrite(A1, LOW);
              delay(150);
              digitalWrite(A1, HIGH);
              delay(150);
              digitalWrite(A1,LOW);
              delay(150);
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2, LOW);
              delay(150);
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2,LOW);
              delay(150);
              sendSMS(" Worker 1 is present"); 
              Serial.println("message sent."); 
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2, LOW);
              delay(150);
              goto MAIN;
              }
              
              if ( (mfrc522.uid.uidByte[0] == 217) && (mfrc522.uid.uidByte[1] == 21) && (mfrc522.uid.uidByte[2] == 231) && (mfrc522.uid.uidByte[3] == 193) ) {
              Serial.println("WORKER 2");
              digitalWrite(A1, HIGH);
              delay(150);
              digitalWrite(A1, LOW);
              delay(150);
              digitalWrite(A1, HIGH);
              delay(150);
              digitalWrite(A1,LOW);
              delay(150);
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2, LOW);
              delay(150);
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2,LOW);
              delay(150);
              sendSMS(" Worker 2 is present"); 
              Serial.println("message sent."); 
              digitalWrite(A2, HIGH);
              delay(150);
              digitalWrite(A2, LOW);
              delay(150);
              goto MAIN;
              }
     }

        else if ( digitalRead(pirsensor) == LOW) 
        Serial.println("SECURE"); 
        delay(1000);
}

 
void sendSMS(String message)
{
  SIM800.print("AT+CMGF=1\r"); 
  delay(1000);
  SIM800.println("AT + CMGS = \"+91XXXXXXXXXX\"");
  delay(1000);
  SIM800.println(message); 
  delay(1000);
  SIM800.println((char)26); 
  delay(1000); 
  SIM800.println();
  delay(100); 
}
 
