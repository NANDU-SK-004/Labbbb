# Labbbb

#include<stdio.h>

struct node {

unsigned dist[20];

unsigned from[20];

}rt[10];

int main()

(int costmat[20][20];

int nodes.i.j.k.count=0;

printf("\nEnter the number of nodes: ");

scanf("%d",&nodes);

printf("\nEnter the cost matrix:\n");

for(i=0;i<nodes;i++)

{

for(j=0;j<nodes;j++)

{

scanf("%d",&costmat[i][j]);

costmat[i][i]=0;

rt[i].dist[j]=costmat[i][j]://initialize the distance equal to cost matrix

rt[i].from[j]=j; // initialize the source node

do

count=0;

for(i=0;i<nodes;i++) //We choose arbitrary vertex k and we calculate the direct distance from node i to k

using cost matrix.

//and add the distance from k to node j

for(j=0;j<nodes;j++)

for(k=0;k<nodes;k++)

if(rt[i].dist[j]>costmat[i][k]+rt[k].dist[j])

{//We calculate the minimum distance

rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];

rt[i].from[j]=k;

count++;

}while(count!=0);

for(i=0;i<nodes;i++)

{ printf("\n\n For router %d\n",i+1);

for(j=0;j<nodes;j++)

printf("\t\nnode %d via %d Distance %d ",j+1,rt[i].from[j]+1,rt[i].dist[j]);

}

printf("\n\n");

2

B

Initial routing table

Router 1

Router 2

Router Ronchability

Router


















#include<stdio.h>

#include<stdlib.h>

#include<sys/socket.h>

#include<sys/types.h>

#include<string.h>

#include<netinet/in.h>

#include<errno.h>

#include<time.h>

int main(int argc, char *argv[]) {

int n,s,t;

struct sockaddr_in servaddr, local, rem;

char buffer[1024];

if(argc<3)

{

printf("usage:client<server-addr><port>");

exit(0);

} if((s=socket(AF_INET,SOCK_DGRAM,0))<0) { perror("error in socket creation"); exit(0);

} bzero((char *)&local,sizeof(local)); local.sin_family=AF_INET; local.sin_port=htons(6677); local.sin_addr.s_addr=inet_addr(argv[1]); if(bind(s, (struct sockaddr *)&local, sizeof(local))=-1)

{ perror("bind error"); exit(1);

}

bzero((char *)&servaddr, sizeof(local)); servaddr.sin_family=AF_INET; servaddr.sin_port=htons((short)atoi(argv[2]));

servaddr.sin_addr.s_addr=inet_addr(argv[1]);

strcpy(buffer,"TIME");

if(sendto(s,buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)

{ perror("error in sendto");

exit(0);

} t-sizeof(servaddr); printf("the current time is:"); if((n-recvfrom(s,buffer, 1024,0, (struct sockaddr *)&servaddr,&t))>0)

{ buffer[n]='\0'; fputs(buffer, stdout);

}

else

{ if(n<0)

{ perror("error in read from");

exit(0);

} else printf("server closed connection\n");

exit(1);

} memset(buffer,0,100);

close(s);

CONCURRENT SERVER PROGRAM-conserver.c

return 0; } #include<stdio.h> #include<stdlib.h> #include<sys/socket.h> #include<sys/types.h> #include<string.h> #include<netinet/in.h> #include<errno.h> #include<time.h> int main(int argc, char *argv[])

{ int s,t,cp; struct sockaddr_in servaddr, cliaddr; char buffer[1024]; time_t ct; if(argc!=2)

{ printf("\n usage:client<server-adr><port>"); exit(0);

} if((s=socket(AF_INET,SOCK_DGRAM,0))<0)

{ perror("error in socket creation"); exit(0);

} bzero((char*)&servaddr, sizeof(servaddr)); servaddr.sin_family=AF_INET; servaddr.sin_port=htons((short)atoi(argv[1])); servaddr.sin_addr.s_addr=htonl(INADDR_ANY); if(bind(s,(struct sockaddr*)&servaddr, sizeof(servaddr))<0)

{ perror("bind"); exit(0);

} t-sizeof(cliaddr); memset(buffer,0,100); while(1)

{ if (recvfrom(s,buffer, 1024,0, (struct sockaddr*)&cliaddr,&t)<0)

{ perror("error in recvfrom"); exit(0);

} ct-time(NULL); sprintf(buffer,"%s", ctime(&ct)); if((cp-fork())=0)

while(1) {

{ if(sendto(s,buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr))<0)

{ perror("error in send to"); exit(0);

} memset(buffer,0,100); if (recvfrom(s,buffer, 1024,0, (struct sockaddr*)&cliaddr,&t)<0)

{ perror("error in recvfrom"); exit(0);

} sprintf(buffer,"%s", ctime(&ct));

} } else if(cp<0) { perror("fork error"); exit(0); }

} close(s); return 0;


