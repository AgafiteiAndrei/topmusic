#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

extern int errno;

int port;

int main (int argc, char *argv[])
{
int sd;			// descriptorul de socket
struct sockaddr_in server;	// structura folosita pentru conectare 
char msg[1000];		// mesajul trimis
if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }
port = atoi (argv[2]);
if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }
server.sin_family = AF_INET;
server.sin_addr.s_addr = inet_addr(argv[1]);
server.sin_port = htons (port);
if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }

if(fork())
{
	while(1)
	{
  		bzero (msg, 1000);
    		fflush (stdout);
  		//read (0, msg, 100);
		scanf("%[^\n]%*c",msg);
	  if (write (sd, msg, 1000) <= 0)
    		{
      		perror ("[client]Eroare la write() spre server.\n");
      		return errno;
    		}
if(strstr(msg,"/quit")!=NULL)
exit(1);
	}

}
else
{
	while(1)
	{
		bzero(msg,1000); 

		if (read (sd, msg, 1000) < 0)
    		{
      		perror ("[client]Eroare la read() de la server.\n");
      		return errno;
    		}
if(strstr(msg,"/quit")!=NULL)
exit(1);
printf("%s\n", msg);


	}
}
// close (sd);
}
