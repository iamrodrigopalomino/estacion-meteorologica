#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_TSL2561_U.h>

// Objetos sensor
Adafruit_BME280 bme;
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void setup() {
  Serial.begin(115200);

  // Inicializar I2C ESP32
Wire.begin(21, 22); // SDA,SCL, clock
  // ----- BME280 -----
  Serial.println("Iniciando BME280...");
  if (!bme.begin(0x76)) {
    Serial.println("No se encontró BME280");
    while (1);
  }
  Serial.println("BME280 Detectado");

  // ----- TSL2561 -----
  Serial.println("Iniciando TSL2561...");
  if (!tsl.begin()) {
    Serial.println("No se encontró el TSL2561");
    while (1);
  }
  Serial.println("TSL2561 Detectado");

  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);

  Serial.println("Sensores listos");
}

void loop() {
  // ----- BME280 -----
  Serial.print("Temp: ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Humedad: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Presión: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  // ----- TSL2561 -----
  sensors_event_t event;
  tsl.getEvent(&event);

  if (event.light) {
    Serial.print("Luz: ");
    Serial.print(event.light);
    Serial.println(" lux");
  } else {
    Serial.println("Luz: 0 lux");
  }

  Serial.println("----");
  delay(1000);
}