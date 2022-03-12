
void Menu_Print() {
  Serial.println(F("M E N U"));
  Serial.println(F("=============="));
  Serial.println(F("i   Iniciar cubo montado"));
  Serial.println(F("a   Afinar motores"));
//  Serial.println(F("F   Rotate front ClockWise"));
//  Serial.println(F("f   Rotate front Counter-ClockWise"));
//  Serial.println(F("R   Rotate right ClockWise"));
//  Serial.println(F("r   Rotate right Counter-ClockWise"));
//  Serial.println(F("U   Rotate up ClockWise"));
//  Serial.println(F("u   Rotate up Counter-ClockWise"));
//  Serial.println(F("L   Rotate left ClockWise"));
//  Serial.println(F("l   Rotate left Counter-ClockWise"));
//  Serial.println(F("D   Rotate down ClockWise"));
//  Serial.println(F("d   Rotate down Conter-ClockWise"));
//  Serial.println(F("B   Rotate back ClockWise"));
//  Serial.println(F("b   Rotate back Conter-ClockWise"));
  Serial.println(F("s   scamble the cube"));
  Serial.println(F("S   Solve the Cube"));
  Serial.println(F(""));
}

void (*on_going)();


void Menu_Process() { 

  if (Serial.available()) {

    switch(Serial.read()) {
        case 'i':
          rubik.Init();
          rubik.Print();
          break;
        case 'a':
          Serial.println(F("escolha o motor a afinar\n"));
          while(Serial.available() == 0) {}
            switch(Serial.read()) {
              case 'B':
                Serial.println(F("B\n"));
                while(true) {
                Up_Back.afinar();
                }
                break;
              case 'R':
                while(true) {
                Up_Right.afinar();
                }
                break;
              case 'F':
                while(true) {
                Up_Front.afinar();
                }
                break;
              case 'L':
                while(true) {
                Up_Left.afinar();
                }
                break;
            }
          //}
          break;
     case 'f':  
        rubik.RotateFrontCCW();  
        ServosCube_Movex();
        ServosFace_BackCCW();
        ServosCube_MoveX();
        rubik.Print();
        break;
      case 'F':  
        rubik.RotateFrontCW();
        ServosCube_Movex();
        ServosFace_BackCW();
        ServosCube_MoveX(); 
        rubik.Print();  
        break;
      case 'r':  
        rubik.RotateRightCCW();
        ServosFace_RightCCW();  
        rubik.Print();
        break;
      case 'R':  
        rubik.RotateRightCW(); 
        ServosFace_RightCW();
        rubik.Print();
        break;
      case 'u':  
        rubik.RotateUpCCW();
        ServosFace_FrontCW();
        rubik.Print();
        break;
      case 'U': 
        rubik.RotateUpCW(); 
        ServosFace_FrontCCW(); 
        rubik.Print();
        break;
      case 'l':  
        rubik.RotateLeftCCW(); 
        ServosFace_LeftCW(); 
        rubik.Print(); 
        break;
      case 'L':  
        rubik.RotateLeftCW();
        ServosFace_LeftCCW();
        rubik.Print();
        break;
      case 'd':  
        rubik.RotateDownCCW(); 
        ServosFace_BackCCW();
        rubik.Print();
        break;
      case 'D':  
        rubik.RotateDownCW(); 
        ServosFace_BackCW();
        rubik.Print();
        break;
      case 'b':  
        rubik.RotateBackCCW();  
        ServosCube_Movex();
        ServosFace_FrontCW();
        ServosCube_MoveX();
        rubik.Print();
        break;
      case 'B':  
        rubik.RotateBackCW();  
        ServosCube_Movex();
        ServosFace_FrontCCW();
        ServosCube_MoveX();
        rubik.Print();
        break;
      case 'X':
        ServosCube_MoveX();
        break;
      case 'x':
        ServosCube_Movex();
        break;
      case 'Z':
        ServosCube_MoveZ();
        break;
      case 'z':
        ServosCube_Movez();
        break;
      case 'Y':
        ServosCube_MoveY();
        break;
      case 'y':
        ServosCube_Movey();
        break;
      case 's':
        rubik.Sramble(30);
        rubik.Print();
        break;
      case 'm':
        Menu_Print();
        break;
      case 'M':
        rubik.Init();
        //sequencia_de_armazenamento();
        break;
      case 'S':                                   
        Serial.print(F("Solving the cube.")); delay(600);
        Serial.print(F(".")); delay(600);
        Serial.print(F(".")); delay(800); Serial.print(F("\n"));
        Serial.print(F("\n")); Serial.print(F("Moves to solve the cube: ")); Serial.print(F("\n"));
        rubik.SolveSequence();
        lightAnimation();
        break;
      case 'p':
        servos_init();
        rubik.Print();
        break;
      default:
        Serial.print(F("Comando Invalido"));
    }
  }
}
