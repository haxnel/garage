//Pemanggilan library LCD dan Servo
#include <LiquidCrystal.h> 
#include <Servo.h>
 
//untuk urutannya RS, E, 4, 5, 6, 7
LiquidCrystal lcd(6, 7, 5, 4, 3, 2); //pin yang disambungkan antara arduino dengan LCD
 
//Instalasi servo
Servo servo;

int const trigPin = 12;
int const echoPin = 11;
int const buzzer = 10;

void setup()
  
{ 
  //prosedur untuk mengatur ke contrast-an LCD 16*2
  analogWrite(A1,50);
//prosedur pemanggilan fungsi LCD
lcd.begin(16, 2);//16 = Baris, 2 = kolom

  pinMode(trigPin, OUTPUT ); 
pinMode(echoPin, INPUT); 
    servo.attach(13);
  
  pinMode(buzzer, OUTPUT);
}
 
void loop(){
 //prosedur untuk mevariabelkan durasi dan jarak
     int durasi, jarak;
digitalWrite(trigPin, HIGH); 
digitalWrite(trigPin, LOW);
digitalWrite(buzzer, HIGH);
digitalWrite(buzzer, LOW);
// Mengukur pulsa input di echo pin
durasi = pulseIn(echoPin, HIGH);
// Perhitungan jarak dimana setengah durasi dibagi 29.1 (dari datasheet)
jarak = (durasi/2) / 29.1;
// Jika jarak kurang dari 35 cm dan lebih sama dengan 0
if (jarak <= 35 && jarak >= 0) 
{
  servo.write(90);
      
} 
else 
{
  servo.write(0);
    
}
 delay(1000);
  
 //Pendeklerasian untuk Sensor Suhu Temperature
 int data = analogRead(A0);
  //Rumus untuk penghitungan suhu 
 float v = (data / 1024.0) * 5.0;
  float suhu = (v - 0.5) * 100;
  
 lcd.setCursor(0,0);
 lcd.print("Suhu= ");
 lcd.print(suhu);
 lcd.print(" C   ");
 delay(1000);
  
  if (suhu <= 24){
    tone(buzzer, 1000);
  }
  if (suhu >= 24){
    noTone(buzzer);
  }
  
}
