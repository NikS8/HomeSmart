/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            Settings Hx711 for Pt100
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void pt100hx711Setup() {
  
  int i;
  long buf = 0;
  long U = 0;
 Serial.println(F("HX711 Temperaturmessung mit Pt100 Widerstandsthermometer"));
  get_U.begin(6, 5, 32);

  // Abgleich Messbereichsgrenze unten
  if (Uu <= UMIN || Ru == RMIN) {
   Serial.println(F("Widerstand fuer untere Messbereichsgrenze eingesetzt ??"));
   Serial.print(F("Messung fuer Messbereichsgrenze unten laeuft - "));
   Serial.println(F("bitte warten ..."));
    for (i = 0; i < 5; i++) {
      U = get_U.read_average(40);
      buf = buf + U;
      Serial.print(U); Serial.print(" ");
    }
    if (buf / 5 < UMIN || buf / 5 > UMAX) {
      Serial.println(); Serial.println();
      Serial.println(F("Messfehler, bitte Schaltung ueberpruefen"));
      while (1);
    }
    else {
      Serial.println(); Serial.println();
      Serial.print(F( "Bitte "));
      Serial.print(buf / 5);
      Serial.print(F( " bei Variable 'Uu' und den Wert des eingesetzten "));
      Serial.println(F( " Widerstandes in Ohm bei Variable 'Ru' eintragen "));
      Serial.println(F("Dann das Programm neu hochladen"));
      Serial.println();
      while (1);
    }
  }

  // Abgleich Messbereichsgrenze oben
  if (Uo <= UMIN || Ro == RMIN) {
    Serial.println(F("Widerstand fuer obere Messbereichsgrenze eingesetzt ??"));
    Serial.print(F("Messung fuer Messbereichsgrenze oben laeuft - "));
    Serial.println(F("bitte warten ..."));
    for (i = 0; i < 5; i++) {
      U = get_U.read_average(40);
      buf = buf + U;
      Serial.print(U); Serial.print(" ");
    }
    if (buf / 5 < UMIN || buf / 5 > UMAX) {
      Serial.println(); Serial.println();
      Serial.println(F("Messfehler, bitte Schaltung ueberpruefen"));
      while (1);
    }
    else {
      Serial.println(); Serial.println();
      Serial.print(F( "Bitte "));
      Serial.print(buf / 5);
      Serial.print(F( " bei Variable 'Uo' und den Wert des eingesetzten "));
      Serial.println(F( " Widerstandes in Ohm  bei Variable 'Ro' eintragen "));
      Serial.println(F("Dann das Programm neu hochladen"));
      Serial.println();
      while (1);
    }
  }

  // Prüfung der Abgleichwerte
  if ( Uu < UMIN || Uu > UMAX || Uo < UMIN || Uo > UMAX || Ru < RMIN || Ru > RMAX || Ro < RMIN || Ro > RMAX ||
       Uu > Uo || Uo < Uu || Ru > Ro || Ro < Ru) {
    Serial.println(F( "Abgleichfehler - Bitte Abgleich wiederholen"));
    Serial.println();
    while (1);
  }
  else {
    Serial.println(F( "Abgleich plausiebel"));
    Serial.println();
  }
  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/