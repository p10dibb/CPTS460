#include "ucode.c"


int main(int argc, char * argv[])
{
    char buf[1024],input;
	int displayAmt=30, i=0;
    
	int stdin = open("/dev/tty0", O_RDONLY);

    //checks if has input file
	if(argc > 1)
	{
		close(0);
		open(argv[1], O_RDONLY);
	}

    //defaults to 30 lines. i believe its supposed to be 10% but im not for sure
    //goes till buf is all read
	while(getline(buf))
	{
		for(i = 0; i < displayAmt; i++)
		{
			printf("%s",buf);
            //if ends before 30 then exit to prevent crash
			if(getline(buf)==0){
				return;

            }
		}
        //gets a users input
		while(1)
		{
			read(stdin, &input, 1);
            //if input is space then show 30 more lines
			if(input == ' ')
			{
				displayAmt = 30;
				break;
			}
            //else show just next line
			else
			{
				displayAmt = 1;
				break;
			}
		}
	}	
}
