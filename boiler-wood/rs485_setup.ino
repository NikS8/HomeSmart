/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            setup rs485Setup
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void rs485Setup() {

  ETin.begin(details(rxdata), &Serial); //  //start the library, pass in the data details and the name of the serial port
  ETout.begin(details(txdata), &Serial);

  pinMode(DIR, OUTPUT);
  delay(50);
  digitalWrite(DIR, LOW);     // включаем прием

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
