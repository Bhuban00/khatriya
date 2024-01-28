#include <Servo.h>

#define SENS  2

#define RELE  10

#define SERVO 11

#define RON   LOW
#define ROF   HIGH

Servo servo;

bool flSt = false;
int16_t i = 0;
bool up = false;

void Sens()
{
  //Serial.begin(9600);
  if (!digitalRead(SENS))
  {
    flSt = true;
    //Serial.println("jole");
  }
  else
  {
    flSt = false;
    //Serial.println("jolenaa");
  }
}

void setup()
{
  pinMode(SENS, INPUT_PULLUP);
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, ROF);
  servo.attach(SERVO);
  servo.write(0);
}

void loop()
{
  Sens();
  if (flSt)
  {
    if (servo.attached())
      servo.detach();
    digitalWrite(RELE, RON);
  }
  else
  {
    digitalWrite(RELE, ROF);
    if (!servo.attached())
      servo.attach(SERVO);
    else
    {
      if (!up)
      {
        do
        {
          Sens();
          i++;
          servo.write(i);
          if (i == 180) up = true;
          if (flSt)
          {
            servo.detach();
            break;
          }
        }
        while (i <= 180 && !flSt);
      }
      else
      {
        do
        {
          Sens();
          i--;
          servo.write(i);
          if (i == 0) up = false;
          if (flSt)
          {
            servo.detach();
            break;
          }
        }
        while (i >= 0 && !flSt);
      }
    }
  }
}
