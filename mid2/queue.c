/********************************************************************
Copyright 2010-2017 K.C. Wang, <kwang@eecs.wsu.edu>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

// queue.c file
//extern PROC *freeList;
int enqueue(PROC **queue, PROC *p)
{
  PROC *q  = *queue;
  if (q==0 || p->priority > q->priority){
    *queue = p;
    p->next = q;
    return;
  }
  while (q->next && p->priority <= q->next->priority){
    q = q->next;
  }
  p->next = q->next;
  q->next = p;
}

PROC *dequeue(PROC **queue)
{
  PROC *p = *queue;
  if (p)
    *queue = p->next;
  return p;
}

int tenqueue(TIMERSET **queue, TIMERSET *p)
{
  TIMERSET *q  = *queue;
  if(*queue==0){
    printf("GOGOGO: %d\n",*queue);
    *queue=p;

  }
  
  // if (q==0 ){
  //   *queue = p;
  //   p->next = q;
  //   return 0;
  // }
  // while (q->next ){
  //   q = q->next;
  // }
  // p->next = q->next;
  // q->next = p;
}

TIMERSET *tdequeue(TIMERSET **queue)
{
  PROC *p = *queue;
  if (p)
    *queue = p->next;
  return p;
}

int printList(char *name, PROC *p)
{
  printf("%s=", name);
  while(p){
    printf("[%d%d]->", p->pid, p->priority);
    p = p->next;
  }
  printf("NULL\n");
}

int printsleepList(PROC *p)
{
  printf("sleepList=");
  while(p){
    printf("[%d event=%d timer=%d]->", p->pid, p->event,p->count);
    p = p->next;
  }
  printf("NULL\n");
}

int printTimerList(TIMERSET *p)
{
  printf("timerList=");
  while(p){
    printf("[%d time=%d]->", p->pid, p->count);
    p = p->next;
  }
  printf("NULL\n");
}
