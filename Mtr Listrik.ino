//https://github.com/Aufazahron/MotorListrik
//Create By Azrn <3
byte sda = 10;
byte rst = 9;

#include<KRrfid.h>
#include<ezButton.h>

ezButton standar(4);

const int BUTTON_PIN=7;  // Connect the Button to pin 7 or change here
const int RELAY_PIN=3;
const int kontak=2;
const int slnida=5;
const int slnidb=6;

int relayState = LOW;     // tracks the current state of LED
int lastButtonState;    // the previous state of button
int currentButtonState;

void setup() {
  Serial.begin(9600);
  rfidBegin();
  standar.setDebounceTime(50);
  pinMode(slnida,OUTPUT);
  pinMode(slnidb,OUTPUT);
  pinMode(kontak,OUTPUT);
  digitalWrite(kontak, HIGH);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  lastButtonState    = currentButtonState;      // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state
  
  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The button is pressed");
  
    // toggle state of LED
    if(relayState == LOW)
       relayState = HIGH;
    else
      relayState = LOW;
  
    // control relay arccoding to the toggled state
    digitalWrite(RELAY_PIN, relayState); 
  }

  standar.loop();
  if (standar.isPressed())
    Serial.println("Standar Naik");
  if (standar.isReleased())
    Serial.println("Standar Turun");
    
  int stdr = standar.getState();
  if (stdr == LOW){
    
    getTAG();
    if (TAG=="118514517"){
      Serial.println("TAG : Kartu");
      TAG = "";
      
      if(digitalRead(kontak)==HIGH) {
      Serial.println("Raspberry Sys ON / Selenoid Narik");  
      digitalWrite(kontak,LOW);
      digitalWrite(slnida,LOW);
      digitalWrite(slnidb,HIGH);
      delay(1500);
      digitalWrite(slnidb,LOW);
      delay(1000);
    }
      else {
      Serial.println("Raspberry Sys OFF / Selenoid Dorong");
      digitalWrite(kontak,HIGH); 
      digitalWrite(slnidb,LOW);
      digitalWrite(slnida,HIGH);
      delay(1500);
      digitalWrite(slnida,LOW);
      delay(1000);
      
      Serial.println(" ");
      }
      //Serial.print("TAG : ");
      //Serial.println(TAG);  
    }
  }
}
