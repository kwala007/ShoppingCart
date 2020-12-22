#include <Stepper.h>

//Defines a datatype named WheelVel to be a struct with parameters w(1 - 4).
//This has to be first in the file because everything afterwards will use the defined type WheelVel.
typedef struct
{
  double w1;
  double w2;
  double w3;
  double w4;
} WheelVel; 

//Defines a function calcWheelVels that takes in a pointer to a destination WheelVel struct, a desired x velocity, y velocity, and z angular velocity.
//Does calculations using robot parameters to obtain individual wheel velocities. Modifies fields of destination struct to match.
void calcWheelVels(WheelVel* input, double vx, double vy, double wz)
{
  double r = 0.1;
  double lx = 0.5;
  double ly = 0.5;
  input->w1=(1/r)*(vx-vy-(lx+ly)*wz);
  input->w2=(1/r)*(vx+vy+(lx+ly)*wz);
  input->w3=(1/r)*(vx+vy-(lx+ly)*wz);
  input->w4=(1/r)*(vx-vy+(lx+ly)*wz);
  return;
}

//Defines stepper motors with the specified parameters.
const int stepsPerRevolution = 255;
Stepper myStepper1(stepsPerRevolution, 8, 9, 10, 11); 
Stepper myStepper2(stepsPerRevolution, 4, 5, 6, 7); 

void setup() 
{
  Serial.begin(9600);
  myStepper1.setSpeed(60); myStepper1.step(stepsPerRevolution);
  myStepper2.setSpeed(60); myStepper2.step(stepsPerRevolution);
}

//Loop to execute whatever is supposed to be done. I don't know exactly how this will interface with other programs/machines, so this will have to be modified to pull data from the appropriate sources.
void loop() 
{
  //Might want to dynamically allocate for the WheelVel struct, depending on how much memory the machine has. Left it out for now.
  WheelVel result = {0.0, 0.0, 0.0, 0.0};
  
  //Have to grab data for desired vx, vy, wz. Probably from serial. I've left this out too because I will need to read up on how to read from serial.
  //For now I am just initializing some variables with zero values.
  double vx = 0.0, vy = 0.0, wz = 0.0;
  calcWheelVels(&result, vx, vy, wz);
  
  //I assume the stepper motors were set up for a reason, so something might need to be done here with the resultant angular wheel velocities (e.g. rotate the steppers to match the velocity required).
  //Could print the resultant angular velocities to serial here for testing purposes. I will also need to read up on how to do that.
  
  break; //Just breaking out of the loop after one execution so infinite loops don't accidentally happen when you test. In the final code, this should be triggered conditionally. Maybe a wait would be implemented between loops as well.
}
  
