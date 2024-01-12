#ifndef CUSBMIDI_H
#define CUSBMIDI_H

#define MIDI_DEBUG

extern Adafruit_USBD_MIDI usb_midi;

void controlMessageReceived(byte channel, byte controlNumber, byte value);

void sendControlMessage(byte channel, byte controlNumber, byte value) {
  uint8_t event[] = {0x0B, 0xB0 | (channel - 1), controlNumber, value};
  usb_midi.writePacket(event);
  usb_midi.flush();

  #ifdef MIDI_DEBUG
  Serial.print("> ");
  Serial.print(channel, HEX);
  Serial.print(" ");
  Serial.print(controlNumber, HEX);
  Serial.print(" ");
  Serial.print(value, HEX);
  Serial.println();
  #endif
}

void midiRoutine() {
  uint8_t packet[4];
  if (usb_midi.readPacket(packet)) {

    if (packet[0] == 0x0B) {
      controlMessageReceived(packet[1] + 1, packet[2], packet[3]);
    }

    #ifdef MIDI_DEBUG
    Serial.print("< ");
    Serial.print(packet[1], HEX);
    Serial.print(" ");
    Serial.print(packet[2], HEX);
    Serial.print(" ");
    Serial.print(packet[3], HEX);
    Serial.println();
    #endif
  }
}

#endif