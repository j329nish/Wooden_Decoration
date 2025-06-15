#define PIN_BUZZER 3
#define PIN_BUTTON 2
#define PIN_ADC0 A0

const byte rgbPins[] = {A1, A2, A3};
const byte ledPins[] = {11, 10, 9, 6, 5};
const int led_dutys[] = {0, 0, 0, 0, 0, 255, 128, 64, 32, 16, 0, 0, 0, 0, 0};
const int buzzer_dutys[] = {523, 587, 659, 698, 784, 880, 988, 1047, 1047, 988, 880, 784, 698, 659, 587, 523};
int change_rgb = 0;
int ledCounts = sizeof(ledPins);
int buzzerCounts = 0;
int delayTimes;

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  for (int i = 0; i < 3; i++) {
  	pinMode(rgbPins[i], OUTPUT);
  }
  for (int i = 0; i < ledCounts; i++) {
  	pinMode(ledPins[i], OUTPUT);
  }
}

void loop()
{
  int adcVal = analogRead(PIN_ADC0);
  delayTimes = map(adcVal, 0, 1023, 600, 100);
  
  if (digitalRead(PIN_BUTTON) == LOW) {
    delay(20);
    if (digitalRead(PIN_BUTTON) == LOW) {
	  change_rgb = (change_rgb + 1) % 3;
      for (int i = 0; i < ledCounts; i++) {
        analogWrite(ledPins[i], led_dutys[0]);
      }
      buzzerCounts = 0;
    }
    while (digitalRead(PIN_BUTTON) == LOW);
  }
  
  if (change_rgb == 0) {
    red_mode();
  } else if (change_rgb == 1) {
    yellow_mode();
  } else {
	blue_mode();
  }
  
  Serial.print("2520329B Nishida Shoto:");
  Serial.println(adcVal);
  delay(delayTimes);
}

void red_mode() {
  analogWrite(rgbPins[0], 255);
  analogWrite(rgbPins[1], 0);   
  analogWrite(rgbPins[2], 0);
}

void yellow_mode() {
  analogWrite(rgbPins[0], 255);
  analogWrite(rgbPins[1], 255);   
  analogWrite(rgbPins[2], 0);
  for (int i = 0; i < ledCounts; i++) {
    if (i % 2 == 0) {
      analogWrite(ledPins[i], 255);
    } else {
      analogWrite(ledPins[i], 0);
    }
  }
  tone(PIN_BUZZER, buzzer_dutys[6]);
  delay(delayTimes);
  noTone(PIN_BUZZER);
  delay(delayTimes);
  tone(PIN_BUZZER, buzzer_dutys[6]);
  delay(delayTimes);
  noTone(PIN_BUZZER);
  delay(delayTimes);
  for (int i = 0; i < ledCounts; i++) {
    if (i % 2 == 0) {
      analogWrite(ledPins[i], 0);
    } else {
      analogWrite(ledPins[i], 255);
    }
  }
  tone(PIN_BUZZER, buzzer_dutys[1]);
  delay(delayTimes);
  noTone(PIN_BUZZER);
  delay(delayTimes);
  tone(PIN_BUZZER, buzzer_dutys[1]);
  delay(delayTimes);
  noTone(PIN_BUZZER);
}

void blue_mode() {
  analogWrite(rgbPins[0], 0);
  analogWrite(rgbPins[1], 0);   
  analogWrite(rgbPins[2], 255);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < ledCounts; j++) {
      analogWrite(ledPins[j], led_dutys[i + j]);
    }
    delay(50);
  }
  tone(PIN_BUZZER, buzzer_dutys[buzzerCounts = (buzzerCounts + 1) % 16]);
  delay(delayTimes);
  noTone(PIN_BUZZER);
  delay(delayTimes);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < ledCounts; j++) {
      analogWrite(ledPins[ledCounts - j - 1], led_dutys[i + j]);
    }
    delay(50);
  }
  tone(PIN_BUZZER, buzzer_dutys[buzzerCounts = (buzzerCounts + 1) % 16]);
  delay(delayTimes);
  noTone(PIN_BUZZER);
}