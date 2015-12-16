#ifndef __GRAPH__H__
#define __GRAPH__H__
#include "Debugger.h"
#include <sstream>

class Graph{
    public:
        Graph(std::string filename = "graph.dot",std::string graph_name = "g");
        ~Graph();
        void setVisualizer(bool on_off);
        void setGraphFileName(std::string filename);
        void setLogFileName(std::string filename);
        void setDebug(bool on_off);
        void debug(std::string msg);
        void startBuild();
        void endBuild(std::string imageFileName);
        void addEdge(int pid, int cid);
        void addNode(int id, std::string label);
    private:
      Debugger visualizer;
      Debugger debugger;
      std::string filename, graph_name;
};
#endif
