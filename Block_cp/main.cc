#include "cp.hpp"

const int num = 25;

void* consume_routine(void* arg)
{
  BlockQueue* bqp = (BlockQueue*)arg;
  int data;
  while(1)
  {
    bqp->PopData(data);
    cout << "consume done,data is :" << data << endl;
  }
}

void* product_routine(void* arg)
{
  BlockQueue* bqp = (BlockQueue*)arg;
  srand((unsigned)time(NULL));
  while(1)
  {
    int data = rand()%100 + 1;
    bqp->PushData(data);
    cout << "product done,data is :" << data << endl;
  }
}
int main()
{
  BlockQueue* bqp = new BlockQueue(num);

  pthread_t c,p;

  pthread_create(&p,NULL,product_routine,(void*)bqp);
  pthread_create(&c,NULL,consume_routine,(void*)bqp);

  pthread_join(c,NULL);
  pthread_join(p,NULL);

  delete bqp;
  bqp = NULL;

  
}
