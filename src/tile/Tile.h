#pragma once
#include "../../vendor/Vendor.h"
#include "../game/Common.h"

class Tile {
public:
	static void init();
	static void draw();
	static void update();
	static const int size;
	static int guesses;
	static string hiddenWord;
private:
	int index;
	Sprite sprite;
	Text letter;
	static vector<Tile> v_tile;
	static int currentY;
	static int currentX;
	static char currentKey;
	static int keyCounter;
	static const int keyDelay;
	static bool checkValidity();
	Tile(int x, int y);
	static string addedWord;
	static void showError();
};