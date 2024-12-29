#ifndef A_SEARCHER_H
#define A_SEARCHER_H
#include <iostream>
#include <vector>
#include "SDL.h"
#include<future>
#include <thread>
//#include<mutex>
using std::vector;
/////*** WE want to convert a SDL Point into an class with its attribute as itself,parent etc//////

template <class T>     //////we define an anynomous type T/////
class Node{
public:
//Node(){};
Node(T nodal);      /////T gonna be a SDL point , it is with SDL point we start  /////
Node<T>* ParentNode(Node<T>  *prev_node); 
  //////This will be a pointer to parent class///
int distance(Node<T> &targetnode);
void FindNeighbors();
int g_value;
int h_value;
bool visited;
Node<T> *parent ;
vector<Node<T>*> hood;
T MainNode(){return main_node;}
private:

T main_node;



};




class Asearch{
    public:
//Asearch(){};
Asearch(SDL_Point food  ,SDL_Point start_loc);

//~Asearch(){};
void AddNeighbors(Node<SDL_Point> &currentnode);
Node<SDL_Point>* NextNode();
void ConstructFinalPath(Node<SDL_Point> *currentnode,std::promise<vector<SDL_Point>> &&prms);
vector<SDL_Point> Searcher();
int CalculateHValue(Node<SDL_Point> *node);
//float CalculateGValue(Node<SDL_Point> *node);
void FindNeighbors(Node<SDL_Point>* node);
void Output();

private:

vector<SDL_Point> shortestroute;

//vector<Node<SDL_Point>*> hood;
Node<SDL_Point> start_node;
Node<SDL_Point> end_node;
vector<Node<SDL_Point>*> open_list;
//std::mutex _mtx;
/////so we wanna develop a node out of it using template function ... that template when defined in will Node<SDL_Point> and it will have
//////parent class , distance , and everything ../////
    
};
#endif