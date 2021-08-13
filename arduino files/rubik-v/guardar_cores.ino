#define DELAY_BETWEEN_STEPS1 (500) 


void store_colours(int centerColor, int edgeNumb, int cornerNumb) {

  delay(200);
  Down_Back.rmove(place[3]);
  Rubik[centerColor][edgeNumb] = edgeSensor.ReadColor();
  Rubik[centerColor][cornerNumb] = cornerSensor.ReadColor();
  delay(200);
  Down_Back.rmove(place[1]);
  
}

void sequencia_de_armazenamento() {

    //primeira rotação total:
    store_colours(RC_ORANGE, 1, 8);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveZ();
    store_colours(RC_GREEN, 1, 8);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveX();
    store_colours(RC_YELLOW, 5, 6);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveZ();
    store_colours(RC_RED, 5, 6);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveZ();
    store_colours(RC_WHITE, 5, 6);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveX();
    store_colours(RC_BLUE, 1, 8);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveZ();
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movey();

    //Segunda rotação total
    Serial.println("Segunda Rotação");
    store_colours(RC_ORANGE, 3, 2);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movex();
    store_colours(RC_GREEN, 3, 2);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveZ();
    store_colours(RC_YELLOW, 1, 8);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movex();
    store_colours(RC_RED, 1, 8);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movex();
    store_colours(RC_WHITE, 1, 8);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveZ();
    store_colours(RC_BLUE, 3, 2);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movex();
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movey();

    //terceira rotação total:
    Serial.println("terceira Rotação");
    store_colours(RC_ORANGE, 7, 0);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movez();
    store_colours(RC_GREEN, 7, 0);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movex();
    store_colours(RC_YELLOW, 3, 2);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movez();
    store_colours(RC_RED, 3, 2);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movez();
    store_colours(RC_WHITE, 3, 2);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movex();
    store_colours(RC_BLUE, 7, 0);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movez();
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movey();

    //Quarta rotação total:
    Serial.println("Quarta Rotação");
    store_colours(RC_ORANGE, 5, 6);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveX();
    store_colours(RC_GREEN, 5, 6);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movez();
    store_colours(RC_YELLOW, 7, 0);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveX();
    store_colours(RC_RED, 7, 0);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveX();
    store_colours(RC_WHITE, 7, 0);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movez();
    store_colours(RC_BLUE, 5, 6);
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_MoveX();
    delay(DELAY_BETWEEN_STEPS1);
    ServosCube_Movey();
}

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
}
