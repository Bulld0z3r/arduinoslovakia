/**
   Arduino ESP8266 SPIFFS Examples
   v. 1.0
   Copyright (C) 2019 Robert Ulbricht
   https://www.arduinoslovakia.eu

   SPIFFS basic examples.

   IDE: 1.8.6 or higher
   Board: NodeMCU 0.9 (ESP-12)
   Core: https://github.com/esp8266/Arduino
   Version: 2.5.0

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <FS.h>

void setup() {
  Serial.begin(115200);

  bool res = SPIFFS.begin();
  Serial.print("SPIFFS.begin() = ");
  Serial.println(res);

  if (res) {
    testCreate();
    printFiles();
    printExample();
    testDelete();
    printFiles();
  }
}

void loop() {
}

void testCreate() {
  Serial.println(__FUNCTION__);
  // create file
  File f = SPIFFS.open("example.txt", "w");
  if (!f)
    Serial.println("File 'example.txt' open failed.");
  else {
    f.println("abc");
    f.println("def");
    f.println("ghi");
    f.close();
  }
}

void printFiles() {
  Serial.println(__FUNCTION__);
  Dir dir = SPIFFS.openDir("");
  while (dir.next()) {
    Serial.print(dir.fileName());
    Serial.print(" - ");
    Serial.println(dir.fileSize());
  }
}

void printExample() {
  Serial.println(__FUNCTION__);
  File f = SPIFFS.open("example.txt", "r");
  if (!f)
    Serial.println("File 'example.txt' open failed.");
  else {
    while (f.available())
      Serial.write(f.read());
    f.close();
  }
}

void testDelete() {
  Serial.println(__FUNCTION__);
  SPIFFS.remove("example.txt");
}
