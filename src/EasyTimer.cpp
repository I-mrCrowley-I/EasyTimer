#include "EasyTimer.h"

EasyTimer::~EasyTimer()
{
  while (Head != nullptr)
  {
    TimerNode *current = this->Head;
    this->Head = current->pNext;
    delete current;
  }
}

// Добавление новоего таймера
void EasyTimer::add(const Handler handler, const uint32_t interval)
{
  if (Head == nullptr)
  {
    Head = new TimerNode(millis(),
                         interval,
                         handler);
  }
  else
  {
    TimerNode *current = this->Head;
    while (current->pNext != nullptr)
    {
      current = current->pNext;
    }
    current->pNext = new TimerNode(millis(),
                                   interval,
                                   handler);
  }
}

// Удаление таймера
// Присутствует фрагментация памяти!!!
void EasyTimer::remove(const Handler handler)
{
  TimerNode *toDelete = this->Head;
  if (this->Head != nullptr)
  {
    if (toDelete->handler == handler)
    {
      this->Head = toDelete->pNext;
      delete toDelete;
    }
    else
    {
      TimerNode *previuos;
      while (toDelete != nullptr)
      {
        if (toDelete->handler == handler)
        {
          previuos->pNext = toDelete->pNext;
          delete toDelete;
          break;
        }
        previuos = toDelete;
        toDelete = toDelete->pNext;
      }
    }
  }
}

void EasyTimer::start(const Handler handler)
{
  active(true, handler);
}

void EasyTimer::stop(const Handler handler)
{
  active(false, handler);
}

void EasyTimer::active(const bool active, const Handler handler)
{
  TimerNode *current = this->Head;
  while (current != nullptr)
  {
    if (current->handler == handler)
    {
      current->active = active;
      break;
    }
    current = current->pNext;
  }
}

void EasyTimer::loop()
{
  TimerNode *current = this->Head;
  while (current != nullptr)
  {
    if (millis() - current->previous >= current->interval)
    {
      current->handler();
      current->previous = millis();
    }
    current = current->pNext;
  }
}
