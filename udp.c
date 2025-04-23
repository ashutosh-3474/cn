UDP

client
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd, struct sockaddr_in servaddr)
{
  char buff[MAX];
  int n;
  socklen_t len = sizeof(servaddr);
  for(;;)
  {
    bzero(buff, sizeof(buff));
    printf("Enter the string: ");
    n = 0;
    while((buff[n++] = getchar()) != '\n');
    sendto(sockfd, buff, sizeof(buff), 0, (SA*)&servaddr, len);
    bzero(buff, sizeof(buff));
    recvfrom(sockfd, buff, sizeof(buff), 0, (SA*)&servaddr, &len);
    printf("From server : %s", buff);
    if((strncmp("exit", buff, 4)) == 0)
    {
      printf("Client Exit...\n");
      break;
    }
  }
}

int main()
{
  int sockfd;
  struct sockaddr_in servaddr;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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

  func(sockfd, servaddr);
  close(sockfd);
  return 0;
}

server

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
  char buff[MAX];
  int n;
  struct sockaddr_in cliaddr;
  socklen_t len = sizeof(cliaddr);

  for(;;)
  {
    bzero(buff, MAX);
    recvfrom(sockfd, buff, sizeof(buff), 0, (SA*)&cliaddr, &len);
    printf("From client: %s\t To client: ", buff);
    bzero(buff, MAX);
    n = 0;
    while((buff[n++] = getchar()) != '\n');
    sendto(sockfd, buff, sizeof(buff), 0, (SA*)&cliaddr, len);
    if(strncmp("exit", buff, 4) == 0)
    {
      printf("Server Exit...\n");
      break;
    }
  }
}

int main()
{
  int sockfd;
  struct sockaddr_in servaddr;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd == -1)
  {
    printf("Socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created...\n");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  if(bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
  {
    printf("Socket bind failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully binded...\n");

  printf("Server listening (UDP)...\n");
  func(sockfd);
  close(sockfd);
  return 0;
}