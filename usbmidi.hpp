#ifndef CUSBMIDI_H
#define CUSBMIDI_H

// #define MIDI_DEBUG

extern Adafruit_USBD_MIDI usb_midi;
extern void actionPerformed();
extern void midiValueUpdated(byte controlNumber, byte value);

void controlMessageReceived(byte channel, byte controlNumber, byte value);

void sendControlMessage(byte channel, byte controlNumber, byte value) {
  uint8_t packet[] = {0x0B, 0xB0 | (channel - 1), controlNumber, value};
  usb_midi.writePacket(packet);
  actionPerformed();
  midiValueUpdated(controlNumber, value);

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
  uint8_t packet[256];
  uint8_t numPacketsReceived = 0;
  uint8_t offset = 0;

  while (usb_midi.readPacket(&(packet[offset]))) {
    #ifdef MIDI_DEBUG
    Serial.print("IN  ");
    Serial.print(packet[offset], HEX);
    Serial.print(" ");
    Serial.print(packet[offset + 1], HEX);
    Serial.print(" ");
    Serial.print(packet[offset + 2], HEX);
    Serial.print(" ");
    Serial.print(packet[offset + 3], HEX);
    Serial.println();
    #endif
    offset += 4;
    numPacketsReceived += 1;
  }

  usb_midi.flush();
  if (numPacketsReceived == 0) return;
  Serial.println(numPacketsReceived);

  uint8_t numPacketsParsed = 0;
  offset = 0;
  while (numPacketsParsed < numPacketsReceived) {

    if (packet[offset] == 0x0B) {
      byte channel = packet[offset + 1] - 0xB0 + 1;
      byte controlNumber = packet[offset + 2];
      byte value = packet[offset + 3];
      controlMessageReceived(channel, controlNumber, value);
      actionPerformed();
      midiValueUpdated(controlNumber, value);
    }

    offset += 4;
    numPacketsParsed += 1;
  }
}

#endif