#include "Game.h"
#include <iostream>

void Game::initVariables() { this->window = nullptr; };

void Game::initWindow() {
     // Get the size of screen
  this->videoMode.height = 600;
  this->videoMode.width = 680;
  this->window = new sf::RenderWindow(this -> videoMode, "Game 1",sf::Style::Titlebar | sf::Style::Close);
  this->window->setFramerateLimit(144);
};

void Game::initEnemies() {
  this->enemy.setPosition(10.f,10.f);
  this->enemy.setSize(sf::Vector2f(200.f, 200.f));
  this->enemy.setScale(sf::Vector2f(0.5f,0.5f));
  this->enemy.setFillColor(sf::Color::Cyan);
  this->enemy.setOutlineColor(sf::Color::Green);
  this->enemy.setOutlineThickness(1.f);
}

// Constructor / Destructor
Game::Game() {
  this->initVariables();
  this->initWindow();
  this -> initEnemies();
}

Game::~Game() {
  // Avoid memory leak
  delete this->window;
}

// Accessors
const bool Game::running() const { return this->window->isOpen(); };

// Functions
void Game::pollEvent() {
  // Event polling
  while (this->window->pollEvent(this->ev)) {
    {
      switch (this->ev.type) {
        case sf::Event::Closed:
          this->window->close();
          break;

        case sf::Event::KeyPressed:
          if (this->ev.key.code == sf::Keyboard::Escape) this->window->close();
          break;
      }
    }
  }
}


void Game::update() { 
    this->pollEvent(); 

    //Update mouse position
    //Relative to screen
    std::cout << "Mouse pos: " << sf::Mouse::getPosition().x <<
    " "<<sf::Mouse::getPosition().y <<"\n";
    

    //Relative to window
    std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this -> window).x <<
    " "<<sf::Mouse::getPosition(*this -> window).y <<"\n";
    }


void Game::render() {
  /*
  - clear old frame
  - render object
  -display frame in window
  Render the game objects
  */
  this->window->clear();

  // Draw game objects
  this->window->draw(this->enemy);

  this->window->display();
}


