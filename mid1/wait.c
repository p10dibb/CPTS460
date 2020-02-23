// wait.c file

extern PROC *running;
extern PROC *sleepList;

int kexit(int exitCode) // SIMPLE kexit() for process to terminate
{

  
  printf("proc %d exit\n", running->pid);
  running->status = ZOMBIE;
  kwakeup(running->parent->pid);
  // recurKill(running->child);
  PROC *t=running->child;
  PROC *tnext=running->child;

    while (t->pid != -1)
  {
    tnext=t->sibling;
    addChild(running->parent,t);
   t = tnext;
  }

  tswitch();
  

}

int kwait(int exitCode){

  PROC * temp=running->child,*pre;
  if(temp->pid==-1){
    return -1;
  }
  pre=temp;
  while(temp->pid!=-1){
    if(temp->status==ZOMBIE){
      printf("pid:%d\n",temp->pid);
      //first 1
      if(pre->pid==temp->pid){
        running->child=temp->sibling;
      }else
      {
        pre->sibling=temp->sibling;
      }
      
      temp->sibling=0;
      temp->parent=0;
      temp->child=0;
      temp->priority=0;

      enqueue(&freeList,temp);
      return(temp->pid);
    }
    pre=temp;
    temp=temp->sibling;
  }

}

//recursivly goes through children and sets to ZOMBIE and removes from readyQUEUE
int recurKill(PROC *kid)
{
  PROC *t;
  while (kid->pid != -1)
  {
    
    // recurKill(kid->child);
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
