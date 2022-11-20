

String commandFn(String &readString) {
  String result = "Skipped";
  if (readString.indexOf("servo") >= 0) {
    int ind1 = 0;

    ind1 = readString.indexOf("servo=") + 6;
    readString = readString.substring(ind1, readString.length());
    ind1 = readString.indexOf(" ");
    readString = readString.substring(0, ind1);
    char valueChar[4];
    readString.toCharArray(valueChar, 4);

    int valueInt = atoi(valueChar);
    if (valueInt < 1) {
      valueInt = 1;
    }
    if (valueInt > 155) {
      valueInt = 155;
    }

    int angle = servomotor.read();
    if (angle != valueInt) {
      servomotor.write(valueInt);
      result = "Applied: ";
    }  else {
      result = "Already set ";
    }
      result += valueInt;
  }

  return result;
}