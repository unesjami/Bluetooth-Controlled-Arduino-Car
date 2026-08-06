#include <SoftwareSerial.h>

// --- پین‌های موتور ---
const int IN1 = 4, IN2 = 5, IN3 = 6, IN4 = 7;

// --- پین‌های LED ---
const int LED_FRONT_LEFT  = 8;   // چراغ جلو چپ
const int LED_FRONT_RIGHT = 9;   // چراغ جلو راست
const int LED_REAR_LEFT   = 10;  // چراغ عقب چپ
const int LED_REAR_RIGHT  = 11;  // چراغ عقب راست

// --- پین بازر ---
const int BUZZER = 12;

// بلوتوث
SoftwareSerial BT(2, 3); // RX = 2, TX = 3

// وضعیت روشن/خاموش گروهی LEDها
bool frontLightsOn = false;
bool rearLightsOn  = false;

void setup() {
  BT.begin(9600);  // سرعت تست شده و هماهنگ با ماژول

  // موتورها
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  // LEDها
  pinMode(LED_FRONT_LEFT,  OUTPUT);
  pinMode(LED_FRONT_RIGHT, OUTPUT);
  pinMode(LED_REAR_LEFT,   OUTPUT);
  pinMode(LED_REAR_RIGHT,  OUTPUT);

  // بازر
  pinMode(BUZZER, OUTPUT);

  // خاموش کردن همه چیز در آغاز
  stopMotors();
  digitalWrite(LED_FRONT_LEFT,  LOW);
  digitalWrite(LED_FRONT_RIGHT, LOW);
  digitalWrite(LED_REAR_LEFT,   LOW);
  digitalWrite(LED_REAR_RIGHT,  LOW);
  digitalWrite(BUZZER, LOW);
}

void loop() {
  if (BT.available()) {
    char c = BT.read();

    // ----- حرکت (همان قبل) -----
    if (c == 'F')      moveForward();
    else if (c == 'B') moveBackward();
    else if (c == 'L') turnLeft();
    else if (c == 'R') turnRight();
    else if (c == 'S') stopMotors();

    // ----- رقص‌ها (همان قبل) -----
    else if (c == '1') dance1();
    else if (c == '2') dance2();
    else if (c == '3') dance3();
    else if (c == '4') dance4();

    // ----- چراغ‌های جلو (هر دو با هم) -----
    else if (c == 'W') {
      frontLightsOn = !frontLightsOn;
      digitalWrite(LED_FRONT_LEFT,  frontLightsOn);
      digitalWrite(LED_FRONT_RIGHT, frontLightsOn);
    }

    // ----- چراغ‌های عقب (هر دو با هم) -----
    else if (c == 'X') {
      rearLightsOn = !rearLightsOn;
      digitalWrite(LED_REAR_LEFT,  rearLightsOn);
      digitalWrite(LED_REAR_RIGHT, rearLightsOn);
    }

    // ----- بوق (فشاری؛ تا دریافت S ادامه دارد) -----
    else if (c == 'M') {
      digitalWrite(BUZZER, HIGH);   // فقط روشن می‌شود
    }

    // ----- خاموش کردن همه چراغ‌ها (اختیاری) -----
    else if (c == '0') {
      frontLightsOn = false;
      rearLightsOn  = false;
      digitalWrite(LED_FRONT_LEFT,  LOW);
      digitalWrite(LED_FRONT_RIGHT, LOW);
      digitalWrite(LED_REAR_LEFT,   LOW);
      digitalWrite(LED_REAR_RIGHT,  LOW);
      // بازر هم خاموش شود اگر روشن بود
      digitalWrite(BUZZER, LOW);
    }
  }
}

// ===================== توابع حرکت =====================
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}
void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}
void turnLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}
void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}
void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  digitalWrite(BUZZER, LOW);   // بازر را هم خاموش کن
}

// ===================== رقص‌ها =====================
void dance1() {
  for (int i = 0; i < 3; i++) {
    turnLeft();  delay(300);
    turnRight(); delay(300);
  }
  stopMotors();
}
void dance2() {
  moveForward();  delay(800);
  moveBackward(); delay(800);
  turnLeft();     delay(1200);
  stopMotors();
}
void dance3() {
  moveForward(); delay(500);
  turnLeft();    delay(400);
  moveForward(); delay(500);
  turnRight();   delay(400);
  moveForward(); delay(500);
  stopMotors();
}
void dance4() {
  moveBackward(); delay(1000);
  turnRight();   delay(600);
  turnLeft();    delay(600);
  moveForward(); delay(800);
  stopMotors();
}