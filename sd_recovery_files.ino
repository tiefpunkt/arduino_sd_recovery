#include <SD.h>

File root;

void setup()
{
  Serial.begin(115200);
  pinMode(10, OUTPUT);

  SD.begin(10);

  root = SD.open("/");
  readDirectory(root, "");

  Serial.println("done!");
}

void loop()
{
  // nothing happens after setup finishes.
}

void readDirectory(File dir, String folder) {
  boolean files = true;
  while(files) {
    File entry =  dir.openNextFile();
    if (! entry) {
      files = false;
    } else {
      if (entry.isDirectory()) {
        String folder_new = folder;
        folder_new += entry.name();
        folder_new += "/";
        readDirectory(entry, folder_new);
      } else {
        outputFile(entry, folder);
      }
    }
  }
}

void outputFile(File entry, String folder) {
  Serial.print("--- ");
  Serial.print(folder);
  Serial.print(entry.name());
  Serial.print(";");
  Serial.println(entry.size(), DEC);
  byte r;
  while (entry.available()) {
    r = entry.read();
    if (r < 0x10) {
      Serial.print("0");
    }
    Serial.print(r, HEX);
  }
  Serial.println();
}

