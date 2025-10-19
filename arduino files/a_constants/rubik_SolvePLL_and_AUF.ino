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
      //casos with headlights on the left (almost all)___________________________________
      if(Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8] &&
         Rubik[RF_FRONT][6] != Rubik[RF_FRONT][8]){
        //caso T:
        if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
           Rubik[RF_BACK][7] == Rubik[RF_BACK][8]){
            rubik.RotateStr("RUrurFRRuruRUrf"); 
            caso = 1;
            break; 
        } 
        //caso F:
        else if(Rubik[RF_LEFT][7] == Rubik[RF_LEFT][6] &&
               (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]) && (Rubik[RF_BACK][6] == Rubik[RF_RIGHT][7])){
                  rubik.RotateStr("rufRUrurFRRuruRUrUR");  
                  caso = 2;
                  break;
        }
        //caso A clock wise:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8] &&
                Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7]){
                  rubik.RotateStr("UrFrBBRfrBBrr"); 
                  caso = 3;
                  break;
        }
        //caso A anti clock wise:
        else if(Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
                Rubik[RF_BACK][6] == Rubik[RF_BACK][7]){
                  rubik.RotateStr("uRbRffrBRffRR");
                  caso = 4;
                  break;
        }
        //caso Ra:
        else if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
               (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]) && (Rubik[RF_BACK][6] == Rubik[RF_RIGHT][7])){
                  rubik.RotateStr("RUrfRUUrUUrFRURuur"); 
                  caso = 5;
                  break;
        }
        //caso Rb:
        else if(Rubik[RF_BACK][7] == Rubik[RF_BACK][8] &&
               (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]) && (Rubik[RF_BACK][6] == Rubik[RF_RIGHT][7])){
                  rubik.RotateStr("urUUrdRurDRURuruR");  
                  caso = 6;
                  break;
        }
        //caso Ja:
        else if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
                Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7] &&
                Rubik[RF_BACK][6] == Rubik[RF_BACK][7] &&
                Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8]){
                  rubik.RotateStr("UUluLFluLULfllUL"); 
                  caso = 7;
                  break;
        }
        //caso Jb:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8] &&
                Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
                Rubik[RF_BACK][7] == Rubik[RF_BACK][8] &&
                Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8]){
                  rubik.RotateStr("RUUruRUUlUruL"); 
                  caso = 8;
                  break;
        }
        //caso G1:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8]){
                  rubik.RotateStr("dRRUrUruRuRRuDrUR");  
                  caso = 9;
                  break;
        }
        //caso G2:
        else if(Rubik[RF_BACK][6] == Rubik[RF_BACK][7]){
                  rubik.RotateStr("DRRuRuRUrUrrUdRur");  
                  caso = 10;
                  break;
        }
        //caso G3:
        else if(Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7]){
                  rubik.RotateStr("RUruDRRuRurUrUrrd");  
                  caso = 11;
                  break;
        }
        //caso G4:
        else if(Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8]){
                  rubik.RotateStr("DruRUdRRUrURuRurr");  
                  caso = 12;
                  break;
        }
      }
      //casos without headligths:___________________________________________________
      //caso Y:
      if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
         Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
         Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]){
           rubik.RotateStr("FUfrrFufuRRUrrURR");
           caso = 13;
           break;       
      } 
      //caso V:
      else if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
              Rubik[RF_LEFT][7] == Rubik[RF_LEFT][8]   &&
              Rubik[RF_FRONT][8] == Rubik[RF_BACK][6] &&
              Rubik[RF_RIGHT][6] != Rubik[RF_RIGHT][7]){
                rubik.RotateStr("rUURuuLurUlULuRUl"); 
                caso = 14;
                break; 
      } 
      //caso E:
      else if((Rubik[RF_FRONT][7] == RC_RED)   && (Rubik[RF_LEFT][7] == RC_BLUE)   &&
              (Rubik[RF_BACK][7] == RC_ORANGE) && (Rubik[RF_RIGHT][7] == RC_GREEN) &&
              (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6])){
                rubik.RotateStr("rUlddLuRlUrDDRuL"); 
                caso = 15;
                break; 
      }
      //caso Na:
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
      //caso Nb:
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
      //casos with headlights on all faces________________________________________
      if(Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8]   &&
         Rubik[RF_BACK][6] == Rubik[RF_BACK][8]   &&
         Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][8] &&
         Rubik[RF_FRONT][6] == Rubik[RF_FRONT][8]){
        //caso U clock wise:
        if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][6] &&
           Rubik[RF_LEFT][7] == Rubik[RF_BACK][8]){
            rubik.RotateStr("rUrururURUrr"); 
            caso = 18;
            break; 
        }
        //caso U anti clock wise:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][6] &&
                Rubik[RF_LEFT][7] == Rubik[RF_RIGHT][8]){
            rubik.RotateStr("LuLULULuluLL"); 
            caso = 19;
            break; 
        }
        //caso H:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_BACK][6] &&
                Rubik[RF_LEFT][7] == Rubik[RF_RIGHT][6]){
                  rubik.RotateStr("rrUURuuRRuuRRuuRUUrr"); 
                  caso = 20;
                  break; 
        }
        //caso Z:
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


void AUF() {   //A.U.F. (Adjust Up Face)
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
