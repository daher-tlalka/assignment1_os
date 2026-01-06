#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  char msg[32];
  argint(0, &n);
  argstr(1,msg,32);
  exit(n,msg);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  uint64 p1;
  argaddr(0, &p);
  argaddr(1, &p1);
  return wait(p,p1);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
uint64 
sys_memsize(void){
  return myproc()->sz;
}

//task5
//think to use argint to get the integer that u need
uint64
sys_set_ps_priority(void){
  //not shor
  int priority;
  argint(0, &priority);
    // return -1;
  if(priority<1||priority>10)
    return -1;
  myproc()->ps_priority=priority;
  return 0;
}

//task6
uint64
sys_set_cfs_priority(void){
  struct proc *p=myproc();
  int priority;
  argint(0,&priority);
  if(priority<0 || priority>2)
    return -1;
  acquire(&p->lock);
  if(priority==0){
    p->cfs_priority=0;
  }
  else if(priority==1){
    p->cfs_priority=1;
  }
  else { 
    p->cfs_priority=2;
  }
  release(&p->lock);
  return 0;
}
uint64
sys_get_cfs_stats(void){
  int id;
  uint64 cfsPriority;
  uint64 rtime;
  uint64 stime;
  uint64 rutime;
  argint(0,&id);
  argaddr(1,&cfsPriority);
  argaddr(2,&rtime);
  argaddr(3,&stime);
  argaddr(4,&rutime);
  int res=getProcess(id,&cfsPriority,&rtime,&stime,&rutime);
  if(res==-1) return res;
  return 0;
}
//task7
uint64
sys_set_policy(void){
  int policy;
  argint(0,&policy);
  if(policy<0||policy>2)
    return -1;
  setScher(policy);
  return 0;
}
