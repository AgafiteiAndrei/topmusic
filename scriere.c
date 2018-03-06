#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PORT 2004
extern int errno;



void scriere(char * nume)
{
char fisier[20];
if(strcmp(nume,"rock")==0) strcpy(fisier,"rock.txt");
int file;
file=open(fisier,O_APPEND|O_WRONLY);
write(file,"SUCCES",10);
}



int main()
{
char c[20];
scanf("%[^\n]%*c",c);
scriere(c);

}
