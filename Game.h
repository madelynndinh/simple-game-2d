// prgama once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <ctime>
#ifndef GAME_H
#define GAME_H

/*
Class that acts as the game engine.
Wrapper class
*/

class Game {
 private:
  // Variables
  // Window
  sf::RenderWindow* window;
  sf::VideoMode videoMode;
  sf::Event ev;
  
  //Mouse positions
  sf::Vector2i mousePosWindow;


//Game logic
int points;
float enemySpawnTimer;
float enemySpawnTimerMax;
int maxEnemies;

  // Game objects
  std::vector<sf::RectangleShape> enemies;
  sf::RectangleShape enemy;

  // Private function
  void initVariables();
  void initWindow();
  void initEnemies();

 public:
  // Constructors / destructors
  Game();
  virtual ~Game();

  // Accessors
  const bool running() const;

  // Functions
  void spawnEnemy();
  void pollEvent();
  void updateMousePositions();
  void updateEnemies();
  void update();
  void renderEnemies();
  void render();
};
#endif