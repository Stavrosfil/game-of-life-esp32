#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

#define SCREEN_WIDTH  128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int g[SCREEN_HEIGHT][SCREEN_WIDTH];
int arrayCopy[SCREEN_HEIGHT][SCREEN_WIDTH];

void createRandomMatrix(int (&a)[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            a[i][j] = random(100) < 25 ? WHITE : BLACK;
        }
    }
}

void gameOfLife(int (&a)[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            arrayCopy[i][j] = a[i][j];
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            int total = (a[i][(j - 1) % SCREEN_WIDTH] + a[i][(j + 1) % SCREEN_WIDTH] + a[(i - 1) % SCREEN_HEIGHT][j] +
                         a[(i + 1) % SCREEN_HEIGHT][j] + a[(i - 1) % SCREEN_HEIGHT][(j - 1) % SCREEN_WIDTH] +
                         a[(i - 1) % SCREEN_HEIGHT][(j + 1) % SCREEN_WIDTH] +
                         a[(i + 1) % SCREEN_HEIGHT][(j - 1) % SCREEN_WIDTH] +
                         a[(i + 1) % SCREEN_HEIGHT][(j + 1) % SCREEN_WIDTH]);

            if (a[i][j] == WHITE) {
                if (total < 2 || total > 3) {
                    arrayCopy[i][j] = BLACK;
                }
            } else if (total == 3) {
                arrayCopy[i][j] = WHITE;
            }
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            a[i][j] = arrayCopy[i][j];
        }
    }
}

void addGlider(int i1, int j1, int (&a)[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    int glider[3][3] = {{0, 0, 1}, {1, 0, 1}, {0, 1, 1}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a[i1 + i][j1 + j] = glider[i][j];
        }
    }
}

void setup() {
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    delay(2000);

    randomSeed(analogRead(0));
    createRandomMatrix(g);
    for (int i = 0; i < 10; i++)
        addGlider(random(SCREEN_HEIGHT), random(SCREEN_WIDTH), g);

    display.clearDisplay();
}

void loop() {
    gameOfLife(g);
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            display.drawPixel(j, i, g[i][j]);
        }
    }
    display.display();
}