// This #include statement was automatically added by the Particle IDE.
#include <libfixmath.h>
#include "application.h"
#include <Grove_4Digit_Display.h>
#include <Grove-Ultrasonic-Ranger.h>
#define CLK D4
#define DIO D5
#define NOTE_E5 759
#define NOTE_C5 956
#define NOTE_G5  638

SYSTEM_THREAD(ENABLED); 

int Speaker = A4; 
int SpeakerButton = A2; 
Ultrasonic ultrasonic(D2); 
TM1637 disp(CLK,DIO);

int lastRange = 0;

void setup() {
    pinMode(Speaker, OUTPUT); 
    pinMode(SpeakerButton, INPUT); 
    Serial.begin(9600); 
    disp.init();
//Options are: BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
disp.set(BRIGHT_TYPICAL);
}

void loop() {
    int range; 
    int digit;
    int pos = 3;
    double density = 45.0; 
    
    RGB.control(true); // LED is connected to D1
    
    Serial.println("Obstacle found at: "); 
    
    range = ultrasonic.MeasureInCentimeters(); 
    if (range != lastRange) {
    lastRange = range;
// Fill display with zeros
for (int i = 0; i < 4; i++) {
    disp.display(i, 0);
}

// Extract each digit from the range and write it to the display
while (range >= 1) {
    // Get the current digit by performing modulo (%) division on the range
    digit  = range % 10;
    // Remove the trailing digit by whole-number division
    range /= 10;

    disp.display(pos, digit);
    pos--;
}
}
    Serial.print(range); 
    Serial.println(" cm"); 
    delay(500); 
      if(digitalRead(SpeakerButton) ==  HIGH){
        RGB.color(0, 204, 204);
         int Note = (int)((NOTE_G5*sin((digit/2)/density)*50+60)); 
         int BPM = 30; 
         int noteDuration = (int)(60000/BPM/2);
         tone(Speaker, ((int)(Note)), (int)(noteDuration - 20)); 
    } else if(digitalRead(SpeakerButton) ==  LOW) {
        noTone(Speaker);
         RGB.color(255, 0, 0);
    }
}

