enum Rubik_Faces {
    RF_FRONT,   //0
    RF_UP,      //1
    RF_LEFT,    //2
    RF_RIGHT,   //3
    RF_DOWN,    //4
    RF_BACK,    //5
    RF_TOTAL_FACES, //6 (número total de faces)
};

//const char* Rubik_FaceName[] = {
//    "RF_FRONT ",
//    "RF_UP    ",
//    "RF_LEFT  ",
//    "RF_RIGHT ",
//    "RF_DOWN  ",
//    "RF_BACK  ",
//    "RF_TOTAL_FACES",6
//};

enum Rubik_Colors {
    RC_RED,
    RC_YELLOW,
    RC_BLUE,
    RC_GREEN,
    RC_WHITE,
    RC_ORANGE,
    RC_TOTAL_COLORS,
};

//const char* Rubik_ColorName[] = {
//    "RED",
//    "YELLOW",
//    "BLUE",
//    "GREEN",
//    "WHITE",
//    "ORANGE",
//    "???"
//};

int Rubik_FaceToColorLUT[] = {
    RC_RED,
    RC_YELLOW,
    RC_BLUE,
    RC_GREEN,
    RC_WHITE,
    RC_ORANGE,
};


unsigned char Rubik[RF_TOTAL_FACES][9];
