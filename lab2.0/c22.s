    .text
    .global start
start: ldr sp, =stack_top   !//set stack pointer
    b1 sum                  !//call sum
stop: b stop                !//looping

sum:                        !//int sum()         
    mov r0, #0              !r0 = 0
    ldr r1, =Array          !r1 = &Array
    ldr r2, =N              !r2 = &N
    ldr r2, [r2]            !r2 = N
loop: ldr r3, [r1], #4      !r3 = *(r1++)
    add r0, r0, r3          !r0 += r3
    sub r2, r2, #1          !r2--    
    cmp r2, #0              !if (r2 !=0)
    bne loop                !   goto loop;
    ldr r4,  =Result        ! r4 = &Result
    str r0, [r4]            ! Result = r0