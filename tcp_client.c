#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
  char buff[MAX];
  int n;
  for(;;)
  {
    bzero(buff, sizeof(buff));
    printf("Enter the string:");
    n = 0;
    while((buff[n++] = getchar()) != '\n');
    write(sockfd, buff, sizeof(buff));
    bzero(buff , sizeof(buff));
    read(sockfd , buff, sizeof(buff));
    printf("From server : %s", buff);
    if((strncmp("exit",buff, 4)) == 0)
    {
      printf("Client Exit... \n");
      break;
    }
  }
}

int main()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in servaddr;
  if(sockfd == -1)
  {
    printf("Socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created...\n");
  bzero(&servaddr, sizeof(servaddr));
 
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);
 
  if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
  {
    printf("Connection with the server failed...\n");
  }
  else
    printf("Connected to the server...\n");
 
  func(sockfd);
  close(sockfd);
  return 0;
}



void send_file(int sockfd)
{
	char *filename="file.txt";
	FILE *fp=fopen(filename, "r");
	chat data[size];
	
	while(fgets(data, size, fp)!=NULL)
	{
		send(sockfd, data , size);
		bzero(data, size);
	}
}