#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd)
{
  char buff[MAX];
  int n;
  for(;;)
  {
    bzero(buff,MAX);
    read(connfd,buff,sizeof(buff));
    printf("From client: %s\t To client : ", buff);
    bzero(buff, MAX);
    n = 0;
    while((buff[n++] = getchar()) != '\n');
    write(connfd , buff , sizeof(buff));
    if(strncmp("exit", buff , 4) == 0)
    {
      printf("Server exit... \n");
      break;
    }
  }
}

int main()
{
  int sockfd , connfd, len;
  struct sockaddr_in servaddr , cli;
 
  sockfd = socket(AF_INET , SOCK_STREAM, 0);
  if(sockfd == -1)
  {
    printf("Socket creation failed..\n");
    exit(0);
  }
  else
    printf("Socket successfully created...\n");
  bzero(&servaddr, sizeof(servaddr));
 
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);
 
  if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
  {
    printf("Socket bind failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully binded...\n");
   
  if((listen(sockfd, 5)) != 0)
  {
    printf("Listen failed..\n");
    exit(0);
  }
  else  
    printf("Server listening...\n");
  len = sizeof(cli);
 
  connfd = accept(sockfd, (SA*)&cli, &len);
  if(connfd < 0)
  {
    printf("server accept failed...\n");
  }
  else{
    printf("Server accept the client...\n");
  }
 
  func(connfd);
  close(connfd);
  return 0;
}




void write_file(int sockfd)
{	
	int n;
	FILE *fp;
	char *filename="recv.txt";
	char buff[size];
	
	fp=fopen(filename, "w");
	while(1)
	{
		n=recv(sockfd, buff, size, 0);
		if (n<=0)
		{
			break;
			return;
		}
		fprintf(fp, "%s", buff);
		bzero(buff, size);
	}
	return;
}