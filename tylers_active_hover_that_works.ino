//
// Created by mark kingham on 2019-06-17.
//

#include <rnrquad.h>

float KP = 0.15;
float KD = 3;
float KI = 0.05;
float target = 1;
float minHoverThrottle = .55;
//.15
//1.9
//0.2
//.569
PID dPID;

float throttle = 0;

void setup()
{
  baseSetup();

  dPID.begin(target, KP, KI, KD, minHoverThrottle);
}

void loop()
{
  baseLoop();


  ControllerState controllerState = getControllerState();
  SensorState sensorState = getSensorState();

  //  dPID.KP = KP + .3 * controllerState.trim0;
  //  dPID.target = target + .1 * controllerState.trim1;

  if (controllerState.throttle > .1 )
  {
    controllerState.throttle = constrain(dPID.tstep(sensorState.rangeDown), .3 , .8);
  }

  else
  {
    controllerState.throttle = 0;
  }


  if (sensorState.rangeForward < .3 )
  {
    controllerState.rightStickYPosition = -0.5;
  }

  if (sensorState.rangeRight < .3 )
  {
    controllerState.rightStickXPosition = -0.5;
  }

  if (sensorState.rangeLeft < .3 )
  {
    controllerState.rightStickXPosition = +0.5;
  }

  if (sensorState.rangeUp <.5 )
  {
    controllerState.throttle -.05;
  }
setControllerState(controllerState);
} 
