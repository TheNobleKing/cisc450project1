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


int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *newfile;
  char *filename; // --NEEDS CIN FILENAME

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET; //fill in struct
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); //attempt TCP connection
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Client.\n");

  recv(4

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
