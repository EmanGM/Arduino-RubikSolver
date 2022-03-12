#define S2 2
#define S3 3
#define COLOR_IN1 4
#define COLOR_IN2 5
#define LED1 6
#define LED2 7

unsigned long redFrequency = 0;
unsigned long greenFrequency = 0;
unsigned long blueFrequency = 0;


void getBit(int currentFace) {
  
  int sticker = 0;
  while(sticker < 9) {
    if(Serial.available() > 0)  {
      char Incoming_value = Serial.read(); 
      Serial.print(Incoming_value);
      Serial.print("\n");
      int color = 0;
      switch(Incoming_value) {
        case 'G':
          color = RC_GREEN;
          break;
        case 'R':
          color = RC_RED;
          break;
        case 'B':
          color = RC_BLUE;
          break;
        case 'Y':
          color = RC_YELLOW;
          break;
        case 'W':
          color = RC_WHITE;
          break;
        case 'O':
          color = RC_ORANGE;
          break;
        default:
          Serial.print("Erro + \'");
          Serial.print(Incoming_value);
          Serial.print("\'");
      }
      if(Incoming_value == 'G') {
        color = RC_GREEN;
      }
      Rubik[currentFace][sticker++] = color;
    }      
  }
}


void lightAnimation() {
  
  for(int i = 0; i < 8; i++) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(200);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(200);
  }
}
