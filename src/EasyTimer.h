#ifndef _EASYTIMER_H_
#define _EASYTIMER_H_

#include <Arduino.h>

typedef void (*Handler)();

class EasyTimer
{
private:
  class TimerNode
  {
  public:
    uint32_t previous;
    uint32_t interval;
    Handler handler;
    bool active;
    TimerNode *pNext;

    TimerNode(uint32_t previous, uint32_t interval,
              Handler handler) : active(true), pNext(nullptr)
    {
      this->previous = previous;
      this->interval = interval;
      this->handler = handler;
    }
  };

  TimerNode *Head;

public:
  EasyTimer() : Head(nullptr){};
  ~EasyTimer();

  void add(const Handler, const uint32_t);
  void remove(const Handler);
  void active(const bool, const Handler);
  void start(const Handler);
  void stop(const Handler);
  void loop();
};

#endif
