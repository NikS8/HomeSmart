/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup Current
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void currentSetup() {

  pinMode( PIN_EMON_PUMP, INPUT );
  pinMode( PIN_EMON1, INPUT );
  pinMode( PIN_EMON2, INPUT );
  pinMode( PIN_EMON3, INPUT );
  pinMode( PIN_EMON4, INPUT );
  pinMode( PIN_EMON5, INPUT );
  pinMode( PIN_EMON6, INPUT );

  emon_pump.current(PIN_EMON_PUMP, current_koef_pump);
  emon1.current(PIN_EMON1, current_koef1);
  emon2.current(PIN_EMON2, current_koef2);
  emon3.current(PIN_EMON3, current_koef3);
  emon4.current(PIN_EMON4, current_koef4);
  emon5.current(PIN_EMON5, current_koef5);
  emon6.current(PIN_EMON6, current_koef6);

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
