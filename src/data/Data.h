#pragma once
#include "../../vendor/Vendor.h"
#include "../game/Common.h"

class Data {
public:
	static bool init(string &&path);
	static vector <vector<string>> words;
	static const int MAX_WORD_LENGTH;
	static const int MIN_WORD_LENGTH;
};
