#include "cp.hpp"

const int num = 10;

void* consume_routine(void* arg)
{
  int data;
  RingQueue *q = (RingQueue*)arg;
  while(1)
  {
    q->PopData(d);
  }
}

void* product_routine(void* arg)
{
  RingQueue* q = (RingQueue*)arg;
  srand((unsigned)time(NULL));
  while(1)
  {
    int data = rand()%100 + 1;
    q->PushData(data);
  }
}

int main()
{
  RingQueue *q = new RingQueue(num);
  pthread_t c,p; //一个生产者一个消费者

  pthread_create(&c,NULL,consume_routine,(void*)q);
  pthread_create(&p,NULL,product_routine,(void*)q);

  pthread_join(c,NULL);
  pthread_join(p,NULL);

  delete(q);
  q = NULL;
}
