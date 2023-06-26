#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2

int DELAY = 50;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8,8,PIN,NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);

struct RGB{
    byte r;
    byte g;
    byte b;
};

typedef struct Eye_{
    int v1;
    int v2;
    int v3;
    int v4;
    int v5;
    int v6;
    int v7;
    int v8;
} Eye;

RGB white = {255, 255, 255};
RGB red   = {255, 0, 0};
RGB off   = {0, 0, 0};


void drawEye(int eye[8][8], RGB color){
    for (uint16_t row = 0; row < 8; row++){
        for (uint16_t column = 0; column < 8; column++){
            if (eye[row][column] == 1){
                matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
                matrix.show();
                delay(DELAY);
            }
        }
    }
}

void eyesInlight(int emotion){
    int const angry[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {1, 0, 0, 0, 0, 0, 0, 1},
                             {0, 1, 0, 0, 0, 0, 1, 0},
                             {0, 0, 1, 0, 0, 1, 0, 0},
                             {0, 0, 0, 1, 1, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0}};

    int const happy[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 1, 1, 1, 1, 0, 0},
                             {0, 1, 1, 1, 1, 1, 1, 0},
                             {1, 1, 0, 0, 0, 0, 1, 1},
                             {1, 0, 0, 0, 0, 0, 0, 1},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0}};

    int const sadness[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {1, 0, 0, 0, 0, 0, 0, 1},
                               {1, 1, 0, 0, 0, 0, 1, 1},
                               {0, 1, 1, 1, 1, 1, 1, 0},
                               {0, 0, 1, 1, 1, 1, 0, 0}};

    int const fear[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 1, 1, 0, 0, 0},
                            {0, 0, 0, 1, 1, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0}};

    int const disgust[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 1, 1, 1, 0, 0, 0},
                               {0, 0, 0, 0, 1, 1, 1, 0},
                               {0, 0, 0, 0, 0, 0, 1, 1},
                               {0, 0, 0, 0, 1, 1, 1, 0},
                               {0, 0, 1, 1, 1, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0}};

    int const neutral[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 1, 1, 1, 1, 1, 1, 0},
                               {1, 1, 1, 1, 1, 1, 1, 1},
                               {1, 0, 0, 0, 0, 0, 0, 1},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0}};

    int const turned_off[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}};

    switch (emotion){
        case 0:
            drawEye(neutral, red);
            break;
        case 1:
            drawEye(happy, red);
            break;
        case 2:
            drawEye(angry, red);
            break;
        case 3:
            drawEye(sadness, red);
            break;
        case 4:
            drawEye(fear, red);
            break;
        case 5:
            drawEye(disgust, red);
            break;
        default:
            drawEye(turned_off, red);
            break;
    }
}

void setup(){
    matrix.begin();
    matrix.setBrightness(5);
    matrix.setTextColor(matrix.Color(255, 255, 255));
    matrix.setTextWrap(false);
}

void loop(){
    eyesInlight(2);
}
