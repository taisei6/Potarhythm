#include <MIDI.h>
#include "note.h"

MIDI_CREATE_DEFAULT_INSTANCE();

#define IF_Master_ch 0
#define Master_Slave_ch 4
Note note[5];
int ms[5];


void NoteOn_from_Master(byte channel, byte pitch, byte velocity){
  switch(pitch){
    case 0:
//      ms[0] = analogRead(A0);
      note[0].on(0, velocity);
    break;
    case 1:
//      ms[1] = analogRead(A1);
      note[1].on(1, velocity);
    break;
    case 2:
//      ms[2] = analogRead(A2);
      note[2].on(2, velocity);
    break;
    case 3:
//      ms[3] = analogRead(A3);
      note[3].on(3, velocity);
    break;
    case 4:
//      ms[4] = analogRead(A4);
      note[4].on(4, velocity);
    break;
  }
}

void NoteOff_from_Master(byte channel, byte pitch, byte velocity){
  //何もいらない。自動でノートオフする
}

void setup(){
  
  MIDI.setHandleNoteOn(NoteOn_from_Master);
  MIDI.setHandleNoteOff(NoteOff_from_Master);
  MIDI.begin(MIDI_CHANNEL_OMNI);
//  MIDI.begin(Master_Slave_ch);

  for(int i=0;i<5;i++){
    note[i].setup();
  }
  pinMode(13,OUTPUT);
}

void loop(){
  // リアルタイム性の確保のため、MIDI.readをできるだけ早く呼ぶように
  MIDI.read();
  for(int i=0;i<5;i++){
    note[i].update();
  }
}
