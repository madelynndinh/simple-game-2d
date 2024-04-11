// prgama once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include <sstream>
#include <vector>
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


  // Mouse positions
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;

//Resources
sf::Font font;

//Text
sf::Text uiText;

  // Game logic
  bool endGame;
  unsigned points;  //points are always positive
  int health;
  float enemySpawnTimer;
  float enemySpawnTimerMax;
  int maxEnemies;
  bool mouseHeld; // check if mouse held down

  // Game objects
  std::vector<sf::RectangleShape> enemies;
  sf::RectangleShape enemy;

  // Private function
  void initVariables();
  void initWindow();
  void initFonts();
  void initText();
  void initEnemies();

 public:
  // Constructors / destructors
  Game();
  virtual ~Game();

  // Accessors
  const bool running() const;
    const bool getEndGame() const;
  // Functions
  void spawnEnemy();
  void pollEvent();
  void updateMousePositions();
  void updateText();
  void updateEnemies();
  void update();

  void renderText(sf::RenderTarget& target); //not always render to the main window
  void renderEnemies(sf::RenderTarget& target);
  void render();
};
#endif