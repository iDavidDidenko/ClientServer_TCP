#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    char buffer[1024] = { 0 };
    int new_socket = 0;
    char* hello = "Hello from server";

    // creating end-point server socket. 
    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    

    if(mySocket < 0)
    {
        std::cout << "Failed to init a endpoint SOCKET" << std::endl;
        exit(1);
    } 

    // bind section
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(3000);

    if(bind(mySocket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Error binding socket: " << strerror(errno) << std::endl;
        exit(1);
    }

    // Listen 
    if(listen(mySocket, 5) < 0) // TODO the "5" value.
    {
        std::cout << "Error occured on Listen";
    }
    // 
    socklen_t addrlen = sizeof(serv_addr);
    new_socket = accept(mySocket, (struct sockaddr*)&serv_addr, &addrlen);
    if(new_socket < 0)
    {
        std::cout << "failed to Accept" << std::endl;
    }

    ssize_t valread;

    valread = read(new_socket, buffer, 1024 - 1);

    std:: cout << "Message: " << buffer << std::endl;

    send(new_socket, hello, strlen(hello), 0);

    close(mySocket);
    return 0;
}