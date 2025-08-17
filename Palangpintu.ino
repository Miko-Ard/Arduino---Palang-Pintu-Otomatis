/*******************************************************
Program  : ARDUINO dengan RFID MFRC-522
Chip     : Arduino Uno
********************************************************/

#include <Servo.h>
#include <SPI.h> 
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
Servo myservo;
MFRC522 mfrc522(SS_PIN, RST_PIN); 
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int TRIGPIN = 8;          
const int ECHOPIN = 6;
long timer;
int jarak;
const int pin_buzzer = 7;
int pin_led = 2;
int pos = 3;
 
void setup() 
{
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  myservo.attach(3);
  pinMode(pin_buzzer, OUTPUT);
  digitalWrite(pin_led, OUTPUT);
  lcd.begin(16,2);
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Dekatkan Tag RFID (Dapat berupa kartu atau gantungan kunci) ke RFID reader");
  Serial.println();

}
void loop() 
{
 Serial.print("Jarak = ");
  Serial.print(jarak);
  Serial.print(" cm");
  
  Serial.println();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dekatkan RFID");

 0000 digitalWrite(pin_led, LOW);
 
   if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    // Serial.print(mfrc522.uid.uidByte[i], HEX);
     //content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     //Serial.println(c                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               0      
  Serial.println(content);
    if(content=="38794a6"){   
      bunyiBuzzer(2);
      digitalWrite(pin_buzzer, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(content);
      lcd.setCursor(0, 1);
      lcd.print("SILAHKAN MASUK");
      digitalWrite(pin_led, HIGH);
      delay(100);
      noTone(pin_buzzer);
      delay(5000);
      digitalWrite(pin_led, LOW);

      //naikkan palang
      for(pos = 0; pos < 90; pos += 1)
      {
        myservo.write(pos);
        delay(50);
      }

      //hitung jarak
        digitalWrite(TRIGPIN, LOW);                   
        delayMicroseconds(2);
        digitalWrite(TRIGPIN, HIGH);                  
        delayMicroseconds(10);
        digitalWrite(TRIGPIN, LOW);

        timer = pulseIn(ECHOPIN, HIGH);
        jarak = timer/58;
        delay(1000);

          if (jarak < 15) {
            
        // Menutup pintu karena ada objek dalam jarak kurang dari 5 cm
        for (pos = 90; pos >= 1; pos -= 1) {
          myservo.write(pos);
          delay(50);
        }
  }
}
     if(content=="233fe210"){   
      bunyiBuzzer(2);
      digitalWrite(pin_buzzer, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(content);
      lcd.setCursor(0, 1);
      lcd.print("SILAHKAN MASUK");
      digitalWrite(pin_led, HIGH);
      delay(100);
      noTone(pin_buzzer);
      delay(2000);
      digitalWrite(pin_led, LOW);
            for(pos = 1; pos < 90; pos += 1) {
        myservo.write(pos);
        delay(50);
      }
        digitalWrite(TRIGPIN, LOW);                   
        delayMicroseconds(2);
        digitalWrite(TRIGPIN, HIGH);                  
        delayMicroseconds(10);
        digitalWrite(TRIGPIN, LOW);

        timer = pulseIn(ECHOPIN, HIGH);
        jarak = timer/58;
        delay(1000);

          if (jarak < 15) {
    // Menutup pintu karena ada objek dalam jarak kurang dari 5 cm

    for (pos = 90; pos >= 1; pos -= 1) {
      myservo.write(pos);
      delay(50);
    }
  }
}

    else{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("GaGAL MASUK");
    }
  Serial.println();
  delay(100);
} 

void bunyiBuzzer(int jumlahBunyi) 
{
  for (int i = 0; i < jumlahBunyi; i++) 
  {
    digitalWrite(pin_buzzer, HIGH);
    delay(100);
    digitalWrite(pin_buzzer, LOW);
    delay(100);
  }
}