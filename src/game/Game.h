#pragma once
#include "Common.h"
#include "../../vendor/Vendor.h"

class Game {
public:
	static void init();
	static void run();
	static void getWordLength();
	static RenderWindow window;
	static const unsigned int HEIGHT;
	static const unsigned int WIDTH;
	static int wordLength;
	static bool isWon;
	static bool isLost;
	static void gameOver(bool flag);
};