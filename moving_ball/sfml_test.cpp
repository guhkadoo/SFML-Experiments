#include <SFML/Graphics.hpp>
#include <memory>
#include <assert.h>

namespace Textures
{
    enum ID { Landscape, Airplane, Missile };
}

class TextureHolder
{
    private:
        std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
    public:
        void load(Textures::ID id, const std::string& filename);
        sf::Texture& get(Textures::ID id);
        const sf::Texture& get(Textures::ID id) const;

};

void TextureHolder::load(Textures::ID id, const std::string& filename)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if(!texture->loadFromFile(filename))
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

    auto inserted = mTextureMap.insert(std::make_pair(id, std::move(texture)));
    assert(inserted.second);
};

sf::Texture& TextureHolder::get(Textures::ID id)
{
    auto found = mTextureMap.find(id); 
    assert(found != mTextureMap.end());

    return *found->second;
}

const sf::Texture& TextureHolder::get(Textures::ID id) const
{
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());

    return *found->second;
}

class Game
{
    private:
        void     processEvents(); 
        void     update(sf::Time TimePerFrame);
        void     render();
        
        sf::RenderWindow mWindow;
        TextureHolder textures;
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
    textures.load(Textures::Airplane, "/home/gysk/Projetos/SFML-Experiments/moving_ball/spaceship.png");
    mPlayer.setTexture(textures.get(Textures::Airplane));
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
