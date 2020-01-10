/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup YF-B5 enable Interrupt
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void yfb5InterruptSetup() {
	
  enableInterrupt(A0, flowSensorPulseCounterA0, FALLING);
  enableInterrupt(A1, flowSensorPulseCounterA1, FALLING);
  enableInterrupt(A2, flowSensorPulseCounterA2, FALLING);
  enableInterrupt(A3, flowSensorPulseCounterA3, FALLING);
  enableInterrupt(A4, flowSensorPulseCounterA4, FALLING);
  enableInterrupt(A5, flowSensorPulseCounterA5, FALLING);
  enableInterrupt(2, flowSensorPulseCounter2, FALLING);
//  enableInterrupt(3, flowSensorPulseCounter3, FALLING);

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/