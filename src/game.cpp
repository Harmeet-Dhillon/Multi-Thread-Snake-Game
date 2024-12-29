#include "game.h"
#include <iostream>
#include "SDL.h"
#include <vector>
#include <thread>
#include <future>
#include<iostream>
//#include "a_searcher.h"
Game::Game(std::size_t grid_width, std::size_t grid_height)
    : 
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  snake=std::make_shared<Snake>(grid_height,grid_width);
  //Asearch  my_map(SDL_Point{15,5},SDL_Point{3,5});
  //my_map.Output();
  //path=my_map.Searcher();
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  ///std::vector<std::vector<int>> pathmaker={{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6}};
  /*for(auto v:pathmaker){
    SDL_Point temp;
    temp.x=v[0];
    temp.y=v[1];
    this->path.push_back(temp);
  }*/

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    
    Update();
    //renderer.Render(snake, food,path);
    ////new ///
    
    int new_x = static_cast<int>(snake->head_x);
    int new_y = static_cast<int>(snake->head_y);
    if (!path.empty()){
    if (path.begin()->x==new_x && path.begin()->y==new_y && (!snake->SnakeBodyCheck(path))){
      std::cout<<"automode on hai bhai "<<std::endl;
      AutoModeOn();}}

    if (automode){Autoride();}
    renderer.Render(snake, food,path);
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  
  if (!snake->alive) return;
  
  if (!automode){
  snake->Update();}

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    if(!path.empty()){
    int sl_i=path.size()-2;
    int l_i=path.size()-1;
    if (path[sl_i].x==path[l_i].x){
      if(path[sl_i].y>path[l_i].y){
        snake->direction=Snake::Direction::kUp;
      }
      else{
       snake->direction=Snake::Direction::kDown; 
      }
    }
    if (path[sl_i].y==path[l_i].y){
      if(path[sl_i].x>path[l_i].x){
        snake->direction=Snake::Direction::kLeft;
      }
      else{
       snake->direction=Snake::Direction::kRight; 
      }
    }}
    score++;
    
    SDL_Point starter;
    path.clear();
    PlaceFood();
    if (snake->direction==Snake::Direction::kUp){starter.x=new_x;starter.y=new_y-3;}
    if (snake->direction==Snake::Direction::kDown){starter.x=new_x;starter.y=new_y+3;}
    if (snake->direction==Snake::Direction::kLeft){starter.x=new_x-3;starter.y=new_y;}
    if (snake->direction==Snake::Direction::kRight){starter.x=new_x+3;starter.y=new_y;}

    Asearch  my_map(food,starter);
    std::future<vector<SDL_Point>> ftr=std::async(&Asearch::Searcher,my_map);
    ftr.wait();
    path=ftr.get();
    //Asearch  my_map(SDL_Point{2,21},SDL_Point{18,5});
    //Asearch map(food,starter);
    //my_map.Output();
    
    path.pop_back();
    counter=0;
    automode=false;
    //std::cout<<"no auto shoto"<<std::endl;
    // Grow snake and increase speed.
    std::cout<<"I m entering"<<std::endl;
    
    snake->GrowBody();

    std::cout<<"I m exiting"<<std::endl;
    
    ////checking direction and /// adding two blocks after  getting direction of that and making shortest path available./////
    snake->speed += 0.02;
  }
  
}

int Game::GetScore() const { return score; }

int Game::GetSize() const { return snake->size; }

////we want x to be 
void Game::AutoModeOn(){
  automode=true; 
  snake->head_x=static_cast<float>(path[1].x);
  snake->head_y=static_cast<float>(path[1].y);
  snake->UpdateBody(path[1],path[0]);
  
  counter=1;
  return;}

void Game::Autoride(){
  if (counter<path.size()){
  snake->head_x=static_cast<float>(path[counter+1].x);
  snake->head_y=static_cast<float>(path[counter+1].y);
  snake->UpdateBody(path[counter+1],path[counter]);
  counter++;
  return;}
  }


