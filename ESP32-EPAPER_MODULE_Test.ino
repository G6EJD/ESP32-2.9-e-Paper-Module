#include <mySD.h> // https://github.com/LilyGO/esp32-micro-sdcard
#define LED_BUILTIN 22  //Blink pin 
File root;

void setup(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("Initializing SD card...");  
  if (!SD.begin(13,15,2,14)) { /* initialize SD library with SPI pins */
    Serial.println("initialization failed!");
  }
  Serial.println("initialization done.");
  /* open "test.txt" for writing */
  root = SD.open("test.txt", FILE_WRITE);
  if (!root) {
    Serial.println("error opening test.txt");
  }
  delay(1000);
  /* after writing then reopen the file and read it */
  root = SD.open("test.txt");
  if (root) {    
    while (root.available()) {    /* read from the file until there's nothing else in it */
      Serial.write(root.read());  /* read the file and print to Terminal */
    }
    root.close();
  } else {
    Serial.println("error opening test.txt");
  }
  Serial.println("done!");
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(5000);                       // wait for a second
  beep(0,1500,200);
  delay(5000);
}

void beep(int channel, int freq, int duration){
  #define resolution 8
  ledcAttachPin(25, channel);
  ledcSetup(channel, freq, resolution);
  ledcWriteTone(channel, freq);
  delay(duration);
  ledcWriteTone(channel, 0);
}

