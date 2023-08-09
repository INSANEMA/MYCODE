#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
void read_file(FILE* fp,int client)
{
	char buff[1024];
	while(fgets(buff,sizeof(buff),fp)!=NULL)
	{
		send(client,buff,sizeof(buff),0);
		printf("%s\n",buff);
		memset(buff,0,sizeof(buff));
	}return;
}
	
int main()
{
	int client;
	FILE* fp;
	fp=fopen("read.txt","r");
	struct sockaddr_in servAddr;
	client=socket(AF_INET,SOCK_STREAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(6265);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(client,(struct sockaddr*)&servAddr,sizeof(servAddr));
	read_file(fp,client);
	close(client);
}
