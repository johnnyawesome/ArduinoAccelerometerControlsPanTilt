#include <Wire.h> //Include the Wire library
#include <MMA_7455.h> //Include the MMA_7455 library
#include <Servo.h> 
 

//Make an instance of MMA_7455
MMA_7455 accelerometer = MMA_7455();
//Variables for the values from the Accelerometer Ssensor
char xVal, yVal, zVal; 

//Servo Instances
Servo tiltservo;
Servo panservo;

int serialcount = 0;

void setup()
{
  //Activate Serial
  Serial.begin(9600);
  delay(1000);

  // Set the sensitivity For Accelerometer
  // 2 = 2g, 4 = 4g, 8 = 8g
  accelerometer.initSensitivity(2); 

  //Calibrate Offset of Accelerometer
  accelerometer.calibrateOffset(-1.5, 10.0, -11.0);
  
  //Attach Servo
  tiltservo.attach(9);
  panservo.attach(10);
  
}

void loop()
{
  //Read Values
  xVal = accelerometer.readAxis('x'); //Read out the 'x' Axis
  yVal = accelerometer.readAxis('y'); //Read out the 'y' Axis
  zVal = accelerometer.readAxis('z'); //Read out the 'z' Axis

  //Write Values to Servo
  tiltservo.write(90 + xVal);
  panservo.write(90 - yVal);


  //Write Serial Debug Info every 50th Cycle (500ms)
  if(serialcount <= 29){
    serialcount++;
  }
  else{
    Serial.print("X = ");
    Serial.print(xVal, DEC);
    Serial.print("   Y = ");
    Serial.print(yVal, DEC);
    Serial.print("   Z = ");
    Serial.println(zVal, DEC); 
    serialcount = 0;
  }
 
  
  delay(20);
  
}
