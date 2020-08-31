#include <EEPROM.h>


#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define DELAY_BETWEEN_STEPS (150)
#define DELAY_BETWEEN_STEPS2 (500) 


int place[] = {18, 0, -18, -24};


class RServo {
  protected:

    int channel;
    int pwm_min;
    int pwm_max;
    int phy_min;
    int phy_max;
    int phy_current;
    int pwm_current;

  public:
    //RServo() { }

    void afinar() {
      static int PWM = 400;
      Serial.println(PWM);

      if (Serial.available()) {
        Serial.println("Aqui\n");
        switch (Serial.read()) {
          case 'h':
            setPWM(PWM += 10);
            Serial.println(PWM);
            break;
          case 'l':
            setPWM(PWM -= 10);
            Serial.println(PWM);
            break;
          case '+':
            setPWM(PWM++);
            Serial.println(PWM);
            break;
          case '-':
            setPWM(PWM--);
            Serial.println(PWM);
            break;
        }
      }
    }

    void setPWM(int value) {
      pwm.setPWM(this->channel, 0, value);
      pwm_current = value;
    }
};

class Rotater : public RServo {
  private:

    int pwm_med;
    int phy_med;

  public:
    Rotater(int channel, int pwm_min, int pwm_med, int pwm_max) {
      this->channel = channel;
      this->pwm_min = pwm_min;
      this->pwm_med = pwm_med;
      this->pwm_max = pwm_max;
      phy_min = 0;
      phy_med = 90;
      phy_max = 180;
    }

    void Rotate(int graus) {
      int p;
      switch (graus) {
        case 0:
          p = pwm_min;
          break;
        case 90:
          p = pwm_med;
          break;
        case 180:
          p = pwm_max;
          break;
      }
      setPWM(p);
    }

#define backlash (10)

    void rotate(int graus) {
      int p;
      switch (graus) {
        case 0:
          p = pwm_min - backlash;
          break;
        case 90:
          p = pwm_med;
          if (pwm_current < pwm_med) {
            p += backlash;
          } else if (pwm_current > pwm_med) {
            p -= backlash;
          }
          break;
        case 180:
          p = pwm_max + backlash;
          break;
      }

      setPWM(p);
    }

    void afinar() {
      static int PWM = 400;
      Serial.println(PWM);

      if (Serial.available()) {
        Serial.println("Aqui\n");
        switch (Serial.read()) {
          case 'h':
            setPWM(PWM += 10);
            Serial.println(PWM);
            break;
          case 'l':
            setPWM(PWM -= 10);
            Serial.println(PWM);
            break;
          case '+':
            setPWM(PWM++);
            Serial.println(PWM);
            break;
          case '-':
            setPWM(PWM--);
            Serial.println(PWM);
            break;
        }
      }
    }
};

class Pusher : public RServo {
  private:
    int phy_med; 

  public:
    Pusher(int channel, int phy_med) {
      this->channel = channel;
      this->pwm_min = 150;
      this->pwm_max = 600;
      this->phy_min = 0;
      this->phy_max = 60;
      this->phy_med = phy_med;
    }

    void rmove(int phy) {
      //map(value, fromLow, fromHigh, toLow, toHigh)
      phy += phy_med;
      int p = map(phy, this->phy_min, this->phy_max, this->pwm_min, this->pwm_max);
      setPWM(p);
    }

    void afinar() {
      static int PWM = 400;
      Serial.println(PWM);
      int p = map(PWM, this->pwm_min, this->pwm_max, this->phy_min, this->phy_max);
      Serial.println();
      Serial.println(p);

      if (Serial.available()) {
        Serial.println("Aqui\n");
        switch (Serial.read()) {
          case 'h':
            setPWM(PWM += 10);
            break;
          case 'l':
            setPWM(PWM -= 10);
            break;
          case '+':
            setPWM(PWM++);
            break;
          case '-':
            setPWM(PWM--);
            break;
        }
      }
    }
};

/* Antigos valores(não sei porquê)
Rotater Up_Right(0, 130, 330, 560);             //motor para rodar a face da direita no pino 0
Rotater Up_Back(1, 130, 325, 545);              //motor para rodar a face de trás no pino 1
Rotater Up_Left(2, 125, 310, 530);              //motor para rodar a face da esquerda no pino 2
Rotater Up_Front(3, 125, 340, 585);             //motor para rodar a face da frente no pino 3

Pusher Down_Right(4, 46);            //motor para andar a face da direita no pino 4
Pusher Down_Back(5, 44);             //motor para andar a face de trás no pino 5
Pusher Down_Left(6, 42);             //motor para andar a face da esquerda no pino 6
Pusher Down_Front(7, 45);            //motor para andar a face da frente no pino 7
*/

Rotater Up_Right(0, 120, 375, 660);             //motor para rodar a face da direita no pino 0
Rotater Up_Back(1, 150, 360, 610);              //motor para rodar a face de trás no pino 1
Rotater Up_Left(2, 140, 350, 590);              //motor para rodar a face da esquerda no pino 2
Rotater Up_Front(3, 130, 400, 680);             //motor para rodar a face da frente no pino 3

Pusher Down_Right(4, 51);            //motor para andar a face da direita no pino 4
Pusher Down_Back(5, 47);             //motor para andar a face de trás no pino 5
Pusher Down_Left(6, 45);             //motor para andar a face da esquerda no pino 6
Pusher Down_Front(7, 49);            //motor para andar a face da frente no pino 7


void servos_init();
void servos_init() {
  Up_Right.Rotate(90);
  Up_Back.Rotate(90);
  Up_Left.Rotate(90);
  Up_Front.Rotate(90);
  Down_Right.rmove(-30);
  Down_Back.rmove(-30);
  Down_Left.rmove(-30);
  Down_Front.rmove(-30);

  delay(2500);
  Down_Back.rmove(place[1]);
  Down_Right.rmove(place[1]);
  delay(500);
  Down_Front.rmove(place[1]);
  Down_Left.rmove(place[1]);

//  delay(500);
//  Down_Back.rmove(place[3]);
}


void servos_test() {

//  Down_Front.rmove(10);
//  Down_Back.rmove(10);
//  Down_Right.rmove(10);
//  Down_Left.rmove(10);
//  for(int i = 10; i < 60; i++) {
//    Down_Front.rmove(i);
//    Down_Back.rmove(i);
//    Serial.println(i);
//    delay(50);
//  }
//  delay(2000);
  ServosFace_RightCW();
  delay(500);
  ServosFace_BackCW();
  delay(500);
  ServosFace_LeftCW();
  delay(500);
  ServosFace_FrontCW();
  delay(500);
  ServosCube_MoveX();
  delay(1000);
  ServosCube_Movex();
  delay(1000);
  ServosCube_MoveZ();
  delay(1000);
  ServosCube_Movez();
  delay(1000);
  ServosFace_RightCCW();
  delay(1000);
  ServosFace_BackCCW();
  delay(500);
  ServosFace_LeftCCW();
  delay(500);
  ServosFace_FrontCCW();
  delay(500);
}



//Rotações dos servos da direita:
//______________________________________________________________________

void ServosFace_RightCW() {
  Up_Right.rotate(180);            delay(DELAY_BETWEEN_STEPS2);
  Down_Right.rmove(place[3]);     delay(DELAY_BETWEEN_STEPS);
  Up_Right.Rotate(90);             delay(DELAY_BETWEEN_STEPS);
  Down_Right.rmove(place[1]);     delay(DELAY_BETWEEN_STEPS);
}

void ServosFace_RightCCW() {
  Up_Right.rotate(0);            delay(DELAY_BETWEEN_STEPS2);
  Down_Right.rmove(place[3]);     delay(DELAY_BETWEEN_STEPS);
  Up_Right.Rotate(90);             delay(DELAY_BETWEEN_STEPS);
  Down_Right.rmove(place[1]);     delay(DELAY_BETWEEN_STEPS);
}


//RotaÃ§Ãµes dos servos da esquerda:
//___________________________________________________________________

void ServosFace_LeftCW() {
  Up_Left.rotate(0);              delay(DELAY_BETWEEN_STEPS2);
  Down_Left.rmove(place[3]);     delay(DELAY_BETWEEN_STEPS);
  Up_Left.Rotate(90);             delay(DELAY_BETWEEN_STEPS);
  Down_Left.rmove(place[1]);     delay(DELAY_BETWEEN_STEPS);
}

void ServosFace_LeftCCW() {
  Up_Left.rotate(180);            delay(DELAY_BETWEEN_STEPS2);
  Down_Left.rmove(place[3]);     delay(DELAY_BETWEEN_STEPS);
  Up_Left.Rotate(90);             delay(DELAY_BETWEEN_STEPS);
  Down_Left.rmove(place[1]);     delay(DELAY_BETWEEN_STEPS);
}


//RotaÃ§Ãµes dos servos da frente:
//___________________________________________________________________________

void ServosFace_FrontCW() {
  Up_Front.rotate(0);            delay(DELAY_BETWEEN_STEPS2);
  Down_Front.rmove(place[3]);     delay(DELAY_BETWEEN_STEPS);
  Up_Front.Rotate(90);             delay(DELAY_BETWEEN_STEPS);
  Down_Front.rmove(place[1]);     delay(DELAY_BETWEEN_STEPS);
}
//
void ServosFace_FrontCCW() {
  Up_Front.rotate(180);            delay(DELAY_BETWEEN_STEPS2);
  Down_Front.rmove(place[3]);     delay(DELAY_BETWEEN_STEPS);
  Up_Front.Rotate(90);             delay(DELAY_BETWEEN_STEPS);
  Down_Front.rmove(place[1]);     delay(DELAY_BETWEEN_STEPS);
}


//RotaÃ§Ãµes dos servos de trÃ¡s:
//______________________________________________________________________________

void ServosFace_BackCW() {
  Up_Back.rotate(180);            delay(DELAY_BETWEEN_STEPS2);
  Down_Back.rmove(place[3]);     delay(DELAY_BETWEEN_STEPS);
  Up_Back.Rotate(90);             delay(DELAY_BETWEEN_STEPS);
  Down_Back.rmove(place[1]);     delay(DELAY_BETWEEN_STEPS);
}

void ServosFace_BackCCW() {
  Up_Back.rotate(0);            delay(DELAY_BETWEEN_STEPS2);
  Down_Back.rmove(place[3]);     delay(DELAY_BETWEEN_STEPS);
  Up_Back.Rotate(90);             delay(DELAY_BETWEEN_STEPS);
  Down_Back.rmove(place[1]);     delay(DELAY_BETWEEN_STEPS);
}


//RotaÃ§Ãµes dos motores para rodar o cubo no sentido de R (movimento x e x`):
//__________________________________________________________________________

void ServosCube_MoveX() {
  int aperto = 4;

  Down_Front.rmove(place[2]);
  Down_Back.rmove(place[2]);
  delay(DELAY_BETWEEN_STEPS);
  Down_Right.rmove(aperto);      //
  Down_Left.rmove(aperto);       //
  delay(100);                //
  Up_Right.Rotate(180);
  Up_Left.Rotate(0);
  delay(160);
  Down_Front.rmove(place[1] + aperto);
  Down_Back.rmove(place[1] + aperto);
  delay(DELAY_BETWEEN_STEPS2);                      
  Down_Right.rmove(place[3]);
  Down_Left.rmove(place[3]);
  delay(DELAY_BETWEEN_STEPS);
  Up_Right.Rotate(90);
  Up_Left.Rotate(90);
  delay(DELAY_BETWEEN_STEPS);
  Down_Right.rmove(place[1]);
  Down_Left.rmove(place[1]);
  Down_Front.rmove(place[1]);
  Down_Back.rmove(place[1]);
  delay(DELAY_BETWEEN_STEPS);
}

void ServosCube_Movex() {
  int aperto = 4;
  
  Down_Front.rmove(place[2]);
  Down_Back.rmove(place[2]);
  delay(DELAY_BETWEEN_STEPS);
  Down_Right.rmove(aperto);      //
  Down_Left.rmove(aperto);       //
  delay(100);                //
  Up_Right.Rotate(0);
  Up_Left.Rotate(180);
  delay(160);
  Down_Front.rmove(place[1] + aperto);
  Down_Back.rmove(place[1] + aperto);
  delay(DELAY_BETWEEN_STEPS2);                      
  Down_Right.rmove(place[3]);
  Down_Left.rmove(place[3]);
  delay(DELAY_BETWEEN_STEPS);
  Up_Right.Rotate(90);
  Up_Left.Rotate(90);
  delay(DELAY_BETWEEN_STEPS);
  Down_Right.rmove(place[1]);
  Down_Left.rmove(place[1]);
  Down_Front.rmove(place[1]);
  Down_Back.rmove(place[1]);
  delay(DELAY_BETWEEN_STEPS);
}


//Rotações dos motores para rodar o cubo no sentido de F (movimento z e z`):
//_________________________________________________________________________

void ServosCube_MoveZ() {
  int aperto = 4;
  
  Down_Right.rmove(place[2]);
  Down_Left.rmove(place[2]);
  delay(DELAY_BETWEEN_STEPS);
  Down_Back.rmove(aperto);      //
  Down_Front.rmove(aperto);       //
  delay(100);                //
  Up_Front.Rotate(0);
  Up_Back.Rotate(180);
  delay(160);
  Down_Right.rmove(place[1] + aperto);
  Down_Left.rmove(place[1] + aperto);
  delay(DELAY_BETWEEN_STEPS2);                      
  Down_Front.rmove(place[3]);
  Down_Back.rmove(place[3]);
  delay(DELAY_BETWEEN_STEPS);
  Up_Front.Rotate(90);
  Up_Back.Rotate(90);
  delay(DELAY_BETWEEN_STEPS);
  Down_Front.rmove(place[1]);
  Down_Back.rmove(place[1]);
  Down_Right.rmove(place[1]);
  Down_Left.rmove(place[1]);
  delay(DELAY_BETWEEN_STEPS);
}

void ServosCube_Movez() {
  int aperto = 4;

  Down_Right.rmove(place[2]);
  Down_Left.rmove(place[2]);
  delay(DELAY_BETWEEN_STEPS);
  Down_Back.rmove(aperto);      //
  Down_Front.rmove(aperto);       //
  delay(100);                //
  Up_Front.Rotate(180);
  Up_Back.Rotate(0);
  delay(160);
  Down_Right.rmove(place[1] + aperto);
  Down_Left.rmove(place[1] + aperto);
  delay(DELAY_BETWEEN_STEPS2);                     
  Down_Front.rmove(place[3]);
  Down_Back.rmove(place[3]);
  delay(DELAY_BETWEEN_STEPS);
  Up_Front.Rotate(90);
  Up_Back.Rotate(90);
  delay(DELAY_BETWEEN_STEPS);
  Down_Front.rmove(place[1]);
  Down_Back.rmove(place[1]);
  Down_Right.rmove(place[1]);
  Down_Left.rmove(place[1]);
  delay(DELAY_BETWEEN_STEPS);
}

//Rotações dos motores para rodar o cubo no sentido de U (movimento Y e Y ):
//_________________________________________________________________________

void ServosCube_MoveY() {
  ServosCube_MoveX();
  ServosCube_MoveZ();
  ServosCube_Movex();
}

void ServosCube_Movey() {
  ServosCube_MoveX();
  ServosCube_Movez();
  ServosCube_Movex();
}
