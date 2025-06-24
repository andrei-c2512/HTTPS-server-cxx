#pragma once
#include "Utility/Utility.hpp"

namespace thm::web{
        using namespace util;
	struct Component {
		std::string name;
		file::CompressionType compressionMask = file::CompressionType(0);
		file::FileFormat format = file::FileFormat(0);
	};
};
