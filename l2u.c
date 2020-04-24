#include "ucode.c"

//checks for lowercase
int isLowerCase(char c){
    if(c>='a'&& c<='z'){
        return 1;
    }
    return 0;
}

//checks if lowercase then returns uppercase else returns character
char toUppercase(char c){
    if(isLowerCase(c)){
        return c-32;
    }
    return c;
}

int main(int argc, char * argv[])
{
    
char buf[MAX],tempbuf[MAX];
int i=0;

int infile;
int outfile ;
printf("------------------\n");
printf("Paul's l2u\n");
printf("----------------\n");
if(argc<2){
        printf("Usage: l2u [file1] [file2]\n");
    return;
}
if (argc==3){

//frees up 0 position for reading
close(0);
infile=open(argv[1],O_RDONLY);
//frees up 1 position for wrighting with printf
close(1);
outfile = open(argv[2],O_WRONLY|O_CREAT );
    

}

while(read(infile,buf,1024)){
    i=0;
    while (i<1024 && buf[i]!='\0'){

       tempbuf[i]= toUppercase(buf[i]);
       i++;
    }

    printf("%s",tempbuf);
}
return;


}