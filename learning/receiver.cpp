#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> // provides IPv4-related definitions (like AF_INET)
#include <unistd.h> // For close()

int main() {
    const uint16_t PORT = 8080;

    // STEP 1: Ask the Linux kernel to create a socket endpoint.
    // int list_fd = socket(2, 1, 0);
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd < 0) {
        std::cout << "socket creation failed\n";
        return 1;
    }

    // STEP 2: Fill out the address struct telling the OS which IP and Port to claim.
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Listen on ALL network cards (Wi-Fi, RJ45, localhost)
    server_addr.sin_port = htons(PORT);         // Convert 8080 to Big-Endian (Network Byte Order)

    if(bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cout << "bind failed\n";
        close(listen_fd);
        return 1;
    }

    // STEP 3: Mark the socket as passive so it listens for incoming connections.
    if(listen(listen_fd, 1) < 0) {
        std::cout << "listen failed\n";
        close(listen_fd);
        return 1;
    }

    std::cout << "[Receiver] Waiting for a connection on port " << PORT << "...\n";

    // STEP 4: Block (pause the program) until a client connects.
    // When your PC connects, accept() wakes up and returns a BRAND NEW socket (client_fd)
    // dedicated exclusively to talking with your PC.
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    return 0;
}