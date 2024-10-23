#include <SoftwareSerial.h>

SoftwareSerial serialdobluetooth(8,9);

int leds[] = {13, 12, 11, 7, 6, 5};
int temp = 40;
char valordobluetooth;
char comando;
bool piscando = false;

void setup() {
  Serial.begin(9600);
  serialdobluetooth.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(leds[i], OUTPUT);
  }
} 
void tratarComandoBluetooth(char valordobluetooth) {
  switch(valordobluetooth) {
    case 'A':
      digitalWrite(leds[0], HIGH);
      break;
    case 'a':
      digitalWrite(leds[0], LOW);
      break;
    case 'B':
      digitalWrite(leds[1], HIGH);
      break;
    case 'b':
      digitalWrite(leds[1], LOW);
      break;
    case 'C':
      digitalWrite(leds[2], HIGH);
      break;
    case 'c':
      digitalWrite(leds[2], LOW);
      break;
    case 'D':
      digitalWrite(leds[3], HIGH);
      break;
    case 'd':
      digitalWrite(leds[3], LOW);
      break;
    case 'E':
      digitalWrite(leds[4], HIGH);
      break;
    case 'e':
      digitalWrite(leds[4], LOW);
      break;
    case 'F':
      digitalWrite(leds[5], HIGH);
      break;
    case 'f':
      digitalWrite(leds[5], LOW);
      break;

    case 'G':
    piscando = true; // Inicia o efeito de piscar
    while (piscando) {
      for (int i = 0; i < 6; i++) {
        digitalWrite(leds[i], HIGH); // Acende o LED atual
        delay(temp);
        digitalWrite(leds[i], LOW); // Apaga o LED atual
        delay(temp);
     }

      for (int i = 4; i > 0; i--) {
        digitalWrite(leds[i], HIGH); // Acende o LED atual
       delay(temp);
        digitalWrite(leds[i], LOW); // Apaga o LED atual
        delay(temp);
      }

      if (serialdobluetooth.available()) {
        char stopCommand = serialdobluetooth.read();
        if (stopCommand == 'g') {
        piscando = false; // Para o efeito de piscar
          for (int i = 0; i < 6; i++) {
            digitalWrite(leds[i], LOW); // Apaga todos os LEDs
        }
      }
    }
  }
  break;
    case 'g':
      for (int i = 0; i < 7; i++) {
        digitalWrite(leds[i], LOW);  
      }
      delay(temp);
      break;
      
    default:
      break;
  }
}
void tratarComandoSerial(char comando) {
  switch(comando) {
    case '1':
      digitalWrite(leds[0], HIGH);
      break;
    case '2':
      digitalWrite(leds[1], HIGH);
      break;
    case '3':
      digitalWrite(leds[2], HIGH);
      break;
    case '4':
      digitalWrite(leds[3], HIGH);
      break;
    case '5':
      digitalWrite(leds[4], HIGH);
      break;
    case '6':
      digitalWrite(leds[5], HIGH);
      break;
    case '7':
      piscando = true;
      while (piscando) {
        for (int i = 0; i < 6; i++) {
          digitalWrite(leds[i], HIGH);
        }
        delay(100);
        for (int i = 0; i < 6; i++) {
          digitalWrite(leds[i], LOW);
        }
        delay(100);
        if (Serial.available() > 0 && Serial.read() == '0') {
          piscando = false;
        }
      }
      break;
    case '0':
      piscando = false;
      for (int i = 0; i < 6; i++) {
        digitalWrite(leds[i], LOW);
      }
      break;

    default:
      break;
  }
}
void loop() {
  if (serialdobluetooth.available()){
    valordobluetooth = serialdobluetooth.read();
    tratarComandoBluetooth(valordobluetooth);
  }

  if (Serial.available()) {
    comando = Serial.read();
    tratarComandoSerial(comando);
  }
  if (piscando) {
    for (int i = 0; i < 6; i++) {
      digitalWrite(leds[i], HIGH);
      delay(temp); 
      digitalWrite(leds[i], LOW);
      delay(temp);
    }
  }
}
