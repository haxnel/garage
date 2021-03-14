#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <DHT.h>
 
// Konstruk object LCD dengan alamat I2C
// Ganti 0x3F sesuai dengan alamat I2C modul kalian
// Jika tidak tahu dapat menggunakan LCD I2C Scanner
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo;
#define trigPin D8
#define echoPin D7
#define buzzer D4
#define dhtpin D5
#define DHTTYPE DHT11

DHT dht(dhtpin, DHTTYPE);

void setup() {
  
 pinMode(trigPin, OUTPUT ); 
pinMode(echoPin, INPUT); 
    servo.attach(D0); //pin D0
  
  pinMode(buzzer, OUTPUT);
  // Pemanggilan pertama memerlukan parameter jumlah kolom dan baris
  // Ini harus sama dengan yang dimasukan pada konstruktor.
  lcd.begin(16,2);
  lcd.init();
  // Nyalakan backlight
  lcd.backlight();
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
if (jarak <= 30 && jarak >= 0) 
{
  servo.write(90);
      
} 
else 
{
  servo.write(0);
    
}
 delay(1000);
  
 //Pendeklerasian untuk Sensor Suhu Temperature
  //Rumus untuk penghitungan suhu 
 float v = dht.readHumidity();
  float suhu = dht.readTemperature();
  
 lcd.setCursor(0,0);
 lcd.print("Suhu= ");
 lcd.print(suhu);
 lcd.print(" C   ");
 lcd.setCursor(0,1);
 lcd.print("Kelembapan= ");
 lcd.print(v);
 lcd.print(" %   ");
 Serial.println(v)
 delay(1000);
  
  if (v >= 75){
    tone(buzzer, 1000);
  }
  if (v <= 75 ){
    noTone(buzzer);
  }
  
}
