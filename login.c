/* servTCPIt.c - Exemplu de server TCP iterativ
   Asteapta un nume de la clienti; intoarce clientului sirul
   "Hello nume".
   
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/

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


int separare_ins(char * comanda,char * nume, char * top, char * melodie,char * link)
{
int i=0,j=0,l=0,k=0,it,ok=0,spatiu=0,bloc;
for(it=0;(it<strlen(comanda) && spatiu==0);it++)
{
        if(comanda[it]==' ') {spatiu=1;bloc=it;}
        else if(comanda[it]!=' ') {nume[i]=comanda[it];i++;}
}

spatiu=0;
for(it=bloc+1;(it<strlen(comanda) && spatiu==0);it++)
{
        if(comanda[it]==' ') {spatiu=1;bloc=it;}
        else if(comanda[it]!=' ') {top[j]=comanda[it];j++;}
}
spatiu=0;
for(it=bloc+1;(it<strlen(comanda) && spatiu==0) ;it++)
{
        if(comanda[it]==' ' ) {spatiu=1;bloc=it;}
       else if(comanda[it]!=' ') {melodie[k]=comanda[it];k++;}

}

for(it=bloc+1;it<strlen(comanda);it++) 
{
link[l]=comanda[it];l++;
}


nume[i]='\0';
top[j]='\0';
melodie[k]='\0';
link[l]='\0';
if(nume[0]=='\0') return -1;
else if(top[0]=='\0') return -2;
else if(melodie[0]=='\0') return -3;
else if(link[0]=='\0') return -4;
}


int main()
{
char comanda[100],nume[10],top[10],melodie[100],link[100];
scanf("%[^\n]%*c",comanda);
if(separare_ins(comanda,nume,top,melodie,link)==-1) printf("NUME GOL");
else if(separare_ins(comanda,nume,top,melodie,link)==-2) printf("TOP GOL");
else if(separare_ins(comanda,nume,top,melodie,link)==-3) printf("MELDOIE GOALA");
else if(separare_ins(comanda,nume,top,melodie,link)==-4) printf("LINK GOL");
}
