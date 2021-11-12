/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup Current
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void currentSetup() {
	
  pinMode( PIN_EMON1, INPUT );
  pinMode( PIN_EMON2, INPUT );
  pinMode( PIN_EMON3, INPUT );
  pinMode( PIN_EMON4, INPUT );
  pinMode( PIN_EMON5, INPUT );
  pinMode( PIN_EMON6, INPUT );
  pinMode( PIN_EMON7, INPUT );

  emon1.current(1, 9.3);
  emon2.current(2, 9.27);
  emon3.current(3, 9.29);
  emon4.current(4, 9.29);
  emon5.current(5, 9.29);
  emon6.current(6, 9.29);
  emon7.current(7, current_koef7);
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
