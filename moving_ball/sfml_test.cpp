#include <SFML/Graphics.hpp>

class Game
{
    private:
        void     processEvents(); 
        void     update(sf::Time TimePerFrame);
        void     render();
        
        sf::RenderWindow mWindow;
        sf::Texture texture;
        sf::Sprite mPlayer;

        void     handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        bool     isMovingUp, isMovingDown, isMovingLeft, isMovingRight; 
        float    playerMovement;
        sf::Time    TimePerFrame;

    public:
                Game();
        void    run();

};

Game::Game()
: mWindow(sf::VideoMode(640, 320), "Moving Ball")
, isMovingUp(false), isMovingDown(false), isMovingLeft(false), isMovingRight(false)
, playerMovement(150.f)
, TimePerFrame(sf::seconds(1.f/15.f))
{
    texture.loadFromFile("/home/gysk/Projetos/SFML-Experiments/moving_ball/spaceship.png");
    mPlayer.setTexture(texture);
    mPlayer.setPosition(150.f, 150.f);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
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

void Game::update(sf::Time TimePerFrame)
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
    mPlayer.move(movement * TimePerFrame.asSeconds());
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
