#pragma once

#include <string>

#include "Socket.hpp"

namespace proxyServer {
class Forwarder : proxyServer::Socket {
    private:
        std::string resolveDns();
        std::string fechContents();
    protected:
        std::string fetch();
        void listenLoop() override;
    public:
        Forwarder(unsigned short int t_port_number);
        ~Forwarder();
        
};
}
