1. Use sleep/wakeup in KBD driver

   Download samples/LAB4/lab4.tgz
   run   zcat lab4.tgz | tar xvf -  to extract files.

(1). wait.c files contains kexit(), ksleep(), kwakeup().
     Implement ksleep(), kwakeup() as in 5.6.1 of textbook
     ADD two commands: sleep and wakeup to test YOUR ksleep/kwakeup

sleep : ask for a value to sleep on; sleep on that value.
wakeup: ask for a value to wakeup with; wakeup ALL procs sleeping on that value.
			 
(2). The KBD driver kbd.c uses BUSY wait loop in kgetc().
     Use sleep/wakeup in kgetc()/kbd_handler() to synchronize
     process and KBD interrupts.

2. 5.13.2.2 shows a PIPE using sleep/wakeup. However,
   It does not check for BROKEN pipe condition for pipe_writer,
                     and   no-writer condition for pipe_reader.

   Download samples/LAB4/pipe.tgz

   Implement write_pipe() to detect BROKEN pipe condition (if so, kexit)
             read_pipe()  to detect no-writer condition   (if so, return 0).
   
   Testing: 1. Let writer do while(1) loop; reader only read  2 times
            2. Let reader do while(1) loop; writer only write 2 times.

3. Duplicate and RUN the message passing program in 5.13.4.2