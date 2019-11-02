#include <EasyTimer.h>

void blink()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Timer.add(1000, blink);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Timer.loop();
}
