#include "a_searcher.h"
#include<cmath>
#include <vector>
#include<iostream>
#include<string>
#include <algorithm>
#include<future>
//#include<mutex>
using std::sort;
using std::vector;
template<typename T>
Node<T>::Node(T nodal):main_node(nodal){}   

template<typename T>
int Node<T>::distance(Node<T> &targetnode){
       int dx=abs (this->main_node.x-targetnode.main_node.x);
       int dy=abs(this->main_node.y-targetnode.main_node.y);
       return dx+dy;
   // return std::sqrt(std::pow(this->main_node.x-targetnode.main_node.x,2)+std::pow(this->main_node.y-targetnode.main_node.y,2));
}
template<typename T>
Node<T>* Node<T>::ParentNode(Node<T> *prev_node){
    parent=prev_node;
}
/*template<typename T>
void Node<T>::FindNeighbors() {//////THIS IS main character left///
    vector<vector<int>> v={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
    for (auto cord:v){
        float new_x=this->main_code.x+cord[0];
        float new_y=this->main_code.y+cord[1];
        if (new_x==parent->main_node.x && new_y==parent->main.node.y){
            break;}
        else
        {
            Node<T>
            hood.emplace_back(Node<T>* node(new_x,new_y));
        }
        
    }
}*/

Asearch::Asearch(SDL_Point food,SDL_Point start_loc):end_node(food),start_node(start_loc){} ////reference can be used with this one////
    


int Asearch::CalculateHValue(Node<SDL_Point> *node) { //////distance is x1-x2 & y2-y1 mod   then start - end is H value*****
return node->distance(this->end_node);
}
/*float Asearch::CalculateGValue(Node<SDL_Point> const *node) { //////distance is x1-x2 & y2-y1 mod   then start - end is H value*****
return node->distance(this->end_node);
}*/
/*void Asearch::Output(){//std::cout<<"I wanna fuk u snake"<<std::endl;

std::cout<<"...."<<"Start node is "<<start_node.MainNode().x<<"......"<<start_node.MainNode().y<<"....."<<std::endl;
std::cout<<"...."<<"End Node is "<<end_node.MainNode().x<<"......"<<end_node.MainNode().y<<"....."<<std::endl;
/*auto path = this->Searcher();
for (auto fv:path){
    std::cout<<"vector cords"<<fv.x<<"...."<<fv.y<<"\n"<<std::endl;
}
Node<SDL_Point> *current_node = nullptr;
current_node=&start_node;
start_node.visited=true;
start_node.g_value=0;
int i=0;
while(!((current_node->MainNode().x==end_node.MainNode().x)&&(current_node->MainNode().y==end_node.MainNode().y))){
//while(current_node!=&end_node){
AddNeighbors(*current_node);
// auto av=open_list;
 //for (auto temp:av){
 //std::cout<<temp->MainNode().x<<"... "<<temp->MainNode().y<<std::endl;
//}
for (auto dv:open_list){
    std::cout<<dv->distance(end_node)<<"....."<<std::endl;
    std::cout<<dv->g_value<<"...."<<dv->h_value<<"these are g and h values"<<std::endl;
    std::cout<<"new node is "<<dv->MainNode().x<<"...."<<dv->MainNode().y<<std::endl;
    std::cout<<"these is H value"<<dv->g_value+dv->h_value<<std::endl;
}
current_node=NextNode();
int  farness=current_node->g_value+current_node->h_value;
 //std::cout<<"...."<<current_node->MainNode().x<<"......"<<current_node->MainNode().y<<"....."<<std::endl;

/*auto cv=this->ConstructFinalPath(current_node);
for (auto temp:cv){
 std::cout<<temp.x<<"... "<<temp.y<<"......"<<std::endl;
}


i+=1;

/*this->Searcher();
for (auto temp:av){
    std::cout<<temp->MainNode().x<<"... "<<temp->MainNode().y<<std::endl;
}
auto bv=NextNode();
std::cout<<"...."<<bv->MainNode().x<<"......"<<bv->MainNode().y<<"....."<<std::endl;
std::cout<<"...."<<std::endl;
std::cout<<"one shot end..."<<farness<<std::endl;
std::cout<<"new node is "<<current_node->MainNode().x<<"...."<<current_node->MainNode().y<<std::endl;
std::cout<<"...."<<std::endl;}
}*/



// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.
void Asearch::FindNeighbors(Node<SDL_Point>  *node) {//////THIS IS main character left///
    vector<vector<int>> v={{1,0},{0,1},{-1,0},{0,-1}};
    for (auto cord:v){
        int new_x=node->MainNode().x+cord[0];
        int new_y=node->MainNode().y+cord[1];
        if (new_x==node->parent->MainNode().x && new_y==node->parent->MainNode().y){
            continue;}
        else
        {
            SDL_Point point={new_x,new_y};
            Node<SDL_Point>*pointer=new Node<SDL_Point>(point);
           
            node->hood.emplace_back(std::move(pointer));
        }
        
    }
}

void Asearch::AddNeighbors(Node<SDL_Point> &current_node) { ///// adding neighbors - nearest will be four all up & down,left right
  FindNeighbors(&current_node);      /////// x + the one equal to speed  or y + equal to speed ////this function will have their constructors
  for(auto &my_node:current_node.hood){ 
      if(my_node->visited==false) {//////template to be used/////
      my_node->ParentNode(&current_node);
      my_node->g_value=current_node.g_value+my_node->distance(current_node);
      my_node->h_value=CalculateHValue(my_node);
      my_node->visited=true;
      /*std::cout<<"\n";
      std::cout<<my_node->MainNode().x<<"..."<<my_node->MainNode().y<<std::endl;
       std::cout<<"\n";*/
      this->open_list.emplace_back(my_node);}
      else
      {
          continue;
      }
      
      }
  
}


////////Main changes are required in the findneighbor & distance learner ///////*****

// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.
// bool comp(RouteModel::Node* a,RouteModel::Node* b){
  //float f1=a->g_value+a->h_value;
    //float f2=b->g_value+b->h_value;
    //return f1>f2;
// }  
//sort(open_list.begin(),open_list.end(),comp);

Node<SDL_Point>*Asearch::NextNode() {    /////will automatically ////****
if (open_list.empty()){
    return nullptr;
}
sort(open_list.begin(),open_list.end(),[](Node<SDL_Point>const *a ,Node<SDL_Point>*b){
    return (a->g_value+ a->h_value)<=(b->g_value+ b->h_value);
}
);
Node<SDL_Point>* lowest_node=open_list.front();
//open_list.erase(open_list.begin());
open_list.clear();
return lowest_node;
}

// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

void Asearch::ConstructFinalPath(Node<SDL_Point> *current_node,std::promise<vector<SDL_Point>> &&prms) {  ////automatically then//*******
    // Create path_found vector
    //std::lock_guard<std::mutex> lock(_mutex);
    int  distance = 0.0;
    std::vector<SDL_Point> path_found;

    // TODO: Implement your solution here.
    
    path_found.insert(path_found.begin(),current_node->MainNode()); 
    while(!((current_node->MainNode().x==start_node.MainNode().x)&&(current_node->MainNode().y==start_node.MainNode().y))){
    //while(current_node !=&this->start_node){
      Node<SDL_Point>* k =current_node->parent;
      distance+=current_node->distance(*k);
      path_found.insert(path_found.begin(),k->MainNode());
      current_node=k;
     }
    
    //distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    prms.set_value(path_found);
    
   //return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

std::vector<SDL_Point> Asearch::Searcher() {   //// this will automatically ..//*****then
     
    //std::lock_guard<std::mutex> lock(_mtx);
    Node<SDL_Point> *current_node = nullptr;
    current_node=&this->start_node;
    start_node.visited=true;
    //while(current_node !=&end_node){
    while(!((current_node->MainNode().x==end_node.MainNode().x)&&(current_node->MainNode().y==end_node.MainNode().y))){
    AddNeighbors(*current_node);
    current_node=NextNode();
    if (current_node==nullptr){
         std::cout<<"no path found"<<std::endl;
         return {};
    }
    }
    //lock.unlock();
    std::promise<vector<SDL_Point>> prms ;
    std::future<vector<SDL_Point>>ftr = prms.get_future();
    ConstructFinalPath(current_node,std::move(prms));
    ftr.wait();
    shortestroute=ftr.get();
    //shortestrout;
    return shortestroute;

}

///////FindNeighbors is left /////////