#include <sTCP.h>

#include <string>

#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    sTCP::sTCP("Initializing...");

    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cerr << "Failed to create listening socket!\n";
        return -1;
    }

    // Bind the socket to a IP / Port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(listening, reinterpret_cast<sockaddr*>(&hint), sizeof(hint)) == -1)
    {
        std::cerr << "Failed to bind to IP-Port\n";
        return -2;
    }

    // Mark socket for listening
    if (listen(listening, SOMAXCONN) == -1)
    {
        std::cerr << "Failed to listen!\n";
        return -3;
    }

    // Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int clientSocket = accept(listening, reinterpret_cast<sockaddr*>(&client), &clientSize);
    if (clientSocket == -1)
    {
        std::cerr << "Client failed to connect\n";
        return -4;
    }
    
    // Close the listening socket
    close(listening);

    int result = getnameinfo(reinterpret_cast<sockaddr*>(&client), sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);
    if (result)
    {
        std::cout << host << " connected on " << svc << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << ntohs(client.sin_port) << std::endl;
    }

    // While receiving- messages, echo message
    const int buffSize = 4096;
    char buff[buffSize];
    while (true)
    {
        // Clear buffer
        memset(buff, 0, buffSize);

        // Wait for message
        int bytesRecv = recv(clientSocket, buff, buffSize, 0);
        if (bytesRecv == -1)
        {
            std::cerr << "Connection Issue\n";
            break;
        }

        if (bytesRecv == 0)
        {
            std::cout << "Client disconnected\n";
            break;
        }

        // Display message
        std::cout << "Received: " << std::string(buff, 0, bytesRecv) << std::endl;

        // Resend message
        send(clientSocket, buff, bytesRecv + 1, 0);
    }

    // Close socket
    close(clientSocket);

    sTCP::sTCP("Terminating...");
}
