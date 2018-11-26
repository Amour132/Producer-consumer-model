#pragma once 

#include <iostream>
#include <pthread.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

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

    void PushData(int &data)
    {


    }
    void PopData(int &data);
  private:

  private:
    vector<int>ring;
    int _cap;
    sem_t blank_sem;
    sem_t data_sem;
    int c_step;
    int p_step;
};
