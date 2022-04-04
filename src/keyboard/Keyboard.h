#pragma once
#include "../../vendor/Vendor.h"
#include "../game/Common.h"

class KEY {
public:
	char letter;
	RectangleShape box;
	static vector<KEY> keyVector;
	static void init();
	static void draw();
private:
	KEY(int value);
	Text text;
};