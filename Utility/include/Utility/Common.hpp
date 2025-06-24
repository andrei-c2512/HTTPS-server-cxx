#pragma once
#define OPENSSL_API_COMPAT 0x10100000L

/* Useful stuff from the standard library*/
/* ===================================== */
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <array>
#include <string>
#include <cstring>
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
#include <span>
#include <iostream>
#include <experimental/source_location>
/* ===================================== */
/* Rapid json */
/* ===================================== */
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
/* ===================================== */
/* OpenSSL */
/* ===================================== */
#include "openssl/bio.h"
#include "openssl/evp.h"
/* ===================================== */

