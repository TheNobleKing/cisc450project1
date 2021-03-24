#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 80
#define PORT 8080
#define IPADDR 127.0.0.1

void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) { //while data is still in doc, read 80 byte at a time
    if (send(sockfd, data, sizeof(data), 0) == -1) { //send data
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE); //clear data buffer
  }
}


char getFileName(int sockfd){
 char buff[SIZE];
    int n;

       bzero(buff, SIZE);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));

        // print buffer which contains the client contents
        printf("File named %s\t requested", buff);

        return *buff;
}


int main(){
  char *ip = "IPADDR";
  int port = PORT;
  int isBound;

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename;


  void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
   }
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET; //fill in struct
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  isBound = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); //attempt TCP connection
  if(isBound == -1) {
    perror("[-]Error in binding socket");
    exit(1);
  }
 printf("[+]Connected to Client.\n");

   if(listen(sockfd, 10) == 0){
     printf("[+]Listening....\n");
   } else {
     perror("[-]Error in listening");
    exit(1);
   }


  *filename = getFileName(sockfd);

  fp = fopen(filename, "r"); //buffer file contents
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }


  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");

  printf("[+]Closing the connection.\n");
  close(sockfd);

  return 0;
}
