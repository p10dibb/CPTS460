// kernel.c file

#define NPROC 9
PROC proc[NPROC], *running, *freeList, *readyQueue;
PROC *sleepList;
int procsize = sizeof(PROC);
int body();

int init()
{
  int i, j; 
  PROC *p;
  kprintf("kernel_init()\n");
  for (i=0; i<NPROC; i++){
    p = &proc[i];
    p->pid = i;
    p->status = READY;
    p->next = p + 1;
    p->child->pid=-1;
    p->sibling->pid=-1;
  }
  proc[NPROC-1].next = 0; // circular proc list

  freeList = &proc[0];
  readyQueue = 0;
  sleepList = 0;
  
  p = dequeue(&freeList);
  p->priority = 0;
  p->ppid = 0;
  running = p;

  kprintf("running = %d\n", running->pid);
  printList("freeList", freeList);
}

int addChild(PROC* parent, PROC *newKid){
  newKid->parent=parent;
  newKid->sibling=parent->child;
  parent->child=newKid;
  return;

}
  
int kfork(int func, int priority)
{
  int i;
  PROC *p = dequeue(&freeList);

  printf("func: %d\n",func);
  if (p==0){
    printf("no more PROC, kfork failed\n");
    return 0;
  }
  p->status = READY;
  p->priority = priority;
  p->ppid = running->pid;
  p->parent = running;
  addChild(running,p);


  
  // set kstack for new proc to resume to func()
  // stack = r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r14
  //         1  2  3  4  5  6  7  8  9  10 11  12  13  14
  for (i=1; i<15; i++)
      p->kstack[SSIZE-i] = 0;
  p->kstack[SSIZE-1] = (int)func;  // in dec reg=address ORDER !!!
  p->ksp = &(p->kstack[SSIZE-14]);
  enqueue(&readyQueue, p);

  printf("proc %d kforked a child %d\n", running->pid, p->pid);
  printList("readyQueue", readyQueue);
  return p->pid;
}

int scheduler()
{
  //  kprintf("proc %d in scheduler ", running->pid);
  if (running->status == READY)
     enqueue(&readyQueue, running);
  running = dequeue(&readyQueue);
  //kprintf("next running = %d\n", running->pid);
  if (running->pid){
    color = running->pid;
  }
}  

int showKids(PROC* parent){
  PROC * temp=parent->child;
      printf("children are:",running->pid);
      while (temp->pid!=-1)
      {
        printf(" [%d,",temp->pid);
        
        switch (temp->status)
        {
        case 0: printf("Free]");  break;
        case 1: printf("Ready]");  break;
        case 2: printf("Sleep]");  break;
        case 3: printf("Block]");  break;
        case 4: printf("Zombie]");  break;
        
        default:
          break;
        }
        
        printf("");
        temp=temp->sibling;
      }
}

int body()
{
  char c, cmd[64];

  kprintf("proc %d resume to body()\n", running->pid);
  while(1){
    printf(" proc %d running ppid: %d ,", running->pid,running->parent->pid);
    showKids(running);
    printf("-----------\n");
    printList("freeList  ", freeList);
    printList("readyQueue", readyQueue);
    printsleepList(sleepList);
	
    printf("Enter a command [switch|fork|exit|children|wait] : ",
	   running->pid);
    kgets(cmd);

    if (strcmp(cmd, "switch")==0)
       tswitch();
    else if (strcmp(cmd, "fork")==0)
       kfork((int)body, 1);
    else if (strcmp(cmd, "exit")==0){
      if(running->pid==1){
        printf("cant exit on first proc\n");
      }else{
        printf("which would you like to kill: ");
       kexit(geti());
        
      }
    }
   
    else if(strcmp(cmd,"children")==0){
      showKids(running);
      
    
    }

    // else if(strcmp(cmd,"wakeup")==0){
    //   printf("what value to wakeup on?:\n");
    //   kwakeup(geti());
    //   // kwakeup(running);
    // }
    else if(strcmp(cmd,"wait")==0){
     kwait(0);
    }
    else{
      printf("\n\ninvalid command\n\n");
    }
    printf("\n");
  }
}
