#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

using namespace std;
int port = 8080;

void sendMessage(int self_socket)
{
    std::cout << "Enter your name : ";
    string name;
    std::cin >> name;
    string message;
    while (true)
    {
        char test[1024];
        std::getline(std::cin, message);
        message = name + " : " + message;
        int bytesSent;
        bytesSent = send(self_socket, message.c_str(), message.length(), 0);
        if (bytesSent <= 0)
        {
            cout << "Error\n";
            break;
        }
    }
    close(self_socket);
}
void reciveMessage(int self_socket)
{
    char buffer[1024];
    while (true)
    {
        int recivedBytes = read(self_socket, buffer, 1024);
        string fromClient = string(buffer, recivedBytes);
        std::cout << fromClient << endl;
    }
    close(self_socket);
}

int main()
{
    int self_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (self_socket < 0)
    {
        cout << "Error creating socket\n";
    }

    sockaddr_in server_address;
    server_address.sin_port = htons(port);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    // self_address.sin_addr.s_addr=

    int x = connect(self_socket, (sockaddr *)&server_address, sizeof(sockaddr));
    if (x < 0)
    {
        cout << "Error coneecting \n";
        close(self_socket);
        return 1;
    }

    cout << "Connected to server..." << endl;

    // Send and recive

    std::thread sendThread;
    std::thread reciveThread;

    string message;

    sendThread = thread(sendMessage, self_socket);
    reciveThread = thread(reciveMessage, self_socket);
    sendThread.join();
    reciveThread.join();

    close(self_socket);

    return 0;
}
