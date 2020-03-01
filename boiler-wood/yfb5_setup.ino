/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup YF-B5 Interrupt
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void yfb5InterruptSetup() {

  pinMode(PIN_YFB5, INPUT);
  //digitalWrite(PIN_YFB5, HIGH);
  attachInterrupt(PIN_INTERRUPT_YFB5, yfb5PulseCounter, FALLING);
  sei();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
