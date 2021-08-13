#define S2 2
#define S3 3
#define COLOR_IN1 4
#define COLOR_IN2 5
#define LED1 6
#define LED2 7

unsigned long redFrequency = 0;
unsigned long greenFrequency = 0;
unsigned long blueFrequency = 0;

void getBit() {
  
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
