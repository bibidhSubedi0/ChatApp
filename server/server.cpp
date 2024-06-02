#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <vector>

using namespace std;

#define port 8080

int socketInit()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket < 0)
    {
        std::cerr << "Error creating socket\n";
        return 1;
    }
    std::cout << "Socket Created : " << server_socket << endl;
    return server_socket;
}

sockaddr_in socketAddressInit()
{
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY; // inet_addr("127.0.0.1") -> inet_adder gives a long value compatible to the acceptable ip address form
    server_address.sin_port = htons(port);
    return server_address;
}

void DealWithClient(int client_socket, vector<int> &allClients)
{
    char buffer[1024];
    // const char *buffer = new char[1024];
    while (true)
    {
        int recivedBytes = recv(client_socket, buffer, 1024, 0);

        buffer[recivedBytes] = '\0';
        if (recivedBytes <= 0)
        {
            std::cout << "Client Disconnected : " << endl;
            break;
        }

        // string fromClient(buffer, recivedBytes);
        std::cout << buffer << endl;

        for (auto x : allClients)
        {
            if (x != client_socket)
                send(x, buffer, recivedBytes, 0);
        }
    }

    for (int i = 0; i < allClients.size(); i++)
    {
        if (allClients[i] == client_socket)
        {
            allClients.erase(allClients.begin() + i);
            break;
        }
    }
    close(client_socket);
}

int main()
{

    // Initilize the socket
    int serverSocket = socketInit();

    // Initilizeing the environment for sockaddr structure
    sockaddr_in serverAddress = socketAddressInit();


    // Bind the socket to the local port
    int x = bind(serverSocket, (sockaddr *)&serverAddress, sizeof(sockaddr));
    if (x < 0)
    {
        std::cerr << "Error binding socket\n";
        return 1;
    }
    std::cout << "Binding Successful" << endl;

    // Listen to the given port

    x = listen(serverSocket, 5);

    if (x < 0)
    {
        std::cerr << "Error listening\n";
        return 1;
    }
    std::cout << "Listning..." << endl;

    std::thread t;
    std::vector<int> allClients;
    // Accept the incoming clients
    while (true)
    {
        int client_socket;
        struct sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);
        client_socket = accept(serverSocket, (struct sockaddr *)&client_address, &client_address_size);

        if (client_socket < 0)
        {
            std::cout << "Invalid Client Socket";
        }

        std::cout << "Client Accepted" << endl;
        allClients.push_back(client_socket);

        t = std::thread(DealWithClient, client_socket, std::ref(allClients));
        t.detach();
    }

    close(serverSocket);

    return 0;
}
