#include <OneButton.h>
#include <BleKeyboard.h>

#define PIN_1 12
#define PIN_2 14
#define PIN_3 27
#define PIN_S 26

OneButton buzzer1(PIN_1, true);
OneButton debug2(PIN_2, true);
OneButton debug3(PIN_3, true);
OneButton shutdow(PIN_S, true);

BleKeyboard bleKeyboard("Fotobox-Buzzer", "Espressif", 91);

void setup() {
  //Serial.begin(115200);
  //Serial.println("Starting BLE work!");

  setCpuFrequencyMhz(80);
  
  buzzer1.attachClick(handlebuzzer1);
  debug2.attachClick(handledebug2);
  debug3.attachClick(handledebug3);
  shutdow.attachClick(handleshutdow);
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    buzzer1.tick();
    debug2.tick();
    debug3.tick();
    shutdow.tick();
  }
}


void handlebuzzer1() {
  bleKeyboard.write('1');
}

void handledebug2() {
  bleKeyboard.write('2');
}

void handledebug3() {
  bleKeyboard.write('3');
}

void handleshutdow() {
  bleKeyboard.write('0');
  delay(1000);
  btStop();
  esp_deep_sleep_start();
}
