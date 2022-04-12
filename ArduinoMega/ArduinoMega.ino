//hareket sensörü için değişkenler
int     sensor      = 8;
boolean sensorValue = 0;
int     tetik       = 7;

//dijital termometre için değişkenler
const int lm35 = A0;

float voltaj_deger = 0;
float sicaklik = 0;
int gelen_veri = 0;

#include <LiquidCrystal.h> //LCD için fonksiyon kütüphanesi
LiquidCrystal lcd(6,9,5,4,3,2);//LCD üzerinde kullanılanlarla nesne oluşturuldu(sırayla rs,e..)

void setup() {
  Serial.begin(9600);//seri haberleşmeyi başlatır.
  
  //hareket sensörü kurulumları
  pinMode(sensor,INPUT);
  pinMode(tetik,OUTPUT);
  Serial.println("Hareket sensörü çalışıyor..");
  delay(10);

  //dijital termometre kurulumları
  lcd.begin(16, 2);//16 karakterlik 2 satır LCD kullanılıyor. 
  pinMode(lm35, INPUT);

}

void loop() {
  
  //hareket sensörü için döngüler
  sensorValue = digitalRead(sensor);
  Serial.println("Sensor Value="+String(sensorValue));
  delay(100);

  if (sensorValue == 1) {
    digitalWrite(tetik, HIGH);
  }else{
    digitalWrite(tetik, LOW);
  }

  //dijital termometre için döngüler
  gelen_veri = analogRead(lm35);
  voltaj_deger = (gelen_veri / 1023.0) * 5000;
  sicaklik = voltaj_deger / 10.0;
  lcd.clear();
  lcd.home();
  lcd.print("sicaklik = ");
  lcd.setCursor(0, 1);
  lcd.print(sicaklik);
  lcd.print(" derece");
  delay(1000);



}
