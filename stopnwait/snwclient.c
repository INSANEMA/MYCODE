#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main()
{
	int client;
	int k=5,m=1;
	char buff[1024];
	struct sockaddr_in servAddr;
	client=socket(AF_INET,SOCK_STREAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(6265);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(client,(struct sockaddr*)&servAddr,sizeof(servAddr));
	while(k!=0)
	{
		if(m%2==0)
			strcpy(buff,"frame");
		else
		{
			strcpy(buff,"error");
			printf("frame lost...\n");
			printf("retransmitting...\n");
			for(int i=1;i<=3;i++)
			{
				printf("Waiting for %d seconds\n",i);
			}
			strcpy(buff,"frame");
			sleep(3);
		}
		send(client,buff,sizeof(buff),0);
		printf("frame %d sent\n",m);
		recv(client,buff,sizeof(buff),0);
		if(strcmp(buff,"ack")==0)
		printf("acknowledgement recievd\n...");
		else
			printf("acknowledf=gement lost...\n");
		k--;
		m++;
	}
	close(client);
}
		
		
