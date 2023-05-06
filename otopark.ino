#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcdekran(0x27,16,2);
Servo giris;

#define IRSensor 13
#define IRSensor2 12
int Buzzer=6;
int aracSayisi=0;

int Sensor = 0;
int Sensor2 = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(IRSensor, INPUT);
  pinMode(IRSensor2, INPUT);
  pinMode(Buzzer,OUTPUT);

  lcdekran.init();
  lcdekran.begin(16,2);
  lcdekran.setCursor(0,0);

  giris.attach(3);
}

void loop() {
  giris.write(0);
  delay(50);

  Sensor=digitalRead(IRSensor);
  Sensor2=digitalRead(IRSensor2);
  delay(50);

  Serial.println((String) "Sensör 1: " + Sensor);
  Serial.println((String) "Sensör 2: " + Sensor2);
  delay(50);

  lcdekran.setCursor(0,0);
  lcdekran.print(" ARAC SAYISI: ");
  lcdekran.print(aracSayisi);lcdekran.print(" ");
  delay(50);

  if (Sensor2 == 0 && aracSayisi>0)
  {
    aracSayisi=aracSayisi-1;
    giris.write(90);
    digitalWrite(Buzzer,HIGH);
      delay(500);
      digitalWrite(Buzzer,LOW);
      delay(500);
    lcdekran.setCursor (0, 1);
    lcdekran.print("  ARAC CIKTI  ");
    delay(2000);
    giris.write(0);
    lcdekran.clear();
  }

  if(Sensor==0  && aracSayisi<=4)
  {
     aracSayisi=aracSayisi+1;
     
     giris.write(90);
      digitalWrite(Buzzer,HIGH);
      delay(500);
      digitalWrite(Buzzer,LOW);
      delay(500);
     lcdekran.setCursor (0, 1);
     lcdekran.print("  ARAC GELDI  ");
      delay(1000);
     giris.write(0);
     lcdekran.clear();
   }
   else if(aracSayisi>=5)
   {
     lcdekran.setCursor (0, 1);
     lcdekran.print("  OTOPARK DOLU  ");
   }
 
    if(aracSayisi==0)
    {
      lcdekran.setCursor (0, 1);
      lcdekran.print("  OTOPARK BOS  ");
    }
  
}
