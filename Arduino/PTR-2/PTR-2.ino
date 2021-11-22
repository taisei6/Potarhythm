#include <MIDI.h>
#include "note.h"
#include "pitchshifter.h"

MIDI_CREATE_DEFAULT_INSTANCE();

#define IF_Master_ch 0
#define Master_Slave_ch 4
Note note;
P_shifter p_shifter;


void NoteOn_from_Master(byte channel, byte pitch, byte velocity){
  int P_var = pitch % 12;
//  digitalWrite(13,HIGH);
  note.on(P_var);
  p_shifter.on(P_var);
}

void NoteOff_from_Master(byte channel, byte pitch, byte velocity){
  //ノートオフ時にすること
  int P_var = pitch % 12;
//  digitalWrite(13,LOW);
  note.off(P_var);
  p_shifter.off(P_var);
}

void setup(){
  
  MIDI.setHandleNoteOn(NoteOn_from_Master);
  MIDI.setHandleNoteOff(NoteOff_from_Master);
  MIDI.begin(MIDI_CHANNEL_OMNI);
//  MIDI.begin(Master_Slave_ch);
  
  note.setup();
  p_shifter.setup();  
//  pinMode(13,OUTPUT);
}

void loop(){
  // リアルタイム性の確保のため、MIDI.readをできるだけ早く呼ぶように
  MIDI.read();
  p_shifter.update();
  
}
