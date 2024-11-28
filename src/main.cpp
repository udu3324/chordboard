#define MOZZI_CONTROL_RATE 128

//https://sensorium.github.io/Mozzi/doc/html/hardware_esp32.html
#define MOZZI_AUDIO_MODE MOZZI_OUTPUT_PDM_VIA_I2S
#define MOZZI_I2S_PIN_DATA 42
#define PDM_RESOLUTION 4

#include <Arduino.h>

#include <Mozzi.h>
#include <MozziGuts.h>
#include <Oscil.h>
#include <Smooth.h>
#include <tables/sin2048_int8.h>
#include "MozziConfigValues.h"

Oscil <2048, MOZZI_AUDIO_RATE> aSin(SIN2048_DATA);

const int effectButton = 43;
const int effectLED[] = {0, 17, 18, 21};

const int engineButton = 46;
const int engineLED[] = {38, 39, 40, 41};

const int chordButton[] = {9, 11, 13, 15, 10, 12, 14, 16};

const int touchSlider[] = {1, 2, 3, 4, 5, 6, 7, 8};

void setup() {
  Serial.begin(115200);

  pinMode(effectLED[0], OUTPUT);
  pinMode(effectLED[1], OUTPUT);
  pinMode(effectLED[2], OUTPUT);
  pinMode(effectLED[3], OUTPUT);

  pinMode(engineLED[0], OUTPUT);
  pinMode(engineLED[1], OUTPUT);
  pinMode(engineLED[2], OUTPUT);
  pinMode(engineLED[3], OUTPUT);

  pinMode(chordButton[0], INPUT_PULLUP);
  pinMode(chordButton[1], INPUT_PULLUP);
  pinMode(chordButton[2], INPUT_PULLUP);
  pinMode(chordButton[3], INPUT_PULLUP);
  pinMode(chordButton[4], INPUT_PULLUP);
  pinMode(chordButton[5], INPUT_PULLUP);
  pinMode(chordButton[6], INPUT_PULLUP);
  pinMode(chordButton[7], INPUT_PULLUP);

  aSin.setFreq(440.0f);
  
  startMozzi(MOZZI_CONTROL_RATE);
}

void updateControl() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(chordButton[i]) == HIGH) {
      Serial.println("pressing" + i);
      analogWrite(effectLED[i], 0);
    } else {
      analogWrite(effectLED[i], 1);
    }
  }

  for (int i = 0; i < 4; i++) {
    if (digitalRead(chordButton[i + 4]) == HIGH) {
      Serial.println("pressing" + i);
      analogWrite(engineLED[i], 0);
    } else {
      analogWrite(engineLED[i], 1);
    }
  }

  //delay(50);
}

AudioOutput updateAudio() {
	return MonoOutput::from8Bit(aSin.next());
}

void loop() {
  audioHook();
}