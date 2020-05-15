#pragma once

#include <chrono>
#include <string> 

#include "lista_graf.h"
#include "macierz_graf.h"


double bellmanFord(std::shared_ptr<ListGraph> GrafT, int t_startNode, bool t_printSolution);

double bellmanFord(std::shared_ptr<MatrixGraph> GrafT, int t_startNode, bool t_printSolution);