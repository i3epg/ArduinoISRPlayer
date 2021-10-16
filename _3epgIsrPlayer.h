/***********************************************************************
 * 	_3epgISRPlayer v0.9
 * 
 * Copyright (c) <2021>, <i3epg>
 *
 * Разрешается повторное распространение и использование как в виде 
 * исходного кода, так и в двоичной форме, с изменениями или без, 
 * при соблюдении следующих условий:
 * 
 *  1. При повторном распространении исходного кода должно оставаться 
 *   указанное выше уведомление об авторском праве, этот список 
 *   условий и последующий отказ от гарантий.
 *  2. При повторном распространении двоичного кода должна сохраняться 
 *   указанная выше информация об авторском праве, этот список условий
 *   и последующий отказ от гарантий в документации и/или в других 
 *   материалах, поставляемых при распространении.
 *  3. Ни название <Организации>, ни имена её сотрудников не могут быть 
 *   использованы в качестве поддержки или продвижения продуктов, 
 *   основанных на этом ПО без предварительного письменного разрешения.
 *
 *  ЭТО БИБЛИОТЕКА ПРЕДОСТАВЛЕНА ВЛАДЕЛЬЦАМИ АВТОРСКИХ ПРАВ И/ИЛИ 
 *   ДРУГИМИ СТОРОНАМИ «КАК ОНА ЕСТЬ» БЕЗ КАКОГО-ЛИБО ВИДА ГАРАНТИЙ, 
 *   ВЫРАЖЕННЫХ ЯВНО ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ, НО НЕ ОГРАНИЧИВАЯСЬ 
 *   ИМИ, ПОДРАЗУМЕВАЕМЫЕ ГАРАНТИИ КОММЕРЧЕСКОЙ ЦЕННОСТИ И ПРИГОДНОСТИ 
 *   ДЛЯ КОНКРЕТНОЙ ЦЕЛИ. НИ В КОЕМ СЛУЧАЕ НИ ОДИН ВЛАДЕЛЕЦ АВТОРСКИХ 
 *   ПРАВ И НИ ОДНО ДРУГОЕ ЛИЦО, КОТОРОЕ МОЖЕТ ИЗМЕНЯТЬ И/ИЛИ ПОВТОРНО 
 *   РАСПРОСТРАНЯТЬ ПРОГРАММУ, КАК БЫЛО СКАЗАНО ВЫШЕ, НЕ НЕСЁТ 
 *   ОТВЕТСТВЕННОСТИ, ВКЛЮЧАЯ ЛЮБЫЕ ОБЩИЕ, СЛУЧАЙНЫЕ, СПЕЦИАЛЬНЫЕ ИЛИ 
 *   ПОСЛЕДОВАВШИЕ УБЫТКИ, ВСЛЕДСТВИЕ ИСПОЛЬЗОВАНИЯ ИЛИ НЕВОЗМОЖНОСТИ 
 *   ИСПОЛЬЗОВАНИЯ ПРОГРАММЫ (ВКЛЮЧАЯ, НО НЕ ОГРАНИЧИВАЯСЬ ПОТЕРЕЙ 
 *   ДАННЫХ, ИЛИ ДАННЫМИ, СТАВШИМИ НЕПРАВИЛЬНЫМИ, ИЛИ ПОТЕРЯМИ, 
 *   ПРИНЕСЕННЫМИ ИЗ-ЗА ВАС ИЛИ ТРЕТЬИХ ЛИЦ, ИЛИ ОТКАЗОМ ПРОГРАММЫ 
 *   РАБОТАТЬ СОВМЕСТНО С ДРУГИМИ ПРОГРАММАМИ), ДАЖЕ ЕСЛИ ТАКОЙ 
 *   ВЛАДЕЛЕЦ ИЛИ ДРУГОЕ ЛИЦО БЫЛИ ИЗВЕЩЕНЫ О ВОЗМОЖНОСТИ ТАКИХ УБЫТКОВ.
 * 
 *********************************************************************** 
 * 
 * 
 * 
 * 	Библиотека для реализации проигрывания мелодии через спикер 
 *  на платформе Arduino Uno в фоне, не зависимо от выполнения основной
 *  программы.
 *  Для подключения спикера используется один из выходов  
 *   (или несколько, или все сразу :))порта D (0-7 пины Arduino Uno)
 *  Для этого перед подключенией библиотеки нужно задефайнить 
 *  _3IPPortDPin соответствующим образом (по умолчанию используется
 *   четвёртый пин порта D)
 * 
 *  Для указания частоты работы контроллера имеется
 *  define _3IPCPUfreq, по умолчанию равный 16000000 (16МГц)
 * 
 * 	Занимает Timer2, стандартная функция tone работать не сможет
 * 
 * ТЕСТИРОВАЛОСЬ ТОЛЬКО НА ПЛАТФОРМЕ Arduino Uno!!!
 * 
 * 
 * 
 * 
 **********************************************************************/
 
 
 
 /**********************************************************************
void _3IPSetup(); //первичная настройка прерывания
void _3IPSetMelody(int* arr);	
										//указание массива с мелодией
										//формат массива:
										//[0] - количество нот
										//[1] - первая нота
										//[2] - длительность первой ноты в 1/10000 секундах
										//[3] - вторая нота
										//[4] - длительность второй ноты в 1/10000 секундах
										//....

void _3IPPlay(); 	//Старт
void _3IPPause(); //Пауза
void _3IPStop();	//Стоп, отличается от паузы тем, что при последующем 
			//вызове Play мелодия начнётся с начала

***********************************************************************/
#pragma once
#include <Arduino.h>


/*Скоректированные дефайны нот популяного pitches.h
***********************************************************************/

#define NOTE_ZERO 0				//новый дефайн, при воспроизведении этой
													//ноты ничего не играет :) для вставки паузы
													
#define NOTE_B0  int(10000/31)
#define NOTE_C1  int(10000/33)
#define NOTE_CS1 int(10000/35)
#define NOTE_D1  int(10000/37)
#define NOTE_DS1 int(10000/39)
#define NOTE_E1  int(10000/41)
#define NOTE_F1  int(10000/44)
#define NOTE_FS1 int(10000/46)
#define NOTE_G1  int(10000/49)
#define NOTE_GS1 int(10000/52)
#define NOTE_A1  int(10000/55)
#define NOTE_AS1 int(10000/58)
#define NOTE_B1  int(10000/62)
#define NOTE_C2  int(10000/65)
#define NOTE_CS2 int(10000/69)
#define NOTE_D2  int(10000/73)
#define NOTE_DS2 int(10000/78)
#define NOTE_E2  int(10000/82)
#define NOTE_F2  int(10000/87)
#define NOTE_FS2 int(10000/93)
#define NOTE_G2  int(10000/98)
#define NOTE_GS2 int(10000/104)
#define NOTE_A2  int(10000/110)
#define NOTE_AS2 int(10000/117)
#define NOTE_B2  int(10000/123)
#define NOTE_C3  int(10000/131)
#define NOTE_CS3 int(10000/139)
#define NOTE_D3  int(10000/147)
#define NOTE_DS3 int(10000/156)
#define NOTE_E3  int(10000/165)
#define NOTE_F3  int(10000/175)
#define NOTE_FS3 int(10000/185)
#define NOTE_G3  int(10000/196)
#define NOTE_GS3 int(10000/208)
#define NOTE_A3  int(10000/220)
#define NOTE_AS3 int(10000/233)
#define NOTE_B3  int(10000/247)
#define NOTE_C4  int(10000/262)
#define NOTE_CS4 int(10000/277)
#define NOTE_D4  int(10000/294)
#define NOTE_DS4 int(10000/311)
#define NOTE_E4  int(10000/330)
#define NOTE_F4  int(10000/349)
#define NOTE_FS4 int(10000/370)
#define NOTE_G4  int(10000/392)
#define NOTE_GS4 int(10000/415)
#define NOTE_A4  int(10000/440)
#define NOTE_AS4 int(10000/466)
#define NOTE_B4  int(10000/494)
#define NOTE_C5  int(10000/523)
#define NOTE_CS5 int(10000/554)
#define NOTE_D5  int(10000/587)
#define NOTE_DS5 int(10000/622)
#define NOTE_E5  int(10000/659)
#define NOTE_F5  int(10000/698)
#define NOTE_FS5 int(10000/740)
#define NOTE_G5  int(10000/784)
#define NOTE_GS5 int(10000/831)
#define NOTE_A5  int(10000/880)
#define NOTE_AS5 int(10000/932)
#define NOTE_B5  int(10000/988)
#define NOTE_C6  int(10000/1047)
#define NOTE_CS6 int(10000/1109)
#define NOTE_D6  int(10000/1175)
#define NOTE_DS6 int(10000/1245)
#define NOTE_E6  int(10000/1319)
#define NOTE_F6  int(10000/1397)
#define NOTE_FS6 int(10000/1480)
#define NOTE_G6  int(10000/1568)
#define NOTE_GS6 int(10000/1661)
#define NOTE_A6  int(10000/1760)
#define NOTE_AS6 int(10000/1865)
#define NOTE_B6  int(10000/1976)
#define NOTE_C7  int(10000/2093)
#define NOTE_CS7 int(10000/2217)
#define NOTE_D7  int(10000/2349)
#define NOTE_DS7 int(10000/2489)
#define NOTE_E7  int(10000/2637)
#define NOTE_F7  int(10000/2794)
#define NOTE_FS7 int(10000/2960)
#define NOTE_G7  int(10000/3136)
#define NOTE_GS7 int(10000/3322)
#define NOTE_A7  int(10000/3520)
#define NOTE_AS7 int(10000/3729)
#define NOTE_B7  int(10000/3951)
#define NOTE_C8  int(10000/4186)
#define NOTE_CS8 int(10000/4435)
#define NOTE_D8  int(10000/4699)
#define NOTE_DS8 int(10000/4978)

/**********************************************************************/

#define _3IPpin0 B00000001
#define _3IPpin1 B00000010
#define _3IPpin2 B00000100
#define _3IPpin3 B00001000
#define _3IPpin4 B00010000
#define _3IPpin5 B00100000
#define _3IPpin6 B01000000
#define _3IPpin7 B10000000

#ifndef _3IPPortDPin						//по умолчанию управление PD4
#define _3IPPortDPin B00010000 //4 пин на плате Arduino Uno
#endif  											


#ifndef _3IPCPUfreq							//по умолчанию 
#define _3IPCPUfreq 16000000 		//частота процессора 16000000 - 16МГц
#endif

#define _3IPINVERTpin PORTD ^= _3IPPortDPin
#define _3IPSETpin PORTD |= _3IPPortDPin
#define _3IPRESETpin PORTD &= ~(_3IPPortDPin)

#define _3IPOCR2A _3IPCPUfreq/8/10000

volatile bool _3IPEnablePlay;
volatile bool _3IPFirstStart;

int* _3IPMelody;

void _3IPSetup(){
	  DDRD = DDRD | _3IPPortDPin;
	  
	
	  _3IPEnablePlay=false;
	  _3IPFirstStart=true;
	  
{    // инициализация Timer2
    cli();  // отключить глобальные прерывания

      TCCR2A = (1<<WGM21)|(0<<WGM20);//сброс счётчика при совпадении
      TCCR2B = 0;

      OCR2A = _3IPOCR2A; //значение счётчика (10000 раз в секунду)
    
       // Установить CS1x биты так, чтобы таймер работал при тактовой частоте:
    
      TCCR2B |= (0 << CS22)|(1 << CS21)|(0 << CS20); // Clk/8
    
      TIMSK2 = (1 << OCIE2A);//включить прерывание Timer2 при совпадении
 
    sei(); // включить глобальные прерывания	  
}    


  }

volatile int _3IPfreqNote;
volatile int _3IPCountInvert;
volatile int _3IPHowMuchInvert;
volatile int _3IPToNewNote;
volatile int _3IPCurNote;

#define _freqNote _3IPMelody[(_3IPCurNote*2)+1]
#define _timeNote _3IPMelody[(_3IPCurNote+1)*2]


void _3IPSetMelody(int* arr){
	_3IPMelody=arr;
  _3IPFirstStart=true;
}

void _3IPPlay(){ //Старт
  _3IPEnablePlay=true;
}

	
void _3IPPause(){ //Пауза
  _3IPEnablePlay=false;
}	
	
void _3IPStop(){//Стоп, отличается от паузы тем, что при последующем вызове Play мелодия начнётся с начала
  _3IPEnablePlay=false;
  _3IPFirstStart=true;
}
  
ISR(TIMER2_COMPA_vect)
{

  if (_3IPEnablePlay) {

    if (_3IPFirstStart){ //Первый запуск мелодии
      _3IPCurNote=0;
      _3IPToNewNote=_timeNote; //через сколько итераций следующая нота
      _3IPfreqNote=_freqNote;
      if (_3IPfreqNote>0){
        _3IPCountInvert=_3IPfreqNote; //через сколько итераций переключать пин
      }else {_3IPCountInvert=0;}
    
      _3IPHowMuchInvert=_3IPCountInvert;

      _3IPFirstStart=false;
      if (_3IPCountInvert!=0) _3IPINVERTpin;
    }
  
    _3IPHowMuchInvert--;
    if (_3IPHowMuchInvert<=0){ 
      _3IPHowMuchInvert=_3IPCountInvert;
      if (_3IPCountInvert!=0) _3IPINVERTpin;    //переключаем пин, если нужное количество прошло
    }

    _3IPToNewNote--;
  
    if (_3IPToNewNote<=0){  //включаем следующую ноту
      _3IPRESETpin;
      _3IPCurNote++;
      if (_3IPCurNote>=_3IPMelody[0]){  //если нота была последней
        _3IPCurNote=0;              //то ставим опять первую ноту
      }
      _3IPToNewNote=_timeNote; //через сколько итераций следующая нота
      _3IPfreqNote=_freqNote;
      if (_3IPfreqNote>0){
        _3IPCountInvert=_3IPfreqNote; //через сколько итераций переключать пин
      }else {_3IPCountInvert=0;}
      _3IPHowMuchInvert=_3IPCountInvert;    
    }
  
  }		

}
																			
																			

