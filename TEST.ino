#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_1602_RUS.h>//БИБЛИОТЕКА ДЛЯ ДИСПЛЕЯ С ПОДДЕРЖКОЙ РУССКОГО ЯЗЫКА 
LiquidCrystal_1602_RUS lcd(8, 9, 10, 11, 12, 13);

DS3231 Clock;
bool Century=false;
bool h12;
bool PM;

byte year, month, date, DoW, hour, minute, second; //ДВОИЧНЫЕ ЗНАЧЕНИЯ С ДАТЧИКА DS3231

int SECOND,MINUTE,HOUR,DAYWEEK,DAYMONTH,MONTH,YEAR; //ДЕСЯТИЧНЫЕ ЗНАЧЕНИЯ ДЛЯ ВСЕХ ФУНКЦИЙ

String ALLDAYSWEEK [7] = {"ВОСК","ПОНЕ","ВТОР","СРЕД","ЧЕТВ","ПЯТН","СУБО"}; //ДНИ НЕДЕЛИ

  int del = 150;                      
  int tonePin = 7;
  int mode = 1;
  int changeMode = 2;
  int position = 1;
  int var = 0;
  int sdTime [29][2] = {//РАССПИСАНИЕ ЗВОНКОВ
      {8,30},{9,15},{9,18},{9,20},{10,5},{10,18},
      {10,20},{11,5},{11,8},{11,10},{11,55},{12,8},
      {12,10},{12,55},{12,58},{13,0},{13,45},{13,53},
      {13,55},{14,40},{14,43},{14,45},{15,30},{15,38},
      {15,40},{16,25},{16,28},{16,30},{17,15} 
    };

   String couple[] = {"НАЧАЛО","ПАР 1/1","5 МИН","ПРЕДВ","ПАР 1/2","ПЕРЕРЫВ","ПРЕДВ",
                               "ПАР 2/1","5 МИН","ПРЕДВ","ПАР 2/2","ПЕРЕРЫВ","ПРЕДВ",
                               "ПАР 3/1","5 МИН","ПРЕДВ","ПАР 3/2","ПЕРЕРЫВ","ПРЕДВ",
                               "ПАР 4/1","5 МИН","ПРЕДВ","ПАР 4/2","ПЕРЕРЫВ","ПРЕДВ",
                               "ПАР 5/1","5 МИН","ПРЕДВ","ПАР 5/2","КОНЕЦ"};

void setup(){ 
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  
  lcd.begin(16, 2);
  Wire.begin();
 
//////////ИЗМЕМЕНЕНИЕ ДАТЫ////////////////////////////////////////////////
/*Clock.setSecond(18);//Set the second                              //////
Clock.setMinute(48);//Set the minute                                //////
Clock.setHour(16); //Set the hour                                   //////
Clock.setDoW(5); //Set the day of the week                          //////
Clock.setDate(5); //Set the date of the month                       //////
Clock.setMonth(5); //Set the month of the year                      //////
Clock.setYear(18); //Set the year (Last two digits of the year)*/   //////
//////////////////////////////////////////////////////////////////////////

}

void MDK(){//МЕЛОДИЯ ЗВОНКА //МОРТАЛ КОМБАТ
   tone(tonePin, 440, 164.2335);delay(182.481666667);delay(91.2408333333);tone(tonePin, 440, 164.2335);
    delay(182.481666667);delay(91.2408333333);tone(tonePin, 440, 164.2335);tone(tonePin, 440, 164.2335);
    delay(182.481666667);delay(91.2408333333);tone(tonePin, 440, 164.2335);delay(182.481666667);
    delay(91.2408333333);tone(tonePin, 391, 109.489);delay(121.654444444);delay(60.8272222222);
    tone(tonePin, 523, 109.489);delay(121.654444444);delay(60.8272222222);tone(tonePin, 440, 164.2335);
    delay(182.481666667);delay(91.2408333333);tone(tonePin, 440, 164.2335);delay(182.481666667);
    delay(91.2408333333);tone(tonePin, 440, 164.2335);delay(182.481666667);delay(91.2408333333);
    tone(tonePin, 440, 164.2335);delay(182.481666667);delay(91.2408333333);tone(tonePin, 391, 109.489);
    delay(121.654444444);delay(60.8272222222);tone(tonePin, 329, 109.489);delay(121.654444444);
    delay(60.8272222222);tone(tonePin, 440, 164.2335);delay(182.481666667);delay(91.2408333333);
    tone(tonePin, 440, 164.2);delay(182.481666667);delay(91.2408333333);tone(tonePin, 440, 164.2335);
    delay(182.481666667);delay(91.2408333333);tone(tonePin, 440, 164.2335);delay(182.481666667);
    delay(91.2408333333);tone(tonePin, 391, 109.489);delay(121.654444444);delay(60.8272222222);
    tone(tonePin, 523, 109.489);delay(121.654444444);delay(60.8272222222);tone(tonePin, 440, 164.2335);
    delay(182.481666667);delay(91.2408333333);tone(tonePin, 440, 164.2335);delay(182.481666667);
    delay(91.2408333333);tone(tonePin, 440, 109.489);delay(121.654444444);delay(60.8272222222);
    tone(tonePin, 440, 54.7445);delay(60.8272222222);delay(30.4136111111);tone(tonePin, 440, 54.7445);
    delay(60.8272222222);delay(121.654444444);tone(tonePin, 440, 54.7445);delay(60.8272222222);
    delay(30.4136111111);tone(tonePin, 440, 54.7445);delay(60.8272222222);delay(304.136111111);  
}

void TIME(){//ПОЛУЧЕНИЕ ДАТЫ И ВРЕМЕНИ С DS3231
 int second,minute,hour,date,dayWeek,month,year; 
  second=Clock.getSecond();
  minute=Clock.getMinute();
  hour=Clock.getHour(h12, PM);
  date=Clock.getDate();
  month=Clock.getMonth(Century);
  year=Clock.getYear();
  dayWeek=Clock.getDoW();

  SECOND = second,DEC;
  MINUTE = minute,DEC;
  HOUR = hour,DEC;
  DAYMONTH = date,DEC;
  DAYWEEK = dayWeek,DEC;
  MONTH = month,DEC;
  YEAR = year,DEC;
}

void DayOfWeek(){//СРАВНЕНИЕ С ДНЁМ НЕДЕЛИ
  if((DAYWEEK == 1) || (DAYWEEK == 2) || 
     (DAYWEEK == 3) || (DAYWEEK == 4) || 
     (DAYWEEK == 5) || (DAYWEEK == 6)){
        comparator(HOUR,MINUTE);  
  }
}

void comparator(int h, int m){//СРАВНЕНИЕ С РАСПИСАНИЕМ
  for(int i=0;i<29;i++){
    if((h == sdTime[i][0]) && (m == sdTime[i][1]) && (SECOND == 0)){
      activate();
    }
  }
}

void TIMER(){ //ТАЙМЕР
    int tnHour,tnMin,tpHour,tpMin,NEXTMIN,NOWMIN,PREDMIN;
    
    for(int i=1;i<=29;i++){    
      tnHour = sdTime[i][0];
      tnMin = sdTime[i][1];

      tpHour = sdTime[i-1][0];
      tpMin = sdTime[i-1][1];

      PREDMIN = (tpHour * 60) + tpMin;
      NEXTMIN = (tnHour * 60) + tnMin;
      NOWMIN = (HOUR * 60) + MINUTE; 

     if((NEXTMIN > NOWMIN) && (NOWMIN >= PREDMIN)){
       lcd.setCursor(8,1); 
       if(((NEXTMIN - NOWMIN)/60)<10) {lcd.print("0");}
       lcd.print((NEXTMIN - NOWMIN)/60);
       lcd.print(":");
       if((NEXTMIN - NOWMIN-1)<10){lcd.print("0");}
       lcd.print((NEXTMIN - NOWMIN-1)%60);
       lcd.print(":");
       if((59-SECOND)<10){lcd.print("0");}
       lcd.print(59-SECOND);

       if(changeMode==2){
         lcd.setCursor(0,1);
         lcd.print(couple[i]);
       }
     }
   }
}

void onOff(){ //ВКЛЮЧЕНИЕ И ВЫКЛЮЧЕНИЕ 
    if(mode==1){ 
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print(L"ЗВОНКИ ОТКЛ");
      delay(1500);
    }
    if(mode==2){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print(L"ЗВОНКИ ВКЛ");
      delay(1500);
    }
  
    switch(mode){ 
      case 1:{ 
        mode=2;
        break;
      }
    
      case 2:{
        mode=1;
        break;
      }
    }
}

void clockOnOff(){//ВКЛЮЧЕНИЕ И ВЫКЛЮЧЕНИЕ // КНОПКА
 int x = 0;
  if(digitalRead(2) == HIGH){
    if(changeMode==2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(L"АКТИВАЦИЯ 5 СЕК");

      lcd.setCursor(3,1);
      lcd.print(L"ВКЛ / ВЫКЛ");
    }
    
    for(int i=0;i<50;i++){
      delay(100);
      if(digitalRead(2) == HIGH){x++;}
      if(digitalRead(2) == LOW){break;}
    }
    if(x == 50){onOff();}
  }
}

void activate(){//АКТИВАЦИЯ ЗВОНКА
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print(L"ЗВОНОК");
  lcd.setCursor(0,0);
  lcd.print("#");
  MDK();
}

void bellNow(){//ВКЛЮЧЕНИЕ ЗВОНКА КНОПКОЙ
  int x = 0;
  if(digitalRead(3) == HIGH){
    if(changeMode==2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(L"АКТИВАЦИЯ 5 СЕК");

      lcd.setCursor(4,1);
      lcd.print(L"ЗВОНОК");
    }
    
    for(int i=0;i<50;i++){
      delay(100);
      if(digitalRead(3) == HIGH){x++;}
      if(digitalRead(3) == LOW){break;}
    }
    if(x == 50){activate();}
  }
}

void displayDate(){//ОТОБРАЖЕНИЕ ДАТЫ
  lcd.clear();

  lcd.setCursor(7,0);
  lcd.print("|");
  
  lcd.setCursor(1,0);
  lcd.print(" ");
  if(DAYMONTH<10) lcd.print("0");
  lcd.print(DAYMONTH);
  lcd.print(".");
  if(MONTH<10) lcd.print("0");
  lcd.print(MONTH);
  lcd.setCursor(8,0);
  if(HOUR<10) lcd.print("0");
  lcd.print(HOUR);
  lcd.print(":");
  if(MINUTE<10) lcd.print("0");
  lcd.print(MINUTE);
  lcd.print(":");
  if(SECOND<10) lcd.print("0");
  lcd.print(SECOND);

  if(mode == 1){
    lcd.setCursor(7,1);
    lcd.print("|");
    
    TIMER();
    }
}

void sign(){//ИНДИКАТОР
  lcd.setCursor(0,0);
  lcd.print("*");

  digitalWrite(6,HIGH);
  delay(500);

  lcd.setCursor(0,0);
  lcd.print(" ");
  digitalWrite(6,LOW);
}

void ifOnOff(int check){
 
  switch(check){
    case 1:{
      sign();
      displayDate();
      comparator(HOUR,MINUTE); 
 
      break;
    }
    case 2:{
      displayDate();

      digitalWrite(6,LOW);
      break;
    }
  }
}

void changeTime(){
  int x = 0;   
  
  if(digitalRead(4) == HIGH){//ПЕРЕКЛЮЧЕНИЕ РЕДАКТИРОВАНИЯ ВРЕМЕНИ

    if(changeMode==2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(L"АКТИВАЦИЯ 5 СЕК");

      lcd.setCursor(0,1);
      lcd.print(L"РЕДАКТОР ВРЕМЕНИ");
    }
    for(int i=0;i<50;i++){
      delay(100);
      if(digitalRead(4) == HIGH){x++;}
      if(digitalRead(4) == LOW){break;}
    }
    if(x == 50){
      
      if(changeMode==1){        
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(L"КОРРЕКЦИЯ ВЫКЛ");
        delay(1500);
      }
      if(changeMode==2){
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(L"КОРРЕКЦИЯ ВКЛ");
        delay(1500);
      }
  
      switch(changeMode){ 
        case 1:{
          changeMode=2;
          break;}
        case 2:{
          changeMode=1;
          break;}
      }
    }
  }
  
  switch(changeMode)
    case 1:{
      
      if(digitalRead(3) == HIGH) {position++; if(position>6) position=6;}
      if(digitalRead(2) == HIGH) {position--; if(position<1) position=1;}
      
      switch(position){
        case 1:{
          lcd.setCursor(2,1);
          lcd.print(L"ЧАС");
          delay(del);
          var=HOUR;
          if(digitalRead(5) == HIGH) {var++; if(var>24) var=0;}
          if(digitalRead(4) == HIGH) {var--; if(var<0) var=24;}
          HOUR=var;
          Clock.setHour(HOUR);
          break;
        }
        
        case 2:{
          lcd.setCursor(2,1);
          lcd.print(L"МИН");
          delay(del);
          var=MINUTE;
          if(digitalRead(5) == HIGH) {var++; if(var>59) var=0;}
          if(digitalRead(4) == HIGH) {var--; if(var<0) var=59;}
          MINUTE=var;
          Clock.setMinute(MINUTE);
          break;
        }
        
        case 3:{ 
          lcd.setCursor(2,1);
          lcd.print(L"ДЕНЬ");

          delay(del);
          var=DAYMONTH;
          if(digitalRead(5) == HIGH) {var++; if(var>31) var=1;}
          if(digitalRead(4) == HIGH) {var--; if(var<1) var=31;}
          DAYMONTH=var;
          Clock.setDate(DAYMONTH);
          break;
        }
        
        case 4:{
          lcd.setCursor(2,1);
          lcd.print(L"МЕС");
          delay(del);
          var=MONTH;
          if(digitalRead(5) == HIGH) {var++; if(var>12) var=1;}
          if(digitalRead(4) == HIGH) {var--; if(var<1) var=12;}
          MONTH=var;
          Clock.setMonth(MONTH);
          break;
        }
        
        case 5:{
          lcd.setCursor(2,1);
          lcd.print(L"ГОД");
          lcd.setCursor(2,0);
          lcd.print(2000+YEAR);
          lcd.print(" ");
          delay(del);
          var=YEAR;
          if(digitalRead(5) == HIGH) {var++;}
          if(digitalRead(4) == HIGH) {var--;}
          YEAR=var;
          Clock.setYear(YEAR);
          break;
        }
        
        case 6:{
          lcd.setCursor(2,1);
          lcd.print(L"ДНЕД");
          lcd.setCursor(2,0);
          lcd.print(ALLDAYSWEEK[DAYWEEK]);
          lcd.print(" ");
          delay(del);
          var=DAYWEEK;
          if(digitalRead(5) == HIGH) {var++;}
          if(digitalRead(4) == HIGH) {var--;}
          DAYWEEK=var;
          Clock.setDoW(DAYWEEK);
          break;
        }
      }
    }
}

void loop(){
  TIME();
  clockOnOff();
  bellNow();
  ifOnOff(mode);   
  changeTime();
  delay(500);
}
