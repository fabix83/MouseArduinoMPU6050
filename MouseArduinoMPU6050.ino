#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;

void setup() {
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
  }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  int vx = map(gx, -16000, 16000, 90, -90)/1.25;
  int vy = map(gy, -16000, 16000, 90, -90)/1.25;

  //move o mouse
  Mouse.move(vy, -vx);
  delay(10);
}
