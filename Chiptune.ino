#define CN 0
#define CS 1
#define DN 2
#define DS 3
#define EN 4
#define FN 5
#define FS 6
#define GN 7
#define GS 8
#define AN 9
#define AS 10
#define BN 11
#define RS 12

// Pin Definitions
const int output_pin = PB0;
const int octave_pin = A2;
const int bpm_pin = A3;
const int switch_pin = PB1;

// Melody Definitions
const int steps = 16;
const int bpms[4] = {750, 500, 428, 250};
const int top_octave_notes_us[13] = {478, 451, 426, 402, 379, 358, 338,
                                     319, 301, 284, 268, 253, 0}; // C6 - B6

// Edit this to change the melody, the syntax is NOTE_LETTER ACCIDENTAL, 
// for example CN is C Natural wheras DS is D Sharp, RS indicates a rest
const int tune_notes[steps] = {CN, RS, CS, RS, CN, RS, FS, CS,
                               FN, EN, FS, EN, DS, DN, DN, CN};

// Set by Controls
int octave = 4;
int beat_period_ms = 500;
bool looping = false;

// Play a note with a given period (us) for a given duration (ms)
void play_note(int period_us, int duration_ms) {
  unsigned long note_start_time_ms = millis();
  unsigned long cycle_start_time_us = micros();
  while (millis() < note_start_time_ms + duration_ms) {
    if (period_us != 0) {
      cycle_start_time_us = micros();
      while (micros() < cycle_start_time_us + period_us) {
        digitalWrite(output_pin, HIGH);
      }
      cycle_start_time_us = micros();
      while (micros() < cycle_start_time_us + period_us) {
        digitalWrite(output_pin, LOW);
      }
    }
  }
}

void setup() {
  pinMode(output_pin, OUTPUT);
  pinMode(octave_pin, INPUT_PULLUP);
  pinMode(bpm_pin, INPUT_PULLUP);
  pinMode(switch_pin, INPUT_PULLUP);

  looping = !digitalRead(switch_pin);
  int octave_region = map(analogRead(octave_pin), 0, 1024, 0, 5);
  int bpm_region = map(analogRead(bpm_pin), 0, 1024, 0, 4);

  beat_period_ms = bpms[bpm_region];
  octave = 1 << octave_region;

  do {
    for (int i = 0; i < steps; i++) {
      play_note(octave * top_octave_notes_us[tune_notes[i]], beat_period_ms);
    }
  } while (looping);
}

void loop() {}
