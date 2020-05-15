#pragma once

#include "graf.h"

struct Edge {
	int source, dest, weight; 
};


//graf za pomocą listy sąsiedztwa
class ListGraph : public Graph {

	Edge* edge; //array wszystkich edgy

public:
	void fillGraph(const bool allowLoops) const override; 
	void printGraph() const override;
	const int readFromFile() override;
	void createInput(const int startNodeT) const override;

	const Edge* getStruct() const { return edge; } 
	void addEdge(int guardLiczbaT, int LiczbaT, int WagaT, int FlagaT) const;
	bool detectIfExist(int guardLiczbaT, int LiczbaWierzchT) const;
	
	explicit ListGraph(int Vt, double DensT)
		:Graph(Vt, static_cast<int>(DensT* Vt* (Vt - 1)), DensT),
		 edge(new Edge[static_cast<int>(DensT* Vt* (Vt - 1))]) {}
	ListGraph() : Graph() {};
	~ListGraph() { delete[] edge; }
};
