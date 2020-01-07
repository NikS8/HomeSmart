/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            function to measurement temperature PT100
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int getPT100Data () {

  float k1, k2, k3, k4, k5, k6, k7, k8, k9;
  
  // Messwert für die Spannung an Rx einlesen
  Umess = get_U.read();

  // Aus der gemessenen Spannung den Widerstand Rx ausrechnen
  if (Umess >= UMIN && Umess <= UMAX) {
    Rx = ((((Ro - Ru) / (Uo - Uu)) * (Umess - Uu)) + Ru );
    //Serial.print("Umess = "); Serial.print(Umess); Serial.print("  ");
    Serial.print("R = ");     Serial.print(Rx, 3);   Serial.print(" Ohm   ->   ");

    // Temperatur für Rx >= 100 Ohm berechnen
    if (Rx >= 100.0) {
      k1 = 3.90802 * pow(10, -1);
      k2 = 2 * 5.802 * pow(10, -5);
      k3 = pow(3.90802 * pow(10, -1), 2);
      k4 = 4.0 * (pow(5.802 * pow(10, -5), 2));
      k5 = Rx - 100.0;
      k6 = 5.802 * pow(10, -5);

      k7 = k1 / k2;
      k8 = (k3 / k4) - (k5 / k6);
      k9 = sqrt(k8);

      tempPT100 = k7 - k9;
    }
    // Temperatur für Rx < 100 Ohm berechnen
    else {
      k1 = pow (Rx, 5) * 1.597 * pow(10, -10);
      k2 = pow (Rx, 4) * 2.951 * pow(10, -8);
      k3 = pow (Rx, 3) * 4.784 * pow(10, -6);
      k4 = pow (Rx, 2) * 2.613 * pow(10, -3);
      k5 = 2.219 * Rx - 241.9;

      tempPT100 = k1 - k2 - k3 + k4 + k5;
    }
    Serial.print("tempPT100 = ");     Serial.print(tempPT100, 3);   Serial.println(" GrdC");
  }
  else {
    Serial.println("Messfehler");
  }
  return tempPT100;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\