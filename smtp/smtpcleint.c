#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main()
{
	int client;
	char buff[1024];
	struct sockaddr_in servAddr;
	client=socket(AF_INET,SOCK_STREAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(6265);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(client,(struct sockaddr*)&servAddr,sizeof(servAddr));
	char* emailcommands[]=
	{"Hello Localhost\r\n",
	 "MAILFROM:sender@example.com\r\n",
	 "RCPTTO:reciever@example.com\r\n",
	 "SUBJECT: sample mail\r\n",
	 "DATA :\r\n",
	 "This is a sample mail\r\n",
	 ".\r\n"
	 "QUIT\r\n"};
		recv(client,buff,sizeof(buff),0);
		printf("SERVER:%s",buff);
		memset(buff,0,sizeof(buff));
		for(int i=0;i<sizeof(emailcommands)/sizeof(emailcommands[0]);i++)
		{
			send(client,emailcommands[i],strlen(emailcommands[i]),0);
			recv(client,buff,sizeof(buff),0);
			printf("SERVER:%s",buff);
			memset(buff,0,sizeof(buff));
		}
	close(client);
}
