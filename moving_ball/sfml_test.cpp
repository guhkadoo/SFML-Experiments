#include <SFML/Graphics.hpp>

class Game
{
    private:
        void     processEvents(); 
        void     update(sf::Time deltaTime);
        void     render();
        
        sf::RenderWindow mWindow;
        sf::CircleShape mPlayer;

        void     handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        bool     isMovingUp, isMovingDown, isMovingLeft, isMovingRight; 
        float    playerMovement;

    public:
                Game();
        void    run();

};

Game::Game()
: mWindow(sf::VideoMode(640, 320), "Moving Ball")
, mPlayer()
, isMovingUp(false), isMovingDown(false), isMovingLeft(false), isMovingRight(false)
, playerMovement(150.f)
{
    mPlayer.setRadius(50.f);
    mPlayer.setFillColor(sf::Color(100, 134, 32));
    mPlayer.setPosition(320, 160);
}

void Game::run()
{
    sf::Clock clock;
    while(mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false); 
                break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if(isMovingUp)
        movement.y -= playerMovement;
    if(isMovingDown)
        movement.y += playerMovement;
    if(isMovingLeft)
        movement.x -= playerMovement;
    if(isMovingRight)
        movement.x += playerMovement;
    mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::W)
        isMovingUp = isPressed;
    else if(key == sf::Keyboard::S)
        isMovingDown = isPressed;
    else if(key == sf::Keyboard::A)
        isMovingLeft = isPressed;
    else if(key == sf::Keyboard::D)
        isMovingRight = isPressed;
}

int main(int argc, char *argv[])
{
    Game game;
    game.run();

    return 0;
}
