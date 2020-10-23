#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
char auth[] = "pFJ00bugBupd1ldDUjMbpCEwFM-tixyf";
char ssid[] = "lol";
char pass[] = "123456789";
#define DHTPIN 14 // mendefinisikan pin dht di nodemcu
#define DHTTYPE DHT11 // mendefinisikan tipe dht yang kita gunakan
DHT dht(DHTPIN, DHTTYPE); // setting pin dan tipe dht yang digunakan
BlynkTimer timer; // mendefinisikan timer dari blynk
void sendSensor() // fungsi untuk mengirimkan sensor
{

float h = dht.readHumidity(); // variabel untuk membaca kelembapan
float t = dht.readTemperature(); // variable untuk membaca suhu
if (isnan(h) || isnan(t)) { // kondisi bila suhu dan kelembapan tidak mengirimkan data
Serial.println("Failed to read from DHT sensor!");
return;
}
Blynk.virtualWrite(V1, t); // setting pin virtual suhu di aplikasi blynk
Blynk.virtualWrite(V2, h); // setting pin virtual kelembapan di aplikasi blynk
}
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
dht.begin(); // sensor dht mulai membaca data suhu dan kelembapan
timer.setInterval(1000L, sendSensor); // waktu untuk mengirimkan sensor setiap 1 detik
}
void loop()
{
Blynk.run();
timer.run();
}
