#define DELAY_BETWEEN_STEPS1 (500) 



void sequencia_de_armazenamento() {

   //face 0 = front
   getBit(RF_FRONT);
   //face 1 = up
   ServosCube_Movex();
   getBit(RF_UP);
   //face 2 = right
   ServosCube_MoveX();
   ServosCube_MoveY();
   getBit(RF_RIGHT);
   //face 3 = back
   ServosCube_MoveY();
   getBit(RF_BACK);
   //face 4 = left
   ServosCube_MoveY();
   getBit(RF_BACK);
   //face 5 = down
   ServosCube_MoveY();
   ServosCube_MoveX();
   getBit(RF_DOWN);

   ServosCube_Movex();
}

/*
void setFaceColors(int face) {
  //int aperto = 20;
  
    delay(DELAY_BETWEEN_STEPS1);      
    Down_Right.rmove(place[2]);
    Down_Left.rmove(place[2]);
    delay(DELAY_BETWEEN_STEPS1);      
    Down_Front.rmove(place[0]);                 
    Down_Back.rmove(place[2]);  
  delay(500);       
  edgeSensor.setColor(face);
  delay(500);
    Down_Front.rmove(place[2]);                
    Down_Back.rmove(place[0]);     
    delay(DELAY_BETWEEN_STEPS1);  
    Down_Right.rmove(place[1]);
    Down_Left.rmove(place[1]);
    delay(DELAY_BETWEEN_STEPS1);   
    Down_Back.rmove(place[3]);   
    Down_Front.rmove(place[3]);       
    delay(DELAY_BETWEEN_STEPS1);    
    Down_Right.rmove((place[0] + 20));
    Down_Left.rmove(place[2]);   
  delay(500);       
  cornerSensor.setColor(face);
  delay(500);
    Down_Right.rmove(place[1]);
    Down_Left.rmove(place[1]); 
    delay(DELAY_BETWEEN_STEPS1); 
    Down_Front.rmove(place[2]);                
    Down_Back.rmove(place[0]);  
    delay(DELAY_BETWEEN_STEPS1);   
    Down_Right.rmove(place[2]);
    Down_Left.rmove(place[2]);        
    delay(200); 
    Down_Front.rmove(place[1]);                
    Down_Back.rmove(place[1]);  
    delay(200);   
    Down_Right.rmove(place[1]);
    Down_Left.rmove(place[1]);  
    delay(DELAY_BETWEEN_STEPS1);      
}

void SetColorPoints() {

  int cor[] = {RC_ORANGE, RC_GREEN, RC_RED, RC_BLUE};
  for(int i = 0; i < 4; i++) {
      setFaceColors(cor[i]);    
      ServosCube_MoveZ();
  }
  delay(1000);
  ServosCube_MoveX();
    setFaceColors(RC_YELLOW);
  ServosCube_Movex();
  delay(DELAY_BETWEEN_STEPS1);      
  ServosCube_Movex();
  delay(1000);
    setFaceColors(RC_WHITE);
  ServosCube_MoveX();
}*/
