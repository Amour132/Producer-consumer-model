#pragma once 

#include <iostream>
#include <pthread.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

using std::cout;
using std::endl;

class RingQueue
{
  public:
    RingQueue(int cap)
             :_cap(cap)
              ,ring(cap)
    {
      c_step = p_step = 0;
      sem_init(&blank_sem,0,cap);
      sem_init(&data_sem,0,0);
    }
    
    ~RingQueue()
    {
      sem_destroy(&blank_sem);
      sem_destroy(&data_sem);
    }

    void PushData(const int &data)
    {
      P(blank_sem);
      ring[p_step] = data;
      cout << "product done,data is :" << data << endl;
      V(data_sem);
      p_step++;
      p_step %= _cap;
    }

    void PopData(int &data)
    {
      P(data_sem);
      data = ring[c_step];
      cout << "consume done,data is :" << data << endl;
      V(blank_sem);
      c_step++;
      c_step %= _cap;
    }
  private:

    void P(sem_t& sem)
    {
      sem_wait(&sem);
    }

    void V(sem_t& sem)
    {
      sem_post(&sem);
    }

  private:
    std::vector<int>ring;
    int _cap;
    sem_t blank_sem;
    sem_t data_sem;
    int c_step;
    int p_step;
};
