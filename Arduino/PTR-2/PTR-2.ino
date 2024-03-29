#include <MIDI.h>
#include "note.h"
#include "pitchshifter.h"
#include "tank.h"

MIDI_CREATE_DEFAULT_INSTANCE();

#define IF_Master_ch 0
#define Master_Slave_ch 4
Note note;
P_shifter p_shifter;
Tank tank;


void NoteOn_from_Master(byte channel, byte pitch, byte velocity){
//  if(63<pitch<85){
if(75<pitch<97){
    int P_var = pitch - 76 ;//E4~C6用,E4=Note No.64だから64引いて0にして配列を呼び出しやすくする
  //  int P_var = pitch % 12;//12音を繰り返し使う用
  
  
  //  digitalWrite(13,HIGH);
    note.on(P_var);
    p_shifter.on(P_var);
  }
}

void NoteOff_from_Master(byte channel, byte pitch, byte velocity){
//  //ノートオフ時にすること
//  if(63<pitch<85){
//    int P_var = pitch -64 ;//E4~C6用
//  //  int P_var = pitch % 12;//12音を繰り返し使う用
//  
//  //  digitalWrite(13,LOW);
//    note.off(P_var);
//  //  p_shifter.off(P_var);
//  }
}

void setup(){
  
  MIDI.setHandleNoteOn(NoteOn_from_Master);
  MIDI.setHandleNoteOff(NoteOff_from_Master);
  MIDI.begin(MIDI_CHANNEL_OMNI);
//  MIDI.begin(Master_Slave_ch);
  
  note.setup();
  p_shifter.setup();
  tank.setup();
//  pinMode(13,OUTPUT);//Lチカデバック用
}

void loop(){
  // リアルタイム性の確保のため、MIDI.readをできるだけ早く呼ぶように
  MIDI.read();
  note.update();
  p_shifter.update();
  tank.update();
  
}
