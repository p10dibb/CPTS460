#include "ucode.c"
#define printk printf

int console;

int main(int argc, char *argv[ ])
{
  int in, out;
  int pid, status;
  
  in  = open("/dev/tty0", O_RDONLY);
  out = open("/dev/tty0", O_WRONLY);

  pid = getpid();

  printf("Paul's INIT %d: fork a login proc on console\n", pid);

  console = fork();
  if (console){ // parent
    while(1){
      pid = wait(&status);
      if (pid == console){ // login child died
	printf("Paul's INIT fork another login on console\n");
	console = fork();
	if (console){
	  continue;
	}
	else{   // child
	  exec("login /dev/tty0");
	  // exec("login /dev/ttyS0");
	  // exec("login /dev/ttyS1");


	}

      }
      printf("Paul's INIT removed orphan proc %d\n", pid);	
    }
  }
}


