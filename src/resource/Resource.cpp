#include "Resource.h"

Font Resource::comfortaa;
Texture Resource::tileTexture;
Texture Resource::lengthPromptTexture;

void Resource::load() {
	comfortaa.loadFromFile("src/resource/comfortaa.ttf");
	tileTexture.loadFromFile("src/resource/spritesheet.png");
	lengthPromptTexture.loadFromFile("src/resource/lengthPrompt.png");
}