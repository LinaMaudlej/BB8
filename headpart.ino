#include <CapacitiveSensor.h>
/* https://www.youtube.com/watch?v=a4mt-gApxiw */
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
/* https://www.youtube.com/watch?v=gi9mqIha8n0 */
int redPin= 7;
int greenPin = 6;
int bluePin = 5;
long minutes = 0;
long lastTime = 0;
long time_passed_sad=2;

/*************/
//speaker
#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch

void setup() {
  Serial.begin(9600);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  /*********/
  //speaker
  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 8 on Uno, Nano, etc
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
 tmrpcm.setVolume(5);
 tmrpcm.quality(1);
// Serial.println("play music");  
  //tmrpcm.play("test.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
 
 tmrpcm.play("slashgear_bb8_owoweeewow.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
  delay(1000);
} 
void loop() {
    long total =  cs_4_2.capacitiveSensor(30);
    if(millis()-lastTime > 60000){
    minutes++;
    lastTime = millis();
  }
    Serial.println(total);                  // print sensor output 1 - this is also the value you can use to use this in other projects
    Serial.println(minutes);                  // print sensor output 1 - this is also the value you can use to use this in other projects

  /**RGB led**/
   while(total > 3000){
      tmrpcm.play("happy.wav");
            // tmrpcm.play("slashgear_bb8_clickingloading.wav");

       happy_status();
       happy_status();
       delay(8000);
       if(minutes>0){
       minutes--;
       }
       Serial.println("happy");   
       total =  cs_4_2.capacitiveSensor(30);
   }

   if(minutes >= time_passed_sad){ 
      sad_status();
      Serial.println("sad");   
     tmrpcm.play("sad1.wav");
          //tmrpcm.play("slashgear_bb8_question.wav");

     
        delay(1000);
      tmrpcm.play("sad2.wav");
          // tmrpcm.play("slashgear_bb8_rightnow.wav");

     
       delay(1000);
     tmrpcm.play("sad3.wav");
            //tmrpcm.play("slashgear_bb8_uhoh.wav");

      
        delay(1000);

//tmrpcm.play("slashgear_bb8_wuhoh.wav");

      
       delay(1000);
      //tmrpcm.play("bb8-uhoh.wav");
      minutes=0;
   }else{
      normal_status(); // White Color
      if(minutes%5==0){
           Serial.println("normal");   
          //tmrpcm.play("slashgear_bb8_bupbupbupewweew.wav");
           //tmrpcm.play("normal.wav");

            delay(1000);
            
      }
   }
  delay(50);
}
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void sad_status(){
  setColor(255, 0, 0); // Red Color
  delay(500);
  setColor(0, 0, 0); // Red Color
  delay(500);
}

void happy_status(){
  setColor(0, 255, 0); // Green Color
  delay(500);
  setColor(0, 0, 255); // Blue Color
  delay(500);
  setColor(170, 0, 255); // Purple Color
  delay(500);
}


void normal_status(){
  setColor(255, 255, 255); // White Color
  delay(500);
}




