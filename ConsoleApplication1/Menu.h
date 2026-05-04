#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
struct Menu
{

    // ================= BACKGROUND =================
    sf::Texture bgTexture;
    sf::Sprite bg;

    // ================= FONT & TEXT =================
    sf::Font font;
    sf::Text menu[5];

    // ================= INSTRUCTIONS =================
    sf::Text instructionsText;
    sf::Texture instructionsTexture;
    sf::Sprite instructionsSprite;
    // ================= CREDITS =================
    sf::Texture creditsTexture;
    sf::Sprite creditsSprite;
    bool showCredits;
    bool isCreditsOpen();
    // ================= STATE =================
    int selectedItem;
    bool showInstructions;
    bool keyPressed;
    bool exitSelected;
    bool playSelected;
    bool backToMenu;
    // ================= SOUND =================
    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;
    //===========options====================
    sf::Text optionsMenu[3];
    int selectedOption;
    bool showOptions;
    int soundValue;
    int musicValue;
    // to manage مينو
    sf::Clock moveClock;
    float moveDelay = 190.f;
    //to manage options 
    float navDelay = 190.f;
    float valueDelay = 190.f;
    //bar
    RectangleShape soundBar;
    RectangleShape musicBar;

    float windowWidth = 800.0f;
    float windowHeight = 600.0f;
    // ================= CONSTRUCTOR =================
    Menu(float width, float height);
    // ================= DRAW =================
    void draw(sf::RenderWindow& window);
    // ================= INPUT =================
    void HandleInput(sf::Event& event);
    // ================= NAVIGATION =================
    void MoveUp();
    void MoveDown();
    // ================= INSTRUCTIONS CONTROL =================
    void openInstructions();
    void closeInstructions();
    bool isInstructionsOpen();
    // ================= GETTERS =================
    int GetSelectedItem();
    bool isPlaySelected();
    void resetPlay();
    void drawBackground(sf::RenderWindow& window);
    //================options=================
    void openOptions();
    void closeOptions();
    bool isOptionsOpen();
    bool shouldExit();
    void playClick();
    int getSound() { return soundValue; }
    int getMusic() { return musicValue; }
    void resetMenu();
    //===========bar=========
    void updateBars();

    void resetBackToMenu();
    bool shouldBackToMenu() const;
};