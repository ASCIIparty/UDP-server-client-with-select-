#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define PORT 4030
#define BUF  1024

int main() {
	
	int sfd, retval, n;
	int count;
	
	unsigned char buf[BUF];
	fd_set rfds;
	char loctime[BUF];
	struct sockaddr_in server, client;
	struct timeval tv;
	time_t time1;
	socklen_t addrlen;

	FILE *fp;
	
	fp = fopen("./sensorwerte.txt", "r");
	if( fp == NULL )
	{
		perror("Error reading sensor data.");
		exit(EXIT_FAILURE);
	} 

	//create UDP socket
	sfd =  socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1) {
		perror("Kein Socket");
		exit(1);
	}
	
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr("127.0.0.1"); //anfrage von client muss genau server addressieren
	
        memset(&client, 0, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);

	//fscanf(fp, BUF, &buf);

	while(count != 3){
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		FD_SET(sfd, &rfds);

		time(&time1);
	
		while(fgets(buf, sizeof(buf), fp)){	

	//strcpy( buf, "hallo\n");
	//	printf("%s: %s: %s\n", ctime(&time1), inet_ntoa(client.sin_addr), buf);
		sendto(sfd, buf, sizeof(buf), 0, (struct sockaddr*) &server, sizeof(server));	
		}
		tv.tv_sec = 3;
		tv.tv_usec = 0;

		retval = select(sfd + 1, &rfds, NULL, NULL, &tv);
		
		if (retval == -1){
			perror("select()");
		}
		if (retval) {
			recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr*) &client, &addrlen);
			printf("%s", buf);
			count = 3;
		} else {
			printf("No data within five seconds.\n");
			count+=1;
	 	}
	}
	
	fclose(fp);
	
	return 0;
}
