void AUF();

void Solve_PLL() {
  int caso = -1;
  //PLL Skip________________________________________________________________
  if((Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7]) && (Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8]) &&
     (Rubik[RF_LEFT][6] == Rubik[RF_LEFT][7]) && (Rubik[RF_LEFT][7] == Rubik[RF_LEFT][8]) &&
     (Rubik[RF_BACK][6] == Rubik[RF_BACK][7]) && (Rubik[RF_BACK][7] == Rubik[RF_BACK][8]) && 
     (Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7]) && (Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8])){
       caso = 0;
  } else {
    for(int i = 0; i < 4; i++){
      //Casos com headlights na esquerdas (quase todos)___________________________________
      if(Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8] &&
         Rubik[RF_FRONT][6] != Rubik[RF_FRONT][8]){
        //Caso T:
        if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
           Rubik[RF_BACK][7] == Rubik[RF_BACK][8]){
            rubik.RotateStr("RUrurFRRuruRUrf"); 
            caso = 1;
            break; 
        } 
        //Caso F:
        else if(Rubik[RF_LEFT][7] == Rubik[RF_LEFT][6] &&
               (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]) && (Rubik[RF_BACK][6] == Rubik[RF_RIGHT][7])){
                  rubik.RotateStr("rufRUrurFRRuruRUrUR");  
                  caso = 2;
                  break;
        }
        //Caso A Horário:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8] &&
                Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7]){
                  rubik.RotateStr("UrFrBBRfrBBrr"); 
                  caso = 3;
                  break;
        }
        //Caso A Anti-Horário:
        else if(Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
                Rubik[RF_BACK][6] == Rubik[RF_BACK][7]){
                  rubik.RotateStr("uRbRffrBRffRR");
                  caso = 4;
                  break;
        }
        //Caso Ra:
        else if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
               (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]) && (Rubik[RF_BACK][6] == Rubik[RF_RIGHT][7])){
                  rubik.RotateStr("RUrfRUUrUUrFRURuur"); 
                  caso = 5;
                  break;
        }
        //Caso Rb:
        else if(Rubik[RF_BACK][7] == Rubik[RF_BACK][8] &&
               (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]) && (Rubik[RF_BACK][6] == Rubik[RF_RIGHT][7])){
                  rubik.RotateStr("urUUrdRurDRURuruR");  
                  caso = 6;
                  break;
        }
        //Caso Ja:
        else if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
                Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7] &&
                Rubik[RF_BACK][6] == Rubik[RF_BACK][7] &&
                Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8]){
                  rubik.RotateStr("UUluLFluLULfllUL"); 
                  caso = 7;
                  break;
        }
        //Caso Jb:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8] &&
                Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
                Rubik[RF_BACK][7] == Rubik[RF_BACK][8] &&
                Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8]){
                  rubik.RotateStr("RUUruRUUlUruL"); 
                  caso = 8;
                  break;
        }
        //Caso G1:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8]){
                  rubik.RotateStr("dRRUrUruRuRRuDrUR");  
                  caso = 9;
                  break;
        }
        //Caso G2:
        else if(Rubik[RF_BACK][6] == Rubik[RF_BACK][7]){
                  rubik.RotateStr("DRRuRuRUrUrrUdRur");  
                  caso = 10;
                  break;
        }
        //Caso G3:
        else if(Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7]){
                  rubik.RotateStr("RUruDRRuRurUrUrrd");  
                  caso = 11;
                  break;
        }
        //Caso G4:
        else if(Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8]){
                  rubik.RotateStr("DruRUdRRUrURuRurr");  
                  caso = 12;
                  break;
        }
      }
      //Casos sem headligths:___________________________________________________
      //Caso Y:
      if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
         Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
         Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]){
           rubik.RotateStr("FUfrrFufuRRUrrURR");
           caso = 13;
           break;       
      } 
      //Caso V:
      else if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
              Rubik[RF_LEFT][7] == Rubik[RF_LEFT][8]   &&
              Rubik[RF_FRONT][8] == Rubik[RF_BACK][6] &&
              Rubik[RF_RIGHT][6] != Rubik[RF_RIGHT][7]){
                rubik.RotateStr("rUURuuLurUlULuRUl"); 
                caso = 14;
                break; 
      } 
      //Caso E:
      else if((Rubik[RF_FRONT][7] == RC_RED)   && (Rubik[RF_LEFT][7] == RC_BLUE)   &&
              (Rubik[RF_BACK][7] == RC_ORANGE) && (Rubik[RF_RIGHT][7] == RC_GREEN) &&
              (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6])){
                rubik.RotateStr("rUlddLuRlUrDDRuL"); 
                caso = 15;
                break; 
      }
      //Caso Que Nunca Aparece1:
      else if(Rubik[RF_LEFT][7] == Rubik[RF_LEFT][8]    &&
              Rubik[RF_BACK][7] == Rubik[RF_BACK][8]   &&
              Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
              Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8] &&
              Rubik[RF_RIGHT][6] != Rubik[RF_RIGHT][8] &&
              Rubik[RF_FRONT][6] != Rubik[RF_FRONT][8] &&
              Rubik[RF_BACK][6] != Rubik[RF_BACK][8] &&
              Rubik[RF_LEFT][6] != Rubik[RF_LEFT][8]){
                rubik.RotateStr("LuRUUlUrLuRuulUr");
                caso = 16;
                break; 
      } 
      //Caso Que Nunca Aparece2:
      else if(Rubik[RF_LEFT][6] == Rubik[RF_LEFT][7]    &&
              Rubik[RF_BACK][6] == Rubik[RF_BACK][7]   &&
              Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7] &&
              Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
              Rubik[RF_RIGHT][6] != Rubik[RF_RIGHT][8] &&
              Rubik[RF_FRONT][6] != Rubik[RF_FRONT][8] &&
              Rubik[RF_BACK][6] != Rubik[RF_BACK][8] &&
              Rubik[RF_LEFT][6] != Rubik[RF_LEFT][8]){
                rubik.RotateStr("lUrUULuRlUrUULuR"); 
                caso = 17;
                break; 
      }
      //Casos com headlights em todas as faces________________________________________
      if(Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8]   &&
         Rubik[RF_BACK][6] == Rubik[RF_BACK][8]   &&
         Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][8] &&
         Rubik[RF_FRONT][6] == Rubik[RF_FRONT][8]){
        //Caso U HorÃ¡rio:
        if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][6] &&
           Rubik[RF_LEFT][7] == Rubik[RF_BACK][8]){
            rubik.RotateStr("rUrururURUrr"); 
            caso = 18;
            break; 
        }
        //Caso U Anti-HorÃ¡rio:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][6] &&
                Rubik[RF_LEFT][7] == Rubik[RF_RIGHT][8]){
            rubik.RotateStr("LuLULULuluLL"); 
            caso = 19;
            break; 
        }
        //Caso H:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_BACK][6] &&
                Rubik[RF_LEFT][7] == Rubik[RF_RIGHT][6]){
                  rubik.RotateStr("rrUURuuRRuuRRuuRUUrr"); 
                  caso = 20;
                  break; 
        }
        //Caso Z:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_RIGHT][6] &&
                Rubik[RF_LEFT][7] == Rubik[RF_BACK][6]){
                  rubik.RotateStr("RUrUrurURuruRRUR");  
                  caso = 21;
                  break; 
        }
      } 
      rubik.RotateStr("u");
    }
  }
//  Serial.println(caso);
//  Serial.flush();

  AUF();
}


void AUF() {               //A.U.F. (adjust Up Face)
  switch(Rubik[RF_FRONT][7]){
    case RC_RED:    
      rubik.RotateStr(""); 
      break;
    case RC_BLUE:   
      rubik.RotateStr("U");  
      break;
    case RC_ORANGE: 
      rubik.RotateStr("uu");   
      break;
    case RC_GREEN:  
      rubik.RotateStr("u");  
      break;
  }
}
