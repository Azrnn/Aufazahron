#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
int LEDPin1=5;
int LEDPin2=4;

int LEDState2=0;
int buttonPin2=7;
int buttonNew2;
int buttonOld2=1;

int LEDState1=0;
int buttonPin1=6;
int buttonNew1;
int buttonOld1=1;


MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(LEDPin1,OUTPUT);
  pinMode(LEDPin2,OUTPUT);
  pinMode(buttonPin2,INPUT);
  pinMode(buttonPin1,INPUT);

}

void loop(){
  buttonNew2=digitalRead(buttonPin2); // pushbutton 2 used ON the LED2
if(buttonOld2==0 && buttonNew2==1){
  if(LEDState2==0){
 digitalWrite(LEDPin2,HIGH);
}}
buttonOld2=buttonNew2;

buttonNew1=digitalRead(buttonPin1);  // pushbutton 1 used ON the LED1
if(buttonOld1==0 && buttonNew1==1){
  if(LEDState1==0){
 digitalWrite(LEDPin1,HIGH);

}}
buttonOld1=buttonNew1;
  rfid1();
  rfid2();
}

int rfid1() {

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())   //Rfid program for tag1 only to OFF LED1
    return; 

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }

  strID.toUpperCase();
if (strID.indexOf("16:72:9A:12") >= 0) {
    Serial.println("********************");
    Serial.println("**Authorised acces for 1**");
    Serial.println("********************");
 digitalWrite(LEDPin1,LOW);
    }
}
int rfid2() {

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())          //Rfid program for tag2 only to OFF LED2
    return;

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }

  strID.toUpperCase();
if (strID.indexOf("EB:34:52:D3") >= 0) {
    Serial.println("********************");
    Serial.println("**Authorised acces for 2**");
    Serial.println("********************");
 digitalWrite(LEDPin2,LOW);
    }
}
