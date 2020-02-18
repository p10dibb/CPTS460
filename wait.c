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
  // implement this
  running->event = event;  // record event in PROC.event
  running->status = SLEEP; // change status to SLEEP
  enqueue(&sleepList, running);
  tswitch(); // give up CPU


}

int kwakeup(int event)
{
  // implement this

  int i;
  PROC *p ,*tproc;
  
  printf("event=%d\n",event);

  for (i = 1; i < NPROC; i++)
  {
    // not applicable to P0
    p = &proc[i];
    if (p->status == SLEEP && p->pid == event)
    {
    printf("p->event==%x\n",p->status);

      p->event = 0;
      // cancel PROC’s event
      p->status = READY; // make it ready to run again

      tproc=dequeue(&sleepList);
      while(tproc->pid!=event){
        enqueue(&sleepList,tproc);
        tproc=dequeue(&sleepList);
      }
      enqueue(&readyQueue, tproc);
    }
  }

}
