#include "Socket.hpp"
#include "Logger.hpp"
#include <unistd.h>
#include <cstring>

proxyServer::Socket::Socket(unsigned short int t_port_number) 
    : socket_fd(-1), port_number(t_port_number), running(false) {}

proxyServer::Socket::~Socket() {
    closeSocket();
}

bool proxyServer::Socket::createSocket(int socket_type) {
    // Verificar si ya existe un socket abierto
    if (socket_fd != -1) {
        closeSocket();
    }

    // Crear nuevo socket
    socket_fd = socket(AF_INET, socket_type, 0);
    if (socket_fd == -1) {
        Logger::log("Failed to create socket: " + std::string(strerror(errno)), 
                    Logger::LogType::ERROR);
        return false;
    }

    return true;
}

bool proxyServer::Socket::setSocketTimeout(int seconds) {
    if (socket_fd == -1) {
        Logger::log("Cannot set timeout on invalid socket", Logger::LogType::ERROR);
        return false;
    }

    struct timeval timeout;
    timeout.tv_sec = seconds;
    timeout.tv_usec = 0;

    // Establecer timeout para envío y recepción
    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        Logger::log("Failed to set receive timeout: " + std::string(strerror(errno)), 
                    Logger::LogType::ERROR);
        return false;
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) {
        Logger::log("Failed to set send timeout: " + std::string(strerror(errno)), 
                    Logger::LogType::ERROR);
        return false;
    }

    return true;
}

void proxyServer::Socket::closeSocket() {
    if (socket_fd != -1) {
        close(socket_fd);
        Logger::log("Socket closed: " + std::to_string(socket_fd), 
                    Logger::LogType::SUCCESS);
        socket_fd = -1;
        running = false;
    }
}
