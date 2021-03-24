#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 80
#define IPADDR 127.0.0.1
#define PORT 8080

void writeFile(int sockfd){
	int n;
	FILE *newfile;
	char *filename = "out.txt";
	char buffer[SIZE];

	newfile = fopen(filename, "w"); //create file
	while(n <= 0){
	  n = recv(sockfd, buffer, SIZE, 0); //receive file and track byte number
	  fprintf(newfile, "%s", buffer);	   //bytestream write to file
	  bzero(buffer, SIZE); //zero out buffer
	}
	return;
}

char clientChat(int sockfd)
{
    char buff[SIZE]; //buffer for filename
    int n;

        bzero(buff, SIZE);
	printf("Enter filename ");

        while ((buff[n++] = getchar()) != '\n'); //(while) getchar, add to buffer[n++] until newline

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));
	return buff;
}


int main(){
  char *ip = "IPADDR";
  int port = PORT;
  int isConnect;

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp; //file contents buffer

  sockfd = socket(AF_INET, SOCK_STREAM, 0); //create socket w/ ID sockfd
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET; //assign IP and port to socket and declare protocol
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  isConnect = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); //connect client to socket
  if(isConnect == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");

  char filename = clientChat(sockfd); //get filename
  printf("Requesting file: ");
  printf(filename);
  printf("\n");

  writeFile(sockfd); //recieve file

  fp = fopen("out.txt", "r");
  if (fp == NULL) {
    perror("[-]Error in reading file."); //check if file is blank
  }

  printf("[+]Closing the connection.\n");
  close(sockfd);

  return 0;
}
