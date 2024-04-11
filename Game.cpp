#include "Game.h"

#include <iostream>

void Game::initVariables() {
  this->window = nullptr;
  // Game logic
  this->endGame=false;
  this->points = 0;
  this->health = 10;
  this->enemySpawnTimerMax = 10.f;  // speed up enemy sp
  this->enemySpawnTimer = 0.f;
  this->maxEnemies = 10;
  this->mouseHeld = false;
};

void Game::initWindow() {
  // Get the size of screen
  this->videoMode.height = 600;
  this->videoMode.width = 800;
  this->window = new sf::RenderWindow(this->videoMode, "Game 1",
                                      sf::Style::Titlebar | sf::Style::Close);
  this->window->setFramerateLimit(60);
}
void Game::initFonts(){
    if(this->font.loadFromFile("Bungee_Spice/BungeeSpice-Regular.ttf")){
        std::cout<<"ERROR::GAME::INITFONTS::Failed to load font!"<<"\n";
    }
};

 void Game::initText(){
    this->uiText.setFont(this->font); //makes the text show up on the screen
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::Red);
    this->uiText.setString("NONE");
 };

void Game::initEnemies() {
  this->enemy.setPosition(10.f, 10.f);
  this->enemy.setSize(sf::Vector2f(100.f, 100.f));
  this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));

  this->enemy.setFillColor(sf::Color::Cyan);
  this->enemy.setOutlineColor(sf::Color::Green);
  this->enemy.setOutlineThickness(1.f);
}

// Constructor / Destructor
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initFonts();
  this->initText();
  this->initEnemies();
}

Game::~Game() {
  // Avoid memory leak
  delete this->window;
}

// Accessors
const bool Game::running() const { return this->window->isOpen(); };
const bool Game::getEndGame() const
{
return this->endGame;
};

// Functions
void Game::spawnEnemy() {
  /*
  return void

  Spawn enemies and sets their colors and positions
  - sets a random position
  - sets a random color
  - adds enemy to the vector
  */

  this->enemy.setPosition(
      // datatype conversion
      static_cast<float>(rand() % static_cast<int>(this->window->getSize().x -
                                                   this->enemy.getSize().x)),
      0.f);
  this->enemy.setFillColor(sf::Color::Green);

  // Spawn the enemy
  this->enemies.push_back(this->enemy);

  // Remove enemies at end of screen
  // std::cout<<this->enemies.size()<<std::endl;
};

void Game::pollEvent() {
  // Event polling
  while (this->window->pollEvent(this->ev)) {
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
void Game::updateMousePositions() {
  /*
  Updates the mouse positions:
  - Mouse position relative to window (Vector2i)
  */

  this->mousePosWindow = sf::Mouse::getPosition(*this->window);

  // Map position to be floats
  this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
};

void Game::updateText() 
{
    std::stringstream ss;

    ss << "Points: " << this->points<<"\n"
    << "Health: " << this->health<<"\n";

    this->uiText.setString(ss.str());

}

void Game::updateEnemies() {
  /*
   return void

   Updates the enemy spawn timer and spawns enemies when
   the total amount of enemies is smaller than the maximum

   Moves the enemies downwards
   Removes the enemies at the edge of the screen

  */

  // Updating the timer for enemy spawning
  if (this->enemies.size() < this->maxEnemies) {
    if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
      // Spawn the enemy and reset the timer
      this->spawnEnemy();
      this->enemySpawnTimer = 0.f;
    } else {
      this->enemySpawnTimer += 1.f;
    }
    // std::cout<<"Print spawntimer" << this->enemySpawnTimer << std::endl;
  }

  // Move and update the enemies

  // do have a lot of loops because if remove one enemy -> bug out
  for (int i = 0; i < this->enemies.size(); i++) {
        bool deleted = false;
    this->enemies[i].move(0.f, 1.f);  // Move downwards]
                                      // for (auto &e: this-> enemies)
                                      // {
                                      // e.move(0.f,5.f);
                                      // }

    // If the enemy is past the bottom of the screen
    if (this->enemies[i].getPosition().y > this->window->getSize().y) {
  
      this->enemies.erase(this->enemies.begin() + i);
      this->health -=1; //Miss an enemy -> health deduction
     std::cout<<"Health: "<<this->health<<std::endl;

    }
  }

  // Check if clicked upon
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (this->mouseHeld==false) {
      bool deleted = false;
      this-> mouseHeld = true;
      for (int i = 0; i < this->enemies.size() && deleted == false; i++) {
        if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
          deleted = true;
          this->enemies.erase(this->enemies.begin() + i);
          // Gain points
          this->points += 1;
          std::cout<<"Points: "<<this->points<<std::endl;
        }
      }
    }
    else
    {
        this-> mouseHeld = false;
    }
    
  }

  // cast current position of enemy
}

void Game::update() {
  this->pollEvent();

if (!this->endGame)
{
    
  // Update mouse position
  this->updateMousePositions();

  // Update text
  this->updateText();

  // Update enemies
  this->updateEnemies();
}

//End game condition
if (this->health <=0)
{
    this-> endGame=true;
}


}


void Game::renderText(sf::RenderTarget& target)
{
target.draw(this->uiText);
}


void Game::renderEnemies(sf::RenderTarget& target) {
  // Rendering all the enemies
  for (auto &e : this->enemies) {
    target.draw(e);
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
  this->renderEnemies(*this->window);
    this->renderText(*this->window);
  this->window->display();
}
