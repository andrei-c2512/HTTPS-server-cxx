#pragma once
#include "Utility/Utility.hpp"

namespace thm::web{
    using namespace util;
    class DataCompressor {
    public:
            DataCompressor() = default;
            DataCompressor(std::span<char> data , file::CompressionType type) {
                    init(data, type);
            }
            void init(std::span<const char> data0, file::CompressionType type0) {
                    data = data0;
                    type = type0;
            }
            [[nodiscard]] std::vector<char> compress() const {
                    switch (type) {
                    case file::CompressionType::NONE:
                            return std::vector<char>(std::begin(data) , std::end(data));
                    default:
                            return {'f' , 'l'};
                    }
            }
            
    private:
            std::span<const char> data;
            file::CompressionType type;
    };
}
