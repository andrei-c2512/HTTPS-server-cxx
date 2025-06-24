#pragma once
#include "Thumos/Core/AbstractConnection.hpp"
#include "Thumos/Core/ClientInterface.hpp"

namespace thm::core{
    //shit's wild , so basically
    /*
            client -> needs something of type message
                       -> a type of connection that takes said message
    */

    //I hate how I cannot verify if connectionType is of type connection without having loads of template arguments
    template<message messageTypeIn , message messageTypeOut, typename connectionType>
    class BasicClient : public ClientInterface<messageTypeIn , messageTypeOut> {
    public:
            BasicClient() {}
            ~BasicClient() {
                    disconnect();
            }
            void connect(const std::string& host, int16_t port) {
                    try {
                            conn = std::make_shared<connectionType>(context , asio::ip::tcp::socket(context) , readQueue);
                            conn->connect(host, port);

                            asio::executor_work_guard<asio::io_context::executor_type> work_guard(context.get_executor());

                            contextThread = std::thread([this]() {
                                    context.run();
                            });
                    }
                    catch (std::exception& e) {
                            Log::error(e.what());
                    }
            }
            void disconnect() {
                    conn->disconnect();
                    onDisconnect();
                    context.stop();

                    if (contextThread.joinable()) contextThread.join();

                    Log::message("Disconnected from server");
            }
            bool isConnected() const noexcept { return conn->isConnected(); }

            void send(std::shared_ptr<messageTypeOut> msg) {
                    conn->send(msg);
            }
            void update() override{
                    while (readQueue.empty() == false) {
                            auto request = readQueue.front();
                            readQueue.pop_front();
                            Log::info("Processing new message...");
                            onNewMessage(request);
                    }
            }
    protected:
            using ClientInterface<messageTypeIn, messageTypeOut>::onDisconnect;
            using ClientInterface<messageTypeIn, messageTypeOut>::onNewMessage;
    protected:
            asio::io_context context;
            std::thread contextThread;

            Utility::TsQueue<std::shared_ptr<messageTypeIn>> readQueue;

            std::shared_ptr<connectionType> conn;
    };
}
