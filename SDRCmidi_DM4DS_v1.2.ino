// MIDI Control (maybe for SDRConsole) by DM4DS
// Universal MIDI Controller Sketch 
// Copyrighted under GNU v3 with special restrictions for modifiaction
// NO modifications allowed , only uncomment included options
// NO Commercial usage allowed without my ok
// NO public part/full publication without my knowledge
// You are allowed to modify if you name me in your mod
// If you are not sure, ask: dm4ds@gmx.de
// ALL used librarys are public and belongs to their owner
// The 5 LEDs inspired from Pieros (IK1IYU) Infos

#include <Wire.h>                // Wire Bibliothek
#define USE_ROTARY_ENCODER      // This MUST STAY HERE - don´t copy & paste it somewhere
#include <MIDI_Controller.h>   // MIDI Bibliothek
// #include "MIDIUSB.h"          // for Leonardo which speaks MIDI over USB without FLIP


// If you have problems , you can use:
//USBDebugMIDI_Interface midiInterface(57600);          /You can use 9600 etc too

const uint8_t MainChan = 2;           // Main Channel Rotary PIN
const uint8_t SecChan = 10;          // Secondary Channel Rotary PIN
const uint8_t ThirdChan = 11;       // Third Channel Rotary PIN
const uint8_t Controller = 0x14;  // MIDI Control Change controller number
const int speedMultiply = 1;             // No change in speed of the encoder (number of steps is multiplied by 1)
const uint8_t velocity = 0b1111111;     // Maximum velocity (0b1111111 = 0x7F = 127)

const int MainClk = A1;               // Main Seconds Third Channel Rotary PINs
const int MainData = A2;
const int SecClk = 4;                 // Seconds Third Channel Rotary PINs
const int SecData = 5;
const int ThirdClk = 6;               // Third Channel Rotary PINs
const int ThirdData = 7;

const int SpeedMod = 8;               // VFO Button for Speedchange
const int SpeedModLedB = 10;          // LED Pins
const int SpeedModLedR = 11;
const int SpeedModLedG = 12;
const int SpeedModLedY = 2;
const int SpeedModLedGr = 3;

const int pttPin = 13;               // PTT
const int volumePin = A5;            // Buttons
const int vfoAPin = 0;
const int vfoBPin = 1;
const int mutePin = 9;               

Digital pttButton(pttPin, 0x9, 1);
Digital vfoAButton(vfoAPin, 0x10, 1);
Digital vfoBButton(vfoBPin, 0x11, 1);
Digital muteButton(mutePin, 0x12, 1);
Digital volPin(volumePin, 0x13, 1);

RotaryEncoder vfoEncoder1(MainClk, MainData, Controller, MainChan, speedMultiply, NORMAL_ENCODER, SIGN_MAGNITUDE);
RotaryEncoder filterLowEncoder(SecClk, SecData, Controller, SecChan, speedMultiply, NORMAL_ENCODER, SIGN_MAGNITUDE);
RotaryEncoder filterHighEncoder(ThirdClk, ThirdData, Controller, ThirdChan, speedMultiply, NORMAL_ENCODER, SIGN_MAGNITUDE);

// If you want to use a analog POTI you can use:
// Analog volume(volumePin, MIDI_CC::Channel_Volume, 1);

Bank bank(1);
BankSelector bankSelector(bank, { SpeedMod }, { SpeedModLedG, SpeedModLedR, SpeedModLedB, SpeedModLedY, SpeedModLedGr } );

void setup()
{
Serial.begin(57600);
bank.add(vfoEncoder1, Bank::CHANGE_CHANNEL);
}

void loop() {
MIDI_Controller.refresh();
}
