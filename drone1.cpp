#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in serverAddr;


    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Erreur lors de la création de la socket");
        exit(1);
    }


    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8890); 
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]); 


    char message[] = "";
    int messageLength = strlen(message);
    int bytesSent = sendto(sockfd, message, messageLength, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bytesSent < 0) {
        perror("Erreur lors de l'envoi du message");
        exit(1);
    }

    printf("Message envoyé avec succès au serveur\n");

    shutdown(sockfd, SHUT_WR);

    return 0;
}
