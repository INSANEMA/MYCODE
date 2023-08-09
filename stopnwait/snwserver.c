#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
	int server,client;
	int k=5,m=1;
	char buff[1024];
	server=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in servAddr;
	struct sockaddr_storage store;
	socklen_t clientsize;
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(6265);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
	if(listen(server,5)==0)
		printf("listening\n...");
	client=accept(server,(struct sockaddr*)&store,&clientsize);
	while(k!=0)
	{
		recv(client,buff,sizeof(buff),0);
		if(strcmp(buff,"frame")==0)
			printf("FRAME %d recieved\n",m);
		else
			printf("error\n");
		printf("sending acknowlegment...\n");
		if(m%2==0)
		{
			strcpy(buff,"ack");
		}
		else
		{
			strcpy(buff,"kca");
			printf("Acknowledgement lost...\n");
			printf("retransmitting...\n");
			for(int i=1;i<=3;i++)
			{
				printf("Waiting for %d seconds\n",i);
			}
			strcpy(buff,"ack");
			sleep(3);
		}
		send(client,buff,sizeof(buff),0);
		printf("acknowledgement sent\n");
		k--;
		m++;
	}
	close(server);
	close(client);
}
	
