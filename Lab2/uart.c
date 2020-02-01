/********************************************************************
Copyright 2010-2017 K.C. Wang, <kwang@eecs.wsu.edu>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/
#define DR   0x00
#define FR   0x18

#define RXFE 0x10
#define TXFF 0x20

typedef struct uart{
  char *base;
  int n;
}UART;

UART uart[4];
int BASE=10;
int uart_init()
{
  int i; UART *up;

  for (i=0; i<4; i++){
    up = &uart[i];
    up->base = (char *)(0x101F1000 + i*0x1000);
    up->n = i;
  }
  uart[3].base = (char *)(0x10009000); // uart3 at 0x10009000
}

int ugetc(UART *up)
{
  while (*(up->base + FR) & RXFE);
  return *(up->base + DR);
}

int uputc(UART *up, char c)
{int uprints(UART *up, char *s)
{
  while(*s)
    uputc(up, *s++);
}

/** WRITE YOUR uprintf(UART *up, char *fmt, . . .) for formatted print **/
  while(*(up->base + FR) & TXFF);
  *(up->base + DR) = c;
}

int ugets(UART *up, char *s)
{
  while ((*s = (char)ugetc(up)) != '\r'){
    uputc(up, *s);
    s++;
  }
 *s = 0;
}

int uprints(UART *up, char *s)
{
  while(*s)
    uputc(up, *s++);
}

//recursive int to char conversion and output
int rpu(UART *up, u32 x)
{  
    char c;
    if (x){
      if(BASE==10){
        c = ctable[x % 10];
       rpu(up,x / 10);
       uputc( up,c);
      }else if(BASE==12){
    c = ctable[x % 12];
       rpu(up,x / 12);
       uputc( up,c);
      }else if(BASE==8){
          c = ctable[x % 8];
       rpu(up,x / 8);
       uputc( up,c);
      }
     
    }
}

//prints unsigned int
int printu(UART *up, u32 x)
{
    BASE=10;
   (x==0)? uputc( up,'0') : rpu(up,x);
   uputc( up,' ');
}

//prints decimal (base 10)
 int  printd(UART *up, int x){
     BASE=10;
    if (x<0){
        uputc( up,'-');
        x= -x;
    }
    rpu(up,x);

 }

//prints base 16
 int  printx(UART *up, u32 x){
     BASE=16;
     uputc( up,'0');
     uputc( up,'x');
     if (x<0){
        uputc( up,'-');
        x= -x;
    }
    rpu(up,x);
 }

//prints base 8
 int  printo(UART *up, u32 x){
     BASE =8;
        uputc( up,'0');
         if (x<0){
        uputc( up,'-');
        x= -x;
                }   
    rpu(up, x);
 }

//prints string
 int prints(UART *up, char* x){
     int i=0;
     while(x[i]!='\0'){
        
         uputc( up,x[i]);
         i++;
     }
 }



int myprintf(UART *up,char *fmt, ...){
      int *ip =&fmt;    
    int i=0;
    char *cp;
    

    cp=fmt;



    while (*(cp+i)!='\0'){
    

    if (*(cp+i)=='\n'){
        uputc( up,'\r\n');
    }
    else if(*(cp+i)!='%'){
        uputc( up,*(cp+i));
     }
     else{
         i++;
         if(*(cp+i)=='d'){
             ip=ip+1;
            
            
            (*ip==0)? uputc( up,'0') :  printd(up,*ip);

      }
      else if(*(cp+i)=='x'){
            ip=ip+1;
            (*ip==0)? uputc( up,'0') : printx(up,*ip);
            
        }else if(*(cp+i)=='c'){
             ip=ip+1;
             uputc( up,*ip);
            
        }else if(*(cp+i)=='o'){
            ip=ip+1;
            
           (*ip==0)? uputc( up,'0') :  printo(up,*ip);
        }
        else if(*(cp+i)=='u'){
              ip=ip+1;
            printu(up,*ip);
        }
        else if(*(cp+i)=='s'){
             ip=ip+1;

      
               prints(up,*ip);
        }
     }
     i++;
    }

}

