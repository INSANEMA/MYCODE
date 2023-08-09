#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int  main()
{
	int client;
	int i;
	char buff[1024];
	struct sockaddr_in servAddr;
	struct sockaddr_storage store;
	socklen_t clientsize;
	client=socket(AF_INET,SOCK_STREAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(6265);
	servAddr.sin_addr.s_addr=inet_addr("127.0.01");
	connect(client,(struct sockaddr*)&servAddr,sizeof(servAddr));
	while(i<=3){
	recv(client,buff,sizeof(buff),0);
	printf("%s",buff);
	gets(buff);
	send(client,buff,sizeof(buff),0);
	memset(buff,0,sizeof(buff));
	}
	recv(client,buff,sizeof(buff),0);
	printf("the result of operation is :%s",buff);
	close(client);
}
