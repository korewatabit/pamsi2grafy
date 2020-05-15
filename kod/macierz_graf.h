#pragma once

#include "graf.h" 

#include <cstdlib>
#include <memory>


class MatrixGraph : public Graph {

	std::unique_ptr<std::unique_ptr<int[]>[]> matrix; //dynamiczna  macierz tablic

public:
	void fillGraph(const bool allowLoops) const override;
	void printGraph() const override;
	const int readFromFile() override;
	void createInput(const int startNodeT) const override;

	const int& getWeight(int t_row, int t_column) const { return matrix[t_row][t_column]; } 

	explicit MatrixGraph(int Vt, double DensT);
	MatrixGraph() : Graph() {};
};