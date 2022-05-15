#include <I2C.h>
#include <II2C.h>
#include <MPU6050.h>
#include <MultiFuncShield.h>
#include <EEPROM.h>

#define s1 6
#define s2 9
#define s3 A5
#define pulse 5
#define On LOW
#define off HIGH 

int y = 0; //0 1 2 3 4 5
bool on = off;
const int rpm[6] = {3, 6, 100, 200, 300, 600};
const long rpmPwm[6] = {3025, 1462, 1400, 1400, 900, 570};

void setup() {

  if(EEPROM.read(10) != 'a') 
  {
    return;
  }
  
  Timer1.initialize();
  MFS.initialize(&Timer1);
  pinMode(pulse, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);

  if(on)
  {
    MFS.write(rpm[y]);    
  }
  else
  {
    MFS.write("OFF"); 
  }  
  digitalWrite(s1, off);
  digitalWrite(s2, off);
  digitalWrite(s3, off);
}

void loop() {

  if(EEPROM.read(10) != 'a') 
  {
    return;
  }
  
  // put your main code here, to run repeatedly:
  int i = 0;
  long timeStart = micros();

  byte btn = MFS.getButton();

  if (btn)
  { 
   byte buttonNumber = btn & B00111111;
   byte buttonAction = btn & B11000000;
  
   if (buttonAction == BUTTON_PRESSED_IND)
   {

      if(buttonNumber == 3)
      {
        on = !on;
        y = 0;
      }
      
      else if(buttonNumber == 2 && on)
      {
        if(y>0)
        {
          y--;
        }
      }
      
      else if(buttonNumber == 1 && on)
      {
        if(y<5 && on)
        {
          y++;

          if(y == 5) {

            digitalWrite(s1, On);
            digitalWrite(s2, On);
            digitalWrite(s3, off);

            for(i=0;i<400;i++) {
              
              delayMicroseconds(800);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            } 
            
            for(i=0;i<400;i++) {
              
              delayMicroseconds(700);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            } 
            
            for(i=0;i<400;i++) {
              
              delayMicroseconds(600);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            }   
  
            for(i=0;i<600;i++) {
              
              delayMicroseconds(550);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            }  
  
            for(i=0;i<600;i++) {
              
              delayMicroseconds(500);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            } 
  
              for(i=0;i<600;i++) {
              
              delayMicroseconds(470);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            }
          }

          else if(y == 4) {
            
            digitalWrite(s1, On);
            digitalWrite(s2, On);
            digitalWrite(s3, off);

            for(i=0;i<200;i++) {
              
              delayMicroseconds(1300);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            } 
            
            for(i=0;i<200;i++) {
              
              delayMicroseconds(1200);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            } 
            
            for(i=0;i<200;i++) {
              
              delayMicroseconds(1100);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            }   
  
            for(i=0;i<200;i++) {
              
              delayMicroseconds(1000);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            }  
  
            for(i=0;i<200;i++) {
              
              delayMicroseconds(900);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            } 
          }

          else if(y == 3) {

            digitalWrite(s1, On);
            digitalWrite(s2, On);
            digitalWrite(s3, off);

            for(i=0;i<100;i++) {
              
              delayMicroseconds(2600);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            } 
            
            for(i=0;i<100;i++) {
              
              delayMicroseconds(2300);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            } 
            
            for(i=0;i<100;i++) {
              
              delayMicroseconds(2000);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            }   
  
            for(i=0;i<100;i++) {
              
              delayMicroseconds(1700);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            }  
  
            for(i=0;i<100;i++) {
              
              delayMicroseconds(1500);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            } 
  
            for(i=0;i<100;i++) {
              
              delayMicroseconds(1400);
              digitalWrite(pulse, HIGH);
              delayMicroseconds(100);
              digitalWrite(pulse, LOW);
            }
          }          
        }
      }

      if(on)
      {
        MFS.write(rpm[y]);    
      }
      else
      {
        MFS.write("OFF"); 
      }
   }
  }

  if(on) {
    
    if(y==1 || y==0) {
      digitalWrite(s1, off);
      digitalWrite(s2, off);
      digitalWrite(s3, off);
    }
    else if(y==2) {
      digitalWrite(s1, On);
      digitalWrite(s2, off);
      digitalWrite(s3, On);
    }
    else {
      digitalWrite(s1, On);
      digitalWrite(s2, On);
      digitalWrite(s3, off);
    }
    
    while((micros() - timeStart) < rpmPwm[y]){}
  
      digitalWrite(pulse, HIGH);
      delayMicroseconds(100);
      digitalWrite(pulse, LOW);
  }
  else {
    digitalWrite(s1, On);
    digitalWrite(s2, On);
    digitalWrite(s3, On);
  }
}
