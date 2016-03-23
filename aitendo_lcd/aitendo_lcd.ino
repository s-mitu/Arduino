 
#include <Wire.h>

// Arduino     i2c-lcd
// Dig 2 ----- 1pin rst (pull-up 10k ohm)
// Ana 5 ----- 2pin scl (pull-up 2.2k ohm)
// Ana 4 ----- 3pin sda (pull-up 2.2k ohm)
// GND ------- 4pin
// 5V -------- 5pin

int ledPin = 13;
int resetPin = 2;
int sdaPin = 18; // analog pin 4
int sclPin = 19; // analog pin 5
int i2cadr = 0x3e;
byte contrast = 40; // 0-63 5V系だとかなり少なくする

void lcd_cmd(byte x)
{
  Wire.beginTransmission(i2cadr);
  Wire.write(0x00);
  Wire.write(x);
  Wire.endTransmission();
}

void lcd_data(byte x)
{
  Wire.beginTransmission(i2cadr);
  Wire.write(0x40);
  Wire.write(x);
  Wire.endTransmission();
}

void lcd_puts(const char *s)
{
  while(*s) lcd_data(*s++);
}

void lcd_init()
{
  // reset
  delay(500);
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, LOW);
  delay(1);
  digitalWrite(resetPin, HIGH);
  delay(10);
  // LCD initialize
  delay(40);
  Wire.begin();
  lcd_cmd(0x38); // function set
  lcd_cmd(0x39); // function set
  lcd_cmd(0x14); // interval osc
  lcd_cmd(0x70 | (contrast & 15)); // contrast low
  lcd_cmd(0x5c | (contrast >> 4 & 3)); // contrast high / icon / power
  lcd_cmd(0x6c); // follower control
  delay(300);
  lcd_cmd(0x38); // function set
  lcd_cmd(0x0c); // display on
  lcd_cmd(0x01); // clear display
  delay(2);
}

void lcd_move(byte pos){
  lcd_cmd(0x80 | pos);
}

void setup()
{
  lcd_init();
  lcd_puts("Hello, Arduino!");
  lcd_move(0x40);
  lcd_puts("i2c LCD module");
  
  pinMode(ledPin, OUTPUT); // Lチカ
}

void loop()
{
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(500);
}

