#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main()
{
	int server,client;
	char buff[1024];
	struct sockaddr_in servAddr;
	struct sockaddr_storage store;
	socklen_t clientsize;
	server=socket(AF_INET,SOCK_STREAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(6265);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
	if(listen(server,1)==0)
		printf("listening....\n");
	client=accept(server,(struct sockaddr*)&store,&clientsize);
	char* welcomemsg="220 WELCOME TO SMTP SERVER\r\n";
	send(client,welcomemsg,strlen(welcomemsg),0);
	while(1)
	{
		recv(client,buff,sizeof(buff),0);
		printf("CLIENT: %s",buff);
		if(strcmp(buff,"QUIT\r\n")==0)
		{
			char *response="221 EXIT \r\n";
			send(client,response,strlen(response),0);
			break;
		}
		char *response="250 OK\r\n";
		send(client,response,strlen(response),0);
		memset(buff,0,sizeof(buff));
	}
	close(server);
	close(client);
}
