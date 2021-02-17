

void relayModuleSetup() {
  for (byte i = 0; i < (sizeof(heaterStatePins) / sizeof(heaterStatePins[0])); i++) {
    pinMode(heaterStatePins[i], OUTPUT);
    digitalWrite(heaterStatePins[i], HIGH);
  }

}
