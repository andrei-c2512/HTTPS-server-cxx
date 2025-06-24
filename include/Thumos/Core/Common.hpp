#pragma once
#include "asio.hpp"
#include "asio/ssl.hpp"
#include "Utility/Utility.hpp"

template <typename T>
concept IsSocket = std::is_base_of_v<T, asio::ip::tcp::socket> ||       //checking if it's a basic socket
				   std::is_base_of_v<T, asio::ssl::stream<asio::ip::tcp::socket>>; // or a secure socket


typedef std::vector<char> ByteArray;
typedef asio::ip::tcp::socket BasicSocket;
typedef asio::ssl::stream<asio::ip::tcp::socket> SslSocket;


#define WEBPROJ_CLEANUP_ENABLED true
