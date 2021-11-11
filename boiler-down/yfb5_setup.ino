/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup YF-B5 Interrupt
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void yfb5InterruptSetup() {

  pinMode(PIN_INTERRUPT_YFB5_BOILER, INPUT);
  //digitalWrite(PIN_INTERRUPT_YFB5_BOILER, HIGH);
  enableInterrupt(PIN_INTERRUPT_YFB5_BOILER, yfb5PulseCounterBoiler, FALLING);
  pinMode(PIN_INTERRUPT_YFB5_TA, INPUT);
  //digitalWrite(PIN_INTERRUPT_YFB5_TA, HIGH);
  enableInterrupt(PIN_INTERRUPT_YFB5_TA, yfb5PulseCounterTA, FALLING);
  
  sei();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/