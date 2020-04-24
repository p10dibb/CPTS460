#include "ucode.c"


int main(int argc, char * argv[])
{
    
char buf[MAX],tempbuf[MAX];
int i=0;

int infile;
int outfile ;
printf("------------------\n");
printf("Paul's cp\n");
printf("----------------\n");
if(argc<2){
        printf("Usage: cp [file1] [file2]\n");
    return;
}
if (argc==3){

close(0);
infile=open(argv[1],O_RDONLY);
close(1);
outfile = open(argv[2],O_WRONLY|O_CREAT );
    

}

while(read(infile,buf,1024)){
  

    printf("%s",buf);
}
return;


}