/* server1.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PORT 	4030
#define BUF 	1472

int main() {
	
	int sfd, len, n;
	unsigned char buf[BUF];
	char loctime[BUF];
	struct sockaddr_in server, client;
	char *ptr;
	time_t time1;
	socklen_t addrlen;

	//create the UDP socket
	sfd =  socket(AF_INET, SOCK_DGRAM, 0);

	if(sfd == -1) {
		perror("Kein Socket");
		exit(1);
	}
	
	// zero out struct "server"
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);	

	//bind socket to port
	if((bind(sfd, (struct sockaddr*) &server, sizeof(server))) != 0){
		perror("Bind Error");
		exit(1);
	}
	
	//keep listening
	printf("Waiting for data ..... \n");
	while(1){
		//initiate puffer
		memset(buf, 0, BUF);
		// recieve msg
		addrlen = sizeof(client);
		n = recvfrom(sfd, buf, sizeof(buf), 0,
        	         (struct sockaddr*) &client, &addrlen);
		if (n < 0) {
			perror("pong: can't recieve data");
			continue;
		}
		if (n >= 0) {
			sendto(sfd, "Server: Data recieved\n", n, 0, (struct sockaddr*) &client, addrlen);
		}
	
		//timestamp
		time(&time1);
	
		//print data
		printf("%s: %s: %s\n", ctime(&time1), inet_ntoa(client.sin_addr), buf);	
	//	fprintf(stderr, "%s \n", inet_ntoa(client));
	  
	};

	close(sfd);

return 0;
}
