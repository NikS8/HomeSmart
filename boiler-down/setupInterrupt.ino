/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup Interrupt
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setupInterrupt() {

  pinMode(PIN_FLOW_SENSOR, INPUT);
  //digitalWrite(PIN_FLOW_SENSOR, HIGH);
  attachInterrupt(PIN_INTERRUPT_FLOW_SENSOR, 
                  flowSensorPulseCounter, FALLING);
  sei();

}

\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
