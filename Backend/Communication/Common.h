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
#include <deque>
#include <mutex>
#include <string_view>
#include "asio.hpp"



#ifdef DEBUG
#define DEBUG_MSG(x) x
#else
#define DEBUG_MSG(x)
#endif

typedef std::vector<char> ByteArray;
