#include "graph.h"
#include <iostream>
/**
@file graph.cpp
@author Yuta Miyake
@brief Creates a dot file of simple tree for graphviz
*/
Graph::Graph(std::string filename, std::string graph_name){
  // parameterized constructor w/ default arguments
  this->filename = filename;
  this->graph_name = graph_name;
  this->debugger.setFileName("astlog.txt");
}
Graph::~Graph(){
}
void Graph::setVisualizer(bool on_off){
  // on/off visualizer
  this->visualizer.setDebug(on_off);
}
void Graph::setGraphFileName(std::string filename){
  this->filename = filename;
}
void Graph::setLogFileName(std::string filename){
  this->debugger.setFileName(filename);
}
void Graph::setDebug(bool on_off){
  this->debugger.setDebug(on_off);
}
void Graph::debug(std::string msg){
  this->debugger.debug(msg);
}
void Graph::startBuild(){
  // start building the dot file
  std::stringstream ss;
  this->visualizer.setFileName(this->filename);
  ss << "digraph " << this->graph_name << " {" << std::endl;
  this->visualizer.debug(ss.str());
}
void Graph::endBuild(std::string imageFileName){
  std::stringstream ss;

  if(!this->visualizer.IsSet()){
    return;
  }
  this->visualizer.debug("}");

  // Wrap the 'dot' command in an if/else which tells us if we have graphviz
  ss << "if hash dot 2>/dev/null; then\n";
  ss << "\tdot -Tpng ";
  ss << this->filename << " -o " << imageFileName << "\n";
  ss << "else\n\t{ echo >&2 "
     << "\"graphviz not installed on this machine. "
     << "Graph will not be generated.\"; exit 1; }\n";
  ss << "fi";

  system(ss.str().c_str());
}
void Graph::addNode(int id, std::string label){
  // add new node into the dot file
  std::stringstream ss;
  ss << id << " [label=\"" << label << "\"];" << std::endl;
  this->visualizer.debug(ss.str());
  //std::cout <<"[graphviz]: add " << label << std::endl;
}
void Graph::addEdge(int pid, int cid){
  // add new edge between two nodes into the dot file
  std::stringstream ss;
  ss << pid << " -> " << cid << ";" << std::endl;
  this->visualizer.debug(ss.str());
  //std::cout <<"[graphviz]: add edge " << pid << " -> " << cid << std::endl;
}
