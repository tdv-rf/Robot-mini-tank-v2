
#include <IRremote.h>
#include "MatrixDisplay.h"
#include "Motor.h"

IRrecv irrecv(A0); //set IRrecv irrecv to A0
decode_results results;
long ir_rec; //save the IR value received

#define Trig 5 //ultrasonic trig Pin
#define Echo 4 //ultrasonic echo Pin
int distance;

Motor motor = Motor();
MatrixDisplay display = MatrixDisplay();

#define light_L_Pin A1   //define the pin of left photo resistor
#define light_R_Pin A2   //define the pin of right photo resistor
int left_light; 
int right_light;

#define servoPin 9 //pin of servo
int pulsewidth;    // save the pulse width value of servo

char bluetooth_val; //save the value of Bluetooth reception

/******************The function to control servo***********/
void procedure(int myangle)
{
  for (int i = 0; i <= 50; i = i + (1))
  {
    pulsewidth = myangle * 11 + 500;
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(servoPin, LOW);
    delay((20 - pulsewidth / 1000));
  }
}

//The function to control ultrasonic sensor function controlling ultrasonic
float checkdistance()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  float distance = pulseIn(Echo, HIGH) / 58.20; //58.20, that is , 2*29.1=58.2
  delay(10);
  return distance;
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); //Initialize the IR reception library

  motor.init(13, 11, 12, 3);
  display.init(A5, A4);

  pinMode(light_L_Pin, INPUT);
  pinMode(light_R_Pin, INPUT);

  pinMode(servoPin, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  procedure(90); //servo rotates to 90°
}

void Distance_control()
{
  distance = checkdistance();           //assign the distance detected by ultrasonic sensor to distance
  if (distance >= 20 && distance <= 60) //range to go front
  {
    motor.Car_front();
  }
  else if (distance > 10 && distance < 20) //range to stop
  {
    motor.Car_Stop();
  }
  else if (distance <= 10) //range to go back
  {
    motor.Car_back();
  }
  else //other situations, stop
  {
    motor.Car_Stop();
  }
}

void Ir_remote_control()
{
  if (irrecv.decode(&results)) //receive the IR remote value
  {
    ir_rec = results.value;
    Serial.println(ir_rec, HEX);
    irrecv.resume();
  }

  switch (ir_rec)
  {
  case 0xFF629D:
    motor.Car_front();
    display.matrix_display(display.front); //display forward sign
    break;
  case 0xFFA857:
    motor.Car_back();
    display.matrix_display(display.front); //show back pattern
    break;
  case 0xFF22DD:
    motor.Car_T_left();
    display.matrix_display(display.left); //display left-turning sign
    break;
  case 0xFFC23D:
    motor.Car_T_right();
    display.matrix_display(display.right); //display right-turning pattern
    break;
  case 0xFF02FD:
    motor.Car_Stop();
    display.matrix_display(display.STOP01); //show stop pattern
    break;
  case 0xFF30CF:
    motor.Car_left();
    display.matrix_display(display.left); //display left-turning pattern
    break;
  case 0xFF7A85:
    motor.Car_right();
    display.matrix_display(display.right); //display right-turning pattern
    break;
  default:
    break;
  }
}

void Light_follow_control()
{
  left_light = analogRead(light_L_Pin);
  right_light = analogRead(light_R_Pin);
  Serial.print("left_light_value = ");
  Serial.println(left_light);
  Serial.print("right_light_value = ");
  Serial.println(right_light);
  if (left_light > 650 && right_light > 650) //the value detected photo resistor，go front
  {
    motor.Car_front();
  }
  else if (left_light > 650 && right_light <= 650) //the value detected photo resistor，turn left
  {
    motor.Car_left();
  }
  else if (left_light <= 650 && right_light > 650) //the value detected photo resistor，turn right
  {
    motor.Car_right();
  }
  else //other situations, stop
  {
    motor.Car_Stop();
  }
}

void Bluetooth_control()
{
  if (Serial.available())
  {
    bluetooth_val = Serial.read();
    Serial.println(bluetooth_val);
  }
  switch (bluetooth_val) 
  {
     case 'F':  //forward command
        motor.Car_front();
        display.matrix_display(display.front);  // show forward design
        break;
     case 'B':  //Back command
        motor.Car_back();
        display.matrix_display(display.back);  //show back pattern
        break;
     case 'L':  // left-turning instruction
        motor.Car_left();
        display.matrix_display(display.left);  //show “left-turning” sign 
        break;
     case 'R':  //right-turning instruction
        motor.Car_right();
        display.matrix_display(display.right);  //display right-turning sign
       break;
     case 'S':  //stop command
        motor.Car_Stop();
        display.matrix_display(display.STOP01);  //show stop picture
        break;
  }
}

void loop()
{
  // Light_follow_control();
  // Distance_control();
  // Ir_remote_control();
  Bluetooth_control();
}
