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
    sTCP::Init();

    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    sTCP_ASSERT(listening != -1, "Failed to create listening socket!");

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    int success = bind(listening, reinterpret_cast<sockaddr*>(&hint), sizeof(hint));
    sTCP_ASSERT(success != -1, "Failed to bind to IP / Port");

    // Mark socket for listening
    success = listen(listening, SOMAXCONN);
    sTCP_ASSERT(success != -1, "Failed to start listening");

    // Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int clientSocket = accept(listening, reinterpret_cast<sockaddr*>(&client), &clientSize);
    sTCP_ASSERT(clientSocket != -1, "Client failed to connect");
    
    // Close the listening socket
    close(listening);

    int result = getnameinfo(reinterpret_cast<sockaddr*>(&client), sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);
    if (result)
    {
        sTCP_INFO("{0} connected on {1}.", host, svc);
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        sTCP_INFO("{0} connected on {1}.", host, ntohs(client.sin_port));
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
            sTCP_ERROR("Connection issue!");
            break;
        }

        if (bytesRecv == 0)
        {
            sTCP_INFO("Client Disconnected");
            break;
        }

        // Display message
        sTCP_LOG("{0}", std::string(buff, 0, bytesRecv));

        // Resend message
        send(clientSocket, buff, bytesRecv + 1, 0);
    }

    // Close socket
    close(clientSocket);
}
