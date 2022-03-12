
void setup() {

  pwm.begin();
  pwm.setPWMFreq(60);

  servos_init();
  Serial.begin(9600); //Can only work with HC-06 with this baud rate
  delay(2000);
  //SetColorPoints();
  rubik.Init();
  sequencia_de_armazenamento();
  rubik.Print();
  //servos_test();
  Menu_Print();
}

void loop() {
//  Menu_Process();
//  servos_test();
  Serial.print(F("Solving the cube.")); delay(600);
  Serial.print(F(".")); delay(600);
  Serial.print(F(".")); delay(800); Serial.print(F("\n"));
  Serial.print(F("\n")); Serial.print(F("Moves to solve the cube: ")); Serial.print(F("\n"));
  rubik.SolveSequence();
  servos_init();
  rubik.Print();
  while(true){}
}
