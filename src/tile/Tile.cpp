#include "Tile.h"
#include "../game/Game.h"
#include "../resource/Resource.h"
#include "../data/Data.h"
#include "../keyboard/Keyboard.h"

vector<Tile> Tile::v_tile;
const int Tile::size = 60;
string Tile::hiddenWord = "";
int Tile::currentX = 0;
int Tile::currentY = 0;
const int Tile::keyDelay = 8;
int Tile::keyCounter = 8;
char Tile::currentKey = ' ';
int Tile::guesses = 0;

Tile::Tile(int x, int y) {
	sprite.setTexture(Resource::tileTexture);
	sprite.setTextureRect(IntRect(0, 0, 60, 60));
	x *= size;
	y *= size;
	sprite.setPosition(static_cast<float>(x + (Game::window.getSize().x / 2 - Game::wordLength * 30)), static_cast<float>(y));
	letter.setFont(Resource::comfortaa);
	letter.setFillColor(Color::Black);
	letter.setPosition(sprite.getPosition().x + 18.f, sprite.getPosition().y + 15.f);
	letter.setString("");
}

void Tile::init() {
	if (v_tile.size() > 0) {
		v_tile.clear();
	}
	currentX = 0;
	currentY = 0;
	hiddenWord = "";
	currentKey = ' ';
	guesses = 0;

	for (int i = 0; i < Game::wordLength + 1; i++) {
		for (int j = 0; j < Game::wordLength; j++) {
			v_tile.push_back(Tile(j, i));
		}
	}

	hiddenWord = Data::words[Game::wordLength - 1][rand() % Data::words[Game::wordLength-1].size()];
}

void Tile::draw() {
	for (size_t i = 0; i < v_tile.size(); i++) {
		Game::window.draw(v_tile[i].sprite);
		Game::window.draw(v_tile[i].letter);
	}
}

//ASCII VALUE: A = 65, Z = 90
//Get letter and add 65 to find the char equivalent
void Tile::update() {
	keyCounter++;
	for (int i = Keyboard::A; i <= Keyboard::Z; i++) {
		if (keyCounter >= keyDelay && Keyboard::isKeyPressed(static_cast<Keyboard::Key>(i))) {
			currentKey = i + 65;
			keyCounter = 0;
			if (currentX < Game::wordLength) {
				v_tile[currentX + (currentY * Game::wordLength)].letter.setString(currentKey);
				v_tile[currentX + (currentY * Game::wordLength)].index = i;
				currentX++;
			}

			break;
		}
	}

	if (keyCounter >= keyDelay && Keyboard::isKeyPressed(Keyboard::LBracket)) {
		cout << hiddenWord << '\n';
		keyCounter = 0;
	}

	if (keyCounter >= keyDelay && currentX >= Game::wordLength - 1 && Keyboard::isKeyPressed(Keyboard::Enter)) {
		if (checkValidity()) {
			string temp = hiddenWord;
			for (size_t i = 0; i < hiddenWord.length(); i++) {
				if (v_tile[i + (currentY * Game::wordLength)].letter.getString() == hiddenWord[i]) {
					v_tile[i + (currentY * Game::wordLength)].sprite.setTextureRect(IntRect(180, 0, 60, 60));
					temp[i] = '_';
					KEY::keyVector[v_tile[i + (currentY * Game::wordLength)].index].box.setFillColor(Color(106, 170, 100));
				}
			}
			for (size_t i = 0; i < hiddenWord.length(); i++) {
				for (size_t j = 0; j < hiddenWord.length(); j++) {
					if (v_tile[i + (currentY * Game::wordLength)].letter.getString() == temp[j]) {
						temp[j] = '_';
						v_tile[i + (currentY * Game::wordLength)].sprite.setTextureRect(IntRect(120, 0, 60, 60));
						if (KEY::keyVector[v_tile[i + (currentY * Game::wordLength)].index].box.getFillColor() != Color(106, 170, 100)) {
							KEY::keyVector[v_tile[i + (currentY * Game::wordLength)].index].box.setFillColor(Color(201, 180, 104));
						}
					}
				}
				if (v_tile[i + (currentY * Game::wordLength)].sprite.getTextureRect() == IntRect(0, 0, 60, 60)) {
					auto& tile = v_tile[i + (currentY * Game::wordLength)];
					v_tile[i + (currentY * Game::wordLength)].sprite.setTextureRect(IntRect(60, 0, 60, 60));
					if (KEY::keyVector[tile.index].box.getFillColor() != Color(106, 170, 100) && KEY::keyVector[tile.index].box.getFillColor() != Color(201, 180, 104)) {
						KEY::keyVector[v_tile[i + (currentY * Game::wordLength)].index].box.setFillColor(Color(120, 124, 126));
					}
				}
			}

			string check;
			for (size_t i = 0; i < temp.length(); i++) {
				check += '_';
			}
			if (check == temp) {
				Game::isWon = true;
			}

			if (currentY < Game::wordLength) {
				currentY++;
				currentX = 0;
				keyCounter = 0;
				guesses++;
			}
			else {
				guesses++;
				if (check == temp) {
					Game::isWon = true;
				}
				else if (check != temp) {
					Game::isLost = true;
				}
			}
		}
	}

	if (keyCounter >= keyDelay && Keyboard::isKeyPressed(Keyboard::Backspace)) {
		if (currentX > Game::wordLength) {
			currentX = Game::wordLength;
		}
		if (currentX > 0) {
			currentX--;
		}
		v_tile[currentX + (currentY * Game::wordLength)].letter.setString(' ');
		keyCounter = 0;
	}
}

bool Tile::checkValidity() {
	string temp;
	for (int i = 0; i < Game::wordLength; i++) {
		temp += v_tile[i + (currentY * Game::wordLength)].letter.getString();
	}
	
	for (size_t i = 0; i < Data::words[Game::wordLength - 1].size(); i++) {
		if (temp == Data::words[Game::wordLength - 1][i]) {
			return true;
		}
	}
	return false;
}