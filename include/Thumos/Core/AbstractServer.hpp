#pragma once
#include "Thumos/Core/Common.hpp"
#include "ServerConnectionList.hpp"


namespace thm::core{
    /* This class uses the Strategy Pattern, or Policy based design to be more precise */
    using namespace util;
    template<typename connection, typename messageTypeIn , typename messageTypeOut>
    class AbstractServer {
    public:
            AbstractServer(int16_t port)
                    :asioAcceptor(asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
            {}
            virtual ~AbstractServer() {
                    stop();
            }
            virtual void start() {
                    if (abort) {
                            log::error("Server is COOKED , cannot start");
                            return;
                    }
                    try {
                            listen();
                            log::message("Listening...");
                            onStart();
                            contextThread = std::thread([this]() { 
                                    asioContext.run(); 
                                    });
                            
                    }
                    catch (const std::exception& e) {
                            log::error(e.what());
                    }

                    log::message("Server started");
            }
            virtual void stop() {
                    if (stopped == false) {
                            onStop();
                            asioContext.stop();

                            if (contextThread.joinable()) contextThread.join();

                            log::message("Server stopped");
                            stopped = true;
                    }
            }
            virtual void listen() {}

            void update(){
                    while (readQueue.empty() == false) {
                            auto request = readQueue.front();
                            readQueue.pop_front();
                            log::info("Processing new message...");
                            onNewMessage(request);
                    }
            }
    protected: 
            /* I don't like the '= 0' thing, so I usually put an empty definition*/
            virtual void onNewMessage(std::shared_ptr<messageTypeIn> message) {
                log::error("Not implemented");
            }
            virtual void onNewConnection(std::shared_ptr<connection> conn) {}
            virtual void onStop() {}
            virtual void onStart() {}
    protected:
            asio::io_context asioContext;
            std::thread contextThread;

            asio::ip::tcp::acceptor asioAcceptor;
            util::ds::TsQueue<std::shared_ptr<messageTypeIn>> readQueue;
            ServerConnectionList<connection , messageTypeOut> list;

            //the abort flag will be used by super classes when some condition for starting isn't met
            // ex: failed to set certificate for a secure server
            bool abort = false;
            bool stopped = false;
    };
}
