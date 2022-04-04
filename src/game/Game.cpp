#include "Game.h"
#include "../data/Data.h"
#include "../resource/Resource.h"
#include "../tile/Tile.h"
#include "../keyboard/Keyboard.h"

RenderWindow Game::window;
const unsigned int Game::WIDTH = 300;
const unsigned int Game::HEIGHT = 300;
int Game::wordLength = 0;
bool Game::isLost;
bool Game::isWon;

void Game::init() {
    window.create(VideoMode(WIDTH, HEIGHT), "Weirdle", Style::Close);
    window.setFramerateLimit(60);
}

void Game::getWordLength() {
    Sprite prompt;
    prompt.setTexture(Resource::lengthPromptTexture);
    int keyCount = 8;
    int temp = 3;
    Text lengthTxt;
    Text title;
    Text selectTxt;
    selectTxt.setFont(Resource::comfortaa);
    selectTxt.setCharacterSize(20);
    selectTxt.setFillColor(Color::Black);
    selectTxt.setString("SELECT WORD LENGTH:\n        (ARROW KEYS)");
    title.setFont(Resource::comfortaa);
    title.setCharacterSize(60);
    title.setFillColor(Color::Red);
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(1.f);
    title.setString("WEIRDLE");
    lengthTxt.setFont(Resource::comfortaa);
    lengthTxt.setCharacterSize(50);
    lengthTxt.setFillColor(Color::Black);
    title.setPosition(10.f, 0.f);
    selectTxt.setPosition(24.f, 82.f);

    while (!(Keyboard::isKeyPressed(Keyboard::Enter)) && window.isOpen()) {
        window.clear(Color::White);
        window.draw(selectTxt);
        window.draw(title);
        window.draw(prompt);
        lengthTxt.setString(to_string(temp));
        if (lengthTxt.getString() != "10") {
            lengthTxt.setPosition(130.f, 140.f);
        }
        else {
            lengthTxt.setPosition(122.f, 140.f);
        }
        window.draw(lengthTxt);
        window.display();

        keyCount++;
        if (temp > Data::MIN_WORD_LENGTH && keyCount >= 8 && Keyboard::isKeyPressed(Keyboard::Left)) {
            temp--;
            keyCount = 0;
        }
        else if (temp < Data::MAX_WORD_LENGTH && keyCount >= 8 && Keyboard::isKeyPressed(Keyboard::Right)) {
            temp++;
            keyCount = 0;
        }
    }

    Game::wordLength = temp;
    View view;
    window.setSize(Vector2u(static_cast<unsigned int>(Data::MAX_WORD_LENGTH * Tile::size), static_cast<unsigned int>((Game::wordLength * Tile::size) + Tile::size) + 120));
    view = window.getView();
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
    view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    window.setView(view);
}

void Game::gameOver(bool flag) {
    if (flag) {
        Time delay = seconds(2);
        sleep(delay);
        window.setSize(Vector2u(WIDTH, HEIGHT));
        window.setView(window.getDefaultView());

        Text winText;
        winText.setFont(Resource::comfortaa);
        winText.setFillColor(Color::Red);
        winText.setOutlineColor(Color::Black);
        winText.setOutlineThickness(1.f);
        winText.setCharacterSize(40);
        winText.setString("WEIRDLE IN " + to_string(Tile::guesses));
        winText.setPosition(10.f, 20.f);

        Text loseText;
        loseText.setFont(Resource::comfortaa);
        loseText.setFillColor(Color::Red);
        loseText.setOutlineColor(Color::Black);
        loseText.setOutlineThickness(1.f);
        loseText.setCharacterSize(40);
        loseText.setString("WORD WAS:");
        loseText.setPosition(23.f, 0.f);
        
        Text wordText;
        wordText.setFont(Resource::comfortaa);
        wordText.setFillColor(Color::Red);
        wordText.setOutlineColor(Color::Black);
        wordText.setOutlineThickness(1.f);
        wordText.setCharacterSize(30);
        wordText.setLetterSpacing(2);
        wordText.setString(Tile::hiddenWord);
        wordText.setOrigin(wordText.getLocalBounds().width / 2.f, wordText.getLocalBounds().height / 2.f);
        wordText.setPosition(window.getSize().x / 2.f, 60.f);

        Text continueText;
        continueText.setFont(Resource::comfortaa);
        continueText.setFillColor(Color::Black);
        continueText.setString("PLAY AGAIN?\n    (SPACE)");
        continueText.setPosition(50.f, 85.f);
       
        while (!(Keyboard::isKeyPressed(Keyboard::Space))) {
            window.clear(Color::White);
            if (isWon) {
                window.draw(winText);
            }
            else if (isLost) {
                window.draw(loseText);
                window.draw(wordText);
            }
            window.draw(continueText);
            window.display();
        }
        run();
    }
}

void Game::run() {
    cout << "\033[H\033[J";
    getWordLength();

    Tile::init();
    KEY::init();
    isLost = false;
    isWon = false;

    bool flag = true;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::White);
        Tile::draw();
        KEY::draw();
        window.display();
        if (!isLost && !isWon) {
            Tile::update();
        }
        else {
            gameOver(flag);
            flag = false;
        }
    }
}