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

#define MAX 256
#define PORT 2018
extern int errno;

int separare(char * comanda,char * nume, char * argument)
{int i=0,j=0,it,ok=0,spatiu=0,bloc;

for(it=0;(it<strlen(comanda) && spatiu==0);it++)
{
	if(comanda[it]==' ')    {bloc=it;spatiu=1;}
	else if(comanda[it]!=' ') {nume[i]=comanda[it];i++;}
}

for(it=bloc+1;it<strlen(comanda);it++)
{	argument[j]=comanda[it];
	j++;
}

nume[i]='\0';
argument[j]='\0';
}


int user1(char * comanda)
{char argument[20],nume[20];
separare(comanda,nume,argument);
int file;
int i=0,ok=0;
char ch;
char aux[20];
file=open("user1",O_RDONLY);
while(read(file,&ch,1) && ok==0)
{if(ch=='\n')    {aux[i]='\0';if(strcmp(aux,argument)==0) ok=1; i=0;}
        else    {aux[i]=ch;i++;}
}
return ok;
}


int user2(char * comanda)
{char argument[20],nume[20],aux[20];
separare(comanda,nume,argument);
int i=0,ok=0,file;
char ch;
file=open("user2",O_RDONLY);
while(read(file,&ch,1) && ok==0)
{
if(ch=='\n')    {aux[i]='\0';if(strcmp(aux,argument)==0) ok=1; i=0;}
        else    {aux[i]=ch;i++;}
}
return ok;
}


int login(char * comanda)
{char nume[20],argument[20],log[20];
separare(comanda,nume,argument);
strcpy(log,"login");
if(strcmp(log,nume)==0 && user1(comanda)==1) return 1;
else if(strcmp(log,nume)==0 && user2(comanda)==1) return 2;
else return -1;
}

int alegere(char * comanda)
{
char nume[20],argument[500];
separare(comanda,nume,argument);
if(strcmp("/top",nume)==0) return 1;
else if(strcmp("/help",nume)==0) return 2;
else if(strcmp("help",nume)==0) return 10;
else if(strcmp("/delete",nume)==0) return 11;
else if(strcmp("/link",nume)==0) return 12;
else if(strcmp("/mkcom",nume)==0) return 13;
else if(strcmp("/links",nume)==0) return 14;
else if(strcmp("/comms",nume)==0) return 15;
else if(strcmp("/quit",nume)==0) return 3;
else if(strcmp("/rock",nume)==0) return 4;
else if(strcmp("/trap",nume)==0) return 5;
else if(strcmp("/rap",nume)==0) return 6;
else if(strcmp("/dance",nume)==0) return 7;
else if(strcmp("/insert",nume)==0) return 8;
else if(strcmp("users",nume)==0) return 9;
else return -1;
}



void Top_x(char comanda[20],char text[500])
{
char fis[20],nume[20],argument[20];
separare(comanda,nume,argument);
if(strcmp(nume,"/rock")==0) strcpy(fis,"rock.txt");
else if(strcmp(nume,"/trap")==0) strcpy(fis,"trap.txt");
else if(strcmp(nume,"/rap")==0) strcpy(fis,"rap.txt");
else if(strcmp(nume,"/dance")==0) strcpy(fis,"dance.txt");
else if(strcmp(nume,"/top")==0) strcpy(fis,"top");
else if(strcmp(nume,"users")==0) strcpy(fis,"user1");
else if(strcmp(nume,"/links")==0) strcpy(fis,"link.fix");
else if(strcmp(nume,"/comms")==0) strcpy(fis,"comentarii.txt");

char ch;
int file,i=0;
file=open(fis,O_RDONLY);
while(read(file,&ch,1))
{
	text[i]=ch;
	i++;
}
text[i]='\0';
}

void help1(char * help)
{
strcat(help,"\t [INFO] Inainte de logare se pot folosi comenzile:\n\t\t  users          -afiseaza lista user-ilor inregistrati;\n\t\t  register <nume>-te inregistrezi cu numele <nume>;\n\t\t  login <nume>   -te logezi cu numele <nume>\n\t\t  help           -afiseaza lista comenzilor ce pot fi utilizate inainte de logare;");
}


void help2(char * help)
{
strcat(help,"\t [INFO] Dupa logare se pot folosi comenzile:\n\t\t@useri obisnuiti:  \n\t\t  /top      -afiseaza topul curent\n\t\t  /<nume>   -afiseaza topul curent pentru <nume>\n\t\t  /help     -afiseaza lista comenzilor(comanda poate fi folosita doar dupa logare)\n\t\t  /link <nume_melodie>    -afiseaza linkul pe YOUTUBE pentru melodia respectiva\n\t\t  /mkcom <nume_melodie>:<comentariu> -adauga un comentariu melodiei respective\n\t\t  /comms         -afiseaza comentariile tuturor melodiiloe\n\t\t  /links         -afiseaza link-urile de youtube al tuturor melodiilor\n\t\t  /insert <nume_top> <nume_melodie>     -insereaza in topul <nume_top> melodia respectiva\n\t\t@admin(includ si cele de la utilizatori obisnuiti): \n\t\t  /delete <nume_top> <nume_melodie>     -sterge din topul <nume_top> melodia respectiva\n\t\t");
}


void separare_ins(char * comanda, char * nume, char * top, char * melodie)
{

int it,i=0,j=0,k=0,bloc=0,spatiu=0;
for(it=0;(it<strlen(comanda) && spatiu==0);it++)
        {
        if(comanda[it]==' ')    {spatiu=1;bloc=it;}
        else if(comanda[it]!=' ') {nume[i]=comanda[it];i++;}
        }
spatiu=0;
for(it=bloc+1;(it<strlen(comanda) && spatiu==0);it++)
        {
        if(comanda[it]==' ')    {spatiu=1;bloc=it;}
        else if(comanda[it]!=' ') {top[j]=comanda[it];j++;}
        }
for(it=bloc+1;it<strlen(comanda);it++)
{
        melodie[k]=comanda[it];k++;
}

nume[i]='\0';
top[j]='\0';
melodie[k]='\0';

}


void separare_insert(char * melodie,char * nume_artist,char * nume_melodie,char * link)
{
int i=0,j=0,it,linie=0,bloc=0,k=0;
for(it=0;(it<strlen(melodie) && linie==0);it++)
{
        if(melodie[it]=='-') {linie=it;}
        else {nume_artist[i]=melodie[it];i++;}
}

for(it=linie+1;(it<strlen(melodie) && bloc==0);it++)
{       if(melodie[it]=='(') {linie=it;bloc=1;}
        else {nume_melodie[j]=melodie[it];j++;}
}
bloc=0;
for(it=linie+1;(it<strlen(melodie) && bloc==0);it++)
{
        if(melodie[it]==')') bloc=1;
        else
        {link[k]=melodie[it];k++;}
}

nume_artist[i]='\0';
nume_melodie[j]='\0';
link[k]='\0';

}


int insert(char * comanda)
{
char functie[20],top[10],melodie[200],fname[20],nume_artist[100],nume_melodie[150],melodie_inserata[500],link[100];
int file,ok=1;
separare_ins(comanda,functie,top,melodie);
if(strcmp(functie,"/insert")==0)
	{
	if(strcmp(top,"rock")==0) {strcpy(fname,"rock.txt");ok=1;}
	else if(strcmp(top,"trap")==0) {strcpy(fname,"trap.txt");ok=1;}
	else if(strcmp(top,"rap")==0) {strcpy(fname,"rap.txt");ok=1;}
	else if(strcmp(top,"dance")==0) {strcpy(fname,"dance.txt");ok=1;}

	if(ok==1)
	{
	file=open(fname,O_APPEND|O_WRONLY);
        separare_insert(melodie,nume_artist,nume_melodie,link);
        bzero(melodie_inserata,500);
        strcat(melodie_inserata,"-");
        strcat(melodie_inserata,nume_artist);
        strcat(melodie_inserata," - ");
        strcat(melodie_inserata,nume_melodie);
        strcat(melodie_inserata,"\n");
        write(file,melodie_inserata,strlen(melodie_inserata));

        file=open("top",O_APPEND|O_WRONLY);
        write(file,melodie_inserata,strlen(melodie_inserata));


	bzero(melodie_inserata,500);
        file=open("link.fix",O_APPEND|O_WRONLY);
        strcat(melodie_inserata,nume_melodie);
        strcat(melodie_inserata,"-");
        strcat(melodie_inserata,link);
        strcat(melodie_inserata,"\n");
        write(file,melodie_inserata,strlen(melodie_inserata));

	}
	else return -2;
	}
else return -1;
}


int reg(char * comanda)
{
int file,ok=0;
file=open("user1",O_APPEND|O_WRONLY);
char argument[20],nume[20];
separare(comanda,nume,argument);
if(strcmp(nume,"register")==0)
{
	if(user1(comanda)!=1) {write(file,argument,strlen(argument));write(file,"\n",strlen("\n"));ok=1;}
	else ok=2;
}
else ok=3;
return ok;
}


void separare_del(char * linie,char * nume)
{
int it,i=0,bloc=0;;
for(it=1;(it<strlen(linie) && bloc==0);it++)
{
	if(linie[it]=='-') bloc=it;
}

for(it=bloc+2;it<strlen(linie);it++)
{
      nume[i]=linie[it];i++;
}
nume[i]='\0';

}



int del(char * comanda)
{
int linie=0,control=0,ok=0,file,gasit=0,numar=0,i=0;
char ch,c;
FILE *fisier1,*fisier2;
char fname[MAX],functie[20],top[20],nume[300],temp[300],num[200],link[100];
char str[MAX],aux[]="aux.txt";
separare_ins(comanda,functie,top,nume);
if(strcmp(functie,"/delete")==0)
{
if(strcmp(top,"rock")==0) {strcpy(fname,"rock.txt");ok=1;}
else if(strcmp(top,"rap")==0) {strcpy(fname,"rap.txt");ok=1;}
else if(strcmp(top,"dance")==0) {strcpy(fname,"dance.txt");ok=1;}
else if(strcmp(top,"trap")==0) {strcpy(fname,"trap.txt");ok=1;}

if(ok==1)
{
fisier1 = fopen(fname, "r");
fisier2 = fopen(aux,"w");

file=open(fname,O_RDONLY);
while(read(file,&c,1) && gasit==0)
        {
        if(c=='\n')     {numar++;temp[i]='\0';
                        separare_del(temp,num);
                        if(strcmp(nume,num)==0) {gasit=1;linie=numar;}
                        i=0;
                        }
        else
                        {temp[i]=c;
                        i++;
                        }
        }

if(gasit==1)
{
while(!feof(fisier1))
        {
        strcpy(str,"\0");
        fgets(str,MAX,fisier1);
        if(!feof(fisier1))
                {
                control++;
                if(control!=linie)
                        {
                        fprintf(fisier2,"%s",str);
                        }
                }
        }
fclose(fisier1);
fclose(fisier2);
remove(fname);
rename(aux,fname);
}

gasit=0;
numar=0;
control=0;

fisier1 = fopen("top", "r");
fisier2 = fopen(aux,"w");

file=open("top",O_RDONLY);
while(read(file,&c,1) && gasit==0)
        {
        if(c=='\n')     {numar++;temp[i]='\0';
                        separare_del(temp,num);
                        if(strcmp(nume,num)==0) {gasit=1;linie=numar;}
                        i=0;
                        }
        else
                        {temp[i]=c;
                        i++;
                        }
        }

if(gasit==1)
{
while(!feof(fisier1))
        {
        strcpy(str,"\0");
        fgets(str,MAX,fisier1);
        if(!feof(fisier1))
                {
                control++;
                if(control!=linie)
                        {
                        fprintf(fisier2,"%s",str);
                        }
                }
        }
fclose(fisier1);
fclose(fisier2);
remove("top");
rename(aux,"top");


gasit=0;
numar=0;
control=0;


fisier1 = fopen("link.fix", "r");
fisier2 = fopen(aux,"w");

file=open("link.txt",O_RDONLY);
while(read(file,&c,1) && gasit==0)
        {
        if(c=='\n')     {numar++;temp[i]='\0';
                        separare_del(temp,num);
                        if(strcmp(nume,num)==0) {gasit=1;linie=numar;}
                        i=0;
                        }
        else
                        {temp[i]=c;
                        i++;
                        }
        }
if(gasit==1)
{
while(!feof(fisier1))
        {
        strcpy(str,"\0");
        fgets(str,MAX,fisier1);
        if(!feof(fisier1))
                {
                control++;
                if(control!=linie)
                        {
                        fprintf(fisier2,"%s",str);
                        }
                }
        }

fclose(fisier1);
fclose(fisier2);
remove("link.fix");
rename(aux,"link.fix");
}


}
else return -1;
}
else return -2;
}
else return -3;

}//final



void separare_cauta(char * linie,char * nume,char * link)
{
int i=0,it,spatiu=0,j=0;
for(it=0;(it<strlen(linie) && spatiu==0);it++)
        {
        if(linie[it]=='-') spatiu=it;
        else {nume[i]=linie[it];i++;}
        }
for(it=spatiu+1;it<strlen(linie);it++)
        {
        link[j]=linie[it];j++;
        }

nume[i]='\0';
link[j]='\0';
}

int cauta(char * comanda,char * link)
{

int file,i=0,ok=0;
file=open("link.fix",O_RDONLY);
char ch,aux[100],copy[100],name[30],argument[20],nume[40];
separare(comanda,nume,argument);
while(read(file,&ch,1) && ok==0)
{
        if(ch=='\n')    {aux[i]='\0';
                        separare_cauta(aux,name,copy);
                        if(strcmp(argument,name)==0) ok=1;
                        i=0;}
        else
        {aux[i]=ch;i++;}
}
if(ok==1)
{
        strcat(link,copy);
	strcat(link,"\n");
}
else return -1;

}


void separare_mk(char * comanda,char * functie, char * nume_melodie, char * descriere)
{
int it,i=0,j=0,k=0,spatiu=0,bloc=0;
for(it=0;(it<strlen(comanda) && spatiu==0);it++)
        {
        if(comanda[it]==' ') {spatiu=1;bloc=it;}
        else {functie[i]=comanda[it];i++;}
        }
spatiu=0;
for(it=bloc+1;(it<strlen(comanda) && spatiu==0);it++)
        {
        if(comanda[it]==':') {spatiu=1;bloc=it;}
        else {nume_melodie[j]=comanda[it];j++;}
        }
for(it=bloc+1;it<strlen(comanda);it++)
        {
        descriere[k]=comanda[it];k++;
        }
functie[i]='\0';
nume_melodie[j]='\0';
descriere[k]='\0';

}

int mk(char * comanda)
{
int file1,file2,ok=0,i=0;
char ch,mesaj[1000],functie[10],nume_melodie[30],descriere[200],nume_aux[30],aux[100],link[100];
separare_mk(comanda,functie,nume_melodie,descriere);
if(strcmp(functie,"/mkcom")==0)
{
        file1=open("link.fix",O_RDONLY);
        file2=open("comentarii.txt",O_WRONLY|O_APPEND);
        while(read(file1,&ch,1) && ok==0)
        {
        if(ch=='\n') {aux[i]='\0';separare_cauta(aux,nume_aux,link);if(strcmp(nume_aux,nume_melodie)==0) ok=1;i=0;}
        else {aux[i]=ch;i++;}
        }

        if(ok==1)
        {
        bzero(mesaj,1000);
        strcat(mesaj,nume_melodie);
        strcat(mesaj," (anonim): [ ");
        strcat(mesaj,descriere);
        strcat(mesaj," ]");
        strcat(mesaj,"\n");
        write(file2,mesaj,strlen(mesaj));
        }
        else return -2;
}
else return -1;
}


int main ()
{
struct sockaddr_in server;	// structura folosita de server
struct sockaddr_in from;	
char msg[1000];		//mesajul primit de la client 
char msgrasp[1000];        //mesaj de raspuns pentru client
int sd;			//descriptorul de socket 

if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }
bzero (&server, sizeof (server));
bzero (&from, sizeof (from));
server.sin_family = AF_INET;	
server.sin_addr.s_addr = htonl (INADDR_ANY);
server.sin_port = htons (PORT);

if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Eroare la bind().\n");
      return errno;
    }

if (listen (sd, 5) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }
int logat=0,top=0,top_x=0,quit=0,admin=0;
char vec_top[200],com[20],text[500],hhelp[1000],copie_link[100];
while (1)
    {
      int client;
      int length = sizeof (from);

      printf ("[server]Asteptam la portul %d...\n",PORT);
      fflush (stdout);

      client = accept (sd, (struct sockaddr *) &from, &length);

      if (client < 0)
	{
	  perror ("[server]Eroare la accept().\n");
	  continue;
	}
	if(fork())
	{
		while(1)
		{
		bzero (msgrasp,1000);
      	 	bzero (msg, 1000);
		bzero (text,500);
		bzero (copie_link,100);
      	      	fflush (stdout);
        	if (read (client, msg, 1000) <= 0)
			{
	  		perror ("[server]Eroare la read() de la client.\n");
	  		close (client);	/* inchidem conexiunea cu clientul */
	  		continue;		/* continuam sa ascultam */
			}
		printf("[%s]\n",msg);
		if(logat==0)
		{
		if(login(msg)==1) {strcat(msgrasp,"[SUCCES] Te-ai logat ca un simplu user.\n");logat=1;}
		else
		if(login(msg)==2) {strcat(msgrasp,"[SUCCES] Te-ai logat ca administrator.\n");logat=2;}
		else
		if(alegere(msg)==1 || alegere(msg)==3 || alegere(msg)==4 || alegere(msg)==5 || alegere(msg)==6 || alegere(msg)==7 || alegere(msg)==15 || alegere(msg)==14 || alegere(msg)==13 || alegere(msg)==12) {strcat(msgrasp,"[EROARE] Trebuie sa fii logat pentru a folosi comanda.\n");}
		else
		if(reg(msg)==1) {strcat(msgrasp,"[SUCCES] Te-ai inregistrat cu succes.\n");}
		else
		if(reg(msg)==2) {strcat(msgrasp,"[EROARE] Utilizator existent.\n");}
		else
		if(alegere(msg)==9) {Top_x(msg,text);strcat(msgrasp,text);}
		else
		if(alegere(msg)==10) {help1(text);strcat(msgrasp,text);}
		else strcat(msgrasp,"[EROARE] Logarea a esuat.Tasteaza help pentru a vedea comenzile disponibile.\n");
		}

		else if(logat==1)
		{

			printf("Logat=1->simplu\n");
			if(alegere(msg)==1) {printf("Top\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
			if(alegere(msg)==2) {help2(text);strcat(msgrasp,text);}
			else
			if(alegere(msg)==3) {printf("Quit\n"); write(client,"/quit",5); close(client); exit(1);}
			else
			if(alegere(msg)==4) {printf("Rock\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
			if(alegere(msg)==5) {printf("Trap\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
			if(alegere(msg)==6) {printf("Rap\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
			if(alegere(msg)==14) {printf("LINKS\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
			if(alegere(msg)==8) {printf("Insert\n"); if(insert(msg)==-2) strcat(msgrasp,"[EROARE] Top inexistent.\n");else strcat(msgrasp,"[SUCCES] Adaugarea a avut succes.\n");}
			else
			if(alegere(msg)==7) {printf("Dance\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
			if(alegere(msg)==12) {printf("Link\n");if(cauta(msg,copie_link)==-1)strcat(msgrasp,"[EROARE] Numele nu se gaseste in fisier.\n");else strcat(msgrasp,copie_link);}
			else
			if(alegere(msg)==11) {strcat(msgrasp,"[EROARE] Nu ai drept de a folosi aceasta comanda.\n");}
			else
                        if(alegere(msg)==15) {printf("Comms\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
			if(alegere(msg)==13) {printf("MKCOM\n");if(mk(msg)==-2) strcat(msgrasp,"[EROARE] Nume inexistent.\n"); else strcat(msgrasp,"[SUCCES] Ai adaugat comentariul cu succes.\n");}
			else strcat(msgrasp,"[EROARE] Comanda invalida sau inexistenta. Tasteaza /help pentru ajutor.\n");

		}

		else if(logat==2)
		{
			printf("Logat=2->admin\n");
			if(alegere(msg)==1) {printf("Top\n");Top_x(msg,text);strcat(msgrasp,text);}
                        else
                        if(alegere(msg)==2) {help2(text);strcat(msgrasp,text);}
                        else
			if(alegere(msg)==3) {printf("Quit\n"); write(client,"/quit",5); close(client); exit(1);}
			else
                        if(alegere(msg)==4) {printf("Rock\n");Top_x(msg,text);strcat(msgrasp,text);}
                        else
                        if(alegere(msg)==5) {printf("Trap\n");Top_x(msg,text);strcat(msgrasp,text);}
                        else
                        if(alegere(msg)==6) {printf("Rap\n");Top_x(msg,text);strcat(msgrasp,text);}
                        else
			if(alegere(msg)==14) {printf("Links\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
                        if(alegere(msg)==7) {printf("Dance\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
                        if(alegere(msg)==15) {printf("Comms\n");Top_x(msg,text);strcat(msgrasp,text);}
			else
			if(alegere(msg)==13) {printf("MKCOM\n");if(mk(msg)==-2) strcat(msgrasp,"[EROARE] Nume inexistent.\n"); else strcat(msgrasp,"[SUCCES] Ai adaugat comentariul cu succes.\n");}
                        else
			if(alegere(msg)==8) {printf("Insert\n"); if(insert(msg)==-2) strcat(msgrasp,"[EROARE] Top inexistent.\n");else strcat(msgrasp,"[SUCCES] Adaugarea a avut succes.\n");}
			else
			if(alegere(msg)==12) {printf("Link\n");if(cauta(msg,copie_link)==-1)strcat(msgrasp,"[EROARE] Numele nu se gaseste in fisier.\n");else strcat(msgrasp,copie_link);}
			else
			if(alegere(msg)==11) {printf("Delete\n");if(del(msg)==-1)strcat(msgrasp,"[EROARE] Nume invalid.\n");else if(del(msg)==-2) strcat(msgrasp,"[EROARE] Top invalid.\n"); else strcat(msgrasp,"[SUCCES] Stergerea a avut succes.\n");}
                        else strcat(msgrasp,"[EROARE] Comanda invalida sau inexistenta. Tasteaza /help pentru ajutor.\n");

		}

      	   	//bzero(msgrasp,100);
      	  	if (write (client, msgrasp, 1000) <= 0)
			{
	  		perror ("[server]Eroare la write() catre client.\n");
	  		continue;		/* continuam sa ascultam */
			}

		}
	}
      /* am terminat cu acest client, inchidem conexiunea */
    // close (client);
    }				/* while */

}				/* main */
