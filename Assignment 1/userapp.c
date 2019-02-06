#include <stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include<string.h>

#define acc_x "/dev/acc_x"
#define acc_y "/dev/acc_y"
#define acc_z "/dev/acc_z"
int s;
char* str;
char c;

int main()

{
  int fd,n;
  uint16_t val;

  printf("PRESS    x : X-AXIS ACCELERATION \n\t y : Y-AXIS ACCELERATION \n\t z : Z-AXIS ACCELERATION : \n");
  scanf("%c",&c);

 switch(c){
  
 case 'x':  fd=open(acc_x, O_RDWR);
 
  if(fd  == -1)
  {
 
    printf("PLEASE GIVE 777 PERMISSION FOR FILE %s \n",acc_x);
    exit(-1);
  }
 
  read(fd,&val,2);


  printf("ACCELERATION IN X-AXIS : %d\n",val);
break;
  
 
 case 'y': fd=open(acc_y , O_RDWR);
 
  if(fd  == -1)
  {
 
    printf("PLEASE GIVE 777 PERMISSION FOR FILE  %s \n",acc_y);
    exit(-1);
  }
 
  read(fd,&val,2);
  printf("ACCELERATION IN Y-AXIS: %d\n",val);
break;

case 'z':  
 
  fd=open(acc_z, O_RDWR);
 
  if(fd  == -1)
  {
 
    printf("PLEASE GIVE 777 PERMISSION FOR FILE  %s ",acc_z);
    exit(-1);
  }
 
  read(fd,&val,2);

  printf("ACCELERATION IN Z-AXIS : %d\n",val);
break;



default: printf("\nCOMMAND NOT RECOGNISED\n");
       break;
}


  close(fd);
 
 
  return 0;
}



