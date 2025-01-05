// ∂®“ÂLED Bar“˝Ω≈
const int ledPins[] = { 13, 12, 11, 10, 9, 8, 7, 6, 5, 4 };
const int buzzerPin = A1;
const int buttonA0 = A0;
const int button3 = 2;
const int button4 = 3;

// º«¬º◊¥Ã¨±‰¡ø
bool isRecording = false;                     //  «∑Ò‘⁄º«¬º÷–
unsigned long lastButtonPress = 0;            // …œ¥Œ∞¥≈•∞¥œ¬µƒ ±º‰
unsigned long currentBuzzerInterval = 1000;  // µ±«∞Ω⁄◊‡º‰∏Ù£®ms£©
bool continuePlaying = false;                 //  «∑Ò≥÷–¯≤•∑≈Ω⁄◊‡
unsigned long recordBuffer[170];              // º«¬ºΩ⁄◊‡µƒª∫≥Â«¯
unsigned long Rpace[170];
int recordIndex = 0;  // µ±«∞º«¬ºÀ˜“˝


// ≥ı ºªØLED≈‹¬Ìµ∆∑ΩœÚ
bool forward = true;
int currentLedIndex = 0;

void setup() {
  // …Ë÷√LED BarŒ™ ‰≥ˆ
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);

  // …Ë÷√∞¥≈•Œ™ ‰»Î
  pinMode(buttonA0, INPUT_PULLUP);
  pinMode(buttonA0, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  handleButtonA0();
  handleRecording();
  handleLedBar();

  if (!isRecording && recordIndex > 4) {
    playLedBar();    // ∏˘æ›º«¬ºµƒΩ⁄◊‡‘À–– LED Bar
  }
  //Serial.println("loop");
}

// ∞¥œ¬A0∞¥≈•øÿ÷∆∑‰√˘∆˜Ω⁄◊‡
void handleButtonA0() {

 
  static bool lastButtonState = LOW;       // …œ“ª¥Œµƒ∞¥≈•◊¥Ã¨
  static unsigned long intervals[10];     // ¥Ê¥¢∞¥œ¬µƒº‰∏Ù ±º‰£¨◊Ó∂‡º«¬º50¥Œ
  static int intervalIndex = 0;            // µ±«∞º«¬ºµƒŒª÷√À˜“˝
  static unsigned long lastPressTime = 0;  // …œ“ª¥Œ∞¥≈•∞¥œ¬µƒ ±º‰

  bool buttonState = digitalRead(buttonA0);  // ∂¡»°∞¥≈•◊¥Ã¨

  // ºÏ≤‚∞¥≈•µƒ…œ…˝—ÿ£®À…ø™£©
  if (lastButtonState == LOW && buttonState == HIGH) {
    unsigned long currentTime = millis();  // ªÒ»°µ±«∞ ±º‰
 
    // »Áπ˚≤ª «µ⁄“ª¥ŒÀ…ø™£¨º«¬ºº‰∏Ù ±º‰
    if (lastPressTime > 0) {
      unsigned long interval = currentTime - lastPressTime;

      // ºÏ≤Èº«¬º «∑Ò‘⁄10√Î∑∂Œßƒ⁄
      if (currentTime - intervals[0] <= 10000 || intervalIndex == 0) {
        if (intervalIndex < 10) {
          intervals[intervalIndex++] = interval;  // Ω´º‰∏Ù¥Ê»Î ˝◊È
        } else {
          //  ˝◊È¬˙¡À£¨“∆≥˝◊Ó‘Áµƒº«¬º≤¢ÃÌº”–¬µƒº‰∏Ù
          for (int i = 1; i < 10; i++) {
            intervals[i - 1] = intervals[i];
          }
          intervals[9] = interval;
        }
      }
    }

    lastPressTime = currentTime;  // ∏¸–¬◊Ó∫ÛÀ…ø™ ±º‰
    continuePlaying = true;       // ∆Ù∂Ø≤•∑≈Ω⁄◊‡
  }

  // ºÏ≤‚ «∑Ò≥¨≥ˆ10√Î£¨«Âø’º«¬º
  if (intervalIndex > 0 && millis() - intervals[0] > 10000) {
    intervalIndex = 0;  // «Âø’À˜“˝
    for (int i = 0; i < 10; i++) {
      intervals[i] = 0;  // «Âø’ ˝◊È
    }
  }

  // º∆À„∆Ωæ˘º‰∏Ù
  if (intervalIndex > 0) {
    unsigned long totalInterval = 0;
    for (int i = 0; i < intervalIndex; i++) {
      totalInterval += intervals[i];
    }
    currentBuzzerInterval = totalInterval / intervalIndex;  // ∏¸–¬∆Ωæ˘º‰∏Ù

    Serial.println(currentBuzzerInterval);
  }

  lastButtonState = buttonState;  // ∏¸–¬∞¥≈•◊¥Ã¨

  // øÿ÷∆∑‰√˘∆˜≤•∑≈
  if (buttonState) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  if (continuePlaying && (!isRecording)) {
    static unsigned long lastBuzzerTime = 0;  // …œ“ª¥Œ«–ªª ±º‰
    static bool isBuzzerOn = false;           // µ±«∞∑‰√˘∆˜◊¥Ã¨

    unsigned long elapsedTime = millis() - lastBuzzerTime;  // º∆À„ ±º‰≤Ó

    // »Áπ˚¥¶”⁄1/5µƒ ±º‰ƒ⁄£¨∑‰√˘∆˜œÏ
    if (elapsedTime <= currentBuzzerInterval / 5) {
      if (!isBuzzerOn) {
        digitalWrite(buzzerPin, HIGH);  // ¥Úø™∑‰√˘∆˜
        isBuzzerOn = true;
      }
    }
    // »Áπ˚≥¨π˝1/5µƒ ±º‰£¨∑‰√˘∆˜æ≤“Ù
    else if (elapsedTime > currentBuzzerInterval / 5 && elapsedTime <= currentBuzzerInterval) {
      if (isBuzzerOn) {
        digitalWrite(buzzerPin, LOW);  // πÿ±’∑‰√˘∆˜
        isBuzzerOn = false;
      }
    }
    // »Áπ˚µ±«∞ ±º‰≥¨π˝“ª∏ˆ÷‹∆⁄£¨÷ÿ÷√ ±º‰
    else if (elapsedTime > currentBuzzerInterval) {
      lastBuzzerTime = millis();  // ÷ÿ÷√ø™ º ±º‰
    }
  }
}

// øÿ÷∆LED Bar≈‹¬Ìµ∆
void handleLedBar() {
  static unsigned long lastLedTime = 0;

  if (isRecording) return;  // º«¬º ±≤ª≈‹¬Ìµ∆

  if (millis() - lastLedTime > (currentBuzzerInterval / 10)) {
    for (int i = 0; i < 10; i++) {
      digitalWrite(ledPins[i], LOW);
    }

    digitalWrite(ledPins[currentLedIndex], HIGH);

    if (forward) {
      currentLedIndex++;

      if (currentLedIndex >= 9) {
        forward = false;
      }

    } else {
      currentLedIndex--;

      if (currentLedIndex <= 0) {
        forward = true;
      }
    }

    lastLedTime = millis();
  }
}

// ¥¶¿Ìº«¬º¬ﬂº≠
void handleRecording() {
  static bool lastButton3State = LOW;
  static bool lastButton4State = LOW;

  bool button3State = digitalRead(button3);
  bool button4State = digitalRead(button4);

  // Õ¨ ±∞¥œ¬∞¥≈•3∫Õ∞¥≈•4«–ªªº«¬ºƒ£ Ω
  if (lastButton3State == LOW && button3State == HIGH && lastButton4State == LOW && button4State == HIGH) {

    if (isRecording == false) {
      isRecording = true;
      for (int i = 0; i < 170; i++) {
        recordBuffer[i] = 0;  // «Âø’ ˝◊È
      }
      recordIndex = 0;
      recordBuffer[recordIndex] = 0;
      recordIndex = 1;
    } else {
      isRecording = false;
      recordIndex = recordIndex + 1;
      recordBuffer[recordIndex] = 0;
    }
  }

  // ∞¥œ¬∞¥≈•3º«¬º
  if (lastButton3State == LOW && button3State == HIGH) {

    if (isRecording) {
      recordBuffer[recordIndex++] = 1;
    }
  }

  // ∞¥œ¬∞¥≈•4º«¬º
  if (lastButton4State == LOW && button4State == HIGH) {

    if (isRecording) {
      recordBuffer[recordIndex++] = 0;
    }
  }

  lastButton3State = button3State;
  lastButton4State = button4State;

   Serial.print("Record Buffer: ");
  for (int i = 0; i < 20; i++) {
    if (recordBuffer[i] != 2) {  // 只打印非零值
      Serial.print(recordBuffer[i]);
      
    }
  }
  Serial.println(); // 换行
}


// ∏˘æ›º«¬ºµƒΩ⁄◊‡øÿ÷∆ LED Bar
void playLedBar() {

  if (isRecording) {
    return;  // »Áπ˚’˝‘⁄º«¬º£¨ÕÀ≥ˆ∫Ø ˝
  }

  int flag = 0;
  int RpaceN = 0;
  unsigned long interval = 5000;

  if (currentBuzzerInterval < 100000) {
    interval = currentBuzzerInterval;
  }

  for (int i = 0; i < recordIndex + 1; i++) {

    if (recordBuffer[i] == 1) {
      flag = flag + 1;
    } else if (recordBuffer[i] == 0 && flag > 0) {

      Rpace[RpaceN++] = flag * interval / 4;
      flag = 0;
    }
  }

  for (int i = 0; i < RpaceN + 1; i++) {

    if (i == 0 || i == recordIndex + 1) {
      blinkAllLeds(3, 500);
    }

    if (forward) {

      for (int j = 0; j < 10; j++) {
        digitalWrite(ledPins[j], HIGH);
        delay(Rpace[i] / 10);
        digitalWrite(ledPins[j], LOW);
      }

      forward = false;
    } else {

      for (int j = 9; j >= 0; j--) {
        digitalWrite(ledPins[j], HIGH);
        delay(Rpace[i] / 10);
        digitalWrite(ledPins[j], LOW);
      }

      forward = true;
    }
  }
}

void blinkAllLeds(int cycles, unsigned long duration) {
  for (int i = 0; i < cycles; i++) {
    // µ„¡¡À˘”– LED
    for (int pin = 4; pin <= 13; pin++) {
      digitalWrite(pin, HIGH);
    }
    delay(duration);  // ≥÷–¯µ„¡¡µƒ ±º‰

    // œ®√À˘”– LED
    for (int pin = 4; pin <= 13; pin++) {
      digitalWrite(pin, LOW);
    }
    delay(duration);  // ≥÷–¯œ®√µƒ ±º‰
  }
}