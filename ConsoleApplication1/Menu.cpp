#include "Menu.h"
#include <sstream>
#include <string>
using namespace std;
using namespace sf;
//=====================================================================Main Menu (Mariham Merzek)  ====================================================================//

Menu::Menu(float width, float height)
{
    backToMenu = false;
    selectedItem = 0;
    selectedOption = 0;

    showInstructions = false;
    showOptions = false;

    keyPressed = false;
    exitSelected = false;
    playSelected = false;

    soundValue = 100;
    musicValue = 100;
    //bar
    soundBar.setPosition(windowWidth * 0.62f, windowHeight * 0.66f);
    musicBar.setPosition(windowWidth * 0.62f, windowHeight * 0.77f);

    soundBar.setFillColor(sf::Color::Red);
    musicBar.setFillColor(sf::Color::Red);

    soundBar.setSize(Vector2f(soundValue * 3, 40));
    musicBar.setSize(Vector2f(musicValue * 3, 40));

    // ================= BACKGROUND =================
    bgTexture.loadFromFile("main menu.png8(1).png");
    bg.setTexture(bgTexture);

    float scaleX = windowWidth / bgTexture.getSize().x;
    float scaleY = windowHeight / bgTexture.getSize().y;
    bg.setScale(scaleX, scaleY);

    // ================= INSTRUCTIONS =================
    instructionsTexture.loadFromFile("instructions.png");
    instructionsSprite.setTexture(instructionsTexture);
    float scalek = windowWidth / instructionsTexture.getSize().x;
    float scalez = windowHeight / instructionsTexture.getSize().y;
    instructionsSprite.setScale(scalek, scalez);

    //====================credits==============
    showCredits = false;
    creditsTexture.loadFromFile("Credits.Jpeg");
    creditsSprite.setTexture(creditsTexture);

    float scaleCX = windowWidth / creditsTexture.getSize().x;
    float scaleCY = windowHeight / creditsTexture.getSize().y;
    creditsSprite.setScale(scaleCX, scaleCY);

    // ================= SOUND =================
    clickBuffer.loadFromFile("menu_change.ogg");
    clickSound.setBuffer(clickBuffer);
    clickSound.setVolume(soundValue);

    // ================= FONT =================
    font.loadFromFile("HalloweenSlimePersonalUse-4B80D.otf");

    // ================= MENU =================
    std::string options[5] = { "Play", "Instructions", "Options", "Credits", "Exit" };

    for (int i = 0; i < 5; i++)
    {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(windowHeight * 0.07f);
        menu[i].setPosition(windowWidth * 0.65f, windowHeight * 0.55f + i * (windowHeight * 0.08f));
        menu[i].setFillColor(sf::Color::Black);
    }

    menu[0].setFillColor(sf::Color::Yellow);

    // ================= OPTIONS =================
    std::string opt[3] = { "Sound", "Music", "Back" };

    for (int i = 0; i < 3; i++)
    {
        optionsMenu[i].setFont(font);
        optionsMenu[i].setString(opt[i]);
        optionsMenu[i].setCharacterSize(windowHeight * 0.05f);
        optionsMenu[i].setPosition(windowWidth * 0.65f, windowHeight * 0.6f + i * (windowHeight * 0.1f));
        optionsMenu[i].setFillColor(sf::Color::Black);
    }

    optionsMenu[0].setFillColor(sf::Color::Yellow);
}

// ================= DRAW =================
void Menu::draw(sf::RenderWindow& window)
{
    window.draw(bg);

    if (showInstructions)
    {
        window.draw(instructionsSprite);
        window.draw(instructionsText);
    }
    else if (showOptions)
    {
        updateBars();

        for (int i = 0; i < 3; i++)
            window.draw(optionsMenu[i]);

        window.draw(soundBar);
        window.draw(musicBar);
    }
    else if (showCredits)
    {
        window.draw(creditsSprite);
    }
    else
    {
        for (int i = 0; i < 5; i++)
            window.draw(menu[i]);
    }
}

// ================= BACKGROUND ONLY =================
void Menu::drawBackground(sf::RenderWindow& window)
{
    window.draw(bg);
}

// ================= NAVIGATION =================
void Menu::MoveUp()
{
    if (showInstructions || showOptions) return;


    if (moveClock.getElapsedTime().asMilliseconds() < moveDelay)
        return;

    menu[selectedItem].setFillColor(sf::Color::Black);
    selectedItem--;

    if (selectedItem < 0)
        selectedItem = 4;

    menu[selectedItem].setFillColor(sf::Color::Yellow);

    moveClock.restart();
}
void Menu::MoveDown()
{
    if (showInstructions || showOptions) return;
    if (moveClock.getElapsedTime().asMilliseconds() < moveDelay)
        return;

    menu[selectedItem].setFillColor(sf::Color::Black);
    selectedItem++;

    if (selectedItem > 4)
        selectedItem = 0;

    menu[selectedItem].setFillColor(sf::Color::Yellow);

    moveClock.restart();
}
// ================= INPUT =================
void Menu::HandleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyReleased)
    {
        keyPressed = false;
    }

    if (event.type != sf::Event::KeyPressed)
        return;

    if (keyPressed)
        return;

    keyPressed = true;

    // ================= OPTIONS =================
    if (showOptions)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            optionsMenu[selectedOption].setFillColor(sf::Color::Black);
            selectedOption--;
            if (selectedOption < 0) selectedOption = 2;
            optionsMenu[selectedOption].setFillColor(sf::Color::Yellow);
            clickSound.play();
        }

        else if (event.key.code == sf::Keyboard::Down)
        {
            optionsMenu[selectedOption].setFillColor(sf::Color::Black);
            selectedOption++;
            if (selectedOption > 2) selectedOption = 0;
            optionsMenu[selectedOption].setFillColor(sf::Color::Yellow);
            clickSound.play();
        }

        else if (event.key.code == sf::Keyboard::Left)
        {
            if (selectedOption == 0 && soundValue > 0)
                soundValue -= 10;

            else if (selectedOption == 1 && musicValue > 0)
                musicValue -= 10;

            clickSound.setVolume(soundValue);
            clickSound.play();
        }

        else if (event.key.code == sf::Keyboard::Right)
        {
            if (selectedOption == 0 && soundValue < 100)
                soundValue += 10;

            else if (selectedOption == 1 && musicValue < 100)
                musicValue += 10;

            clickSound.setVolume(soundValue);
            clickSound.play();
        }

        else if (event.key.code == sf::Keyboard::Enter)
        {
            if (selectedOption == 2)
            {
                closeOptions();
                resetMenu();
                backToMenu = true;
            }
        }

        return;
    }

    // ================= MAIN MENU =================
    if (event.key.code == sf::Keyboard::Up)
    {
        MoveUp();
        clickSound.play();
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
        MoveDown();
        clickSound.play();
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
        if (selectedItem == 0) playSelected = true;
        else if (selectedItem == 1) openInstructions();
        else if (selectedItem == 2) openOptions();
        else if (selectedItem == 3)
        {
            showCredits = true;
        }
        else if (selectedItem == 4) exitSelected = true;
        clickSound.play();
    }
    else if (event.key.code == sf::Keyboard::Escape)
    {
        if (showInstructions)
            closeInstructions();
        else if (showOptions)
            closeOptions();
        {
            showCredits = false;
        }
    }
}

// ================= STATE =================
void Menu::openInstructions() { showInstructions = true; }
void Menu::closeInstructions() { showInstructions = false; }

void Menu::openOptions() { showOptions = true; }
void Menu::closeOptions() {
    showOptions = false;
    selectedOption = 0;
}
bool Menu::isCreditsOpen()
{
    return showCredits;
}
bool Menu::shouldExit()
{
    return exitSelected;
}
bool Menu::isPlaySelected()
{
    return playSelected;
}
bool Menu::isInstructionsOpen() { return showInstructions; }
bool Menu::isOptionsOpen() { return showOptions; }
int Menu::GetSelectedItem() { return selectedItem; }

void Menu::playClick() { clickSound.play(); }
//====================bar======================
void Menu::updateBars()
{
    soundBar.setSize(sf::Vector2f(soundValue * 3, 20));
    musicBar.setSize(sf::Vector2f(musicValue * 3, 20));
}
//==============function reset=======================
void Menu::resetPlay()
{
    playSelected = false;
}
void Menu::resetMenu()
{
    showOptions = false;
    showInstructions = false;

    selectedItem = 0;
    selectedOption = 0;

    exitSelected = false;
    playSelected = false;

    for (int i = 0; i < 5; i++)
        menu[i].setFillColor(sf::Color::Black);

    menu[0].setFillColor(sf::Color::Yellow);
}
void Menu::resetBackToMenu()
{
    backToMenu = false;
}

bool Menu::shouldBackToMenu() const
{
    return backToMenu;
}