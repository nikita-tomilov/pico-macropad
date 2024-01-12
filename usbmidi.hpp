#ifndef CUSBMIDI_H
#define CUSBMIDI_H

#define MIDI_DEBUG

extern Adafruit_USBD_MIDI usb_midi;
extern void actionPerformed();

void controlMessageReceived(byte channel, byte controlNumber, byte value);

void sendControlMessage(byte channel, byte controlNumber, byte value) {
  uint8_t packet[] = {0x0B, 0xB0 | (channel - 1), controlNumber, value};
  usb_midi.writePacket(packet);
  usb_midi.flush();
  actionPerformed();

  #ifdef MIDI_DEBUG
  Serial.print("OUT ");
  Serial.print(packet[0], HEX);
  Serial.print(" ");
  Serial.print(packet[1], HEX);
  Serial.print(" ");
  Serial.print(packet[2], HEX);
  Serial.print(" ");
  Serial.print(packet[3], HEX);  
  Serial.println();
  #endif
}

void midiRoutine() {
  uint8_t packet[4];
  if (usb_midi.readPacket(packet)) {
    #ifdef MIDI_DEBUG
    Serial.print("IN  ");
    Serial.print(packet[0], HEX);
    Serial.print(" ");
    Serial.print(packet[1], HEX);
    Serial.print(" ");
    Serial.print(packet[2], HEX);
    Serial.print(" ");
    Serial.print(packet[3], HEX);
    Serial.println();
    #endif
    
    if (packet[0] == 0x0B) {
      actionPerformed();
      controlMessageReceived(packet[1] - 0xB0 + 1, packet[2], packet[3]);
    }
  }
}

#endif