//yangın sensörü için değişkenler
int buzzer=19;
int alev_sensoru= A0;
boolean fl_sensorValue = 0;


//hareket sensörü için değişkenlerz
int     sensor      = 8;
boolean pir_sensorValue = 0;
int     tetik       = 7;

//dijital termometre için değişkenler
const int lm35 = A1;

float temp_sensorValue = 0;

#include <LiquidCrystal.h> //LCD için fonksiyon kütüphanesi
LiquidCrystal lcd(6,9,5,4,3,2);//LCD üzerinde kullanılanlarla nesne oluşturuldu(sırayla rs,e..)

//kilit sistemi

boolean control=1; 
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

  //yangın sensörü
  pinMode(buzzer,OUTPUT);
  delay(10);
  
  //hareket sensörü kurulumları
  pinMode(sensor,INPUT);
  pinMode(tetik,OUTPUT);
  delay(10);

  //dijital termometre kurulumları
  lcd.begin(16, 2);//16 karakterlik 2 satır LCD kullanılıyor. 
  pinMode(lm35,INPUT);

  //kilit sistemi kurulumları
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  setLocked (true);
  delay(10);

}

void loop() {
  
  //kilit sistemi
  if(control){
    Serial.println("PASSWORD:");
    control=0;
    setLocked(true);
  }
  char code=myKeypad.getKey();
  if(code!=NO_KEY){
      
    Serial.print("*");//keypress
    
    if(code==password[pozisyon]){
      pozisyon++;
      if(pozisyon==4){
        Serial.println("");
        Serial.println("HOSGELDINIZ");
        setLocked(false);
        delay(1000);
        pozisyon=0;
        control=1;
        Serial.println("");
     
      }
    }else{
      Serial.println("");
      Serial.println("HATALI");
      setLocked(true);
      pozisyon=0;
      control=1;
    }
  }

  //yangın alarmı için
  fl_sensorValue=digitalRead(alev_sensoru);
  
  if(fl_sensorValue){
    digitalWrite(buzzer,HIGH);
  }else{
    digitalWrite(buzzer,LOW);
  }
  
  //hareket sensörü için
  pir_sensorValue = digitalRead(sensor);

  if (pir_sensorValue == 1) {
    digitalWrite(tetik, HIGH);
  }else{
    digitalWrite(tetik, LOW);
  }


  //dijital termometre için
  
  temp_sensorValue=analogRead(lm35);
  float TempCel =temp_sensorValue*(500/1023.0);// Getting the celsius value from 10 bit analog value
  lcd.clear();
  lcd.home();
  lcd.print("sicaklik = ");
  lcd.setCursor(0,1);
  lcd.print(TempCel);
  lcd.print(" C");
  delay(100);
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
