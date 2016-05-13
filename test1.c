#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

#define PORT 4030

int main() {
	
	int sfd, berr;
	sfd =  socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server;

	if(sfd == -1) {
		perror("Kein Socket");
		exit(1);
	}
	
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);	

	berr = bind(sfd, (struct sockaddr*) &server, sizeof(server));
		
	sleep(60);

return 0;
}
