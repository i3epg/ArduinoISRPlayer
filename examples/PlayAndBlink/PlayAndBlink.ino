/* Данный скетч демонстрирует работу библиотеки _3epgIsrPlayer
 *  В функции setup настраиваем работу и запускаем мелодию
 *  В функции loop моргаем светодиодом каждые пол секунды, 
 *    не отвлекаясь на воспроизведение мелодии
 */

#define _3IPPortDPin _3IPpin2 //назначение 3го пина для воспроизведения
                              //именно к этому пину нужно подключать спикер
                              //данный дефайн нужно указывать ДО подлючения библиотеки!!!

#define _3IPCPUfreq 16000000 //указываем нужную частоту работы контроллера
                             //также делаем это ДО подлючения библиотеки!!!

#include <_3epgIsrPlayer.h>


//создаём массив с мелодией, длина массива - количество нот * 2 плюс один
int Melody[(28*2)+1]{28, //количество нот в мелодии
                      NOTE_C4,2500, //сначала нота, потом длительность в 1/10000 секундах
                      NOTE_A4,2500,  NOTE_A4,2500, NOTE_G4,2500, NOTE_A4,2500, NOTE_F4,2500, 
                      NOTE_C4,2500,  NOTE_C4,2500, NOTE_C4,2500, NOTE_A4,2500, NOTE_A4,2500, 
                      NOTE_AS4,2500, NOTE_G4,2500, NOTE_C5,5000, NOTE_C5,2500, NOTE_D4,2500, 
                      NOTE_D4,2500,  NOTE_AS4,2500,NOTE_AS4,2500,NOTE_A4,2500, NOTE_G4,2500, 
                      NOTE_F4,2500,  NOTE_C4,2500, NOTE_A4,2500, NOTE_A4,2500, NOTE_G4,2500, 
                      NOTE_A4,2500,  NOTE_F4,5000};

void setup() {
  // put your setup code here, to run once:

  _3IPSetup();          //первоначальная настройка библиотеки

  _3IPSetMelody(Melody);//указание на массив с мелодией

  _3IPPlay();           //Начало поспроизведения

  pinMode(LED_BUILTIN,OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:

  delay(500);  
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));

}
