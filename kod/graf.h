#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>

//klasa reprezentująca graf
class Graph {

protected:
	int Vm, Em; //ilość wierzchołków i krawędzi (Vertices/Edges)
	double DensM; //density of graph

public:
	const int& getV() const { return Vm; }						
	const int& getE() const { return Em; }

	virtual void fillGraph(const bool allowLoops) const = 0; //losowo wypełnia graf
	virtual void printGraph() const =  0; //pokazuje graf w konsoli
	virtual const int readFromFile() = 0; //wypełnia graf instrukcją z pliku
	virtual void createInput(const int startNodeT) const = 0; //tworzy input
	virtual ~Graph() {};
	explicit Graph(int Vt, int Et, double DensT) : Vm(Vt), Em(Et), DensM(DensT) {}
	Graph() {}; //konstruktor
};