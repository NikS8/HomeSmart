/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup Interrupt
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setupYfb5Interrupt() {

  pinMode(PIN_YFB5, INPUT);
  //digitalWrite(PIN_YFB5, HIGH);
  attachInterrupt(PIN_INTERRUPT_YFB5, 
                  yfb5PulseCounter, FALLING);
  sei();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
