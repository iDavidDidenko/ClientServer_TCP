#include <iostream>

#ifdef _WIN32
    #include <winsock.h> 
    
#else 
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
#endif



int main()
{
    // length of input
    char buffer[1024] = { 0 };
    // 
    int accept_socket = 0;
    const char* hello = "Hello from server";

    #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
    #endif

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

    //socklen_t addrlen = sizeof(serv_addr);
    int addrlen = sizeof(serv_addr);
    accept_socket = accept(mySocket, (struct sockaddr*)&serv_addr, &addrlen);
    if(accept_socket < 0)
    {
        std::cout << "failed to Accept" << std::endl;
    }

    ssize_t valread;

    #ifdef _WIN32
    valread = recv(accept_socket, buffer, 1024 - 1, 0);
    #else
    valread = read(accept_socket, buffer, 1024 - 1);
    #endif

    std:: cout << "Message: " << buffer << std::endl;

    #ifdef _WIN32
    send(accept_socket, hello, strlen(hello), 0);
    #else
    write(accept_socket, hello, strlen(hello));
    #endif

    // Close the socket
    #ifdef _WIN32
    closesocket(mySocket);
    #else
    close(mySocket);
    #endif
    return 0;
}