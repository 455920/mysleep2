#include<signal.h>
#include<iostream>
#include<unistd.h>
using namespace std;


void handler(int sig)
{
  //do nothing
}

int  mysleep(unsigned time)
{
  struct sigaction newact,oldact;
  sigset_t suspmask,newmask,oldmask;
  unsigned int unslept;

  newact.sa_handler=handler;

  
  //处理信号的时候要屏蔽该信号，因为处理信号本来就是一个系统调用，而系统调用结束的时候就会检查有没有信号抵达，这样在处理某个信号的时候，如果该信号再次抵达，就可能会出现又去处理信号的情况
  sigemptyset(&newact.sa_mask);
//
//flag当信号处理函数正在进行时，不阻塞对于信号处理函数自身信号功能
  newact.sa_flags=0;//?

  //sa_mask字段说明了一个信号集，在调用该信号捕捉函数之前，这一信号集要加进进程的信号屏蔽字中。仅当从信号捕捉函数返回时再将进程的信号屏蔽字复位为原先值。
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGALRM);
  sigprocmask(SIG_BLOCK,&newmask,&oldmask);//先阻塞
  sigaction(SIGALRM,&newact,&oldact);//改行为
  
  alarm(time);//放闹钟
  
  suspmask = oldmask;
  sigdelset(&suspmask,SIGALRM);

  sigsuspend(&suspmask);//原子操作，解除屏蔽，然后挂起，等待捕获
  //如果解除屏蔽和挂起不是原子操作，就可能在因为切换了进程导致再没有pause的时候信号就已经被处理了，那么pause永远是挂起
  unslept=alarm(0);

  //信号的东西回到原来的模样
 sigaction(SIGALRM,&oldact,NULL);
  

 //屏蔽字回到初始模样
 sigprocmask(SIG_SETMASK,&oldmask,NULL);

 return (unslept);

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
