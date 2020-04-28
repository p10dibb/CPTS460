


#include "ucode.c"


int main(int argc, char * argv[])
{
char buf[MAX] ,str[500];
    // printf("\n---------------------\n");
    // printf("Pauls CAT\n");
    // printf("----------------------\n");
    int fd=0;
    //checks if thier is an input file
	if(argc > 1)
	{        
        //opens new file
        close(0);
		fd=open(argv[1], O_RDONLY);
          //reads untill end of file and displays
	while(read(fd, buf, MAX))
	{
		printf("%s",buf);
	}
	}else{

        while(strcmp("exit",str)!=0){
    gets(str);
    printf("%s\n",str);
        }

    
    }
    
  

	
	return 0;
}
