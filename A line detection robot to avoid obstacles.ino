const int trigPin = 10; // kết nối chân trig với chân 11 arduino
const int echoPin = 11; // kết nối chân echo với chân 12 arduino
uint8_t Sensor[5] = {A0, A1, A2};
uint8_t PWM_MAX_SPEED = 230;
uint8_t PWM_SPEED = 153;
char SET_Mode;
uint8_t MOTOR_LEFT_1 = 4;
uint8_t MOTOR_LEFT_2 = 5;
uint8_t MOTOR_RIGHT_1 = 6;
uint8_t MOTOR_RIGHT_2 = 7;
uint8_t ENA   = 9;
uint8_t ENB   = 3;
uint8_t Button = 12;
uint8_t StatusButton = 0;
uint8_t Save_StatusButton = 0;
bool left_1, center, right_1;
long duration;
int distance;
void setup()
{
  pinMode(Button, INPUT_PULLUP);
  pinMode(MOTOR_LEFT_1, OUTPUT);
  pinMode(MOTOR_LEFT_2, OUTPUT);
  pinMode(MOTOR_RIGHT_1, OUTPUT);
  pinMode(MOTOR_RIGHT_2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (uint8_t i = 0 ; i < 3; i++)
  {
    pinMode(Sensor[i], INPUT);
  }
  Serial.begin(9600);
  analogWrite(ENA, 120); // tốc độ động cơ a ban đầu 120 ( 0 - 255)
  analogWrite(ENB, 120);// tốc độ động cơ b ban đầu 120 ( 0 - 255)
}
void Forward()
{
  analogWrite(ENA, PWM_MAX_SPEED);
  analogWrite(ENB, PWM_MAX_SPEED);
  digitalWrite(MOTOR_LEFT_1, 1);
  digitalWrite(MOTOR_LEFT_2, 0);
  digitalWrite(MOTOR_RIGHT_1, 1);
  digitalWrite(MOTOR_RIGHT_2, 0);
}
void Back()
{
  analogWrite(ENA, PWM_MAX_SPEED);
  analogWrite(ENB, PWM_MAX_SPEED);
  digitalWrite(MOTOR_LEFT_1, 0);
  digitalWrite(MOTOR_LEFT_2, 1);
  digitalWrite(MOTOR_RIGHT_1, 0);
  digitalWrite(MOTOR_RIGHT_2, 1);
}
void Right()
{
  analogWrite(ENA, PWM_MAX_SPEED);
  analogWrite(ENB, PWM_MAX_SPEED);
  analogWrite(MOTOR_LEFT_1, PWM_SPEED);
  digitalWrite(MOTOR_LEFT_2, 0);
  digitalWrite(MOTOR_RIGHT_1, 0);
  digitalWrite(MOTOR_RIGHT_2, 1);
}
void Left()
{
  analogWrite(ENA, PWM_MAX_SPEED);
  analogWrite(ENB, PWM_MAX_SPEED);
  digitalWrite(MOTOR_LEFT_1, 0);
  digitalWrite(MOTOR_LEFT_2, 1);
  analogWrite(MOTOR_RIGHT_1, PWM_SPEED);
  digitalWrite(MOTOR_RIGHT_2, 0);
}
void Stop()
{
  analogWrite(ENA, PWM_MAX_SPEED);
  analogWrite(ENB, PWM_MAX_SPEED);
  digitalWrite(MOTOR_LEFT_1, 0);
  digitalWrite(MOTOR_LEFT_2, 0);
  digitalWrite(MOTOR_RIGHT_1, 0);
  digitalWrite(MOTOR_RIGHT_2, 0);
}
void loop()
{
  KhoangCach();
  Mode_DoLine();
  if (distance < 20)
  {
    digitalWrite(MOTOR_LEFT_1, 0);
    digitalWrite(MOTOR_LEFT_2, 1);
    digitalWrite(MOTOR_RIGHT_1, 0);
    digitalWrite(MOTOR_RIGHT_2, 1);
    delay(200);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    delay(200);
    analogWrite(ENA, PWM_SPEED);
    analogWrite(ENB, PWM_SPEED); // 90
    digitalWrite(MOTOR_LEFT_1, 1);
    digitalWrite(MOTOR_LEFT_2, 0);
    digitalWrite(MOTOR_RIGHT_1, 0);
    digitalWrite(MOTOR_RIGHT_2, 1);
    delay(400);
    digitalWrite(MOTOR_LEFT_1, 1);
    digitalWrite(MOTOR_LEFT_2, 0);
    digitalWrite(MOTOR_RIGHT_1, 1);
    digitalWrite(MOTOR_RIGHT_2, 0);
    analogWrite(ENA, PWM_SPEED);
    analogWrite(ENB, PWM_SPEED);// 90
    delay(600);
    digitalWrite(MOTOR_LEFT_1, 0);
    digitalWrite(MOTOR_LEFT_2, 1);
    digitalWrite(MOTOR_RIGHT_1, 1);
    digitalWrite(MOTOR_RIGHT_2, 0);
    analogWrite(ENA, PWM_MAX_SPEED);
    analogWrite(ENB, PWM_MAX_SPEED);// 110
    delay(400); // thay doi
    digitalWrite(MOTOR_LEFT_1, 1);
    digitalWrite(MOTOR_LEFT_2, 0);
    digitalWrite(MOTOR_RIGHT_1, 1);
    digitalWrite(MOTOR_RIGHT_2, 0);
    analogWrite(ENA, PWM_MAX_SPEED);
    analogWrite(ENB, PWM_MAX_SPEED);// 100
    delay(300);
    while (left_1 == 0)
    {
      left_1 = digitalRead(Sensor[0]);
      center = digitalRead(Sensor[1]);
      right_1 = digitalRead(Sensor[2]);
    }
  }
}
void Mode_DoLine()
{
  left_1 = digitalRead(Sensor[0]);
  center = digitalRead(Sensor[1]);
  right_1 = digitalRead(Sensor[2]);
  PWM_MAX_SPEED = 153;
  PWM_SPEED = 128;
  Serial.println(String(left_1) + "," + String(center) + "," + String(right_1));
  //Line Kep
  if ((digitalRead(Sensor[0]) == 1) && (digitalRead(Sensor[1]) == 0 ) && (digitalRead(Sensor[2]) == 1)) {
    Forward();
  }
  if ((digitalRead(Sensor[0]) == 0) && (digitalRead(Sensor[1]) == 0 ) && (digitalRead(Sensor[2]) == 1)) {
    Left();
  }
  if ((digitalRead(Sensor[0]) == 0) && (digitalRead(Sensor[1]) == 1 ) && (digitalRead(Sensor[2]) == 1)) {
    Left();
  }
  if ((digitalRead(Sensor[0]) == 1) && (digitalRead(Sensor[1]) == 0 ) && (digitalRead(Sensor[2]) == 0)) {
    Right();
  }
  if ((digitalRead(Sensor[0]) == 1) && (digitalRead(Sensor[1]) == 1 ) && (digitalRead(Sensor[2]) == 0)) {
    Right();
  }
  if ((digitalRead(Sensor[0]) == 0) && (digitalRead(Sensor[1]) == 0 ) && (digitalRead(Sensor[2]) == 0)) {
    Stop();
  }
//  //   Line Don
//  if ((digitalRead(Sensor[0]) == 0) && (digitalRead(Sensor[1]) == 1 ) && (digitalRead(Sensor[2]) == 0)) {
//    Forward();
//  }
//  if ((digitalRead(Sensor[0]) == 1) && (digitalRead(Sensor[1]) == 1 ) && (digitalRead(Sensor[2]) == 0)) {
//    Left();
//  }
//  if ((digitalRead(Sensor[0]) == 1) && (digitalRead(Sensor[1]) == 0 ) && (digitalRead(Sensor[2]) == 0)) {
//    Left();
//  }
//  if ((digitalRead(Sensor[0]) == 0) && (digitalRead(Sensor[1]) == 1 ) && (digitalRead(Sensor[2]) == 1)) {
//    Right();
//  }
//  if ((digitalRead(Sensor[0]) == 0) && (digitalRead(Sensor[1]) == 0 ) && (digitalRead(Sensor[2]) == 1)) {
//    Right();
//  }
//  if ((digitalRead(Sensor[0]) == 1) && (digitalRead(Sensor[1]) == 1 ) && (digitalRead(Sensor[2]) == 1)) {
//    Back();
//  }
}
void KhoangCach()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
}
