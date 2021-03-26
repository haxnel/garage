#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <DHT.h>
#include <AntaresESP8266HTTP.h>

// Konstruk object LCD dengan alamat I2C
// Ganti 0x3F sesuai dengan alamat I2C modul kalian
// Jika tidak tahu dapat menggunakan LCD I2C Scanner
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo;

// sediakan variabel untuk akses ke antares
#define ACCESSKEY "c0769d7e2f485191:1a356b543f0d7083"
#define projectName "Smartgarbage"
#define deviceName "HC-SR04"

// menambahkan SSID dan pass wifi
#define WIFISSID "Halo"
#define PASSWORD "@megatron12"

#define trigPin D8
#define echoPin D7
#define buzzer D4
#define dhtpin D5
#define DHTTYPE DHT11
//membuat sebuah object untuk DHT11
DHT dht(dhtpin, DHTTYPE);
//membuat sebuah object untuk antares
AntaresESP8266HTTP antares(ACCESSKEY);

void setup() {  
pinMode(trigPin, OUTPUT ); 
pinMode(echoPin, INPUT); 
servo.attach(D0); // sinyal yang diterima oleh servo berada pada pin D0
pinMode(buzzer, OUTPUT);
// Pemanggilan pertama memerlukan parameter jumlah kolom dan baris
lcd.begin(16,2);
lcd.init();
Serial.begin(115200); //untuk menentukan kecepatan pengiriman dan penerimaan data melalui port serial.
// Nyalakan backlight
lcd.backlight();
dht.begin(); //Nyalakan Sensor DHT11

WiFi.begin(WIFISSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
     { 
       delay(1000);
     }
  antares.setDebug(true); //Untuk informasi data yang terkirim
  antares.wifiConnection(WIFISSID, PASSWORD);
}
 
void loop(){
 //prosedur untuk mevariabelkan durasi dan jarak
int durasi, jarak;
digitalWrite(trigPin, LOW);
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin, LOW);
digitalWrite(buzzer, HIGH);
digitalWrite(buzzer, LOW);
// Mengukur pulse input di echo pin
durasi = pulseIn(echoPin, HIGH);
// Perhitungan jarak dimana setengah durasi dibagi 29.1 (dari datasheet)
jarak = (durasi/2) / 29.1;
Serial.print("Jarak=");
Serial.print(jarak);
Serial.println(" cm");

//membuat vartiabel untuk ditampilkan (dikirimkan) di antares
antares.add("Jarak: ", jarak);

// Jika jarak kurang dari 25 cm dan lebih sama dengan 0
if (jarak <= 25 && jarak >= 0) 
{
  servo.write(90);
      
} 
else 
{
  servo.write(0);
    
}
 delay(1000);
  
 //Pendeklerasian untuk Sensor Suhu Temperature
 float v = dht.readHumidity();
  float suhu = dht.readTemperature();
Serial.print("Suhu= ");
Serial.print(suhu);
Serial.println(" C");
Serial.print("Kelembapan= ");
Serial.print(v);
Serial.println(" %");
antares.add("Temperature: ", suhu);
antares.add("Kelembapan: ", v);

  if (v > 75){
    tone(buzzer, 2000);
    delay(1000);
    lcd.setCursor(1,0);
    lcd.print("-Tong Sampah-");
    lcd.setCursor(3,1);
    lcd.print("Lembab :(");
  }
  else if (v <= 75 ){
    noTone(buzzer);
    lcd.setCursor(0,0);
    lcd.print("Suhu= ");
    lcd.print(suhu);
    lcd.print(" C");
    lcd.setCursor(0,1);
    lcd.print("Lembab= ");
    lcd.print(v);
    lcd.print(" %");
  }

antares.send(projectName, deviceName);
delay(1000);
}
