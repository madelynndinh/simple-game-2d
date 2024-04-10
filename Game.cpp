#include "Game.h"
#include <iostream>

void Game::initVariables() { 
    this->window = nullptr;
    //Game logic
int points;
float enemySpawnTimer;
float enemySpawnTimerMax;
int maxEnemies;
this-> points = 0;
this-> enemySpawnTimer = 0.f;
this-> enemySpawnTimerMax = 1000.f;
this-> maxEnemies = 5;
 };

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
void Game::spawnEnemy(){
/* 
return void

Spawn enemies and sets their colors and positions
- sets a random position
- sets a random color
- adds enemy to the vector
*/

this -> enemy.setPosition(
    //datatype conversion
    static_cast<float>(rand() % static_cast<int>(this -> window-> getSize().x - this -> enemy.getSize().x)),
0.f
);
this -> enemy.setFillColor(sf::Color::Green);

//Spawn the enemy
this -> enemies.push_back(this -> enemy);

//Remove enemies at end of screen

};
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
  void Game::updateMousePositions(){
    /*
    Updates the mouse positions:
    - Mouse position relative to window (Vector2i)
    */

   this -> mousePosWindow = sf::Mouse::getPosition(*this -> window);
  };
void Game::updateEnemies(){
    /*
     return void

     Updates thee enemy spawn timer and spawns enemies when 
     the total amount of enemies is smaller than the maximum

     Moves the enemies downwards
     Removes the enemies at the edge of the screen

    */


    //Updating the timer for enemy spawning
    if(this->enemies.size()<this-> maxEnemies)
   {if(this-> enemySpawnTimer >= this -> enemySpawnTimerMax)
   {
    //Spawn the enemy and reset the timer
    this -> spawnEnemy();
    this ->enemySpawnTimer = 0.f;
   }
   else
   this -> enemySpawnTimer+= 1.f;
   }

   //Move the enemies
   for (auto &e: this -> enemies)
   {
    e.move(0.f,5.f); //Move downwards
   }
   

}


void Game::update() { 
    this->pollEvent(); 
    //Update mouse position
this -> updateMousePositions();
    //Update enemies
     this -> updateEnemies();
}

  void Game::renderEnemies(){
 //Rendering all the enemies
   for (auto &e: this -> enemies)
   {
    this-> window -> draw(e);
   }
  };


void Game::render() {
  /*
  - clear old frame
  - render object
  -display frame in window
  Render the game objects
  */
  this->window->clear();

  // Draw game objects
  this->renderEnemies();

  this->window->display();
}


