#include <iostream>

#ifdef _WIN32
    #include <winsock.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h> 
#endif


int main()
{
    const char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    int valread = 0;

    #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
    #endif

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
        #ifdef _WIN32
            closesocket(mySocket);
        #else
            close(mySocket);
        #endif
        return 1;
    }
    
    #ifdef _WIN32
    send(mySocket, hello, strlen(hello), 0);
    #else
    write(mySocket, hello, strlen(hello));
    #endif

    // Close the socket
    #ifdef _WIN32
    closesocket(mySocket);
    #else
    close(mySocket);
    #endif
    // send(mySocket, hello, strlen(hello), 0);
    // valread = read(mySocket, buffer, 1024 - 1); // subtract 1 for the null // terminator at the end
    // std:: cout << "inside client " << buffer << std::endl;

    // close(mySocket);
    return 0;
}