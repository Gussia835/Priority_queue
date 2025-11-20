#pragma once
#include <string>


struct LengthComparator {
	bool operator() (const std::string& a, const std::string& b) const
	{
		return a.length() > b.length();
	}
};
