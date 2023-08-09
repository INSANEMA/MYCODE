#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main()
{
	int server;
	struct sockaddr_in servAddr;
	struct sockaddr_storage store;
	int clientsize=sizeof(store);
	char buff[1024];
	server=socket(AF_INET,SOCK_DGRAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(2002);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
	while(1)
	{
		recvfrom(server,buff,sizeof(buff),0,(struct sockaadr*)&store,&clientsize);
		printf("CLIENT :%s\n",buff);
		if(strcmp(buff,"bye")==0)
		{
			strcpy(buff,"bye");
			sendto(server,buff,sizeof(buff),0,(struct sockaddr*)&store,clientsize);
			break;
		}
		printf("enter the data to sent to client\n");
		gets(buff);
		sendto(server,buff,sizeof(buff),0,(struct sockaddr*)&store,clientsize);
		memset(buff,0,sizeof(buff));
	}
	close(server);
}
		
