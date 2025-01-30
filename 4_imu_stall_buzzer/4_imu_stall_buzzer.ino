#include "FastIMU.h"
#include <LiquidCrystal.h>
#include <Wire.h>

/* pin setup for LCD */
LiquidCrystal lcd(7, 8, 9, 10, 11,12);

/* IMU setup */
#define IMU_ADDRESS 0x68    //Change to the address of the IMU
#define PERFORM_CALIBRATION //Comment to disable startup calibration
MPU6500 IMU;               //Change to the name of any supported IMU! 

/* buzzer setup */
#define BUZZ_S_PIN 5

// Currently supported IMUS: MPU9255 MPU9250 MPU6886 MPU6500 MPU6050 ICM20689 ICM20690 BMI055 BMX055 BMI160 LSM6DS3 LSM6DSL QMI8658

calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data
GyroData gyroData;
MagData magData;
unsigned long lastTime;
unsigned long currentTime;
unsigned long dt;
float pitch = 0;
float roll = 0;
float yaw = 0;
float height = 0;
float z_velocity = 0;
float z_velocity_mean = 0;
float z_velocity_sum = 0;
unsigned long num_samples = 0;
float z_accel = 0;
int N = 10;

void calibrateIMU() {
  int err = IMU.init(calib, IMU_ADDRESS);
  if (err != 0) {
    Serial.print("Error initializing IMU: ");
    Serial.println(err);
    while (true) {
      ;
    }
  }
  
#ifdef PERFORM_CALIBRATION
  Serial.println("FastIMU calibration & data example");
  if (IMU.hasMagnetometer()) {
    delay(1000);
    Serial.println("Move IMU in figure 8 pattern until done.");
    delay(3000);
    IMU.calibrateMag(&calib);
    Serial.println("Magnetic calibration done!");
  }
  else {
    delay(5000);
  }

  delay(5000);
  Serial.println("Keep IMU level.");
  delay(5000);
  IMU.calibrateAccelGyro(&calib);
  //Serial.println("Calibration done!");
  //Serial.println("Accel biases X/Y/Z: ");
  // Serial.print(calib.accelBias[0]);
  // Serial.print(", ");
  // Serial.print(calib.accelBias[1]);
  // Serial.print(", ");
  // Serial.println(calib.accelBias[2]);
  // Serial.println("Gyro biases X/Y/Z: ");
  // Serial.print(calib.gyroBias[0]);
  // Serial.print(", ");
  // Serial.print(calib.gyroBias[1]);
  // Serial.print(", ");
  // Serial.println(calib.gyroBias[2]);
  // if (IMU.hasMagnetometer()) {
  //   Serial.println("Mag biases X/Y/Z: ");
  //   Serial.print(calib.magBias[0]);
  //   Serial.print(", ");
  //   Serial.print(calib.magBias[1]);
  //   Serial.print(", ");
  //   Serial.println(calib.magBias[2]);
  //   Serial.println("Mag Scale X/Y/Z: ");
  //   Serial.print(calib.magScale[0]);
  //   Serial.print(", ");
  //   Serial.print(calib.magScale[1]);
  //   Serial.print(", ");
  //   Serial.println(calib.magScale[2]);
  //}
  delay(5000);
  IMU.init(calib, IMU_ADDRESS);
#endif

  //err = IMU.setGyroRange(500);      //USE THESE TO SET THE RANGE, IF AN INVALID RANGE IS SET IT WILL RETURN -1
  //err = IMU.setAccelRange(2);       //THESE TWO SET THE GYRO RANGE TO ±500 DPS AND THE ACCELEROMETER RANGE TO ±2g
  
  if (err != 0) {
    Serial.print("Error Setting range: ");
    Serial.println(err);
    while (true) {
      ;
    }
  }
  Serial.println("time,accelX,accelY,accelZ,gyroX,gyroY,gyroZ,temp");
}

void printIMUData() {
  Serial.print((float) millis()/1000.0);
  Serial.print(",");
  Serial.print(accelData.accelX);
  Serial.print(",");
  Serial.print(accelData.accelY);
  Serial.print(",");
  Serial.print(accelData.accelZ);
  Serial.print(",");
  Serial.print(gyroData.gyroX);
  Serial.print(",");
  Serial.print(gyroData.gyroY);
  Serial.print(",");
  Serial.print(gyroData.gyroZ);
  if (IMU.hasMagnetometer()) {
    IMU.getMag(&magData);
    Serial.print(",");
    Serial.print(magData.magX);
    Serial.print(",");
    Serial.print(magData.magY);
    Serial.print(",");
    Serial.print(magData.magZ);
  }
  if (IMU.hasTemperature()) {
	  Serial.print(",");
	  Serial.println(IMU.getTemp());
  }
  else {
    Serial.println();
  }
}

void setup() {
  Wire.begin();
  Wire.setClock(400000); //400khz clock
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  calibrateIMU();
  lastTime = millis();
  lcd.begin(16, 2);	// Set up the LCD's number of columns and rows:
  // configure buzzer pin as output
  pinMode(BUZZ_S_PIN, OUTPUT);
}

void loop() {
  IMU.update();
  IMU.getAccel(&accelData);
  IMU.getGyro(&gyroData);
  currentTime = millis();
  dt = currentTime - lastTime;
  lastTime = currentTime;
  num_samples++;

  /* BASED ON MY CONFIGURATION  */
  /* Rotation around x axis is pitch */
  /* Rotation around y axis is roll */
  /* Rotation around z axis is yaw */
  pitch += gyroData.gyroX * (dt/1000.0);
  roll += gyroData.gyroY * (dt/1000.0);
  yaw += gyroData.gyroZ * (dt/1000.0);
  /* need to remove gravity */
  float actualAccelZ = 9.81*(accelData.accelZ - 1.00);
  /* Try to get rid of small values when stationary */
  if (abs(actualAccelZ) < 0.2) {
    actualAccelZ = 0;
  }

  z_velocity += (actualAccelZ)* (dt/1000.0);
  Serial.println(z_velocity);
  height += z_velocity * (dt/1000.0);

  if (pitch >= 20.0) {
    tone(BUZZ_S_PIN, 1000);
  } else {
    noTone(BUZZ_S_PIN);
  }

  // if (num_samples <= N) {
  //   z_accel += actualAccelZ;
  // } else {
  //   z_velocity += (z_accel/N)* (dt/1000.0);
  //   height += z_velocity * (dt/1000.0);
  //   num_samples = 0;
  //   z_accel = 0;
  // }

  /* Display on LCD */
  lcd.setCursor(0, 0);
  lcd.print( "P=" );
  lcd.print( pitch, 1 );
  lcd.print(" R=");
  lcd.print( roll, 1 );
  lcd.setCursor(0, 1);
  lcd.print("Y=");
  lcd.print(yaw, 1);
  lcd.print(" H=");
  lcd.print(height, 1);
  // printIMUData();
  delay(50);
}
