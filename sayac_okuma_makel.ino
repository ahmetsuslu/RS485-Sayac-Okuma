#include <SPI.h>
#include <SD.h>

// Not: Güvenlik nedeniyle sayaç numaraları maskelenmiştir. 
// Format: İlk iki rakam + yıldız + son iki rakam şeklindedir.
// Gerçek uygulamada tam sayaç numaralarını kullanınız.

const int chipSelect = 4;
#define RTS_pin    9    //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW
String T;
String Tarih;
String Saat;
String dataString;

void setup() {
 dataString = "Tarih, Saat, Soldaki Sayaç(52******41), Tarih, Saat, Sağdaki Sayaç(52******91)\r\n";
  pinMode(RTS_pin, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(300, SERIAL_7E1);
  delay(1000);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    digitalWrite(6, HIGH);
  }

  if (!SD.begin(chipSelect)) {
    digitalWrite(7, HIGH);
    while (1);
    digitalWrite(6, HIGH);
  }
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

void loop() {

  digitalWrite(7, HIGH);

  SelamVer1();
  delay(100);
  sohbeteBasla1();
  delay(100);
  getTarih();
  delay(100);
  dataString += Tarih;
  dataString += ",";
  getSaat();
  delay(100);
  dataString += Saat;
  dataString += ",";
  getT();
  delay(100);
  dataString += T;
  dataString += ",";
  byebye();
  
  SelamVer2();
  delay(100);
  sohbeteBasla2();
  delay(100);
  getTarih();
  delay(100);
  dataString += Tarih;
  dataString += ",";
  getSaat();
  delay(100);
  dataString += Saat;
  dataString += ",";
  getT();
  delay(100);
  dataString += T;
  byebye();
  digitalWrite(7, HIGH);
  File dataFile = SD.open("sayaclar.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    dataString = "";
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
  else {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  delay(1000);
  digitalWrite(7, LOW);
  delay(100);
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
}


void SelamVer1() {

  digitalWrite(RTS_pin, RS485Transmit);     // init Transmit
  // Sayaç 52******41 için iletişim başlatma komutu
  byte selam_ver1[] = {0x2f, 0x3f, 0x4d, 0x53, 0x59, 0x35, 0x32, 0x37, 0x34, 0x31, 0x37, 0x34, 0x31, 0x21, 0x0d, 0x0a};
  Serial.write(selam_ver1, sizeof(selam_ver1));

  Serial.flush();
  digitalWrite(RTS_pin, RS485Receive);      // Init Receive
  byte selam_al1[23];
  Serial.readBytes(selam_al1, 23);


}

void SelamVer2() {

  digitalWrite(RTS_pin, RS485Transmit);     // init Transmit
  // Sayaç 52******91 için iletişim başlatma komutu
  byte selam_ver2[] = {0x2f, 0x3f, 0x4d, 0x53, 0x59, 0x35, 0x32, 0x37, 0x34, 0x31, 0x36, 0x39, 0x31, 0x21, 0x0d, 0x0a};
  Serial.write(selam_ver2, sizeof(selam_ver2));

  Serial.flush();
  digitalWrite(RTS_pin, RS485Receive);      // Init Receive
  byte selam_al2[23];
  Serial.readBytes(selam_al2, 23);


}


void sohbeteBasla1() {

  digitalWrite(RTS_pin, RS485Transmit);     // init Transmit
  byte baslayalimmi1[] = {0x06, 0x30, 0x30, 0x31, 0x0d, 0x0a};
  Serial.write(baslayalimmi1, sizeof(baslayalimmi1));

  Serial.flush();
  digitalWrite(RTS_pin, RS485Receive);      // Init Receive
  byte baslayalim1[16];
  Serial.readBytes(baslayalim1, 16);


}


void sohbeteBasla2() {

  digitalWrite(RTS_pin, RS485Transmit);     // init Transmit
  byte baslayalimmi2[] = {0x06, 0x30, 0x30, 0x31, 0x0d, 0x0a};
  Serial.write(baslayalimmi2, sizeof(baslayalimmi2));

  Serial.flush();
  digitalWrite(RTS_pin, RS485Receive);      // Init Receive
  byte baslayalim2[16];
  Serial.readBytes(baslayalim2, 16);


}


void getT() {
  T = "";
  digitalWrite(RTS_pin, RS485Transmit);     // init Transmit
  byte iste[] = {0x01, 0x52, 0x32, 0x02, 0x31, 0x2e, 0x38, 0x2e, 0x30, 0x28, 0x29, 0x03, 0x59};
  Serial.write(iste, sizeof(iste));

  Serial.flush();
  digitalWrite(RTS_pin, RS485Receive);      // Init Receive
  byte al[24];
  Serial.readBytes(al, 24);

  for ( byte i = 7; i < 17; i++ ) {
    if (al[i] - 48 == -2) {
      T += ".";
    }
    else {
      T += String(al[i] - 48);
    }
  }



}

void getTarih() {

  Tarih = "";
  digitalWrite(RTS_pin, RS485Transmit);     // init Transmit
  byte tarihne[] = {0x01, 0x52, 0x32, 0x02, 0x30, 0x2e, 0x39, 0x2e, 0x32, 0x28, 0x29, 0x03, 0x5b};
  Serial.write(tarihne, sizeof(tarihne));

  Serial.flush();
  digitalWrite(RTS_pin, RS485Receive);      // Init Receive
  byte tarih[24];
  Serial.readBytes(tarih, 24);

  for ( byte i = 7; i < 15; i++ ) {
    if (tarih[i] - 48 == -3) {
      Tarih += "/";
    }
    else {
      Tarih += String(tarih[i] - 48);
    }
  }



}

void getSaat() {

  Saat = "";

  digitalWrite(RTS_pin, RS485Transmit);     // init Transmit
  byte saatne[] = {0x01, 0x52, 0x32, 0x02, 0x30, 0x2e, 0x39, 0x2e, 0x31, 0x28, 0x29, 0x03, 0x58};
  Serial.write(saatne, sizeof(saatne));

  Serial.flush();
  digitalWrite(RTS_pin, RS485Receive);      // Init Receive
  byte saat[18];
  Serial.readBytes(saat, 18);

  for ( byte i = 7; i < 15; i++ ) {
    if (saat[i] == 0x3a ) {
      Saat += ":";
    }
    else {
      Saat += String(saat[i] - 48);
    }
  }



}






void byebye() {

  digitalWrite(RTS_pin, RS485Transmit);     // init Transmit
  byte bb[] = {0x01, 0x42, 0x30, 0x03, 0x71};
  Serial.write(bb, sizeof(bb));

  Serial.flush();
  digitalWrite(RTS_pin, RS485Receive);      // Init Receive

}
