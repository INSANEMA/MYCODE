#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int  main()
{
	int server,client;
	char buff[1024];
	struct sockaddr_in servAddr;
	struct sockaddr_storage store;
	socklen_t clientsize;
	server=socket(AF_INET,SOCK_STREAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(6265);
	servAddr.sin_addr.s_addr=inet_addr("127.0.01");
	bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
	if(listen(server,5)==0)
		printf("listening\n");
	client=accept(server,(struct sockaddr*)&store,&clientsize);
	strcpy(buff,"enter the first number\n");
	send(client,buff,sizeof(buff),0);
	recv(client,buff,sizeof(buff),0);
	int a=atoi(buff);
	printf("the number recivied %d\n",a);
	strcpy(buff,"enter the second number\n");
	send(client,buff,sizeof(buff),0);
	recv(client,buff,sizeof(buff),0);
	int b=atoi(buff);
	printf("the number recivied %d\n",b);
	strcpy(buff,"enter the operator number\n");
	send(client,buff,sizeof(buff),0);
	recv(client,buff,sizeof(buff),0);
	char op=buff[0];
	printf("the operator recivied %c\n",op);
	
	int result=0;
	if(op=='+')
		result=a+b;
	else if(op=='-')
		result=a-b;
	else if(op=='/')
		result=a/b;
	else if(op=='%')
		result=a%b;
	printf("the result of operation is %d",result);
	sprintf(buff,"%d",result);
	send(client,buff,sizeof(buff),0);
	close(server);
	close(client);
}
