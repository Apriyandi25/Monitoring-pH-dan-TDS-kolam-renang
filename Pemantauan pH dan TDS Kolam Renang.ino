
#include <OneWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

 
#define TDSPIN A1
#define PHPIN A0
#define BLYNK_PRINT Serial
#define ESP8266_BAUD 115200
#define EspSerial Serial

char auth[] = "HVhcQSCFGvXlb3-amwUoS4iAqBOpN0_E";
char ssid[] = "ayamjago";
char pass[] = "00000000";
float PH = 0.0 ;
float TDS ;
ESP8266 wifi(&EspSerial);


LiquidCrystal_I2C lcd(0x3F, 16, 2);

float temperature = 25;
float temp;
 
void setup()
{  
  lcd.init(); // 16 baris, 2 kolom
  lcd.backlight(); //menyalakan lampu latar
  lcd.setCursor(0,0);
  lcd.print("pH: ");
  lcd.setCursor(0,1);
  lcd.print("TDS: ");
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
}
 
void loop()
{
  TDS = analogRead(TDSPIN);
  TDS = (((TDS*(5.0/1024))*333.69)*1,02)+1,66;
  
  pH = analogRead(PHPIN);
  pH = (((pH*(5.0/1024))*3.39)*0.44)+3.96;
  
  

  lcd.setCursor(4,0);
  lcd.print(pH);
  lcd.setCursor(5,1);
  lcd.print(TDS, 2);
  Blynk.virtualWrite(V0, pH);
  Blynk.virtualWrite(V1, TDS);
  pH = 0.0;
  delay(5000);
}
