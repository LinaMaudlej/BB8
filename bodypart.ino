
#include <SoftwareSerial.h>

#include <AFMotor.h>
#define ledPin 13

SoftwareSerial HM10(0, 1); // RX = 2, TX = 3

int state = 0;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
char appData;  
String inData = "";


void setup() {
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  pinMode(13, OUTPUT); // onboard LED
  digitalWrite(13, LOW); // switch OFF LED


  set_speed(200);               // set the speed to 200/255
  
}

void loop() {
   /******bluetooth module*****/
  HM10.listen();  // listen the HM10 port

  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();      //send it with no lining format
    inData = String(appData);  // save the data in string format
    Serial.write(appData);
  }


  if (Serial.available()) {           // Read user input if available.
    delay(10);
    HM10.write(Serial.read());
  }
  if ( inData == "F") {
    Serial.println("forward the BB8");
    forward_BB8();
    delay(500);
  }
  if ( inData == "B") {
    Serial.println("back the bb8");
    backward_BB8();
    delay(500);
  }

    if ( inData == "R") {
    Serial.println("turn right the BB8");
    right_BB8();
    delay(500);
  }

  if ( inData == "L") {
    Serial.println("turn left the BB8");
    left_BB8();
    delay(500);
  }

  
  if ( inData == "S") {
    Serial.println("stop the BB8");
     stop_BB8();
    delay(500);
  }
  delay(1000);
}

void set_speed(int speed){
  motor1.setSpeed(speed);     
  motor2.setSpeed(speed);     
}

void forward_BB8(){
  motor1.setSpeed(220); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor clockwise
  motor2.setSpeed(220); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise  
}

void backward_BB8(){
 motor1.setSpeed(220); 
  motor1.run(FORWARD); //rotate the motor counterclockwise
  motor2.setSpeed(220); 
  motor2.run(BACKWARD); //rotate the motor counterclockwis   
}

void right_BB8(){
  motor1.setSpeed(100);
  motor1.run(BACKWARD); //turn motor1 off
  motor2.setSpeed(200); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise  

}

void left_BB8(){
  motor1.setSpeed(20s0); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor clockwise
  motor2.setSpeed(100);
  motor2.run(FORWARD); //turn motor2 off     
}

void stop_BB8(){
 motor1.setSpeed(0);
 motor1.run(RELEASE); 
 motor2.setSpeed(0);     
 motor2.run(RELEASE);     
}

