#include "Keyboard.h"
#include "../resource/Resource.h"
#include "../game/Game.h"

vector<KEY> KEY::keyVector;

KEY::KEY(int value) {
    letter = value + 65;
    text.setFont(Resource::comfortaa);
    text.setString(letter);
    text.setFillColor(Color::Black);
    text.setCharacterSize(25);
    box.setSize(Vector2f(30.f, 30.f));
    box.setOutlineColor(Color::Black);
    box.setOutlineThickness(2.f);
    box.setFillColor(Color::White);
}
//ASCII VALUE: A = 65, Z = 90
//Get letter and add 65 to find the char equivalent

void KEY::init() {
    if (keyVector.size() > 0) {
        keyVector.clear();
    }
    for (int i = 0; i <= 25; i++) {
        keyVector.push_back(i);
        if (i < 13) {
            keyVector[i].box.setPosition(static_cast<float>(Game::window.getSize().x / 2.f - 234.f + (i * 36)), Game::window.getSize().y - 100.f);
        }
        else {
            keyVector[i].box.setPosition(static_cast<float>(Game::window.getSize().x / 2.f - 234.f + ((i - 13) * 36.f)), Game::window.getSize().y - 50.f);
        }
        keyVector[i].text.setPosition(keyVector[i].box.getPosition().x + 5.f, keyVector[i].box.getPosition().y);
    }
}

void KEY::draw() {
    for (size_t i = 0; i < keyVector.size(); i++) {
        Game::window.draw(keyVector[i].box);
        Game::window.draw(keyVector[i].text);
    }
}