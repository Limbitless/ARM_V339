/*
 * Limbitless_Arm_v3.3.8
 *
 * Title: Limbitless v3.3.9
 * Author1: John Sparkman & JE
 * Date: 5-27
 *
 */

// Library for servo use
#include "pins.h"

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position  
 
double static_analog_dta = 0;
double open_value = 1023;
double closed_value = 580;
int hand_pos = 0;
double muscle_temp;
int times = 10;

// find the initial value
double getStaticdta()
{
  delay(50);
    double sum = 0;

    for(int i=0; i<=10; i++)
    {
        for(int j=0; j<100; j++)
        {
            sum += analogRead(muscle)*(5.0/1023.0);
            delay(5);
        }
    }
    
    sum /= 1100;
    return sum;
}

void open_hand()
{
myservo.write(0);
delay(1000);
}

void close_hand()
{
myservo.write(120);   
delay(1000);
}

// Sets up the system. Runs once on startup.
void setup()
{
  // Uncomment this for calibration purposes.
 //Serial.begin(9600);
  
  myservo.attach(servo_pin);
  
  // Set pins to recieve data
 // pinMode(muscle, INPUT);
  pinMode(motor_pos,INPUT);
    
  close_hand();
  
  static_analog_dta = getStaticdta();
    
    open_hand();
    close_hand();
    open_hand();  
    close_hand();
    open_hand();
}

void loop()
{
  float muscle_sensor_value = analogRead(muscle);
  double muscle_sensor_scaled = muscle_sensor_value * (5 / 1023.0);    

  
  if (muscle_sensor_scaled >= static_analog_dta + 0.2)
  {
    if((hand_pos % 2) == 0)
    {
      close_hand();
    }
    else
      open_hand();
      
    hand_pos = hand_pos +1;
    muscle_temp = muscle_sensor_scaled;
  }
}

