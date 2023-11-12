#include <Keypad.h>
#include <LiquidCrystal.h>
//#include <MIDI.h>
//MIDI_CREATE_DEFAULT_INSTANCE();

int D7_pin = A4;
int D6_pin = A3;
int D5_pin = A2;
int D4_pin = A1;
int EN_pin = A0;
int RS_pin = 12;

LiquidCrystal lcd(RS_pin, EN_pin, D4_pin, D5_pin, D6_pin, D7_pin);
 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '#','0','*', 'D' }
};
 
const byte rowPins[rowsCount] = { 11, 10, 9, 8 };
const byte columnPins[columsCount] = { 7, 6, 5, 4 };
 
Keypad kpd = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
int kpc = 144;
int midC = 60;
int transpose = 0;
int noteDisplay = 0;
int octaveDisplay = 5;
char dataReceived = ' ';

void setup() {
  // put your setup code here, to run once:
  //MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(9600);
  lcd.begin(16, 2);
  printState();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (kpd.getKeys())  // supports up to ten simultaneous key presses
  {
    for (int i = 0; i < 16; i++) // scan the whole key list
    {
      if ( kpd.key[i].stateChanged)   // find keys that have changed state
      {
        if (kpd.key[i].kstate == PRESSED) // sends MIDI on message when keys are pressed
        {
          switch (kpd.key[i].kchar) {
            case '1':
              MIDImessage(kpc, midC + transpose + 0, 127);
              break;
            case '2':
              MIDImessage(kpc, midC + transpose + 1, 127);
              break;
            case '3':
              MIDImessage(kpc, midC + transpose + 2, 127);
              break;
            case 'A':
              MIDImessage(kpc, midC + transpose + 3, 127);
              break;
            case '4':
              MIDImessage(kpc, midC + transpose + 4, 127);
              break;
            case '5':
              MIDImessage(kpc, midC + transpose + 5, 127);
              break;
            case '6':
              MIDImessage(kpc, midC + transpose + 6, 127);
              break;
            case 'B':
              MIDImessage(kpc, midC + transpose + 7, 127);
              break;
            case '7':
              MIDImessage(kpc, midC + transpose + 8, 127);
              break;
            case '8':
              MIDImessage(kpc, midC + transpose + 9, 127);
              break;
            case '9':
              MIDImessage(kpc, midC + transpose + 10, 127);
              break;
            case 'C':
              MIDImessage(kpc, midC + transpose + 11, 127);
              break;
            case '#':
              MIDImessage(kpc, midC + transpose + 12, 127);
              break;
            case '0':
              MIDImessage(kpc, midC + transpose + 13, 127);
              break;
            case '*':
              MIDImessage(kpc, midC + transpose + 14, 127);
              break;
            case 'D':
              MIDImessage(kpc, midC + transpose + 15, 127);
              break;
          }
        }

        if (kpd.key[i].kstate == RELEASED)  // sends MIDI off message when keys are released
        {
          switch (kpd.key[i].kchar) {
            case '1':
              MIDImessage(kpc - 16, midC + transpose + 0, 0);
              break;
            case '2':
              MIDImessage(kpc - 16, midC + transpose + 1, 0);
              break;
            case '3':
              MIDImessage(kpc - 16, midC + transpose + 2, 0);
              break;
            case 'A':
              MIDImessage(kpc - 16, midC + transpose + 3, 0);
              break;
            case '4':
              MIDImessage(kpc - 16, midC + transpose + 4, 0);
              break;
            case '5':
              MIDImessage(kpc - 16, midC + transpose + 5, 0);
              break;
            case '6':
              MIDImessage(kpc - 16, midC + transpose + 6, 0);
              break;
            case 'B':
              MIDImessage(kpc - 16, midC + transpose + 7, 0);
              break;
            case '7':
              MIDImessage(kpc - 16, midC + transpose + 8, 0);
              break;
            case '8':
              MIDImessage(kpc - 16, midC + transpose + 9, 0);
              break;
            case '9':
              MIDImessage(kpc - 16, midC + transpose + 10, 0);
              break;
            case 'C':
              MIDImessage(kpc - 16, midC + transpose + 11, 0);
              break;
            case '#':
              MIDImessage(kpc - 16, midC + transpose + 12, 0);
              break;
            case '0':
              MIDImessage(kpc - 16, midC + transpose + 13, 0);
              break;
            case '*':
              MIDImessage(kpc - 16, midC + transpose + 14, 0);
              break;
            case 'D':
              MIDImessage(kpc - 16, midC + transpose + 15, 0);
              break;
          }
        }
      }
    }
  }
  if (Serial.available() != 0){
    dataReceived = Serial.read();
    switch(dataReceived){
      case 't':
        transponer(-1);
        break;
      case 'T':
        transponer(1);
        break;
      case 'o':
        transponer(-12);
        break;
      case 'O':
        transponer(12);
        break;
    }
  }
}

void MIDImessage(byte status, byte data1, byte data2)
{
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}

void printState(){
  lcd.clear();
  switch(noteDisplay){
    case 0:
      lcd.print("C / ");
      lcd.print(octaveDisplay);
      break;
    case 1:
      lcd.print("C# / ");
      lcd.print(octaveDisplay);
      break;
    case 2:
      lcd.print("D / ");
      lcd.print(octaveDisplay);
      break;
    case 3:
      lcd.print("D# / ");
      lcd.print(octaveDisplay);
      break;
    case 4:
      lcd.print("E / ");
      lcd.print(octaveDisplay);
      break;
    case 5:
      lcd.print("F / ");
      lcd.print(octaveDisplay);
      break;
    case 6:
      lcd.print("F# / ");
      lcd.print(octaveDisplay);
      break;
    case 7:
      lcd.print("G / ");
      lcd.print(octaveDisplay);
      break;
    case 8:
      lcd.print("G# / ");
      lcd.print(octaveDisplay);
      break;
    case 9:
      lcd.print("A / ");
      lcd.print(octaveDisplay);
      break;
    case 10:
      lcd.print("A# / ");
      lcd.print(octaveDisplay);
      break;
    case 11:
      lcd.print("B / ");
      lcd.print(octaveDisplay);
      break;
  }
}

void transponer(int nNotas){
  transpose += nNotas;
  noteDisplay = (midC + transpose)%12;
  octaveDisplay = (midC + transpose)/12;
  printState();
}
