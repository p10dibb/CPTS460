#include "type.h"
#include "string.c"
#include "queue.c"
#include "vid.c"
#include "kbd.c"
#include "exceptions.c"
#include "kernel.c"
#include "wait.c"
#include "uart.c"
#include "Message.c"

void copy_vectors(void)
{
    extern u32 vectors_start;
    extern u32 vectors_end;
    u32 *vectors_src = &vectors_start;
    u32 *vectors_dst = (u32 *)0;

    while (vectors_src < &vectors_end)
        *vectors_dst++ = *vectors_src++;
}

void IRQ_handler()
{
    int vicstatus, sicstatus;
    vicstatus = VIC_STATUS; // VIC_STATUS=0x10140000=status reg
    sicstatus = SIC_STATUS;

    if (vicstatus & (1 << 31))
    {
        if (sicstatus & (1 << 3))
        {
            kbd_handler();
        }
    }
}

int sender() // send task code
{
    struct uart *up = &uart[0];
    char line[128];
    while (1)
    {

        uprintf("send mesege:\n");
        ugets(up, line);
        printf("task%d got a line=%s\n", running->pid, line);
        send(line, 2);
        printf("task%d send %s to pid=4\n", running->pid, line);
        tswitch();
    }
}
int receiver() // receiver task code
{
    char line[128];
    int pid;
    while (1)
    {

        printf("task%d try to receive msg\n", running->pid);
        pid = recv(line);
        printf("task%d received: [%s] from task%d\n",
               running->pid, line, pid);
    }
}
int main()
{

    int i;
    char line[128];
    //   u8 kbdstatus, key, scode;

    color = WHITE;
    row = col = 0;
    fbuf_init();
    kbd_init();
    uart_init();

    // allow KBD interrupts
    VIC_INTENABLE |= (1 << 31); // allow VIC IRQ31

    // enable KBD IRQ
    SIC_ENSET = 1 << 3;    // KBD int=3 on SIC
    SIC_PICENSET = 1 << 3; // KBD int=3 on SIC

    init();

    msg_init();
    printf("P0 kfork tasks\n");
    kfork((int)sender, 1); // sender process

    kfork((int)receiver, 1); // receiver process



    while (1)
    {
        printList("readyQueue", readyQueue);

        if (readyQueue)
            uprintf("switching\n");
        tswitch();

        printf("fail\n");
        break;
    }
}