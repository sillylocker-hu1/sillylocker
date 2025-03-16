#include <Servo.h>
#include <Keypad.h>

// 서보모터 객체 생성
Servo servo0, servo1, servo2, servo3;

// 서보모터가 연결된 핀 번호
const int servoPins[] = {A0, A1, A2, A3};

// 서보모터 상태 변수
int servoAngles[] = {0, 0, 0, 0};
bool toggle = false;  // 움직임을 토글하기 위한 변수

// 키패드 설정
const byte ROWS = 4; // 행 개수
const byte COLS = 4; // 열 개수
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; // R1, R2, R3, R4 → 2,3,4,5
byte colPins[COLS] = {6, 7, 8, 9}; // C1, C2, C3, C4 → 6,7,8,9
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String inputCode = ""; // 키패드 입력 저장 변수

void setup() {
  Serial.begin(9600);
  
  // 서보모터 핀 설정 및 초기 위치 설정
  servo0.attach(servoPins[0]);
  servo1.attach(servoPins[1]);
  servo2.attach(servoPins[2]);
  servo3.attach(servoPins[3]);

  servo0.write(0);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
}

void loop() {
  char key = keypad.getKey();

  if (key) { // 키가 눌렸을 때
    Serial.print("Key Pressed: ");
    Serial.println(key);

    inputCode += key; // 키 입력 저장

    if (inputCode.length() > 5) { // 5자리 초과되면 초기화
      inputCode = inputCode.substring(1);
    }

    if (inputCode == "1111#") { // 비밀번호 입력 확인
      Serial.println("Correct Code Entered!");
      moveServos();
      inputCode = ""; // 코드 초기화
    }
  }
}

// 서보모터 순차 제어 함수
void moveServos() {
  if (!toggle) {
    servo0.write(90);
    delay(500);
  } 
  else {
    servo0.write(-90);
    delay(500);
    servo1.write(90);
    delay(500);
    servo2.write(90);
    servo3.write(90);
    delay(500);
    servo2.write(-90);
    servo3.write(-90);
    delay(500);
    servo1.write(-90);
    delay(500);
  }
  toggle = !toggle; // 다음 실행 때 방향 변경
}
