
void setup() {

  pwm.begin();
  pwm.setPWMFreq(60);

  servos_init();
  ColorSensorBegin();
  Serial.begin(115200);
  delay(2000);
  SetColorPoints();
  Menu_Print();
}

void loop() {
  Menu_Process();
  //while(true);
  //servos_test();
  //Down_Back.rmove(place[3]);
  //edgeSensor.ReadColor();
  //cornerSensor.ReadColor();
  //cornerSensor.testValues();
  //Serial.println("");
  //delay(5000);
}
