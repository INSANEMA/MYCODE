#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
void write_file(int client)
{
	FILE* fp;
	int n;
	char buff[1024];
	fp=fopen("write.txt","w");
	while(1)
	{
		n=recv(client,buff,sizeof(buff),0);
		if(n<=0)
		{
			break;
			return;
		}
		printf("%s\n",buff);
		fprintf(fp,"%s",buff);
		
		memset(buff,0,sizeof(buff));
	}return;
}
int main()
{
	int server,client;
	struct sockaddr_in servAddr;
	struct sockaddr_storage store;
	socklen_t clientsize;
	server=socket(AF_INET,SOCK_STREAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(6265);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
	if(listen(server,5)==0)
		printf("listening....\n");
	client=accept(server,(struct sockaddr*)&store,&clientsize);
	write_file(client);
	close(server);
	close(client);
}
