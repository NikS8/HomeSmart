/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            function to measurement flow water
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int getFlowDataBoiler() {

  unsigned long flowSensorPulsesPerSecondBoiler;
  unsigned long deltaTime = millis() - sensorPulseLastTimeBoiler;

  if (deltaTime < 15000)  {
    return;
  }
  flowSensorPulsesPerSecondBoiler = sensorPulseCountBoiler * 15000 / deltaTime;
  sensorPulseLastTimeBoiler = millis();
  sensorPulseCountBoiler = 0;

  return flowSensorPulsesPerSecondBoiler;
}

  int getFlowDataTA()
  {
  unsigned long flowSensorPulsesPerSecondTA;
  unsigned long deltaTime = millis() - sensorPulseLastTimeTA;

  if (deltaTime < 15000)  { 
    return; 
    }
  flowSensorPulsesPerSecondTA = sensorPulseCountTA * 15000 / deltaTime;
  sensorPulseLastTimeTA = millis();
  sensorPulseCountTA = 0;

  return flowSensorPulsesPerSecondTA;
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/