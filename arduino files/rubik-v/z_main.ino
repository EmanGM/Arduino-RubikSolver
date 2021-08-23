
void setup() {

  pwm.begin();
  pwm.setPWMFreq(60);

  servos_init();
  Serial.begin(9600); //Can only work with HC-05 with this baud rate
  delay(2000);
  //SetColorPoints();
  rubik.Init();
//  rubik.Print();
//  for(int i = 0; i < 6; i++) {
//    getBit(i);
//  }
  rubik.Print();
  //servos_test();
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
