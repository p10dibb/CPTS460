


#include "ucode.c"

char buffer[1024];

int main(int argc, char * argv[])
{
    printf("\n---------------------\n");
    printf("Pauls CAT\n");
    printf("----------------------\n");
    int fd=0;
    //checks if thier is an input file
	if(argc > 1)
	{
        
        //opens new file
		fd=open(argv[1], O_RDONLY);
        // printf("fd=%d argv[1]=%s\n",fd,argv[1]);
	}
    // int i=0;
    
    //reads untill end of file and displays
	while(read(fd, buffer, 1024))
	{
		printf("%s",buffer);
       // i++;
	}
   // printf("\n%d\n",i);
	
	return 0;
}
