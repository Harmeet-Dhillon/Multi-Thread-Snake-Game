#ifndef GAME_H
#define GAME_H
#include<vector>
#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "memory"
#include "a_searcher.h"
//class Asearch;
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  std::shared_ptr<Snake>snake;
  SDL_Point food;
  std::vector<SDL_Point> path;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  //Asearch my_map;
  int score{0};
   ////new
  bool automode;
  int counter;
  void PlaceFood();
  void Update();
  void Autoride();
  void AutoModeOn();
};

#endif