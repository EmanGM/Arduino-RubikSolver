#define PRINT_WITH_COLORS (false)


void Rubik_PrintColor (int color) {
  if(PRINT_WITH_COLORS) {
    switch (color) {
      case RC_RED:    Serial.print("\e[0;31m"); break;
      case RC_YELLOW: Serial.print("\e[1;33m"); break;
      case RC_BLUE:   Serial.print("\e[0;34m"); break;
      case RC_GREEN:  Serial.print("\e[0;32m"); break;
      case RC_WHITE:  Serial.print("\e[0;37m"); break;
      case RC_ORANGE: Serial.print("\e[0;35m"); break;
    }
    Serial.print("# ");
    Serial.print("\e[0m");
  } else {
      switch (color) {
        case RC_RED:    Serial.print("R"); break;
        case RC_YELLOW: Serial.print("Y"); break;
        case RC_BLUE:   Serial.print("B"); break;
        case RC_GREEN:  Serial.print("G"); break;
        case RC_WHITE:  Serial.print("W"); break;
        case RC_ORANGE: Serial.print("O"); break;
    }
  }
  Serial.flush();
}


void Rubik_PrintSpace () {
  Serial.print("   ");
}

void Rubik_PrintLineFeed () {
  Serial.write("\n");
}

void Cubo::Print() {
  int i;
  for (i = 6; i >= 0; i -= 3) {
    Rubik_PrintSpace(); Rubik_PrintSpace(); Rubik_PrintSpace(); 
    Rubik_PrintColor (Rubik[RF_UP][i + 0]); Rubik_PrintColor (Rubik[RF_UP][i + 1]); Rubik_PrintColor (Rubik[RF_UP][i + 2]);
    Rubik_PrintLineFeed();
  }
  Rubik_PrintLineFeed ();
  for (i = 6; i >= 0; i -= 3) {
    Rubik_PrintColor(Rubik[RF_LEFT][i + 0]);  Rubik_PrintColor(Rubik[RF_LEFT][i + 1]);  Rubik_PrintColor(Rubik[RF_LEFT][i + 2]);  Rubik_PrintSpace();
    Rubik_PrintColor(Rubik[RF_FRONT][i + 0]); Rubik_PrintColor(Rubik[RF_FRONT][i + 1]); Rubik_PrintColor(Rubik[RF_FRONT][i + 2]); Rubik_PrintSpace();
    Rubik_PrintColor(Rubik[RF_RIGHT][i + 0]); Rubik_PrintColor(Rubik[RF_RIGHT][i + 1]); Rubik_PrintColor(Rubik[RF_RIGHT][i + 2]); Rubik_PrintSpace();
    Rubik_PrintColor(Rubik[RF_BACK][i + 0]);  Rubik_PrintColor(Rubik[RF_BACK][i + 1]);  Rubik_PrintColor(Rubik[RF_BACK][i + 2]);  Rubik_PrintSpace();
    Rubik_PrintLineFeed ();
  }
  Rubik_PrintLineFeed ();
  for (i = 6; i >= 0; i -= 3) {
    Rubik_PrintSpace(); Rubik_PrintSpace(); Rubik_PrintSpace();
    Rubik_PrintColor(Rubik[RF_DOWN][i + 0]); Rubik_PrintColor(Rubik[RF_DOWN][i + 1]); Rubik_PrintColor(Rubik[RF_DOWN][i + 2]);
    Rubik_PrintLineFeed ();
  }
  Rubik_PrintLineFeed (); Rubik_PrintLineFeed ();
}
