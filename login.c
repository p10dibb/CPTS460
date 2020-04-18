#include "ucode.c"

char * items[7];
char username[100], password[100];


//parses the file lines at the :
void parseItems(char *s){
    int i=0, exiter=0;
    char *t="";
    while(i!=7&& ! exiter)
    {
        items[i] = s;
        while(  *s != '\0' &&*s != ':')
		{			
            ++s;
		}
        if(*s=='\0'){
            exiter=1;
        }
        *s = '\0';
        s++;
        i++;
    }
}


//main for login
int main(int argc, char * argv[])
{
   
    close(0); 
    close(1); 


    //gets the stdin
    int stdin = open(argv[1], O_RDONLY);
    
    fixtty(argv[1]);
    while(1)
    {

        //gets user input
        printf("My Login: "); 
        gets(username);
        printf("My Password: "); 
        gets(password);

        
        int stdinDup = dup(stdin);
        //closes stdin
        close(0);
    
        //opens the file with all the passwords
        open("/etc/passwd", O_RDONLY);

        char line[256];
        
        //reads all lines or reads till correct match
        while(getline(line))
        {
            //splits line at : 
            printf("%s\n",line);
            parseItems(line);

            //item[0]=username [1]= password [2]= gid ?   [3]=user id [4]: other name? [5]:directory  [6]: path?
            if(strcmp(items[0], username) == 0 && strcmp(items[1], password) == 0)
            {
                chuid(atoi(items[3]), atoi(items[2]));
                chdir(items[5]);
                close(0);
                dup2(stdinDup, 0);
                exec("sh");
            }
        }

        close(0);
        dup2(stdinDup, 0);
        close(stdinDup);
    }
}

/*
root : 12345
kcw : abcde
guest : mercy
buster 123
*/
