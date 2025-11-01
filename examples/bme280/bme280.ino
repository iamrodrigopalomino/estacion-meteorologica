#include <Wire.h>  
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL

  Serial.println("Iniciando BME280...");

  if (!bme.begin(0x76)) {  
    Serial.println("No se encontró BME280");
    while (1);
  }

  Serial.println("BME280 Detectado");
}

void loop() {
  Serial.print("Temp: ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Humedad: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Presion: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.println("----");
  delay(1000);
}