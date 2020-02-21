// wait.c file

extern PROC *running;
extern PROC *sleepList;

int kexit() // SIMPLE kexit() for process to terminate
{
  printf("proc %d exit\n", running->pid);
  running->status = ZOMBIE;
  tswitch();
}

int ksleep(int event)
{
  PROC *p;
  running->event = running;  // record event in PROC.event
  running->status = SLEEP; // change status to SLEEP
  enqueue(&sleepList, running);
  tswitch(); // give up CPU
}

int kwakeup(int event)
{
  // implement this

  int i;
  PROC *p ,*tproc;
  
  printf("pid=%d\n",event);

  for (i = 1; i < NPROC; i++)
  {
    // not applicable to P0
    p = &proc[i];
    if (p->status == SLEEP && p->pid == event)
    {
    printf("p->pid==%d\n",p->pid);
    

      p->event = 0;
      // cancel PROC’s event
      p->status = READY; // make it ready to run again

      tproc=dequeue(&sleepList);
      while(tproc->pid!=p->pid){
        enqueue(&sleepList,tproc);
        tproc=dequeue(&sleepList);
      }
      enqueue(&readyQueue, p);
    }
  }

}
