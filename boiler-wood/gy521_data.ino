/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
            GY-521
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int getShutter() {

   // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  //accelgyro.getMotion6(&ax,,,,,);

  // these methods (and a few others) are also available
  //accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);
#ifdef OUTPUT_READABLE_ACCELGYRO
  // display tab-separated accel/gyro x/y/z values
  accelX = ax / 141;
  //accelX = (atan2(ax, -az) + PI) * RAD_TO_DEG;
  //  double accYangle = (atan2(ay,az)+PI)*RAD_TO_DEG;
  accelX = 175-accelX;
  Serial.print("    x ");
  //Serial.print(ax/141);
  //Serial.print("    ");
  Serial.print(accelX);
  /*
    Serial.print("    y ");
    Serial.print(ay/141);
    Serial.print("   ");
    Serial.print(accYangle);

    Serial.print(" :    y/x ");
    Serial.print(ay/141);
    Serial.print("   ");
    Serial.print(accXangle);

    Serial.print("   x/y ");
    Serial.print(ax/141);
    Serial.print("   ");
    Serial.print(accYangle);
    //Serial.print("   z ");
    //Serial.print(az);
  */
  /*
    Serial.print("   gx ");
    Serial.print(gx);
    Serial.print("   gy ");
    Serial.print(gy);
    //Serial.print("   gz ");
    //Serial.print(gz);
  */
  Serial.println();

#endif
#ifdef OUTPUT_BINARY_ACCELGYRO
  Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
  /*
    Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
    Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
    Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
    Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
    Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
  */
#endif

    return accelX;

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
