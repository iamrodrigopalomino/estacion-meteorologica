#include <HardwareSerial.h>

HardwareSerial pmsSerial(2); // UART2

String calidadAirePM25(uint16_t pm25) {
  if (pm25 <= 12) return "Buena";
  else if (pm25 <= 35) return "Moderada";
  else if (pm25 <= 55) return "Mala para sensibles";
  else if (pm25 <= 150) return "Mala";
  else if (pm25 <= 250) return "Muy mala";
  else return "Peligrosa";
}

void setup() {
  Serial.begin(115200);
  pmsSerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  Serial.println("Iniciando PMS5003...");
}

void loop() {
  if (pmsSerial.available() > 32) {
    uint8_t buffer[32];
    pmsSerial.readBytes(buffer, 32);

    if (buffer[0] == 0x42 && buffer[1] == 0x4D) {
      uint16_t pm1  = (buffer[10] << 8) | buffer[11];
      uint16_t pm25 = (buffer[12] << 8) | buffer[13];
      uint16_t pm10 = (buffer[14] << 8) | buffer[15];

      String calidad = calidadAirePM25(pm25);

      Serial.print("PM1.0: "); Serial.print(pm1); Serial.print(" ug/m3   ");
      Serial.print("PM2.5: "); Serial.print(pm25); Serial.print(" ug/m3   ");
      Serial.print("PM10: "); Serial.print(pm10); Serial.println(" ug/m3");

      Serial.print("Calidad del Aire (PM2.5): ");
      Serial.println(calidad);
      Serial.println("-----------------------------");
    }
  }
  delay(1000);
}