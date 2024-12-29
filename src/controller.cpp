#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include <memory>
#include <iostream>
void Controller::ChangeDirection( std::shared_ptr<Snake>snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->direction != opposite || snake->size == 1) snake->direction = input;
  return;
}

void Controller::HandleInput(bool &running, std::shared_ptr<Snake>snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          //std::cout<<"direction changed to up"<<std::endl;
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          //std::cout<<"direction changed to down"<<std::endl;
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          //std::cout<<"direction changed to left"<<std::endl;
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);

          //std::cout<<"direction changed to up"<<std::endl;
          break;
      }
    }
  }
}