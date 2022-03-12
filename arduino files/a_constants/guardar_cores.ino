#define DELAY_BETWEEN_STEPS1 (500) 
#define APERTO (4)


static void clearVision() {
  
  Down_Right.rmove(place[3]);
  Down_Left.rmove(place[3]);
  delay(DELAY_BETWEEN_STEPS1);
  Down_Front.rmove(place[1] + APERTO);
  Down_Back.rmove(place[1] + APERTO);
  delay(DELAY_BETWEEN_STEPS1);
  Up_Back.Rotate(0);
  Up_Front.Rotate(180);
  
}

void sequencia_de_armazenamento() {

   //face 0 = right
   clearVision();
   getBit(RF_RIGHT);
   Up_Back.Rotate(180);
   Up_Front.Rotate(0);
   //face 1 = left
   getBit(RF_LEFT);
   Up_Front.Rotate(90);
   Up_Back.Rotate(90);
   Down_Front.rmove(place[1]);
   Down_Back.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1);
   Down_Right.rmove(place[1] + APERTO);
   Down_Left.rmove(place[1] + APERTO);
   delay(DELAY_BETWEEN_STEPS1);
   Down_Front.rmove(place[3]);
   Down_Back.rmove(place[3]);
   delay(DELAY_BETWEEN_STEPS1);
   Up_Right.Rotate(0);
   Up_Left.Rotate(180);
   //face 2 = Up
   getBit(RF_UP);
   Up_Right.Rotate(180);
   Up_Left.Rotate(0);
   //face 3 = Down
   getBit(RF_DOWN);
   Up_Right.Rotate(90);
   Up_Left.Rotate(90);
   Down_Right.rmove(place[1]);
   Down_Left.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1);
   Down_Back.rmove(place[1]);
   Down_Front.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1);
   ServosCube_MoveZ();
   //face 4 = front
   clearVision();
   getBit(RF_FRONT);
   Up_Back.Rotate(180);
   Up_Front.Rotate(0);
   //face 5 = back
   getBit(RF_BACK);
   Up_Back.Rotate(90);
   Up_Front.Rotate(90);
   Down_Front.rmove(place[1]);
   Down_Back.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1);
   Down_Left.rmove(place[1]);
   Down_Right.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1);
   ServosCube_Movez();
   delay(DELAY_BETWEEN_STEPS1);
}
