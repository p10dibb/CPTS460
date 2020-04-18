#include "ucode.c"

int main(int argc,char argv[]){
    char str[500],temp[100];
    char *commands[20];
    char * split_cmd;
    int i=1,pid,status,child;
    while(1){

        //gets inputs
        printf("Paul's SH :>");
        gets(str);

        //if no input then continue
        if(strlen(str)==0){
            continue;
        }

        //parses the commands
        commands[0]=strtok(str,'|');
        while(1){
            commands[i]=strtok(NULL,'|');

            if(commands[i]==NULL){
                break;
            }
            i++;
        }

        i=0;
        //runs the commands
        while(commands[i]!=NULL){
            
            strcpy(temp,commands[0]);
            
            split_cmd=strtok(temp,' ');
            //checks for change cd
            if(strcmp(split_cmd,"cd")==0){
                //gets the new directories
                split_cmd=strtok(NULL,' ');
                chdir(split_cmd);
            }
            //else if other cmd
            else{
            //forks new child and waits till done
             pid=fork();
             if(pid){
                while(child!=pid){
                    child=wait(&status);
                }
             }
             else{
                //helper function so main isnt so long
                runCommands(commands);

             }
            }

            i++;
        }

    }
}

void runCommands(char **commands){
    char * first = *commands;
	redirecter(first);
	char ** rest = commands + 1;
    //if only 1 command
	if(*rest == NULL)
	{
		exec(first);
		exit(0);
	}
	else
	{
		int pid, pd[2];
		pipe(pd);
		pid = fork();
        //recursivly goes through
		if (pid)
		{
			close(pd[1]);
			dup2(pd[0], 0);
            
			runCommands(rest);
		}
		else
		{
			close(pd[0]);
			dup2(pd[1], 1);
			exec(first);
		}
	}
}


void redirecter(char * command)
{
    char * fname;
	int len = strlen(command);
	for(int i = 0; i < len; i++)
	{

        //opend the files in correc way based on the command
		if(command[i] == '>')
		{
			if(i < len - 1 && command[i + 1] == '>')
			{
				command[i] = command[i + 1] = '\0';
				fname = command + i + 2;
				close(1);
				open(strtok(fname, ' '), O_WRONLY|O_APPEND);
			}
			else
			{
				command[i] = '\0';
				fname = command + i + 1;
				close(1);
				open(strtok(fname, ' '), O_WRONLY|O_CREAT);
			}
		}
		else if(command[i] == '<')
		{
			command[i] = '\0';
			fname = command + i + 1;
			close(0);
			open(strtok(fname, ' '), O_RDONLY);
		}
	}

}