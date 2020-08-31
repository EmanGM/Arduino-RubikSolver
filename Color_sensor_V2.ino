#define S2 2
#define S3 3
#define COLOR_IN1 4
#define COLOR_IN2 5
#define LED1 6
#define LED2 7

unsigned long redFrequency = 0;
unsigned long greenFrequency = 0;
unsigned long blueFrequency = 0;

void ColorSensorBegin();
void ColorSensorBegin() {                                                                                                                                   
  
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(COLOR_IN1, INPUT);
  pinMode(COLOR_IN2, INPUT);

  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);

  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, HIGH);
}

int getRed(bool isEdgeSensor);
int getGreen(bool isEdgeSensor);
int getBlue(bool isEdgeSensor);

class ColorSensor {
  private:
  int ColorGuide[6][3];
  bool isEdgeSensor;
  
  public:

  ColorSensor(bool isEdgeSensor) {
    this->isEdgeSensor = isEdgeSensor;
  }
  
  void testValues() {

  int pin = (isEdgeSensor == true) ? COLOR_IN1 : COLOR_IN2; 
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  redFrequency = pulseIn(pin, LOW);

  // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redFrequency);
  delay(100);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  greenFrequency = pulseIn(pin, LOW);

  // Printing the GREEN (G) value
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  delay(100);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  blueFrequency = pulseIn(pin, LOW);

  // Printing the BLUE (B) value
  Serial.print(" B = ");
  Serial.print(blueFrequency);
  delay(100);

  Serial.print("\n");
}

  int ReadColor() {
  //Tempo de prevenção:
  delay(200);
  
  int red = getRed(isEdgeSensor);
  int green = getGreen(isEdgeSensor);
  int blue = getBlue(isEdgeSensor);


  int color = printColor(red, green, blue);
  if(color >= 0) {
    return color;
  } else {
    Serial.print("2ª Vez! \n");
    ReadColor();
  }
}

  void setColor(int face) {
    //Tempo de prevenção:
    delay(200);
    
    ColorGuide[face][0] = getRed(isEdgeSensor);
    ColorGuide[face][1] = getGreen(isEdgeSensor);
    ColorGuide[face][2] = getBlue(isEdgeSensor);
  
    Serial.print("\n");
    for (int i = 0; i < 3; i++) {
      //Serial.println(ColorGuide[face][i]);
    }
  }

  int printColor(int redColor, int greenColor, int blueColor) {
    long d;
    long minimo;
    int color = -1;
  
    Serial.print("\n");
    d = pow((ColorGuide[RC_WHITE][0] - redColor), 2) + (pow((ColorGuide[RC_WHITE][1] - greenColor), 2)) + (pow((ColorGuide[RC_WHITE][2] - blueColor), 2));
    Serial.print(d); Serial.print("  ");
    minimo = d;
    color = RC_WHITE;
  
    d = pow((ColorGuide[RC_RED][0] - redColor), 2) + (pow((ColorGuide[RC_RED][1] - greenColor), 2)) + (pow((ColorGuide[RC_RED][2] - blueColor), 2));
    Serial.print(d); Serial.print("  ");
    if (abs(d - minimo) > 4000) {
      if(d < minimo) {
        minimo = d;
        color = RC_RED;
      }
    } else{
        return -1;
    }
    d = pow((ColorGuide[RC_GREEN][0] - redColor), 2) + (pow((ColorGuide[RC_GREEN][1] - greenColor), 2)) + (pow((ColorGuide[RC_GREEN][2] - blueColor), 2));
    Serial.print(d); Serial.print("  ");
    if (abs(d - minimo) > 4000) {
      if(d < minimo) {
        minimo = d;
        color = RC_GREEN;
      }
    } else{
        return -1;
    }
    d = pow((ColorGuide[RC_BLUE][0] - redColor), 2) + (pow((ColorGuide[RC_BLUE][1] - greenColor), 2)) + (pow((ColorGuide[RC_BLUE][2] - blueColor), 2));
    Serial.print(d); Serial.print("  ");
    if (abs(d - minimo) > 4000) {
      if(d < minimo) {
        minimo = d;
        color = RC_BLUE;
      }
    } else{
        return -1;
    }
    d = pow((ColorGuide[RC_YELLOW][0] - redColor), 2) + (pow((ColorGuide[RC_YELLOW][1] - greenColor), 2)) + (pow((ColorGuide[RC_YELLOW][2] - blueColor), 2));
    Serial.print(d); Serial.print("  ");
    if (abs(d - minimo) > 4000) {
      if(d < minimo) {
        minimo = d;
        color = RC_YELLOW;
      }
    } else{
        return -1;
    }
    d = pow((ColorGuide[RC_ORANGE][0] - redColor), 2) + (pow((ColorGuide[RC_ORANGE][1] - greenColor), 2)) + (pow((ColorGuide[RC_ORANGE][2] - blueColor), 2));
    Serial.print(d); Serial.print("  ");
    if (abs(d - minimo) > 4000) {
      if(d < minimo) {
        minimo = d;
        color = RC_ORANGE;
      }
    } else{
        return -1;
    }
    
    Serial.print("\n");
//    if (minimo > 50000) {
//      Serial.print("Errado!");
//      color = -1;
//    }
    
    switch (color) {
      case RC_WHITE:
        Serial.println("   White!");
          break;
        case RC_RED:
          Serial.println("   Red!");
          break;
        case RC_GREEN:
          Serial.println("   Green!");
          break;
        case RC_BLUE:
          Serial.println("   Blue!");
          break;
        case RC_YELLOW:
          Serial.println("   Yellow!");
          break;
        case RC_ORANGE:
          Serial.println("   Orange!");
          break;
        default:
          Serial.println("   Nada!");
      }
  
    return color;
  }
};

ColorSensor edgeSensor(true);
ColorSensor cornerSensor(false);

int getRed(bool isEdgeSensor) {
  
  int pin = (isEdgeSensor == true) ? COLOR_IN1 : COLOR_IN2; 
  int redColor;
  
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  redFrequency = pulseIn(pin, LOW);
  Serial.print("R = ");
  Serial.print(redFrequency);
  if(pin == COLOR_IN1) {  
    redColor = map(redFrequency, 270, 3600, 1023, 0);
  } else {
    redColor = map(redFrequency, 500, 4000, 1023, 0);
  }

  Serial.print("  r = ");
  Serial.print(redColor);
  delay(100);

  return redColor;
}

int getGreen(bool isEdgeSensor) {

  int pin = (isEdgeSensor == true) ? COLOR_IN1 : COLOR_IN2; 
  int greenColor;
  
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  greenFrequency = pulseIn(pin, LOW);
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  if(pin == COLOR_IN1) {
    greenColor = map(greenFrequency, 250, 2800, 1023, 0);
  } else {
    greenColor = map(greenFrequency, 450, 3400, 1023, 0);
  }

  Serial.print("   g = ");
  Serial.print(greenColor);
  delay(100);

  return greenColor;
}

int getBlue(bool isEdgeSensor) {

  int pin = (isEdgeSensor == true) ? COLOR_IN1 : COLOR_IN2; 
  int blueColor;
  
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  blueFrequency = pulseIn(pin, LOW);
  Serial.print(" B = ");
  Serial.print(blueFrequency);
  if(pin == COLOR_IN1) {
    blueColor = map(blueFrequency, 300, 2600, 1023, 0);
  } else {
    blueColor = map(blueFrequency, 480, 2900, 1023, 0);
  }

  Serial.print("   b = ");
  Serial.print(blueColor);
  delay(100);

  return blueColor;
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
