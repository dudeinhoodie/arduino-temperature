
//
// const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//
//void setup() {
//
//   lcd.begin(16, 2);
//   lcd.print("hello");
//
//  // lcd.setCursor(0,1);
//
//  // lcd.write("LIGHT: ");
//
//}
//
//void loop() {
//  //lcd.setCursor(0, 1);
//  //lcd.print(millis() / 1000);
//}
//

#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));

    lcd.begin(16, 2);

    bool status;
    
    // default settings
    status = bme.begin();
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 1000;

    Serial.println();

    delay(100); // let sensor boot up
}


void loop() { 
    printValues();
    delay(delayTime);
}


void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    lcd.setCursor(0, 0);
    lcd.print("Humidity = ");
    lcd.print(bme.readHumidity());
    lcd.print(" %");

    lcd.setCursor(0, 1);
    lcd.print("Temp = ");
    lcd.print(bme.readTemperature());
    lcd.print(" *C");


    Serial.println();
}
