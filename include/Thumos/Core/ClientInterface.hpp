#pragma once
#include <string>
#include <memory>

namespace thm::core{
    template <typename messageTypeIn , typename messageTypeOut>
    class ClientInterface {
    public:
            virtual void connect(const std::string& host, int16_t port) = 0;
            virtual void disconnect() = 0;
            virtual bool isConnected() const = 0;
            virtual void send(std::shared_ptr<messageTypeOut> msg) = 0;
            virtual void update() = 0;
    protected:
            virtual void onDisconnect() {}
            virtual void onNewMessage(std::shared_ptr<messageTypeIn> message) {}
    };
}
