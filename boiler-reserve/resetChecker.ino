/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            resetChecker
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void(* resetFunc) (void) = 0; //declare reset function @ address 0

void resetChecker() {
  if (millis() > (RESET_UPTIME_TIME)) {
    resetFunc();
  }
  if (millis() - lastRequestTime > RESET_ON_SILENCE_TIMEOUT) {
    resetFunc();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
