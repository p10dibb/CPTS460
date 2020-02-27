#include "defines.h"
#include "type.h"

#include "string.c"
#include "uart.c"

#include "kbd.c"


#include "timer.c"
#include "vid.c"

#include "exceptions.c"

int svc_stack_top(){

}

int abt_stack_top(){

}

int und_stack_top(){

}

int irq_stack_top(){

}

int timer0_handler(){

}

int get_cpu_id(){
    
}

// int uart0_handler(){

// }

// int uart_init(){

// }


void copy_vectors(void) {
    printf("in copy vectors\n");
    extern u32 vectors_start;
    extern u32 vectors_end;
    u32 *vectors_src = &vectors_start;
    u32 *vectors_dst = (u32 *)0;

    while(vectors_src < &vectors_end)
       *vectors_dst++ = *vectors_src++;
}
int kprintf(char *fmt, ...);
void IRQ_handler()
{
    // printf("in irq handler\n");
    int vicstatus, sicstatus;
    vicstatus = VIC_STATUS; // VIC_STATUS=0x10140000=status reg
    sicstatus = SIC_STATUS;  
 if (vicstatus & (1 << 4))
    {
        for(int i=0;i<1;i++){
        timer_handler(i);
            
        }
      //   timer_handler(0);
      //   bit4=1:timer0,1
      //   timer0 only
    }
    if (vicstatus & (1 << 31)){
      if (sicstatus & (1 << 3)){
          kbd_handler();
       }
    }
}


int mkptable()
{
    printf("in mkptable\n");

    int i, pentry, *ptable;
    // printf("step1\n");
    printf("1. build level-1 pgtable at 16 KB\n");
    // ptable = (int *)0x4000;
    ptable = (int *)0x4000;

   

    for (i = 0; i < 4096; i++)
    { // zero out the pgtable
        ptable[i] = 0;
    }
    

    printf("2. fill 258 entries of pgtable to ID map 258 MB VA to PA\n");
    pentry = 0x412; // AP = 01,domain = 0000, CB = 00, type = 02 for section
    for (i = 0; i < 258; i++)
    { // 258 level-1 page table entries
  
        ptable[i]  = pentry;
        pentry += 0x100000;
    }
    
    
    printf("3. finished building level-1 page table\n");
    printf("4. return to set TTB, domain and enable MMU\n");
}

int data_chandler() //data abort handler
{
    u32 fault_status, fault_addr, domain, status;
    int spsr = get_spsr();
    printf("data_abort exception in ");
    if ((spsr & 0x1F) == 0x13)
        printf("SVC mode\n");
    fault_status = get_fault_status();
    fault_addr = get_fault_addr();

    domain = (fault_status & 0xF0 >> 4);
    status = fault_status & 0xF;
    printf("status = %x : domain = % x status = %x(0x5 = Trans Invalid)\n ",
           fault_status, domain, status);
    printf("VA addr =%x\n", fault_addr);
}
int dch(){
    printf("here\n");
}

int copy_vector_table()
{   
    printf("in copy vecor table\n");
     extern u32 vectors_start;
    extern u32 vectors_end;
    u32 *vectors_src = &vectors_start;
    u32 *vectors_dst = (u32 *)0;
    while (vectors_src < &vectors_end)
        *vectors_dst++ = *vectors_src++;
}

int irq_chandler() // IRQ interrupts handler
{
    printf("in irq\n");
    // read VIC, SIC status registers to find out which interrupt
    int vicstatus = VIC_STATUS;
    int sicstatus = SIC_STATUS;
    if (vicstatus & (1 << 4))
        timer0_handler();
    if (vicstatus & (1 << 12))
        uart0_handler();
    if (vicstatus & (1 << 31) && sicstatus & (1 << 3))
        kbd_handler();
}

int main()
{
 
 kbd_init();

    int i, *p;
    char line[128];


//    fbuf_init();


   
    uart_init();


    VIC_INTENABLE |= (1 << 4);  // timer0 at 4
    VIC_INTENABLE |= (1 << 12); // UART0 at 12
    VIC_INTENABLE = 1 << 31;
    UART0_IMSC = 1 << 4;
    SIC_ENSET = 1 << 3; // KBD int = 3 on SIC
    SIC_PICENSET = 1 << 3;


    timer_init();

    timer_start(0);

color=WHITE;
    	printf("test MM at VA=2MB\n");
		p = (int *)(2*0x100000); *p = 123;

		
		printf("test MM at VA=127MB\n");
		p = (int *)(127*0x100000); *p = 123;
		
		printf("test MM at VA=257MB\n");
		p = (int *)(257*0x100000); *p = 123;

		printf("test MM at VA=258MB\n");
		p = (int *)(258*0x100000); *p = 123;

		printf("test MM at VA=512MB\n");
		p = (int *)(512*0x100000); *p = 123;
    printf("step5\n");

    while (1)
    {
        printf("main running Input a line: ");
        kgets(line);
        printf(" line=%s\n", line);
    }
}