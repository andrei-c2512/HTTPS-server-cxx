#pragma once
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <array>
#include <string>
#include <concepts>
#include "Common.hpp"
#include "asio.hpp"
#include "asio/ssl.hpp"

template <typename T>
concept IsSocket = std::is_base_of_v<T, asio::ip::tcp::socket> ||       //checking if it's a basic socket
				   std::is_base_of_v<T, asio::ssl::stream<asio::ip::tcp::socket>>; // or a secure socket


typedef std::vector<char> ByteArray;
typedef asio::ip::tcp::socket BasicSocket;
typedef asio::ssl::stream<asio::ip::tcp::socket> SslSocket;


#define WEBPROJ_CLEANUP_ENABLED true