#pragma once

#include <iostream>
#include <unistd.h>
#include <queue>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

class BlockQueue
{
  public:

    BlockQueue(int cap):_cap(cap),waterline(cap*2/3)
    {
      pthread_mutex_init(&lock,NULL);
      pthread_cond_init(&cond_c,NULL);
      pthread_cond_init(&cond_p,NULL);
    }

    ~BlockQueue()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&cond_c);
      pthread_cond_destroy(&cond_p);
    }

    void PushData(const int &data)
    {
      LockQueue();
      if(IsFull())
      {
        ProductWait();
      }
      bq.push(data);
      if(IsWaterLine())
      {
        SignalConsume();
      }
      Unlock();
    }

    void PopData(int &data)
    {
      LockQueue();
      if(IsEmpty())
      {
        ConsumeWait();
        SignalProduct();
      }
      data = bq.front();
      bq.pop();
      Unlock();
    }

  private:
    void LockQueue()
    {
      pthread_mutex_lock(&lock);
    }

    void Unlock()
    {
      pthread_mutex_unlock(&lock);
    }

    void ConsumeWait()
    {
      pthread_cond_wait(&cond_c,&lock);
    }
    
    void ProductWait()
    {
      pthread_cond_wait(&cond_p,&lock);
    }

    void SignalConsume()
    {
      pthread_cond_signal(&cond_c);
    }
    
    void SignalProduct()
    {
      pthread_cond_signal(&cond_p);
    }

    bool IsFull()
    {
      return bq.size() == _cap;
    }
     
    bool IsEmpty()
    {
      return bq.size() == 0;
    }
      
    bool IsWaterLine()
    {
      return bq.size() > waterline ? true : false;
    }
        
  private:
    queue<int> bq;
    int _cap;
    int waterline;

    pthread_mutex_t lock;
    pthread_cond_t cond_c;
    pthread_cond_t cond_p;

};
