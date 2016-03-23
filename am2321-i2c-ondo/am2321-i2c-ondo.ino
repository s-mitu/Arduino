#include <Wire.h>

unsigned char data[7];
unsigned int byte_no = 0;
int situdo=0;
int kion=0;
unsigned char am2321_I2C_adr = 0x5c; // b8 >>1 and 7f

void setup(){

  Wire.begin();
  Serial.begin(9600);
}

void loop(){
  Wire.beginTransmission(am2321_I2C_adr);
  Wire.write(0x00);
  Wire.endTransmission();
  delayMicroseconds(800);
  Wire.beginTransmission(am2321_I2C_adr);
  Wire.write(0x03);
  Wire.write(0x00);
  Wire.write(0x04);
  Wire.endTransmission();
  delayMicroseconds(1500);
  Wire.requestFrom(0x5c, 0x08);
  byte_no=0;
  while(Wire.available())
  {
    data[byte_no]= Wire.read();
    Serial.println(data[byte_no],HEX);
    byte_no++;
  }
  Serial.println(":");
  situdo = (data[2]*0xff+data[3])/10;
  Serial.print("situdo=");
  Serial.print(situdo);
  Serial.println(" %");
  
  if (data[4] & 0x80){
    kion=((data[4] & 0x7f)*0xff) + data[5];
  } else{
    kion=(data[4] * 0xff) + data[5];
  }
  Serial.print("kion=");
  Serial.print(kion);
  Serial.println(" do");
  
  delay(8000);
} // loop
