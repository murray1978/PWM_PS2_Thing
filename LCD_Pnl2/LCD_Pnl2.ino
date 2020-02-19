/*
  Test Program.
  Button on Pin 4,
  PWM on Pin 3,
  Pot on adc0
  I2C LCD on SDA and SCL pins, Jaycar XC3706 
  
  Arduino PWM runs at 500hz, 
    we will need an RC filter 
    either one at 500hz(3KR, 100nF) 
    or
    at 100hz (1K5, 10nF)
    Real Values used are 1K5 and 10uF
    https://www.allaboutcircuits.com/technical-articles/low-pass-filter-a-pwm-signal-into-an-analog-voltage/
    and 
    https://www.electronicproducts.com/RC_Filter_Cutoff_Frequency_Calculator.aspx

    voltages and pecentages.
    Voltages measured, percentages 5V and 3.3V
    Power   80mV,   1.6%   2.42%
    vol_up  1.68V,  33.6%  50%
    menu    1V,     20%    30%
    vol_dn  680mV,  13.6%  20%
    v1/v2   360mV,  7.2%   11%   
    3.3V for no button down = 66% for 5V and 100% for 3.3V
*/
//LCD for testing
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);

//Pins we will use, and pwm values we calculated from above.
#define POWER       13  
#define POWER_VAL   4
#define VOL_UP      12
#define VOL_UP_VAL  84
#define MENU        11
#define MENU_VAL    51
#define VOL_DN      10  
#define VOL_DN_VAL  34
#define V1V2        9  
#define V1V2_VAL    18
#define REST        0
#define REST_VAL    140

#define ADCPIN      3

#define PRESS_DELAY 25    //beats the debounce code?

void setup() 
{
  Serial.begin(9600);
  Serial.println(__FILE__); Serial.println(__DATE__);

  //Setup our LCD screen
  Wire.begin();
  Wire.beginTransmission(0x27);
  int error = Wire.endTransmission();
  
  if (error == 0) 
  {
    Serial.println(": LCD found.");

  } 
  else 
  {
    Serial.println(": LCD not found.");
  }
  lcd.begin(16,2);
  lcd.setBacklight(127);
  lcd.home();
  lcd.clear();
  lcd.noBlink();
  lcd.noCursor();
  
  lcd.setCursor(0, 0);
  lcd.print("PWM:");
  lcd.setCursor(0, 1);
  lcd.print("V:");
  
  pinMode( ADCPIN, OUTPUT);
}

void loop() 
{
  //Read our Pot and scale for the adc
  int pwmSignal = analogRead(0);
  pwmSignal = map(pwmSignal, 0, 1024, 0, 255);
  //Calculated voltage = real voltage with above real RC filter
  float volt = ((float)pwmSignal/255.0) * 5.0;

  //Just for debugging
  Serial.println(volt);

  //If we are pressing a button we send the pwm value, else we send the REST_VAL 
  if(digitalRead(4))
  {
    analogWrite(ADCPIN, pwmSignal);
    delay(30); //switch debounce
  }
  else
  {
    analogWrite(ADCPIN, REST_VAL);
  }

  
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PWM:");
  lcd.setCursor(0, 1);
  lcd.print("V:");
  lcd.setCursor(5, 0);
  lcd.print(pwmSignal);
  lcd.setCursor(5, 1);
  lcd.print(volt);
}
