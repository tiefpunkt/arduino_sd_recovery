# SD Card Recovery using an Arduino

One of my SD card "died". More specifically, my laptop wouldn't read it anymore, and neither would any other machines or cameras I tried. It did react (looking at the dmesg output), but would only though errors. So I decided to try and read it using an Arduino.

## Background
__Attention__ _Dangerous half knowledge ahead_

SD cards have two modes in which they can be accessed. One is the SDIO mode, which is used by your average card reader, your camera, etc. It's fast, and somewhat complicated. The other mode is SPI mode. It's much slower, but it's fairly simple. That's what you use if you connect your SD card to a microcontroller such as an arduino.

## Hardware
I used a Playduino One Arduino clone, that I had lying around, and a SD card shield I got from ElectroDragon. Just plugged them together, and done is the card reader hardware.

## Software
I took 3 steps in the recovery process.

### CardInfo
The SD card library in the Arduino IDE contains an example called `CardInfo`. It connects to the card, and gets information such as size, filesystem type, and a list of files on the card.

That worked, so I kept going.

### sd_recovery_files
The sketch `sd_recovery_files.ino` tries to iterate over the filesystem, and outputs all files in a HEX encoded format over the serial port. If you save the output to a file on your machine, you can then parse the file using the supplied python script `parse_files.py`.

This surprisingly worked for a number of files, but the `openNextFile()` doesn't seem to work all that well, so not all files were copied.

### sd_recovery_raw
The sketch `sd_recovery_raw.ino` reads the SD card block by block, and outputs it in a HEX encoded format over the serial port. You can parse the output back into a binary file using the supplied `parse_raw.py` python script.

This may just take forever, and I have not been successful in using that file, but I have yet to actually copy the entire SD card that way (might take a few days for the 4GB card I have).
