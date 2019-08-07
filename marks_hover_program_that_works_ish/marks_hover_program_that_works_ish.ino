 //
// Created by Florian VanKampen on 2019-06-17.
//

#include <rnrquad.h>

float KP = 0.15;
float KD = 1.9;
float KI = 0;
float target = .6;
float minHoverThrottle = .55;
//.2
//.75
//0
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

  setControllerState(controllerState);
}
