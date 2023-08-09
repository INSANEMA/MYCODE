#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main()
{
	int server,client;
	struct sockaddr_in servAddr;
	struct sockaddr_storage store;
	socklen_t clientlen;
	char buff[1024];
	server=socket(AF_INET,SOCK_STREAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(6265);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
	if(listen(server,5)==0)
		printf("listening...\n");
	client=accept(server,(struct sockaddr*)&store,&clientlen);
	while(1)
	{
		recv(client,buff,sizeof(buff),0);
		printf("CLIENT :%s\n",buff);
		if(strcmp(buff,"bye")==0)
		{
			strcpy(buff,"bye");
			send(client,buff,sizeof(buff),0);
			break;
		}
		printf("enter the data to sent to client\n");
		gets(buff);
		send(client,buff,sizeof(buff),0);
		memset(buff,0,sizeof(buff));
	}
	close(server);
	close(client);
}
