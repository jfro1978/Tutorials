#include <Wire.h>

int IMU_Address = 104; //decimal conversion of B1101000 (from datasheet)

int8_t X0, X2, X4, X6, X8, X10 = 0;
uint8_t X1, X3, X5, X7, X9, X11 = 0;
byte gyro_mask = B00000000; 

float accel_tempx = 0;
float accel_tempy = 0;
float accel_tempz = 0;

float gyro_tempx = 0;
float gyro_tempy = 0;
float gyro_tempz = 0;

#define GYRO_CONFIG 0x1B //Hex address of gyro config register

#define ACCEL_XOUT_H 0x3B //Hex address for high byte of x axis acceleration
#define ACCEL_XOUT_L 0x3C //Hex address for low byte of x axis acceleration

#define ACCEL_YOUT_H 0x3D //Hex address for high byte of y axis acceleration
#define ACCEL_YOUT_L 0x3E //Hex address for low byte of y axis acceleration

#define ACCEL_ZOUT_H 0x3F //Hex address for high byte of z axis acceleration
#define ACCEL_ZOUT_L 0x40 //Hex address for low byte of z axis acceleration

#define TEMP_H 0x41
#define TEMP_L 0x42

#define GYRO_XOUT_H 0x43 //Hex address for high byte of x axis gyro
#define GYRO_XOUT_L 0x44 //Hex address for low byte of x axis gyro

#define GYRO_YOUT_H 0x45 //Hex address for high byte of y axis gyro
#define GYRO_YOUT_L 0x46 //Hex address for low byte of y axis gyro

#define GYRO_ZOUT_H 0x47 //Hex address for high byte of z axis gyro
#define GYRO_ZOUT_L 0x48 //Hex address for low byte of z axis gyro

#define WHOAMI 0x75 //Hex address of WHOAMI register

void setup() {
  Wire.begin(); //Start the I2C communication capability
  Serial.begin(9600); //Start serial comms between pc and Arduino board

  Wire.beginTransmission(IMU_Address);

  Wire.write(GYRO_CONFIG);

  Wire.write(gyro_mask);

  Wire.endTransmission();  
}

void loop() {

  Wire.beginTransmission(IMU_Address); 

  Wire.write(ACCEL_XOUT_H);

  Wire.endTransmission();

  Wire.requestFrom(IMU_Address, 6);

  if(Wire.available() <= 6)
  { 
    X0 = Wire.read();
    X1 = Wire.read();

    X2 = Wire.read();
    X3 = Wire.read();

    X4 = Wire.read();
    X5 = Wire.read();
  }

  accel_tempx = X0 << 8 | X1;
  accel_tempy = X2 << 8 | X3;
  accel_tempz = X4 << 8 | X5;

  Wire.beginTransmission(IMU_Address); 

  Wire.write(GYRO_XOUT_H);

  Wire.endTransmission();

  Wire.requestFrom(IMU_Address, 6);

  if(Wire.available() <= 6)
  {
    
    X6 = Wire.read();
    X7 = Wire.read();

    X8 = Wire.read();
    X9 = Wire.read();

    X10 = Wire.read();
    X11 = Wire.read();
  }

  gyro_tempx = X6 << 8 | X7;
  gyro_tempy = X8 << 8 | X9;
  gyro_tempz = X10 << 8 | X11; 

  Serial.print(accel_tempx/16384);
  Serial.print("\t");
  Serial.print(accel_tempy/16384);
  Serial.print("\t");
  Serial.print(accel_tempz/16384);
  Serial.print("\t");

  Serial.print(gyro_tempx/131);
  Serial.print("\t");
  Serial.print(gyro_tempy/131);
  Serial.print("\t");
  Serial.println(gyro_tempz/131);

  delay(100);

}
