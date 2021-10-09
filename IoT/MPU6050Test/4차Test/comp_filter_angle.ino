/* 
GY-521(MPU6050) 가속도, 자이로 센서를 상보필터를 적용하여
Roll, Pitch, Yaw 각도 구하기
*/

#include <Wire.h> // I2C 통신을 위한 라이브러리
const int MPU_ADDR = 0x68; // IC2 통신을 위한 MPU6050의 주소
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; // 가속도(Acceleration) 선언
double angleAcX, angleAcY, angleAcZ;
double angleGyX, angleGyY, angleGyZ;
double angleFiX, angleFiY, angleFiZ;

const double RADIAN_TO_DEGREE = 180 / 3.14159;
const double DEG_PER_SEC = 32767 / 250; // 1초에 회전하는 각도
const double ALPHA = 0.9; // 1 / (1 + 0.04); 관성 센서기반 스쿼트 각도 측정 융합 시스템 논문에 따르면 최적의 상보 필터 계수는 0.9 이다.

unsigned long now = 0; // 현재 시간 저장용 변수
unsigned long past = 0; // 이전 시간 저장용 변수
double dt = 0; // 한 사이클 동안 걸린 시간 변수

double averAcX, averAcY, averAcZ;
double averGyX, averGyY, averGyZ;

void initSensor();
void getData();
void getDT();
void caliSensor();


void setup() {
  initSensor();
  Serial.begin(115200);
  caliSensor(); // 초기 센서 캘리브레이션 함수 호출
  past = millis(); // past에 현재 시간 저장
}

void loop() {
  getData();
  getDT();

  angleAcX = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2)));
  angleAcX *= RADIAN_TO_DEGREE;
  angleAcY = atan(-AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2)));
  angleAcY *= RADIAN_TO_DEGREE;
  // 가속도 센서로는 Z축 회전각 계산 불가

  // 가속도 현재 값에서 초기 평균값을 빼서 센서값에 대한 보정
  angleGyX += ((GyX - averGyX) / DEG_PER_SEC) * dt;  // 각속도로 변환
  angleGyY += ((GyY - averGyY) / DEG_PER_SEC) * dt;
  angleGyZ += ((GyZ - averGyZ) / DEG_PER_SEC) * dt;

  // 상보필터 처리를 위한 임시각도 저장
  double angleTmpX = angleFiX + angleGyX * dt;
  double angleTmpY = angleFiY + angleGyY * dt;
  double angleTmpZ = angleFiZ + angleGyZ * dt;

  // 상보필터 값 처리
  // 임시 각도에 0.96, 가속도 센서로 얻어진 각도 0.04의 비중을 두어 현재 각도 구함
  angleFiX = ALPHA * angleTmpX + (1.0 - ALPHA) * angleAcX;
  angleFiY = ALPHA * angleTmpY + (1.0 - ALPHA) * angleAcY;
  angleFiZ = angleGyZ; // Z축은 자이로 센서만을 이용
  //Serial.print("AngleAcX: ");
  //Serial.print(angleAcX);
  Serial.print("FiX: ");
  Serial.print(angleFiX);
  //Serial.print("\t AngleAcY: ");
  //Serial.print(angleAcY);
  Serial.print(" FiY: ");
  Serial.print(angleFiY);
  //Serial.print("\t AngleAcZ: ");
  //Serial.print(angleGyZ);
  Serial.print(" FiZ: ");
  Serial.println(angleFiZ);
  delay(100);
}

void initSensor() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // I2C 통신용 주소
  Wire.write(0X6B); // MPU6050과 통신을 시작하기 위해서는 0X68에
  Wire.write(0); // MPU6050을 동작 대기 모드로 변경
  Wire.endTransmission(true);
}

void getData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // AcX 레지스터 주소를 지칭
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true); // AcX 주소 이후의 14byte의 데이터 요청

  AcX = Wire.read() << 8 | Wire.read(); // 두 개의 나뉘어진 바이트를 하나로 이어 붙여서 각 변수에 저장
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}

// loop 한 사이클동안 걸리는 시간을 알기위한 함수
void getDT() {
  now = millis();
  dt = (now - past) / 1000.0;
  past = now;
}

// 센서의 초기값을 10회 정도 평균값으로 구하여 저장하는 함수
void caliSensor() {
  double sumAcX = 0, sumAcY = 0, sumAcZ = 0;
  double sumGyX = 0, sumGyY = 0, sumGyZ = 0;
  getData();
  for(int i = 0; i < 10; i++) {
    getData();
    sumAcX += AcX;
    sumAcY += AcY;
    sumAcZ += AcZ;
    sumGyX += GyX;
    sumGyY += GyY;
    sumGyZ += GyZ;
    delay(50);
  }

  averAcX = sumAcX / 10;
  averAcY = sumAcY / 10;
  averAcZ = sumAcZ / 10;
  averGyX = sumGyX / 10;
  averGyY = sumGyY / 10;
  averGyZ = sumGyZ / 10;
}
