#include "bellman_algorytm.h"

static int  NieskonczonoscS = 1000000; 
static int  UjemnaNieskonczonoscS = -1000000;

void finalSolution(std::string t_pathArr[], int t_dist[], int t_n, int startNodeT) {

	std::ofstream file("Output.txt");
	
	std::cout << std::string(20, '-') << "\n   FinalSolution\n\n";
	std::cout << "The starting node was -> " << startNodeT << "\n\n";

	file << std::string(20, '-') << "\n   FinalSolution\n\n";
	file << "The starting node was -> " << startNodeT << "\n\n";

	for (int i = 0; i < t_n; ++i) {
		 
		if (t_dist[i] == UjemnaNieskonczonoscS) {
			std::cout << i << "->" << "-inf\n";
			file << i << "->" << "-inf\n";
			continue; 
		}
		else if (t_dist[i] == NieskonczonoscS) {
			std::cout << i << "->" << "inf\n";
			file << i << "->" << "inf\n";
			continue;
		}
		else {
			std::cout << i << "->" << t_dist[i];
			file << i << "->" << t_dist[i];
		}



		if (i < 10) {
			std::cout << "   ";
			file << "   ";
		}
		else if (i < 100) {
			std::cout << "  ";
			file << "  ";
		}
		else {
			std::cout << " ";
			file << " ";
		}
		

		if ((t_dist[i] >= 100 && t_dist[i] < 1000) || (-100 > t_dist[i]  && t_dist[i] <= -10)) {
		
			std::cout << " The shortest path: " << t_pathArr[i] << i;
			file << " The shortest path: " << t_pathArr[i] << i;
		}
		else if (0 <= t_dist[i] && t_dist[i] < 10) {

			std::cout << "   The shortest path: " << t_pathArr[i] << i;
			file << "   The shortest path: " << t_pathArr[i] << i;
		}
		else if ((t_dist[i] >= 10 && t_dist[i] < 100) || (-10 < t_dist[i] && t_dist[i] < 0)) {

			std::cout << "  The shortest path: " << t_pathArr[i] << i;
			file << "  The shortest path: " << t_pathArr[i] << i;
		}
		else { 
			std::cout << "The shortest path: " << t_pathArr[i] << i;
			file << "The shortest path: " << t_pathArr[i] << i;
		}
		std::cout << std::endl;
		file << std::endl;
	}
	std::cout << std::endl;
	file.close();
}


//bellman dla listy
double bellmanFord(std::shared_ptr<ListGraph> GrafT, int startNodeT, bool t_printSolution) {

	std::string* storePath = new std::string[GrafT->getV()]; 

	auto t_start = std::chrono::high_resolution_clock::now(); //rozpocznij zegar

	int* storeDistance = new int[GrafT->getV()]; 
	
	for (int iCell = 0; iCell < GrafT->getV(); ++iCell) {

		storeDistance[iCell] = NieskonczonoscS; 
	}

	storeDistance[startNodeT] = 0; 

	for (int i = 1; i < GrafT->getV(); ++i) { 
		for (int j = 0; j < GrafT->getE(); ++j) { 

			int u = GrafT->getStruct()[j].source;
			int v = GrafT->getStruct()[j].dest;
			int weight = GrafT->getStruct()[j].weight;

			if (storeDistance[u] + weight < storeDistance[v]) { //sprawdzanie czy nie ma krótszej ścieżki
				storeDistance[v] = storeDistance[u] + weight;
					
				if (t_printSolution) { 
						
					storePath[v].clear();
					storePath[v].append(storePath[u] + std::to_string(u) + "->");
				}
			}
		}
	}

	for (int i = 1; i < GrafT->getV(); ++i) {
		for (int j = 0; j < GrafT->getE(); ++j) {
			
			int u = GrafT->getStruct()[j].source;
			int v = GrafT->getStruct()[j].dest;
			int weight = GrafT->getStruct()[j].weight;
			if (storeDistance[u] + weight < storeDistance[v]) {

				if (storeDistance[u] > NieskonczonoscS/2) storeDistance[u] = NieskonczonoscS;  
				else storeDistance[v] = UjemnaNieskonczonoscS;
			}
			else if (storeDistance[u] > NieskonczonoscS/2) storeDistance[u] = NieskonczonoscS;  
		}
	}
	auto t_end = std::chrono::high_resolution_clock::now(); //stop zegar

	if (t_printSolution) finalSolution(std::move(storePath), std::move(storeDistance), GrafT->getV(), startNodeT);
	delete[] storeDistance;
	delete[] storePath;
	return std::chrono::duration<double, std::milli>(t_end - t_start).count(); //zwróć różnicę czasu
}


//bellman dla macierzy
double bellmanFord(std::shared_ptr<MatrixGraph> GrafT, int startNodeT, bool t_printSolution) {
	
	std::string* storePath = new std::string[GrafT->getV()];

	auto t_start = std::chrono::high_resolution_clock::now(); 

	int* storeDistance = new int[GrafT->getV()];

	for (int iCell = 0; iCell < GrafT->getV(); ++iCell) {

		storeDistance[iCell] = NieskonczonoscS;
	}

	storeDistance[startNodeT] = 0;

	for (int i = 1; i < GrafT->getV(); ++i) {
		for (int j = 0; j < GrafT->getV(); ++j) {
			for (int w = 0; w < GrafT->getV(); ++w) {

				int u = j;
				int v = w;
				int weight = GrafT->getWeight(j, w);
				if (storeDistance[u] + weight < storeDistance[v]) {
					
					storeDistance[v] = storeDistance[u] + weight;
					if (t_printSolution) {

						storePath[v].clear();
						storePath[v].append(storePath[u] + std::to_string(u) + "->");
					}
				}
			}
		}
	}
	for (int i = 1; i < GrafT->getV(); ++i) {
		for (int j = 0; j < GrafT->getV(); ++j) {
			for (int w = 0; w < GrafT->getV(); ++w) {

				int u = j;
				int v = w;
				int weight = GrafT->getWeight(j, w);
				if (storeDistance[u] + weight < storeDistance[v]) {
				
					if (storeDistance[u] > NieskonczonoscS / 2) storeDistance[u] = NieskonczonoscS;
					else if (weight == NieskonczonoscS) continue; 
					else storeDistance[v] = UjemnaNieskonczonoscS;
				}
				else if (storeDistance[u] > NieskonczonoscS/2) storeDistance[u] = NieskonczonoscS;	
			}
		}
	}
	auto t_end = std::chrono::high_resolution_clock::now(); 

	if (t_printSolution) finalSolution(std::move(storePath), std::move(storeDistance), GrafT->getV(), startNodeT);
	delete[] storeDistance;
	delete[] storePath;
	return std::chrono::duration<double, std::milli>(t_end - t_start).count(); 
}
