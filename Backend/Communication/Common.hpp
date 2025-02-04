#pragma once
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <array>
#include <string>
#include <concepts>
#include <assert.h>
#include <thread>
#include <queue>
#include <stack>
#include <deque>
#include <mutex>
#include <string_view>
#include <type_traits>
#include <functional>
#include <fstream>
#include <filesystem>
#include "asio.hpp"
#include "asio/ssl.hpp"

template <typename T>
concept IsSocket = std::is_base_of_v<T, asio::ip::tcp::socket> ||       //checking if it's a basic socket
				   std::is_base_of_v<T, asio::ssl::stream<asio::ip::tcp::socket>>; // or a secure socket


typedef std::vector<char> ByteArray;
typedef asio::ip::tcp::socket BasicSocket;
typedef asio::ssl::stream<asio::ip::tcp::socket> SslSocket;
