#include <SD.h>

File root;

Sd2Card card;

void setup()
{
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  
  card.init(SPI_HALF_SPEED, 10);
//  SD.begin(10);

  long blocks = card.cardSize();
  //Serial.println(blocks);

  uint8_t  data[512];
  int i = 0;
  boolean notZero = false;
  for (long blockNumber = 0; blockNumber < blocks; blockNumber++) {
    //card.chipSelectLow();
    if (!card.readBlock(blockNumber, data)) {
      Serial.println("Z");
      break;
    }
    
    notZero = false;
    
    for (i = 0; i<512; i++) {
      if (data[i] > 0x00) {
        notZero = true;
        break;
      }
    }
    if (notZero) {
      for (i = 0; i<512; i++) {
        if (data[i] < 0x10) {
          Serial.print("0");
        }
        Serial.print(data[i], HEX);
      }
      Serial.println("X");
    } else {
      Serial.println("Y");
    
  }
  
  //Serial.println("done!");
}

void loop()
{
  // nothing happens after setup finishes.
}

void printDirectory(File dir, String folder) {
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
        printDirectory(entry, folder_new);
      } else {
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
    }
  }
}


