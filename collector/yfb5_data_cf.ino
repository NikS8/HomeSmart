/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            function to measurement flow water
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int getFlowData2()
{
  unsigned long flowSensorPulsesPerSecond2;
  unsigned long deltaTime = millis() - flowSensorLastTime2;

  if (deltaTime < 15000)  {
    return;
  }
  flowSensorPulsesPerSecond2 = flowSensorPulseCount2 * 15000 / deltaTime;
  flowSensorLastTime2 = millis();
  flowSensorPulseCount2 = 0;

  return flowSensorPulsesPerSecond2;
}
/*
  /////////////////////
  int getFlowData3()
  {
  unsigned long flowSensorPulsesPerSecond3;
  unsigned long deltaTime = millis() - flowSensorLastTime3;

  if (deltaTime < 15000)  { return; }
  flowSensorPulsesPerSecond3 = flowSensorPulseCount3 * 15000 / deltaTime;
  flowSensorLastTime3 = millis();
  flowSensorPulseCount3 = 0;

  return flowSensorPulsesPerSecond3;
  }
*/
/////////////////////
int getFlowDataA0()
{
  unsigned long flowSensorPulsesPerSecondA0;
  unsigned long deltaTime = millis() - flowSensorLastTimeA0;

  if (deltaTime < 15000)  {
    return;
  }
  flowSensorPulsesPerSecondA0 = flowSensorPulseCountA0 * 15000 / deltaTime;
  flowSensorLastTimeA0 = millis();
  flowSensorPulseCountA0 = 0;

  return flowSensorPulsesPerSecondA0;
}

/////////////////////
int getFlowDataA1()
{
  unsigned long flowSensorPulsesPerSecondA1;
  unsigned long deltaTime = millis() - flowSensorLastTimeA1;

  if (deltaTime < 15000)  {
    return;
  }
  flowSensorPulsesPerSecondA1 = flowSensorPulseCountA1 * 15000 / deltaTime;
  flowSensorLastTimeA1 = millis();
  flowSensorPulseCountA1 = 0;

  return flowSensorPulsesPerSecondA1;
}

/////////////////////
int getFlowDataA2()
{
  unsigned long flowSensorPulsesPerSecondA2;
  unsigned long deltaTime = millis() - flowSensorLastTimeA2;

  if (deltaTime < 15000)  {
    return;
  }
  flowSensorPulsesPerSecondA2 = flowSensorPulseCountA2 * 15000 / deltaTime;
  flowSensorLastTimeA2 = millis();
  flowSensorPulseCountA2 = 0;

  return flowSensorPulsesPerSecondA2;
}


/////////////////////
int getFlowDataA3()
{
  unsigned long flowSensorPulsesPerSecondA3;
  unsigned long deltaTime = millis() - flowSensorLastTimeA3;

  if (deltaTime < 15000)  {
    return;
  }
  flowSensorPulsesPerSecondA3 = flowSensorPulseCountA3 * 15000 / deltaTime;
  flowSensorLastTimeA3 = millis();
  flowSensorPulseCountA3 = 0;

  return flowSensorPulsesPerSecondA3;
}

/////////////////////
int getFlowDataA4()
{
  unsigned long flowSensorPulsesPerSecondA4;
  unsigned long deltaTime = millis() - flowSensorLastTimeA4;

  if (deltaTime < 15000)  {
    return;
  }
  flowSensorPulsesPerSecondA4 = flowSensorPulseCountA4 * 15000 / deltaTime;
  flowSensorLastTimeA4 = millis();
  flowSensorPulseCountA4 = 0;

  return flowSensorPulsesPerSecondA4;
}

/////////////////////
int getFlowDataA5()
{
  unsigned long flowSensorPulsesPerSecondA5;
  unsigned long deltaTime = millis() - flowSensorLastTimeA5;

  if (deltaTime < 15000)  {
    return;
  }

  flowSensorPulsesPerSecondA5 = flowSensorPulseCountA5 * 15000 / deltaTime;
  flowSensorLastTimeA5 = millis();
  flowSensorPulseCountA5 = 0;

  return flowSensorPulsesPerSecondA5;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
