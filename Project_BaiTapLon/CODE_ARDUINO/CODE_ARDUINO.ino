#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Wire.h>
/*
#include <LiquidCrystal.h>  //this library is included in the Arduino IDE
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
/*                                    -------------------
                                      |  LCD  | Arduino |
                                      -------------------
 LCD RS pin to digital pin 12         |  RS   |   12    |
 LCD Enable pin to digital pin 11     |  E    |   11    |
 LCD D4 pin to digital pin 5          |  D4   |   5     |
 LCD D5 pin to digital pin 4          |  D5   |   4     |
 LCD D6 pin to digital pin 3          |  D6   |   3     |
 LCD D7 pin to digital pin 2          |  D7   |   2     |
 LCD R/W pin to ground                |  R/W  |   GND   |
                                      -------------------
*/
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int LM35 = A0;// chân analog kết nối tới cảm biến LM35
int den=8;
int quat=A1;
void setup() {
 //cau hinh thanh ghi DDRB output
 DDRB=DDRB|B0000001;
 DDRC=DDRC|B0000010;
 DDRC=DDRC&B1111110;
 pinMode(den,OUTPUT);
 pinMode(quat,OUTPUT);
 //pinMode(LM35,INPUT);//Che do ngo vao
 lcd.begin(16,2);
 
 lcd.print("May Ap Trung Ga");
 lcd.setCursor(0,1);
 Serial.begin(9600); 
}
void loop(){
  delay(1000);
  lcd.clear();
  int NhietDo;
  while (1){
    /*  
     *   theo quy tac tam suat ta co
     *   cứ 5000mv thi tuong ung 1024 adc(2^10-1)
     *   vậy điện áp  reading
     *   dienap=reading*5000/1024
     *   theo datasheet ta co
     *   cu 10mV thi tuong ung 1 do C
     *   vay dien ap        nhiet do
     *   => nhietdo=dienap/10
     *   hay nhietdo=(reading*5000/1024)/10
     *   hay nhietdo=(reading*500/1024)
    */
    //đọc giá trị từ cảm biến LM35
      int reading = analogRead(PINC&B00000001);
      float temp=(((float)reading*500.00)/1024.00);
      NhietDo=(float)temp;
      lcd.setCursor(0,0);
      lcd.print("NHIET DO:");
      lcd.print(NhietDo);
      lcd.write(233);
      lcd.print("C");
      if(NhietDo>37){
        lcd.setCursor(0,1);
        lcd.print("WARRING!:HOT   ");
        PORTC|=B00000010;//BAT QUAT
        digitalWrite(den,LOW);//Tắt đèn khi nhiệt độ lên cao hơn 37 độ C
        delay(2000);
     }
     if(NhietDo<37){
        lcd.setCursor(0,1);
        lcd.print("WARRING!:COOL  ");
        PORTB|=B00000001;//BẬT ĐÈN 
        digitalWrite(quat,LOW);//Tắt quạt khi nhiệt độ bé hơn 37 độ C  
        delay(2000);    
     }
     if((NhietDo==37)&&(NhietDo<38)){
        lcd.setCursor(0,1);
        lcd.print("BINH THUONG   ");
        PORTB|=B00000001;//BẬT ĐÈN
        digitalWrite(quat,LOW);//Tắt quạt khi nhiệt độ binh thuong  
        delay(2000);
     }
      
      delay(1000);
      
  }
  
}
