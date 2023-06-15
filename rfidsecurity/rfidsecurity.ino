//ESP8266 Blynk RFID Security Access Control System
#define BLYNK_TEMPLATE_ID           "TMPLm-8Y738Y"
#define BLYNK_DEVICE_NAME           "rfid system"
#define BLYNK_AUTH_TOKEN            "bqOepV_YExbb9G7MPdOLyvpFpjaREAOz"
#include <SPI.h>
#include <MFRC522.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define SS_PIN 4  // sda
#define RST_PIN 2
Servo myservo;
int pos=180;    
 
MFRC522 mfrc522(RST_PIN, SS_PIN);        // Create MFRC522 instance.
char auth[] = BLYNK_AUTH_TOKEN;    //Blynk Authentication Token -- sent via Email from Blynk
char ssid[] = "Jyothsna";   //Enter WiFi Name
char pass[] = "neethi1728";   //Enter Wifi Password
 
SimpleTimer timer;
int fflag = 0; 
int eflag = 0; 
int jflag = 0; 
WidgetTerminal terminal(V2);
 
void setup() {
        Serial.begin(9600);        // Initialize serial communications with the PC
        Blynk.begin(auth, ssid, pass);
        myservo.attach(16);
        SPI.begin();                // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
        //Serial.println("Scan a MIFARE Classic PICC to demonstrate Value Blocks.");
        //timer.setInterval(1000L, iot_rfid);
}
 
void loop() {
        
  //timer.run(); // Initiates SimpleTimer
  Blynk.run();
  iot_rfid();
       
}
void openServo() {
  Serial.println("Opening Gates");
  for(pos=180;pos>=-180;pos--){   
  myservo.write(pos);
  }
}
void closeServo() {
  Serial.println("Closing Gates");
  for (pos = -180; pos <= 180; pos++) { 
  myservo.write(pos);
  
  }
}
 
void iot_rfid()
{
        MFRC522::MIFARE_Key key;
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) {
                return;
        }
 
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) {
                return;
        }        
        // Dump UID
        Serial.print("Card UID:");
        String content= "";
        byte letter;
        for (byte i = 0; i < mfrc522.uid.size; i++) {
               Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
               Serial.print(mfrc522.uid.uidByte[i], HEX);
               content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
               content.concat(String(mfrc522.uid.uidByte[i], HEX));
        } 
        Serial.println();
 
        // Dump PICC type
        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    //    Serial.print("PICC type: ");
//Serial.println(mfrc522.PICC_GetTypeName(piccType));
        if (        piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_1K
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
                //Serial.println("This sample only works with MIFARE Classic cards.");
                return;
        }
        content.toUpperCase();
        if ((content.substring(1) == "CC FD EF 38") && (fflag == 1))
        {
         Serial.println("Authorized access");
         Serial.println("John");   
         Blynk.virtualWrite(V2, "John" );   
         openServo();
         delay(2000);
         closeServo();
         Serial.println();
         delay(3000);
        }
        else if((content.substring(1) == "7A EC 09 B2") && (eflag == 1))
        {
         Serial.println("Authorized access");
         Serial.println("Mary");   //Enter User1 Name
         Blynk.virtualWrite(V2, "Mary" );   //Enter User1 Name
         openServo();
         delay(2000);
         closeServo();
         Serial.println();
         delay(3000);
        }
        else if((content.substring(1) == "D3 A5 C5 A9") && (jflag == 1))
        {
         Serial.println("Authorized access");
         Serial.println("Tom");   
         Blynk.virtualWrite(V2, "Tom" );   
         openServo();
         delay(2000);
         closeServo();
         Serial.println();
         delay(3000);
        }
        else 
          {
          Serial.println("Not authorized");
          if ((fflag == 0) && (eflag == 0) && (jflag == 0)){
            Serial.println("Admin has disabled access...");
          }
          else if ((fflag == 0) && (eflag == 0) && (jflag == 1)){
            Serial.println("Admin has disabled access...");
          }
          else if ((fflag == 0) && (eflag == 1) && (jflag == 0)){
            Serial.println("Admin has disabled access...");
          }
          else if ((fflag == 0) && (eflag == 1) && (jflag == 1)){
            Serial.println("Admin has disabled access...");
          }
          else if ((fflag == 1) && (eflag == 0) && (jflag == 0)){
            Serial.println("Admin has disabled access...");
          }
          else if ((fflag == 1) && (eflag == 0) && (jflag == 1)){
            Serial.println("Admin has disabled access...");
          }
          else if ((fflag == 1) && (eflag == 1) && (jflag == 0)){
            Serial.println("Admin has disabled access...");
          }
          else {
            Serial.println("RFID not Authorized...");
          }
         
          }
        // Enter RFID Tag ID here 
        /*
        if( ((mfrc522.uid.uidByte[0] == CC) && (mfrc522.uid.uidByte[1] == FD) && (mfrc522.uid.uidByte[2] == EF) && (mfrc522.uid.uidByte[3] == 38)) && (fflag == 1) )
        {
         Serial.println("John's Car");   
         Blynk.virtualWrite(V2, "John" );   
         openServo();
         delay(5000);
         closeServo();
        }
  
        else
        if(( (mfrc522.uid.uidByte[0] == D3) && (mfrc522.uid.uidByte[1] == A5) && (mfrc522.uid.uidByte[2] == C5) && (mfrc522.uid.uidByte[3] == A9))&& (eflag == 1) )
        {
         Serial.println("Mary's Car");    
         Blynk.virtualWrite(V2, "Mary" );   
         openServo();
         delay(5000);
         closeServo();
        }
        else
        if( ((mfrc522.uid.uidByte[0] == 21) && (mfrc522.uid.uidByte[1] == 22) && (mfrc522.uid.uidByte[2] == 23) && (mfrc522.uid.uidByte[3] == 24))&& (jflag == 1) )
        {
         Serial.println("Tom's Car");   
         Blynk.virtualWrite(V2, "Tom" );   
         openServo();
         delay(5000);
         closeServo(); 
        }
 
        else 
        Serial.println("Unregistered User");
 */
}

BLYNK_WRITE(V3)
{
   fflag = param.asInt(); 
 
}
 
 
// in Blynk app writes values to the Virtual Pin 4
BLYNK_WRITE(V4)
{
   eflag = param.asInt(); 
}
 
BLYNK_WRITE(V5)
{
   jflag = param.asInt(); 
}
