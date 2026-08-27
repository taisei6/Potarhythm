#include <MIDI.h>
#include "note.h"

MIDI_CREATE_DEFAULT_INSTANCE();

#define IF_Master_ch 0
#define Master_Slave_ch 4
Note note[8];
int ms[8];


void NoteOn_from_Master(byte channel, byte pitch, byte velocity){
  int _velocity = map(velocity, 0, 127, 20, 147);
  switch(pitch){
    case 58:
//      ms[0] = analogRead(A0);
      note[0].on(0, _velocity);
    break;
    case 59:
//      ms[1] = analogRead(A1);
      note[1].on(1, _velocity);
    break;
    case 60:
//      ms[2] = analogRead(A2);
      note[2].on(2, _velocity);
    break;
    case 61:
//      ms[3] = analogRead(A3);
      note[3].on(3, _velocity);
    break;
    case 62:
//      ms[4] = analogRead(A4);
      note[4].on(4, _velocity);
    break;
    case 63:
//      ms[4] = analogRead(A4);
      note[5].on(5, _velocity);
    break;

    case 64 ... 70:
//      ms[4] = analogRead(A4);
      note[6].on(6, _velocity);
    break;

    case 71 ... 84:
//      ms[4] = analogRead(A4);
      note[7].on(7, _velocity);
    break;

    case 85 ... 90:
      note[pitch-85].hold(pitch-85);
      break;
  }
}

void NoteOff_from_Master(byte channel, byte pitch, byte velocity){
  //何もいらない。自動でノートオフする
  switch (pitch) {
    // 85〜90のNote Offを受信したときだけ閉じる
    case 85 ... 90:
      note[pitch - 85].off(pitch - 85);
      break;
  }
}

void setup(){
  
  MIDI.setHandleNoteOn(NoteOn_from_Master);
  MIDI.setHandleNoteOff(NoteOff_from_Master);
  MIDI.begin(MIDI_CHANNEL_OMNI);
//  MIDI.begin(Master_Slave_ch);

  for(int i=0;i<8;i++){
    note[i].setup();
  }
  // pinMode(13,OUTPUT);
}

void loop(){
  // リアルタイム性の確保のため、MIDI.readをできるだけ早く呼ぶように
  MIDI.read();
  for(int i=0;i<8;i++){
    note[i].update();
  }
}
