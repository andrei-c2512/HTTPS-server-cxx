#pragma once
#include "Thumos/Core/AbstractServer.hpp"

namespace thm::core{
    //will only work for connection classes that use BasicSocket
    template<typename connection, typename messageTypeIn , typename messageTypeOut>
    class BasicServer : public AbstractServer<connection , messageTypeIn , messageTypeOut>{
    public:
            BasicServer(int16_t port)
                    :AbstractServer<connection, messageTypeIn , messageTypeOut>(port)
            {}
            

            void listen() override{
                    asioAcceptor.async_accept(
                            [this](std::error_code ec, asio::ip::tcp::socket socket) {
                                    util::log::message("Listening...");
                                    if (!ec) {
                                            util::log::info("New connection");
                                            std::shared_ptr<connection> conn = std::make_shared<connection>(asioContext, std::move(socket), readQueue);
                                            list.addNew(conn);
                                            conn->listen();
                                    }
                                    else {
                                            util::log::error("Connection error: " + ec.message());
                                    }
                                    listen();
                            }
                    );
            }
            using AbstractServer<connection, messageTypeIn , messageTypeOut>::update;
            using AbstractServer<connection, messageTypeIn , messageTypeOut>::stop;
            using AbstractServer<connection, messageTypeIn , messageTypeOut>::start;
    protected:
            using AbstractServer<connection, messageTypeIn , messageTypeOut>::asioAcceptor;
            using AbstractServer<connection, messageTypeIn , messageTypeOut>::readQueue;
            using AbstractServer<connection, messageTypeIn , messageTypeOut>::list;
            using AbstractServer<connection, messageTypeIn , messageTypeOut>::asioContext;
    };
}
