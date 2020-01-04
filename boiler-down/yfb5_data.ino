/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            function to measurement flow water
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int getFlowData() {
  //  static int yfb5PulsesPerSecond;
  unsigned long yfb5PulsesPerSecond;

  unsigned long deltaTime = millis() - yfb5LastTime;
  //  if ((millis() - yfb5LastTime) < 1000) {
  if (deltaTime < 15000)
  {
    return;
  }

  //detachInterrupt(yfb5Interrupt);
  detachInterrupt(PIN_INTERRUPT_YFB5);
  yfb5PulsesPerSecond = yfb5PulseCount;
  yfb5PulsesPerSecond *= 15000;
  yfb5PulsesPerSecond /= deltaTime; //  количество за секунду

  yfb5LastTime = millis();
  yfb5PulseCount = 0;
  //attachInterrupt(yfb5Interrupt, yfb5PulseCounter, FALLING);
  attachInterrupt(PIN_INTERRUPT_YFB5, yfb5PulseCounter, FALLING);

  return yfb5PulsesPerSecond;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
