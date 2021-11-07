#include <BleKeyboard.h>

BleKeyboard bleKeyboard;
int meetingEndButtonPin = 13;
int muteButtonPin = 15;
int ledPin = 23;
bool on = true;

void setup() {
  Serial.begin(115200);
  bleKeyboard.deviceName = "Zoom Button";
  bleKeyboard.begin();
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  int mute_button_state = digitalRead(muteButtonPin);
  int end_meeting_button_state = digitalRead(meetingEndButtonPin);
  if (mute_button_state == HIGH) {
    if (on == false) {
      digitalWrite(ledPin, HIGH);
      muteCommand();
      on = true;
    }
  } else if(mute_button_state == LOW) {
    if (on == true) {
      digitalWrite(ledPin, LOW);
      muteCommand();
      on = false;  
    }
  }

  if (end_meeting_button_state == HIGH) {
    endMeetingCommand();
  }
}

void muteCommand() {
  if (bleKeyboard.isConnected()) {
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.print("a");
    delay(100);
    bleKeyboard.releaseAll();
  }
}

void endMeetingCommand() {
  if (bleKeyboard.isConnected()) {
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.print("w");
    delay(100);
    bleKeyboard.releaseAll();
    
    bleKeyboard.press(KEY_RETURN);
    delay(100);
    bleKeyboard.releaseAll();
  }
}
