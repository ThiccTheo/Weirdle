#include "Data.h"

vector<vector<string>> Data::words;
const int Data::MAX_WORD_LENGTH = 10;
const int Data::MIN_WORD_LENGTH = 3;

bool Data::init(string &&path) {
	for (int i = 0; i < MAX_WORD_LENGTH; i++) {
		vector<string> empty;
		words.push_back(empty);
	}

	fstream src;
	src.open(path, ios::in);
	if (!src.is_open()) {
		cout << "COULD NOT OPEN FILE: " << path << '\n';
		return false;
	}
	else {
		string txt;
		size_t length;

		while (getline(src, txt)) {
			length = txt.length() - 1;

			if (!(length > MAX_WORD_LENGTH) && txt[0] >= 65 && txt[0] <= 90) {
				words[length].push_back(txt);
			}
		}
		src.close();
	}

	return true;
}