//LIBRERIAS USADAS EN EL PROYECTO
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

//CREACION DE OBJETO TIPO SENSOR
#define DHTTYPE DHT22
DHT dht(D5,DHTTYPE);

//CREACION DE OBJETO TIPO PANTALLA LCD
LiquidCrystal_I2C lcd(0x3f,16,2);

int screenWidth = 16;
int screenHeigth = 16;
String TXT = "TEMPERATURA Y HUMEDAD ACTUAL";
int stringStart, stringStop = 0;
int scrollCursor = screenWidth;

//CARACTERES ESPECIALES
byte t[8] = { B00100, B01010, B01010, B01110, B01110, B11111, B11111, B01110 };
byte c[8] = { B11000, B11000, B00000, B00111, B01000, B01000, B01000, B00111 };
byte h[8] = { B10101, B01010, B10101, B01010, B10101, B01010, B00000, B11111 };




void setup() {

  //INICIALIZAR SENSOR
  dht.begin();
  //INICIALIZAR PUERTOS PARA PROTOCOLO I2C
  Wire.begin();
  //INICIALIZAR PANTALLA LCD
  lcd.begin();
  //ENCENDER PANTALLA LCD
  lcd.backlight();
  //CREACION DE CARACTERES ESPECIALES 
  lcd.createChar(0,t);
  lcd.createChar(1,c);
  lcd.createChar(2,h);
}
void loop() {
  

 
//SCROLL DEL TEXTO LINEA 1
  lcd.setCursor(scrollCursor, 0);
  lcd.print(TXT.substring(stringStart, stringStop));

  delay(200);
  lcd.clear();

  if(stringStart == 0 && scrollCursor > 0){
    scrollCursor--;
    stringStop++;
  }
  else if (stringStart == stringStop) {
    stringStart = stringStop = 0;
    scrollCursor = screenWidth;
  }
  else if (stringStop == TXT.length() && scrollCursor == 0){
    stringStart++;
  }
  else {
    stringStart++;
    stringStop++;
  }

 //LECTURAS DE TEMPERATURA

    float dhtHumidity = dht.readHumidity();
    float dhtTempC = dht.readTemperature();

//MOSTRAR INFORMACION EN PANTALLA LCD
    lcd.setCursor(0,1);
    //lcd.print(" " + (String)dhtHumidity);
    lcd.print(" " + (String)dhtTempC + "    " + (String)dhtHumidity + "%");

    lcd.setCursor(0,1);
    lcd.write(byte(0));

    lcd.setCursor(6,1);
    lcd.write(byte(1));

    lcd.setCursor(9,1);
    lcd.write(byte(2));

    
    
  
}

  
  
