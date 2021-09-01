
void Solve_WhiteCross_1 () {
  //Procurar edges com a cor branca na face de baixo
  if(Rubik[RF_DOWN][1] == RC_WHITE){
    switch(Rubik[RF_BACK][1]) {
      case RC_RED:    rubik.RotateStr("dd"); break;
      case RC_BLUE:   rubik.RotateStr("D");  break;
      case RC_ORANGE: rubik.RotateStr("");   break;
      case RC_GREEN:  rubik.RotateStr("d");  break;
    }
  }

  if(Rubik[RF_DOWN][3] == RC_WHITE){
    switch(Rubik[RF_LEFT][1]) {
      case RC_RED:    rubik.RotateStr("D");  break;
      case RC_BLUE:   rubik.RotateStr("");   break;
      case RC_ORANGE: rubik.RotateStr("d");  break;
      case RC_GREEN:  rubik.RotateStr("dd"); break;
    }
  }

  if(Rubik[RF_RIGHT][5] == RC_WHITE){
    switch(Rubik[RF_DOWN][1]) {
      case RC_RED:    rubik.RotateStr("d");  break;
      case RC_BLUE:   rubik.RotateStr("dd"); break;
      case RC_ORANGE: rubik.RotateStr("D");  break;
      case RC_GREEN:  rubik.RotateStr("");   break;
    }
  }

  if(Rubik[RF_FRONT][7] == RC_WHITE){
    switch(Rubik[RF_DOWN][1]) {
      case RC_RED:    rubik.RotateStr("");   break;
      case RC_BLUE:   rubik.RotateStr("d");  break;
      case RC_ORANGE: rubik.RotateStr("dd"); break;
      case RC_GREEN:  rubik.RotateStr("D");  break;
    }
  }
}

void Solve_WhiteCross_2() {
    int side_color;
    int rot = 0;
    //Procurar por edges com a cor branca na face de cima
    if (Rubik[RF_UP][1] == RC_WHITE) {
        side_color = Rubik[RF_FRONT][7];
        rot -= 0;
    } else if (Rubik[RF_UP][3] == RC_WHITE) {
        side_color = Rubik[RF_LEFT][7];
        rot -= 3;
    } else if (Rubik[RF_UP][5] == RC_WHITE) {
        side_color = Rubik[RF_RIGHT][7];
        rot -= 1;
    } else if (Rubik[RF_UP][7] == RC_WHITE) {
        side_color = Rubik[RF_BACK][7];
        rot -= 2;
    } else {
        return;
    }
    
    switch(side_color) {
      case RC_RED:    rot += 0; break;
      case RC_GREEN:  rot += 1; break;
      case RC_ORANGE: rot += 2; break;
      case RC_BLUE:   rot += 3; break;
    }
    
    if(rot == 0) {
        rubik.RotateStr(""); // nÃ£o ReadColor nada
    } else if (rot == -3 || rot == 1) {
        rubik.RotateStr("u"); // Up counter clock wise
    } else if (rot == 2 || rot == -2){
        rubik.RotateStr("UU"); // Up 2x
    } else if(rot == -1 || rot == 3){
        rubik.RotateStr("U"); // Up clock wise
    }
    
    switch(side_color) {
      case RC_RED:    rubik.RotateStr("FF"); break;
      case RC_GREEN:  rubik.RotateStr("RR"); break;
      case RC_ORANGE: rubik.RotateStr("BB"); break;
      case RC_BLUE:   rubik.RotateStr("LL"); break;
    }
    // no final voltamos a tentar recursivamente atÃ© nÃ£o haver mais faces
    // brancas em cima
    Solve_WhiteCross_2();
}


void Solve_WhiteCross_3() {
//Procurar por edges com a cor branca nas faces laterais da camada de cima
    if (Rubik[RF_FRONT][7] == RC_WHITE) {
        switch(Rubik[RF_UP][1]) {
          case RC_RED:    rubik.RotateStr("urFR"); break;
          case RC_BLUE:   rubik.RotateStr("fLF"); break;
          case RC_ORANGE: rubik.RotateStr("uRbr"); break;
          case RC_GREEN:  rubik.RotateStr("Frf"); break;
        }
    } else if (Rubik[RF_LEFT][7] == RC_WHITE) {
        switch(Rubik[RF_UP][3]) {
          case RC_RED:    rubik.RotateStr("Lfl"); break;
          case RC_BLUE:   rubik.RotateStr("ufLF"); break;
          case RC_ORANGE: rubik.RotateStr("lBL"); break;
          case RC_GREEN:  rubik.RotateStr("uFrf"); break;
        }
    } else if (Rubik[RF_RIGHT][7] == RC_WHITE) {
        switch(Rubik[RF_UP][5]) {
          case RC_RED:    rubik.RotateStr("rFR"); break;
          case RC_BLUE:   rubik.RotateStr("UfLF"); break;
          case RC_ORANGE: rubik.RotateStr("Rbr"); break;
          case RC_GREEN:  rubik.RotateStr("UFrf"); break;
        }
    } else if (Rubik[RF_BACK][7] == RC_WHITE) {
        switch(Rubik[RF_UP][7]) {
          case RC_RED:    rubik.RotateStr("uLfl"); break;
          case RC_BLUE:   rubik.RotateStr("Blb"); break;
          case RC_ORANGE: rubik.RotateStr("ulBL"); break;
          case RC_GREEN:  rubik.RotateStr("bRB"); break;
        }
    } else {
        return;
    }
    // no final voltamos a tentar recursivamente atÃ© nÃ£o haver mais
    Solve_WhiteCross_2();
    Solve_WhiteCross_3();
}

void Solve_WhiteCross_4() {
  //Procurar por edges com a cor branca nos sÃ­tios 3 e 5 das faces da frente e de trÃ¡s
  if ((Rubik[RF_FRONT][3] == RC_WHITE) && (Rubik[RF_LEFT][5] != RC_BLUE)){
    rubik.RotateStr("lUL");
  } else if ((Rubik[RF_FRONT][3] == RC_WHITE) && (Rubik[RF_LEFT][5] == RC_BLUE)){
    rubik.RotateStr("L"); 
  } else if ((Rubik[RF_FRONT][5] == RC_WHITE) && (Rubik[RF_RIGHT][3] != RC_GREEN)){
    rubik.RotateStr("RUr");
  } else if ((Rubik[RF_FRONT][5] == RC_WHITE) && (Rubik[RF_RIGHT][3] == RC_GREEN)){
    rubik.RotateStr("r");
  } else if ((Rubik[RF_BACK][3] == RC_WHITE) && (Rubik[RF_RIGHT][5] != RC_GREEN)){
    rubik.RotateStr("ruR");
  } else if ((Rubik[RF_BACK][3] == RC_WHITE) && (Rubik[RF_RIGHT][5] == RC_GREEN)){
    rubik.RotateStr("R");
  } else if ((Rubik[RF_BACK][5] == RC_WHITE) && (Rubik[RF_LEFT][3] != RC_BLUE)){
    rubik.RotateStr("LUl");
  } else if ((Rubik[RF_BACK][5] == RC_WHITE) && (Rubik[RF_LEFT][3] == RC_BLUE)){
    rubik.RotateStr("l");
  } else {
      // Se nÃ£o hÃ¡ faces brancas em cima, terminamos!
//      Serial.println("(None)  ");
      return;
  }
  
  Solve_WhiteCross_2();
  Solve_WhiteCross_3();
  Solve_WhiteCross_4();
}


void Solve_WhiteCross_5() {
  //Procurar por edges com a cor branca nos sÃ­tios 3 e 5 das faces da esquerda e da direita
  if ((Rubik[RF_LEFT][3] == RC_WHITE) && (Rubik[RF_BACK][5] != RC_ORANGE)){
    rubik.RotateStr("buB");
  } else if ((Rubik[RF_LEFT][3] == RC_WHITE) && (Rubik[RF_BACK][5] == RC_ORANGE)){
    rubik.RotateStr("B"); 
  } else if ((Rubik[RF_LEFT][5] == RC_WHITE) && (Rubik[RF_FRONT][3] != RC_RED)){
    rubik.RotateStr("FUf");
  } else if ((Rubik[RF_LEFT][5] == RC_WHITE) && (Rubik[RF_FRONT][3] == RC_RED)){
    rubik.RotateStr("f");
  } else if ((Rubik[RF_RIGHT][3] == RC_WHITE) && (Rubik[RF_FRONT][5] != RC_RED)){
    rubik.RotateStr("fuF");
  } else if ((Rubik[RF_RIGHT][3] == RC_WHITE) && (Rubik[RF_FRONT][5] == RC_RED)){
    rubik.RotateStr("F");
  } else if ((Rubik[RF_RIGHT][5] == RC_WHITE) && (Rubik[RF_BACK][3] != RC_ORANGE)){
    rubik.RotateStr("BUb");
  } else if ((Rubik[RF_RIGHT][5] == RC_WHITE) && (Rubik[RF_BACK][3] == RC_ORANGE)){
    rubik.RotateStr("b");
  } else {
      return;
  }
  
  Solve_WhiteCross_2();
  Solve_WhiteCross_3();
  Solve_WhiteCross_4();
  Solve_WhiteCross_5();
}

void Solve_WhiteCross_6() {
  if (Rubik[RF_FRONT][1] == RC_WHITE){
    rubik.RotateStr("FF");
  }
  if (Rubik[RF_RIGHT][1] == RC_WHITE){
    rubik.RotateStr("RR");
  }
  if (Rubik[RF_LEFT][1] == RC_WHITE){
    rubik.RotateStr("LL");
  }
  if (Rubik[RF_BACK][1] == RC_WHITE){
    rubik.RotateStr("bb");
  }
  
  Solve_WhiteCross_3(); 
  Solve_WhiteCross_4();
  Solve_WhiteCross_5();
}
