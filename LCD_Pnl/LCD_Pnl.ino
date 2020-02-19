/*
  Proof of concept code for Mark's project.
  Arduino PWM runs at 500hz, 
    we will need an RC filter 
    either one at 500hz(3KR, 100nF) 
    or
    at 100hz (1K5, 100nF)
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
//Pins we will use
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

void setup() {
  Serial.begin(9600);
  Serial.println(__FILE__); Serial.println(__DATE__);

  //Define your inputs. basiclly many calls to TRISB = TRISB << pin;
  pinMode( POWER, INPUT );
  pinMode( VOL_UP, INPUT );
  pinMode( MENU, INPUT );
  pinMode( VOL_DN, INPUT );
  pinMode( V1V2, INPUT );
  pinMode( ADCPIN, OUTPUT);
}

void loop() {

  if( digitalRead(POWER) )
  {
    analogWrite(ADCPIN, POWER_VAL);
    delay(20);
    Serial.println("Power");
  }
  else if( digitalRead(VOL_UP) )
  {
    analogWrite(ADCPIN, VOL_UP_VAL);
    delay(20);
    Serial.println("VolumeUp");
  }
  else if( digitalRead(MENU) )
  {
    analogWrite(ADCPIN,MENU_VAL);
    delay(20);
    Serial.println("menu");
  }
  else if( digitalRead(VOL_DN) )
  {
    analogWrite(ADCPIN,VOL_DN_VAL);
    delay(20);
    Serial.println("volume_dn");
  }
  else if( digitalRead(V1V2) )
  {
    analogWrite(ADCPIN, V1V2_VAL);
    delay(20);
    Serial.println("V1V2");
  }
  analogWrite(ADCPIN, REST_VAL);
}
