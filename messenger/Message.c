/******** message.c file ************/

#define NMBUF 10
struct semaphore nmbuf, mlock;
MBUF mbuf[NMBUF], *mbufList; // mbufs buffers and mbufList

int P(struct semaphore *s)
{
    int sr = int_off();
    s->value--;
    if (s->value < 0)
    {
        
        running->status = BLOCK;
        enqueue(&s->queue, running);
      
        tswitch();
    }
    int_on(sr);
}

int V(struct semaphore *s)
{
    PROC *p;
    int sr = int_off();
    s->value++;
    if (s->value <= 0)
    {
        p = dequeue(&s->queue);
        p->status = READY;
        enqueue(&readyQueue, p);
    }
    int_on(sr);
}
int menqueue(MBUF **queue, MBUF *p)
{
    MBUF *q = *queue;
    if (q == 0 || p->priority > q->priority)
    {
        *queue = p;
        p->next = q;
        return;
    }
    while (q->next && p->priority <= q->next->priority)
    {
        q = q->next;
    }
    p->next = q->next;
    q->next = p;
}
MBUF *mdequeue(MBUF **queue)
{
    MBUF *p = *queue;
    if (p)
        *queue = p->next;
    return p;
}
int msg_init()
{
    int i;
    MBUF *mp;
    printf("mesg_init()\n");
    mbufList = 0;
    for (i = 0; i < NMBUF; i++)
        // initialize mbufList
        menqueue(&mbufList, &mbuf[i]); // all priority=0, so use menqueue()
    nmbuf.value = NMBUF;
    nmbuf.queue = 0; // counting semaphore
    mlock.value = 1;
    mlock.queue = 0; // lock semaphore
}
MBUF *get_mbuf()
// allocate a mbuf
{
    P(&nmbuf);
    P(&mlock);
    MBUF *mp = mdequeue(&mbufList);
    V(&mlock);
}
int put_mbuf(MBUF *mp) // release a mbuf
{
    P(&mlock);
    menqueue(&mbufList, mp);
    V(&mlock);
    V(&nmbuf);
}
int send(char *msg, int pid) // send msg to partet pid
{
    if (pid < 0)
        // validate receiving pid
        return -1;
    printf("step1\n");
    PROC *p = &proc[pid];
    MBUF *mp = get_mbuf();
    mp->pid = running->pid;
    mp->priority = 1;
    printf("step2\n");

    strcpy(mp->contents, msg);
    P(&p->mQlock);
    printf("step3\n");
    printf("mqlock:val:%d\n",p->mQlock.value);

    menqueue(&p->mQueue, mp);
    printf("step4\n");

    V(&p->mQlock);
    V(&p->nmsg);
    printf("step5\n");

    return 0;
}
int recv(char *msg)
{
    printf("rec step1\n");

    P(&running->nmsg);
    printf("rec step2\n");

    P(&running->mQlock);
    printf("rec step3\n");

    MBUF *mp = mdequeue(&running->mQueue);
    
    printf("rec step4\n");

    strcpy(msg, mp->contents);
    int sender = mp->pid;

    printf("rec step5\n");
    return sender;
}