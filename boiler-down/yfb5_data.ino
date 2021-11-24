/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            function to measurement flow water
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int getFlowData() {

  unsigned long flowSensorPulsesPerSecond;
  unsigned long deltaTime = millis() - yfb5LastTime;

  if (deltaTime < 15000)  {
    return;
  }
  flowSensorPulsesPerSecond = yfb5PulseCount * 15000 / deltaTime;
  yfb5LastTime = millis();
  yfb5PulseCount = 0;

  return flowSensorPulsesPerSecond;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
