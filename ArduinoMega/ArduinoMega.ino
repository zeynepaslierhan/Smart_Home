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

//kilit sistemi
#include <Keypad.h>//keypad için fonksiyon kütüphanesi
const byte rows = 4;//keypad'in sütun ve satır sayıları
const byte cols = 3;
char keyMap[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins [rows] = {13,12,11,10}; //pins of the keypad
byte colPins [cols] = {14, 15, 16};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);

#define redLED 21 //Ledlerin pinleri tanımlanır
#define greenLED 20

char* password ="1234"; //varsayılan şifre
int pozisyon = 0;//keypad için başlangıç

void setup() {
  Serial.begin(9600);//seri haberleşmeyi başlatır.
  
  //hareket sensörü kurulumları
  pinMode(sensor,INPUT);
  pinMode(tetik,OUTPUT);
  delay(10);

  //dijital termometre kurulumları
  lcd.begin(16, 2);//16 karakterlik 2 satır LCD kullanılıyor. 
  pinMode(lm35, INPUT);

  //kilit sistemi kurulumları
  lcd.begin(16, 2);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  setLocked (true);

}

void loop() {
  
  //kilit sistemi için
  Serial.println("HOSGELDINIZ");
  Serial.println("SIFRE GIRINIZ:");
  
  while(pozisyon!=4){
        
      char whichKey = myKeypad.getKey(); //define which key is pressed with getKey
      
      if(whichKey =='*'||whichKey=='#'){//define invalid keys
        pozisyon=0;
        setLocked(true);
        Serial.println("HATALI!");
        delay(1000);
        break;
      }
      if(whichKey==password[pozisyon]){
        pozisyon++;
      }
      if(pozisyon == 4){
        setLocked (false);
        Serial.println("*** Verified ***");
        delay(3000);
        Serial.println("Zeynep ile Hazar");
        Serial.println("Kapi Acildi");
        delay(7000);
      }else{
        setLocked(true);
        Serial.println("HATALI!");
       }
       delay(1000);
  }

  
  //hareket sensörü için
  sensorValue = digitalRead(sensor);
  delay(100);

  if (sensorValue == 1) {
    digitalWrite(tetik, HIGH);
  }else{
    digitalWrite(tetik, LOW);
  }

  //dijital termometre için
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

//kilit sistemi için kilit fonksiyonu
void setLocked(int locked){
  if(locked){
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    }
    else{
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
    }
  }
