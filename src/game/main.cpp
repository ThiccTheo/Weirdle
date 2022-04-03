#include "Game.h"
#include "../data/Data.h"
#include "../resource/Resource.h"

int main(){
    if (Data::init("src/data/words.txt")) {
        srand(static_cast<unsigned int>(time(NULL)));
        Game::init();
        Resource::load();
        Game::run();
    }
    return EXIT_SUCCESS;
}