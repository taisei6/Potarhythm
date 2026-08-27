#include <MIDI.h>
#include "note.h"

MIDI_CREATE_DEFAULT_INSTANCE();

#define IF_Master_ch 0
#define Master_Slave_ch 4

#define NUM_VALVES 8
Note note[NUM_VALVES];

// 左から順に バルブA(0), B(1), C(2), D(3), E(4), F(5), G(6), H(7)
int valvePins[NUM_VALVES] = {6,7,8,9,10,11,12,5}; 

void NoteOn_from_Master(byte channel, byte pitch, byte velocity){
  int _velocity = int(velocity);
  int velo = map(_velocity, 0, 127, 30, 120);

  // switch文による分岐
  switch (pitch) {
    // --- パターン1: 通常の自動消音ノート (58〜63) ---
    case 58: note[0].on(velo); break; // バルブA
    case 59: note[1].on(velo); break; // バルブB
    case 60: note[2].on(velo); break; // バルブC
    case 61: note[3].on(velo); break; // バルブD
    case 62: note[4].on(velo); break; // バルブE
    case 63: note[5].on(velo); break; // バルブF

    // --- パターン2: 共鳴管 (範囲指定 64〜84) ---
    // ※「...」の前後には必ず半角スペースが必要です
    case 64 ... 70: note[6].on(velo); break; // バルブG
    case 71 ... 84: note[7].on(velo); break; // バルブH
    
    // --- パターン3: Note Offを待つ手動消音ノート (85〜90) ---
    case 85 ... 90:
      note[pitch - 85].on(); // 引数なしで呼ぶ
      break;
  }
}

void NoteOff_from_Master(byte channel, byte pitch, byte velocity){
  switch (pitch) {
    // 85〜90のNote Offを受信したときだけ閉じる
    case 85 ... 90:
      note[pitch - 85].off();
      break;
  }
}

void setup(){
  MIDI.setHandleNoteOn(NoteOn_from_Master);
  MIDI.setHandleNoteOff(NoteOff_from_Master);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  for(int i = 0; i < NUM_VALVES; i++){
    note[i].setup(valvePins[i]);
  }
}

void loop(){
  MIDI.read();
  
  for(int i = 0; i < NUM_VALVES; i++){
    note[i].update();
  }
}