#include <avr/pgmspace.h>

#define ProgStrArray_Index(prog_str_array, i)  (char*)pgm_read_word(&(prog_str_array[i]))

class Cubo {
  public:
    Cubo() {
      
    }
    void Init() {
      // preencher cores
      //________________________________________________________________
      int face;
      int i;
      for (face = 0; face < RF_TOTAL_FACES; face ++) {
        for (i = 0; i < 9; i++) {
            int color = Rubik_FaceToColorLUT[face];
            Rubik[face][i] = color;
        }
      }
    }

    void Print();

    
    void Rubik_Rotate(char rot, bool motorsMove) {
 // static char storeMove;
  bool MotorRotate = motorsMove;
/*
  if((storeMove == rot) && (rot != 'Y')){
    Serial.print("2 ");   
    MotorRotate = false; 
    HTM--;
  } else {
    Serial.print(" ");    
    MotorRotate = true; 
    HTM++;  QTM++;
  }
  storeMove = rot;
 */ 
  switch(rot) {
    case 'f':  
      RotateFrontCCW();  
      if(MotorRotate == true){
        ServosCube_Movex();
        ServosFace_BackCCW();
        ServosCube_MoveX();
      } 
      Serial.print(F("F'"));
      break;
    case 'F':  
      RotateFrontCW();
      if(MotorRotate == true){
        ServosCube_Movex();
        ServosFace_BackCW();
        ServosCube_MoveX(); 
      }   
      Serial.print(F("F")); 
      break;
    case 'r':  
      RotateRightCCW();
      if(MotorRotate == true){ 
        ServosFace_RightCCW();  
      }  
      Serial.print(F("R'"));
      break;
    case 'R':  
      RotateRightCW(); 
      if(MotorRotate == true){
        ServosFace_RightCW();  
      }  
      Serial.print(F("R"));  
      break;
    case 'u':  
      RotateUpCCW();
      if(MotorRotate == true){     
        ServosFace_FrontCW();
      }
      Serial.print(F("U'"));
      break;
    case 'U': 
      RotateUpCW(); 
      if(MotorRotate == true){     
        ServosFace_FrontCCW(); 
      }   
      Serial.print(F("U")); 
      break;
    case 'l':  
      RotateLeftCCW(); 
      if(MotorRotate == true){ 
        ServosFace_LeftCW();  
      }   
      Serial.print(F("L'"));
      break;
    case 'L':  
      RotateLeftCW();
      if(MotorRotate == true){
        ServosFace_LeftCCW();     
      }   
      Serial.print(F("L"));
      break;
    case 'd':  
      RotateDownCCW(); 
      if(MotorRotate == true){
        ServosFace_BackCCW();  
      }  
      Serial.print(F("D'")); 
      break;
    case 'D':  
      RotateDownCW(); 
      if(MotorRotate == true){ 
        ServosFace_BackCW();    
      }  
      Serial.print(F("D"));
      break;
    case 'b':  
      RotateBackCCW();  
      if(MotorRotate == true){
        ServosCube_Movex();
        ServosFace_FrontCW();
        ServosCube_MoveX();
      }  
      Serial.print(F("B'")); 
      break;
    case 'B':  
      RotateBackCW();  
      if(MotorRotate == true){  
        ServosCube_Movex();
        ServosFace_FrontCCW();
        ServosCube_MoveX();
      }   
      Serial.print(F("B")); 
      break;
    case 'Y':  
      RotateY();
      if(MotorRotate == true){  
        ServosCube_MoveZ();
      }  
      if((HTM > 0) && (QTM > 0)) {
        HTM--;  QTM--;
      }  
      break;
  }
  if(MotorRotate == true){  
    Print();
  }
}


  void RotateStr(String sequence) {
  
    for (int i = 0; i < sequence.length(); i++) {
      Rubik_Rotate(sequence.charAt(i), false);
      resolutionStr += sequence.charAt(i);
    }
  }

  void RotateStr_Progmem(char *sequence) {
    static char buff[30];
    
    strcpy_P(buff, sequence);
    int len = strlen(buff);
  
    
    for (int i = 0; i < len; i++) {
      Rubik_Rotate(buff[i], false);
      resolutionStr += buff[i];
    }
  }

    void ProcessStr(int caze = 0) {
      bool flag = true;
      while(flag == true) {
        flag = false;
        for(int i = 0; i < resolutionStr.length(); i++) {
          switch(caze) {
            case 0:
              if(resolutionStr[i] == 'r' && resolutionStr[i + 1] == 'R' || resolutionStr[i] == 'R' && resolutionStr[i + 1] == 'r' ||
                resolutionStr[i] == 'l' && resolutionStr[i + 1] == 'L'  || resolutionStr[i] == 'L' && resolutionStr[i + 1] == 'l' ||
                resolutionStr[i] == 'f' && resolutionStr[i + 1] == 'F'  || resolutionStr[i] == 'F' && resolutionStr[i + 1] == 'f' ||
                resolutionStr[i] == 'b' && resolutionStr[i + 1] == 'B'  || resolutionStr[i] == 'B' && resolutionStr[i + 1] == 'b' ||
                resolutionStr[i] == 'u' && resolutionStr[i + 1] == 'U'  || resolutionStr[i] == 'U' && resolutionStr[i + 1] == 'u' ||
                resolutionStr[i] == 'd' && resolutionStr[i + 1] == 'D'  || resolutionStr[i] == 'D' && resolutionStr[i + 1] == 'd') {
                  resolutionStr.remove(i, 2);
                  i++;
                  flag = true;
                  //Serial.print("  C1  "); 
              } else if((resolutionStr[i] == resolutionStr[i + 1]) && (resolutionStr[i] == resolutionStr[i + 2])) {
                  if(isUpperCase(resolutionStr[i])) {
                    resolutionStr[i] = toLowerCase(resolutionStr[i]);
                  } else {
                    resolutionStr[i] = toUpperCase(resolutionStr[i]);
                  }
                  resolutionStr.remove(i + 1, 2);
                  i++;
                  flag = true;
                  //Serial.print("  C2  "); 
              } else if((resolutionStr[i] == resolutionStr[i + 1]) &&  (resolutionStr[i] == resolutionStr[i + 2]) && (resolutionStr[i] == resolutionStr[i + 3])) {
                resolutionStr.remove(i, 4);
                i++;
                flag = true;
                //Serial.print("  C3  "); 
              }
              break;
            case 1:
              if(resolutionStr[i] == 'r' && resolutionStr[i + 1] == 'r' || resolutionStr[i] == 'R' && resolutionStr[i + 1] == 'R' ||
                resolutionStr[i] == 'l' && resolutionStr[i + 1] == 'l'  || resolutionStr[i] == 'L' && resolutionStr[i + 1] == 'L' ||
                resolutionStr[i] == 'f' && resolutionStr[i + 1] == 'F'  || resolutionStr[i] == 'F' && resolutionStr[i + 1] == 'F' ||
                resolutionStr[i] == 'b' && resolutionStr[i + 1] == 'b'  || resolutionStr[i] == 'B' && resolutionStr[i + 1] == 'B' ||
                resolutionStr[i] == 'u' && resolutionStr[i + 1] == 'u'  || resolutionStr[i] == 'U' && resolutionStr[i + 1] == 'U' ||
                resolutionStr[i] == 'd' && resolutionStr[i + 1] == 'd'  || resolutionStr[i] == 'D' && resolutionStr[i + 1] == 'D') {
                  resolutionStr[i + 1] = '2';
                  i++;
                  flag = true;
                  //Serial.print("  C4  "); 
              } 
              break;
            case 2:
              return;
              break;
            }
          }
          //Serial.print("\nResolução = ");  Serial.print(resolutionStr);  Serial.print(F("\n")); 
       }
       
       //Rubik_ProcessStr(caze + 1);
    }
  
    void SolveSequence() {
      CopyCube(Rubik, Rubik_ToSolve);
      Print();
      delay(1000);
      Solve_WhiteCross_1 ();
      Solve_WhiteCross_2 ();
      Solve_WhiteCross_3 ();
      Solve_WhiteCross_4 ();
      Solve_WhiteCross_5 ();
      Solve_WhiteCross_6 ();
      SolveF2L();
      Solve_OLL();
      Solve_PLL();
      ProcessStr();
      CopyCube(Rubik_ToSolve, Rubik);
      for(int i = 0; i < resolutionStr.length(); i++) {
        Rubik_Rotate(resolutionStr.charAt(i), true);
      }
      Serial.print("\nResolução = ");  Serial.print(resolutionStr);  Serial.print(F("\n")); 
      Serial.print("        (HTM = ");  Serial.print(HTM);  Serial.print(F(")")); 
      Serial.print("  (QTM = ");  Serial.print(QTM);  Serial.print(F(")"));  Serial.print(F("\n"));
      Print();
    }
  
    void Sramble(int rotations_count) {
      static const char rotations[] = {'f', 'F', 'r', 'R', 'u', 'U', 'l', 'L', 'd', 'D', 'b', 'B'};
    
      randomSeed(millis()); // iniciar gerador peseudo-aleatório
      
      for (int i = 0; i < rotations_count; i++) {
        char i_rot = random(sizeof(rotations)); // gerar nÃºmero aleatÃ³rio entre 0 e o número de opÃ§Ãµes de rotaÃ§Ã£o (tamanho do array rotations - 12)
        Rubik_Rotate(rotations[i_rot], false);
      }
      Serial.println(F("\n"));
    }

    void CopyCube(unsigned char de[][9], unsigned char para[][9]) {

      Serial.print(F("A")); 
      for (int face = 0; face < RF_TOTAL_FACES; face ++) {
        for (int i = 0; i < 9; i++) {
            para[face][i] = de[face][i];
        }
      }
    }
    
  private:
    //unsigned char Rubik[RF_TOTAL_FACES][9];
    unsigned char Rubik_Backup[RF_TOTAL_FACES][9];
    unsigned char Rubik_ToSolve[RF_TOTAL_FACES][9];

    String resolutionStr = "";
    
    int QTM;
    int HTM;

  public:
    void RotateRightCW();
    void RotateRightCCW();
    void RotateLeftCW();
    void RotateLeftCCW();
    void RotateUpCW();
    void RotateUpCCW();
    void RotateDownCW();
    void RotateDownCCW();
    void RotateFrontCW();
    void RotateFrontCCW();
    void RotateBackCW();
    void RotateBackCCW();
    void RotateY();

  private:
    void MakeBackup() {
      int face , i;
      for (face = 0; face < RF_TOTAL_FACES; face++) {
        for (i = 0; i < 9; i++) {
            Rubik_Backup [face][i] = Rubik [face][i];
        }
      }
    }
};

Cubo rubik;

//__________________________________________________________________________________
// RotaÃ§Ãµes:
//__________________________________________________________________________________
//
// RotaÃ§Ã£o da face da frente:
//____________________________________________________________

void Cubo::RotateFrontCCW () {
  MakeBackup();
  //Cantos da face
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_FRONT][6];
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_FRONT][0];
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_FRONT][2];
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_FRONT][8];
  //Edges da face
  Rubik[RF_FRONT][1] = Rubik_Backup[RF_FRONT][3];
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_FRONT][1];
  Rubik[RF_FRONT][7] = Rubik_Backup[RF_FRONT][5];
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_FRONT][7];
  //3 peÃ§as de cima movem-se para a esquerda
  Rubik[RF_UP][0] = Rubik_Backup[RF_RIGHT][6];
  Rubik[RF_UP][1] = Rubik_Backup[RF_RIGHT][3];
  Rubik[RF_UP][2] = Rubik_Backup[RF_RIGHT][0];
  //3 peÃ§as da direita movem-se para cima
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_DOWN][8];
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_DOWN][7];
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_DOWN][6];
  //3 peÃ§as de baixo movem-se para a direita
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_LEFT][2];
  Rubik[RF_DOWN][7] = Rubik_Backup[RF_LEFT][5];
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_LEFT][8];
  //3 peÃ§as da esquerda movem-se para baixo
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_UP][0];
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_UP][1];
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_UP][2];
}

void Cubo::RotateFrontCW () {
  MakeBackup();
  //Cantos da face
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_FRONT][2];
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_FRONT][8];
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_FRONT][6];
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_FRONT][0];
  //Edges da face
  Rubik[RF_FRONT][1] = Rubik_Backup[RF_FRONT][5];
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_FRONT][7];
  Rubik[RF_FRONT][7] = Rubik_Backup[RF_FRONT][3];
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_FRONT][1];
  //3 peÃ§as de cima movem-se para a direita
  Rubik[RF_UP][0] = Rubik_Backup[RF_LEFT][2];
  Rubik[RF_UP][1] = Rubik_Backup[RF_LEFT][5];
  Rubik[RF_UP][2] = Rubik_Backup[RF_LEFT][8];
  //3 peÃ§as da direita movem-se para baixo
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_UP][0];
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_UP][1];
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_UP][2];
  //3 peÃ§as de baixo movem-se para a esquerda
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_RIGHT][6];
  Rubik[RF_DOWN][7] = Rubik_Backup[RF_RIGHT][3];
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_RIGHT][0];
  //3 peÃ§as da esquerda movem-se para cima
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_DOWN][8];
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_DOWN][7];
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_DOWN][6];
}


// RotaÃ§Ã£o da face da direita:
//________________________________________________________________
void Cubo::RotateRightCW () {
  MakeBackup();
  //Cantos da direita
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_RIGHT][2];
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_RIGHT][8];
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_RIGHT][6];
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_RIGHT][0];
  //Eges da direita
  Rubik[RF_RIGHT][1] = Rubik_Backup[RF_RIGHT][5];
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_RIGHT][7];
  Rubik[RF_RIGHT][7] = Rubik_Backup[RF_RIGHT][3];
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_RIGHT][1];
  //3 peÃ§as de cima movem-se para trÃ¡s.
  Rubik[RF_UP][2] = Rubik_Backup[RF_FRONT][2];
  Rubik[RF_UP][5] = Rubik_Backup[RF_FRONT][5];
  Rubik[RF_UP][8] = Rubik_Backup[RF_FRONT][8];
  //3 peÃ§as de trÃ¡s movem-se para baixo
  Rubik[RF_BACK][6] = Rubik_Backup[RF_UP][2];
  Rubik[RF_BACK][3] = Rubik_Backup[RF_UP][5];
  Rubik[RF_BACK][0] = Rubik_Backup[RF_UP][8];
  //3 peÃ§as de baixo movem-se para a frente
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_BACK][6];
  Rubik[RF_DOWN][5] = Rubik_Backup[RF_BACK][3];
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_BACK][0];
  //3 peÃ§as da frente movem-se para cima
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_DOWN][2];
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_DOWN][5];
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_DOWN][8];
}

void Cubo::RotateRightCCW () {
  MakeBackup();
  //Cantos da direita
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_RIGHT][6];
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_RIGHT][0];
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_RIGHT][2];
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_RIGHT][8];
  //Edges da direita
  Rubik[RF_RIGHT][1] = Rubik_Backup[RF_RIGHT][3];
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_RIGHT][1];
  Rubik[RF_RIGHT][7] = Rubik_Backup[RF_RIGHT][5];
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_RIGHT][7];
  //3 peÃ§as de cima movem-se para a frente
  Rubik[RF_UP][8] = Rubik_Backup[RF_BACK][0];
  Rubik[RF_UP][5] = Rubik_Backup[RF_BACK][3];
  Rubik[RF_UP][2] = Rubik_Backup[RF_BACK][6];
  //3 peÃ§as da frente movem-se para baixo
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_UP][8];
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_UP][5];
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_UP][2];
  //3 peÃ§as de baixo movem-se para trÃ¡s
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_FRONT][8];
  Rubik[RF_DOWN][5] = Rubik_Backup[RF_FRONT][5];
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_FRONT][2];
  //3 peÃ§as de trÃ¡s movem-se para cima
  Rubik[RF_BACK][0] = Rubik_Backup[RF_DOWN][8];
  Rubik[RF_BACK][3] = Rubik_Backup[RF_DOWN][5];
  Rubik[RF_BACK][6] = Rubik_Backup[RF_DOWN][2];
}


// RotaÃ§Ã£o da face de cima
//________________________________________________________________
void Cubo::RotateUpCW () {
  MakeBackup();
  //Cantos de cima
  Rubik[RF_UP][0] = Rubik_Backup[RF_UP][2];
  Rubik[RF_UP][2] = Rubik_Backup[RF_UP][8];
  Rubik[RF_UP][8] = Rubik_Backup[RF_UP][6];
  Rubik[RF_UP][6] = Rubik_Backup[RF_UP][0];
  //Edges de cima
  Rubik[RF_UP][1] = Rubik_Backup[RF_UP][5];
  Rubik[RF_UP][5] = Rubik_Backup[RF_UP][7];
  Rubik[RF_UP][7] = Rubik_Backup[RF_UP][3];
  Rubik[RF_UP][3] = Rubik_Backup[RF_UP][1];
  //3 peÃ§as de trÃ¡s movem-se para a direita
  Rubik[RF_BACK][8] = Rubik_Backup[RF_LEFT][8];
  Rubik[RF_BACK][7] = Rubik_Backup[RF_LEFT][7];
  Rubik[RF_BACK][6] = Rubik_Backup[RF_LEFT][6];
  //3 peÃ§as da direita movem-se para a frente
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_BACK][8];
  Rubik[RF_RIGHT][7] = Rubik_Backup[RF_BACK][7];
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_BACK][6];
  //3 peÃ§as da frente movem-se para a esquerda
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_RIGHT][8];
  Rubik[RF_FRONT][7] = Rubik_Backup[RF_RIGHT][7];
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_RIGHT][6];
  //3 peÃ§as da esquerda movem-se para trÃ¡s
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_FRONT][8];
  Rubik[RF_LEFT][7] = Rubik_Backup[RF_FRONT][7];
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_FRONT][6];
}

void Cubo::RotateUpCCW () {
  MakeBackup();
  //Cantos de cima
  Rubik[RF_UP][0] = Rubik_Backup[RF_UP][6];
  Rubik[RF_UP][2] = Rubik_Backup[RF_UP][0];
  Rubik[RF_UP][8] = Rubik_Backup[RF_UP][2];
  Rubik[RF_UP][6] = Rubik_Backup[RF_UP][8];
  //Edges de cima
  Rubik[RF_UP][1] = Rubik_Backup[RF_UP][3];
  Rubik[RF_UP][5] = Rubik_Backup[RF_UP][1];
  Rubik[RF_UP][7] = Rubik_Backup[RF_UP][5];
  Rubik[RF_UP][3] = Rubik_Backup[RF_UP][7];
  //3 peÃ§as de trÃ¡s movem-se para a esquerda
  Rubik[RF_BACK][6] = Rubik_Backup[RF_RIGHT][6];
  Rubik[RF_BACK][7] = Rubik_Backup[RF_RIGHT][7];
  Rubik[RF_BACK][8] = Rubik_Backup[RF_RIGHT][8];
  //3 peÃ§as da esquerda movem-se para a frente
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_BACK][6];
  Rubik[RF_LEFT][7] = Rubik_Backup[RF_BACK][7];
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_BACK][8];
  //3 peÃ§as de frente movem-se para a direita
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_LEFT][6];
  Rubik[RF_FRONT][7] = Rubik_Backup[RF_LEFT][7];
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_LEFT][8];
  //3 peÃ§as da direita movem-se para trÃ¡s
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_FRONT][6];
  Rubik[RF_RIGHT][7] = Rubik_Backup[RF_FRONT][7];
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_FRONT][8];
}


// RotaÃ§Ã£o da face da esquerda
//________________________________________________________________
void Cubo::RotateLeftCW () {
  MakeBackup();
  //Cantos da esquerda
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_LEFT][2];
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_LEFT][8];
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_LEFT][6];
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_LEFT][0];
  //Edges da esquerda
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_LEFT][1];
  Rubik[RF_LEFT][1] = Rubik_Backup[RF_LEFT][5];
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_LEFT][7];
  Rubik[RF_LEFT][7] = Rubik_Backup[RF_LEFT][3];
  //3 peÃ§as de cima movem-se para a frente
  Rubik[RF_UP][6] = Rubik_Backup[RF_BACK][2];
  Rubik[RF_UP][3] = Rubik_Backup[RF_BACK][5];
  Rubik[RF_UP][0] = Rubik_Backup[RF_BACK][8];
  //3 peÃ§as da frente movem-se para baixo
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_UP][6];
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_UP][3];
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_UP][0];
  //3 peÃ§as de baixo movem-se para trÃ¡s
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_FRONT][6];
  Rubik[RF_DOWN][3] = Rubik_Backup[RF_FRONT][3];
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_FRONT][0];
  //3 peÃ§as de trÃ¡s movem-se para cima
  Rubik[RF_BACK][2] = Rubik_Backup[RF_DOWN][6];
  Rubik[RF_BACK][5] = Rubik_Backup[RF_DOWN][3];
  Rubik[RF_BACK][8] = Rubik_Backup[RF_DOWN][0];
}

void Cubo::RotateLeftCCW () {
  MakeBackup();
  //Cantos da esquerda
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_LEFT][6];
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_LEFT][0];
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_LEFT][2];
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_LEFT][8];
  //Edges da esquerda
  Rubik[RF_LEFT][1] = Rubik_Backup[RF_LEFT][3];
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_LEFT][1];
  Rubik[RF_LEFT][7] = Rubik_Backup[RF_LEFT][5];
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_LEFT][7];
  //3 peÃ§as de cima movem-se para trÃ¡s
  Rubik[RF_UP][0] = Rubik_Backup[RF_FRONT][0];
  Rubik[RF_UP][3] = Rubik_Backup[RF_FRONT][3];
  Rubik[RF_UP][6] = Rubik_Backup[RF_FRONT][6];
  //3 peÃ§as de trÃ¡s movem-se para baixo
  Rubik[RF_BACK][8] = Rubik_Backup[RF_UP][0];
  Rubik[RF_BACK][5] = Rubik_Backup[RF_UP][3];
  Rubik[RF_BACK][2] = Rubik_Backup[RF_UP][6];
  //3 peÃ§as de baixo movem-se para a frente
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_BACK][8];
  Rubik[RF_DOWN][3] = Rubik_Backup[RF_BACK][5];
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_BACK][2];
  //3 peÃ§as da frente movem-se para cima
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_DOWN][0];
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_DOWN][3];
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_DOWN][6];
}


// RotaÃ§Ã£o da face de baixo
//________________________________________________________________
void Cubo::RotateDownCW () {
  MakeBackup();
  //Cantos de baixo
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_DOWN][0];
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_DOWN][6];
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_DOWN][8];
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_DOWN][2];
  //Edges de baixo
  Rubik[RF_DOWN][7] = Rubik_Backup[RF_DOWN][3];
  Rubik[RF_DOWN][5] = Rubik_Backup[RF_DOWN][7];
  Rubik[RF_DOWN][1] = Rubik_Backup[RF_DOWN][5];
  Rubik[RF_DOWN][3] = Rubik_Backup[RF_DOWN][1];
  //3 peÃ§as da frente movem-se para a direita
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_LEFT][0];
  Rubik[RF_FRONT][1] = Rubik_Backup[RF_LEFT][1];
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_LEFT][2];
  //3 peÃ§as da direita movem-se para trÃ¡s
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_FRONT][0];
  Rubik[RF_RIGHT][1] = Rubik_Backup[RF_FRONT][1];
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_FRONT][2];
  //3 peÃ§as e trÃ¡s movem-se para a esquerda
  Rubik[RF_BACK][0] = Rubik_Backup[RF_RIGHT][0];
  Rubik[RF_BACK][1] = Rubik_Backup[RF_RIGHT][1];
  Rubik[RF_BACK][2] = Rubik_Backup[RF_RIGHT][2];
  //3 peÃ§as da esquerda movem-se para a frente
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_BACK][0];
  Rubik[RF_LEFT][1] = Rubik_Backup[RF_BACK][1];
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_BACK][2];
}

void Cubo::RotateDownCCW () {
  MakeBackup();
  //Cantos de baixo
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_DOWN][8];
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_DOWN][6];
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_DOWN][0];
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_DOWN][2];
  //Edges de baixo
  Rubik[RF_DOWN][7] = Rubik_Backup[RF_DOWN][5];
  Rubik[RF_DOWN][3] = Rubik_Backup[RF_DOWN][7];
  Rubik[RF_DOWN][1] = Rubik_Backup[RF_DOWN][3];
  Rubik[RF_DOWN][5] = Rubik_Backup[RF_DOWN][1];
  //3 peÃ§as da frente movem-se para a esquerda
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_RIGHT][2];
  Rubik[RF_FRONT][1] = Rubik_Backup[RF_RIGHT][1];
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_RIGHT][0];
  //3 peÃ§as da esquerda movem-se para trÃ¡s
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_FRONT][2];
  Rubik[RF_LEFT][1] = Rubik_Backup[RF_FRONT][1];
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_FRONT][0];
  //3 peÃ§as e trÃ¡s movem-se para a direita
  Rubik[RF_BACK][2] = Rubik_Backup[RF_LEFT][2];
  Rubik[RF_BACK][1] = Rubik_Backup[RF_LEFT][1];
  Rubik[RF_BACK][0] = Rubik_Backup[RF_LEFT][0];
  //3 peÃ§as da direita movem-se para a frente
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_BACK][2];
  Rubik[RF_RIGHT][1] = Rubik_Backup[RF_BACK][1];
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_BACK][0];
}

// RotaÃ§Ã£o da face de trÃ¡s
//________________________________________________________________
void Cubo::RotateBackCW () {
  MakeBackup();
  //Cantos de trÃ¡s
  Rubik[RF_BACK][0] = Rubik_Backup[RF_BACK][2];
  Rubik[RF_BACK][6] = Rubik_Backup[RF_BACK][0];
  Rubik[RF_BACK][8] = Rubik_Backup[RF_BACK][6];
  Rubik[RF_BACK][2] = Rubik_Backup[RF_BACK][8];
  //Edges de trÃ¡s
  Rubik[RF_BACK][1] = Rubik_Backup[RF_BACK][5];
  Rubik[RF_BACK][3] = Rubik_Backup[RF_BACK][1];
  Rubik[RF_BACK][7] = Rubik_Backup[RF_BACK][3];
  Rubik[RF_BACK][5] = Rubik_Backup[RF_BACK][7];
  //3 peÃ§as de cima movem-se para a direita
  Rubik[RF_UP][8] = Rubik_Backup[RF_RIGHT][2];
  Rubik[RF_UP][7] = Rubik_Backup[RF_RIGHT][5];
  Rubik[RF_UP][6] = Rubik_Backup[RF_RIGHT][8];
  //3 peÃ§as da direita movem-se para baixo
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_UP][8];
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_UP][7];
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_UP][6];
  //3 peÃ§as de baixo movem-se para a esquerda
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_LEFT][6];
  Rubik[RF_DOWN][1] = Rubik_Backup[RF_LEFT][3];
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_LEFT][0];
  //3 peÃ§as de esquerda movem-se para cima
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_DOWN][0];
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_DOWN][1];
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_DOWN][2];
}

void Cubo::RotateBackCCW () {
  MakeBackup();
  //Cantos de trÃ¡s
  Rubik[RF_BACK][0] = Rubik_Backup[RF_BACK][6];
  Rubik[RF_BACK][2] = Rubik_Backup[RF_BACK][0];
  Rubik[RF_BACK][8] = Rubik_Backup[RF_BACK][2];
  Rubik[RF_BACK][6] = Rubik_Backup[RF_BACK][8];
  //Edges de trÃ¡s
  Rubik[RF_BACK][1] = Rubik_Backup[RF_BACK][3];
  Rubik[RF_BACK][5] = Rubik_Backup[RF_BACK][1];
  Rubik[RF_BACK][7] = Rubik_Backup[RF_BACK][5];
  Rubik[RF_BACK][3] = Rubik_Backup[RF_BACK][7];
  //3 peÃ§as de cima movem-se para a esquerda
  Rubik[RF_UP][6] = Rubik_Backup[RF_LEFT][0];
  Rubik[RF_UP][7] = Rubik_Backup[RF_LEFT][3];
  Rubik[RF_UP][8] = Rubik_Backup[RF_LEFT][6];
  //3 peÃ§as da esquerda movem-se para baixo
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_UP][6];
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_UP][7];
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_UP][8];
  //3 peÃ§as de baixo movem-se para a direita
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_RIGHT][8];
  Rubik[RF_DOWN][1] = Rubik_Backup[RF_RIGHT][5];
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_RIGHT][2];
  //3 peÃ§as da direita movem-se para cima
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_DOWN][2];
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_DOWN][1];
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_DOWN][0];
}

void Cubo::RotateY() {
  RotateUpCCW ();
  RotateDownCW ();
  MakeBackup();
  //Mover toda a 2ª camada do cubo
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_LEFT][5];
  Rubik[RF_FRONT][4] = Rubik_Backup[RF_LEFT][4];
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_LEFT][3];
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_BACK][5];
  Rubik[RF_LEFT][4] = Rubik_Backup[RF_BACK][4];
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_BACK][3];
  Rubik[RF_BACK][5] = Rubik_Backup[RF_RIGHT][5];
  Rubik[RF_BACK][4] = Rubik_Backup[RF_RIGHT][4];
  Rubik[RF_BACK][3] = Rubik_Backup[RF_RIGHT][3];
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_FRONT][5];
  Rubik[RF_RIGHT][4] = Rubik_Backup[RF_FRONT][4];
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_FRONT][3];
}
 
  
