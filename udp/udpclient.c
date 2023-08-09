#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main()
{
	int client;
	struct sockaddr_in servAddr;
	int serversize=sizeof(servAddr);
	char buff[1024];
	client=socket(AF_INET,SOCK_DGRAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(2002);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	while(1)
	{
		printf("enter the data to sent to server\n");
		gets(buff);
		sendto(client,buff,sizeof(buff),0,(struct sockaddr*)&servAddr,serversize);
		recvfrom(client,buff,sizeof(buff),0,(struct sockaddr*)&servAddr,&serversize);
		printf("SERVER :%s\n",buff);
		if(strcmp(buff,"bye")==0)
		{
			break;
		}
		memset(buff,0,sizeof(buff));
	}
	close(client);
}
