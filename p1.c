#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[3];

void * loop_print(void * arg)
{
  // printf("Starting new thread\n");
  int *args = arg;
  unsigned long i = 0;
  int j = args[0];
  // printf("j: %d\n", j);
  int k = args[1];
  // printf("k: %d\n", k);

  int cnt[2+k];

  while(j > 0)
  {
    cnt[k] = k;
    printf("%d ", cnt[k]);
    for(i = 0; i < 100000000; i++)
    {}
    k++;
    j--;
  }
  free(args);
  
}

int main()
{
  int i = 0;
  int j = 3;
  int k = 1;
  int err;

  int * args;
  while(i < 3) {
      args = (int *)malloc(sizeof(int)*2);
      args[0] = j;
      args[1] = k;
      //printf("im ohk here\n");

    err = pthread_create(&(tid[i]), NULL, &loop_print, args);
    if (err != 0)
    {
      printf("\ncan't create thread :[%s]", strerror(err));
      free(args);
    }
    
    j--;
    k *= 10;
    i++;
  }

  sleep(5);
  return 0;
}