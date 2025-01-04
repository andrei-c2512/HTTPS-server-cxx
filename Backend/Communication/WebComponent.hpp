#pragma once
#include "FileHelper.hpp"

namespace WebDelivery {
	struct Component {
		std::string name;
		FileHelper::CompressionType compressionMask = FileHelper::CompressionType(0);
		FileHelper::FileFormat format = FileHelper::FileFormat(0);
	};
};
