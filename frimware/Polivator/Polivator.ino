#include <GyverPower.h>
#include <powerConstants.h>


// Выводы, подключенные к датчику
#define sensorPower 7
#define sensorPin A0

void setup()
{
  pinMode(sensorPower, OUTPUT);
  pinMode(6, OUTPUT);
  // Изначально оставляем датчику выключенным
  digitalWrite(sensorPower, LOW);

  Serial.begin(9600);

  power.autoCalibrate(); // автоматическая калибровка ~ 2 секунды , средняя но достаточная точность
  // отключение ненужной периферии
  power.hardwareDisable(PWR_TIMER1); // см раздел константы в GyverPower.h, разделяющий знак " | "
  // управление системной частотой
  //power.setSystemPrescaler(PRESCALER_2); // см константы в GyverPower.h

  // настройка параметров сна
  power.setSleepMode(STANDBY_SLEEP); // если нужен другой режим сна, см константы в GyverPower.h (по умолчанию POWERDOWN_SLEEP)
  power.bodInSleep(false); // рекомендуется выключить bod во сне для сохранения энергии (по умолчанию false - выключен!!)
}
//int i = 0;
int flag = 1;
int flag1 = 0;
int flag2 = 0;
int timee = 0;
void loop() {
 power.hardwareEnable(PWR_ALL);
  // получить показание из функции ниже и напечатать его
  Serial.print("Analog output: ");
  Serial.println(analogRead(readSensor()));
  if (analogRead(sensorPin) > 400) {
    digitalWrite(6, HIGH);
    power.hardwareDisable(PWR_ALL);//PWR_ADC
    power.sleepDelay(10000);
     power.hardwareEnable(PWR_ALL);
    digitalWrite(6, LOW);
    //digitalWrite(6, HIGH);
  }
  /* if (analogRead(sensorPin) < 300) {
     digitalWrite(6, LOW);
     //digitalWrite(6, HIGH);
    }

    while (flag == 0) {
      if (analogRead(readSensor()) > 600) {
        digitalWrite(6, HIGH);
        delay(10000);
        //power.sleepDelay(10000);
        digitalWrite(6, LOW);
      }
      else {
        flag = 0;
      }
     }
     flag = 1;*/
  delay(100);
  power.hardwareDisable(PWR_ALL);
  //power.sleepDelay(5000);
  power.sleepDelay(43200000);
}

// Данная функция возвращает аналоговый результат измерений датчика влажности почвы
int readSensor()
{
  digitalWrite(sensorPower, HIGH);  // Включить датчик
  delay(10);                        // Дать время питанию установиться
  int val = analogRead(sensorPin);  // Прочитать аналоговое значение от датчика
  digitalWrite(sensorPower, LOW);   // Выключить датчик
  return val;                       // Вернуть аналоговое значение влажности
}
