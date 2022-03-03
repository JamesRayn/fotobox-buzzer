#include <OneButton.h>
#include <BleKeyboard.h>

#define PIN_1 12
#define PIN_2 14
#define PIN_3 27
#define PIN_S 26
#define PIN_L 22

OneButton buzzer1(PIN_1, true);
OneButton debug2(PIN_2, true);
OneButton debug3(PIN_3, true);
OneButton shtdwn(PIN_S, true);

BleKeyboard bleKeyboard("Fotobox-Buzzer", "Espressif", 91);

int bttimeout = 3000; //Bluetooth connect timeout ~300sek / ~5min

void setup() {
  //Serial.begin(115200);
  //Serial.println("Starting BLE work!");

  setCpuFrequencyMhz(80);
  pinMode(PIN_L, OUTPUT);
  delay(200);
  digitalWrite(PIN_L, HIGH);
  
  buzzer1.attachClick(handlebuzzer1);
  debug2.attachClick(handledebug2);
  debug3.attachClick(handledebug3);
  shtdwn.attachClick(handleshtdwn);
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    buzzer1.tick();
    debug2.tick();
    debug3.tick();
    shtdwn.tick();
  }

  if(!bleKeyboard.isConnected()) {
    shtdwn.tick();
    delay(100);
    bttimeout--;
    
    if(bttimeout % 5 == 0) {
      digitalWrite(PIN_L, LOW);
      delay(25);
      digitalWrite(PIN_L, HIGH);
    }
   
    if(bttimeout<0) {
      btStop();
      esp_deep_sleep_start();
    }
  }
}


void handlebuzzer1() {
  bleKeyboard.write('1');
}

void handledebug2() {
  digitalWrite(PIN_L, LOW);
  bleKeyboard.write('2');
  delay(100);
  digitalWrite(PIN_L, HIGH);
}

void handledebug3() {
  digitalWrite(PIN_L, LOW);
  bleKeyboard.write('3');
  delay(100);
  digitalWrite(PIN_L, HIGH);
}

void handleshtdwn() {
  bleKeyboard.write('0');
  digitalWrite(PIN_L, LOW);
  delay(100);
  digitalWrite(PIN_L, HIGH);
  delay(200);  
  digitalWrite(PIN_L, LOW);
  delay(100);
  digitalWrite(PIN_L, HIGH);
  delay(200);  
  digitalWrite(PIN_L, LOW);
  delay(100);
  digitalWrite(PIN_L, HIGH);
  delay(300);
  btStop();
  esp_deep_sleep_start();
}
