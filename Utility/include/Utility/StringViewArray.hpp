#pragma once
#include "Common.hpp"

namespace util::ds{
    template<size_t Size>
    class StringViewArray {
    public:
            template<typename... Args>
                    requires (sizeof...(Args) == Size)
            constexpr StringViewArray(Args&&... args) : arr{std::forward<Args>(args)...}
            {}
            std::string copyAt(int8_t i) const noexcept{
                    assert(i >= 0 && i < arr.size());
                    return std::string(arr[i].data());
            }
            std::string_view at(int8_t i) const noexcept {
                    assert(i >= 0 && i < arr.size());
                    return arr[i].data();
            }
    public:
            std::array<std::string_view, Size> arr;
    };
}
