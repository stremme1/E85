#include "EasyREDVIO_ThingPlus.h"
#include <stdio.h>

// LED matrix pin mapping
const int rowPins[7] = {13, 1, 0, 9, 10, 12, 11}; // Row pins
const int colPins[5] = {17, 23, 22, 21, 20}; // Column pins (only 5 for each letter)

// Define rotated letter patterns for 5x7 matrix (each bit represents a column for horizontal scroll)
const uint8_t LETTERS[][7] = {
    {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b11111}, // H
    {0b11111, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b11111}, // E
    {0b11111, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001}, // L
    {0b11111, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001}, // L
    {0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110}, // O
    {0b11111, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001}, // M
    {0b10001, 0b11011, 0b11111, 0b10101, 0b10001, 0b10001, 0b10001}, // E
    {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b11111}, // T
    {0b00100, 0b00100, 0b11111, 0b00100, 0b00100, 0b00100, 0b00100}, // !
};

// Function prototypes
void setupLEDMatrix(void);
void clearLEDMatrix(void);
void displayColumn(uint8_t columnData[7]);
void scrollMessage(const char* message);
void delayMs(int ms);

int main(void) {
    setupLEDMatrix();
    while (1) {
        scrollMessage("HELLO EMMETT!");
    }
}

void setupLEDMatrix(void) {
    for (int i = 0; i < 7; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], LOW);  
    }
    for (int i = 0; i < 5; i++) {
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], HIGH); 
    }
}

void clearLEDMatrix(void) {
    for (int i = 0; i < 7; i++) {
        digitalWrite(rowPins[i], LOW);
    }
    for (int i = 0; i < 5; i++) {
        digitalWrite(colPins[i], HIGH);
    }
}

void displayColumn(uint8_t columnData[7]) {
    for (int row = 0; row < 7; row++) {
        digitalWrite(rowPins[row], columnData[row] ? HIGH : LOW);
    }
}

void scrollMessage(const char* message) {
    while (*message) {
        int letterIndex = (*message >= 'A' && *message <= 'Z') ? *message - 'A' : 26;  // map character to letter index
        
        for (int colOffset = 0; colOffset < 5; colOffset++) {
            clearLEDMatrix();

            uint8_t columnData[7] = {0};
            for (int row = 0; row < 7; row++) {
                columnData[row] = (LETTERS[letterIndex][row] >> (4 - colOffset)) & 1;
            }

            displayColumn(columnData);
            delayMs(150);  // Increase delay for better display stability
        }

        message++;
        delayMs(300);  // Space between letters
    }
}

void delayMs(int ms) {
    for (volatile int i = 0; i < ms * 100; i++);
}
