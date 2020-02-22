// wait.c file

extern PROC *running;
extern PROC *sleepList;

int kexit() // SIMPLE kexit() for process to terminate
{
  printf("proc %d exit\n", running->pid);
  running->status = ZOMBIE;
  kwakeup(running->parent->pid);
  recurKill(running->child);
  tswitch();
}

//recursivly goes through children and sets to ZOMBIE and removes from readyQUEUE
int recurKill(PROC *kid)
{
  PROC *t;
  while (kid->pid != -1)
  {

    recurKill(kid->child);
    t = dequeue(&readyQueue);
    while (t->pid != kid->pid)
    {
      enqueue(&readyQueue, t);
      t = dequeue(&readyQueue);
    }
    kid->status = ZOMBIE;
    kid = kid->sibling;
  }
}

int ksleep(int event)
{
  PROC *p;
  int sr = int_off();
  running->event = event;  // record event in PROC.event
  running->status = SLEEP; // change status to SLEEP
  enqueue(&sleepList, running);
  tswitch(); // give up CPU
  int_on(sr);
}

int kwakeup(int event)
{
  // implement this

  int i;
  PROC *p, *tproc;

  int sr = int_off();

  // printf("event=%d\n",event);

  for (i = 1; i < NPROC; i++)
  {
    // not applicable to P0
    p = &proc[i];
    if (p->status == SLEEP && p->event == event)
    {
      // printf("p->event==%x\n",p->status);

      p->event = 0;
      // cancel PROC’s event
      p->status = READY; // make it ready to run again

      tproc = dequeue(&sleepList);
      while (tproc->pid != p->pid)
      {
        enqueue(&sleepList, tproc);
        tproc = dequeue(&sleepList);
      }
      enqueue(&readyQueue, p);
    }
  }

  int_on(sr);
}
