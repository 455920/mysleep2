#include<signal.h>
#include<iostream>
#include<unistd.h>
using namespace std;


void handler(int sig)
{
  //do nothing
}

void mysleep(unsigned time)
{
  struct sigaction newsig,oldsig;
  newsig.sa_handler=handler;
  sigemptyset(&newsig.sa_mask);
  sigaddset(&newsig.sa_mask,14);
  sigaction(SIGALRM,&newsig,&oldsig);
  alarm(time);
  newsig=oldsig;
  newsig.sa_handler=handler;
  //sigemptyset(&newsig.sa_mask);
  sigsuspend(&newsig.sa_mask);
 // sigaction(SIGALRM,&oldsig,NULL);
}

int main()
{
 

  while(1)
  {
    cout<<"sleep"<<endl;
    mysleep(1);
  }


  return 0;
}
