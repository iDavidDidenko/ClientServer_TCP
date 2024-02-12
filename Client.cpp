#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 



int main()
{
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    int valread = 0;

    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if(mySocket < 0)
    {
        std::cout << "Failed to init a endpoint SOCKET" << std::endl;
        exit(1);
    } 

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(3000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(mySocket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        close(mySocket);
        return 1;
    }

    send(mySocket, hello, strlen(hello), 0);
    valread = read(mySocket, buffer, 1024 - 1); // subtract 1 for the null // terminator at the end
    std:: cout << "inside client " << buffer << std::endl;

    close(mySocket);
    return 0;
}