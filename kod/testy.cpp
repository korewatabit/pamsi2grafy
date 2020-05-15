#include <time.h>

#include "bellman_algorytm.h"


template<typename T>
std::ostream& tests(std::ostream& file, int (&vertTab)[5], double (&densTab)[4], int loops) {
	
	for (double density : densTab) { //dla każdej gęstości
		for (int vertices : vertTab) { //dla każdej ilości wierzchołków
			double sum = 0;
			for (int iLoops = 0; iLoops < loops; ++iLoops) { //podaną ilość razy

				std::shared_ptr<T> graph = std::make_shared<T>(vertices, density); 
				int startNode = rand() % vertices; 

				graph->fillGraph(true); //wypełnia graf

				sum += bellmanFord(std::move(graph), startNode, false); //zwraca czas
				std::cout << (iLoops * 100 / loops) + 1 << "%" << "\r" << std::flush;
			}
			file << sum / loops << " "; //zapis średniej
			std::cout << vertices << " WIERZCHOŁKI SPRAWDZONE" << std::endl;
		}
		std::cout << "\n" << density << " GĘSTOŚĆ SPRAWDZONA\n" << std::endl;
	}
	file << "\n";
	return file;
}


int main() {

	srand(static_cast<unsigned int>(time(NULL)));

	bool testZone = true; //test lub nie
	
	if (testZone) {
		
		int vertTab[5] = {10, 25, 50, 100, 250}; //liczba wierzchołków do przetestowania
		double densTab[4] = {0.25, 0.5, 0.75, 1}; //gęstości do przetestowania
		int loops = 100;		//ilośc powtórzeń

		std::ofstream file("OutputTimes.txt");
		if (!file.is_open()) {

			std::cerr << "OUTPUTTIMES NIE OTWARTE!" << std::flush;
			return 1;
		}

		tests<ListGraph>(file, vertTab, densTab, loops); //test dla listy
		std::cout << "LISTA ZROBIONA\n" << std::endl;
		tests<MatrixGraph>(file, vertTab, densTab, loops);	//test dla macierzy
		std::cout << "MACIERZ ZROBIONA" << std::endl;

		file.close();
		return 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////

	typedef	ListGraph ActualGraph; //reprezentacja grafu
	bool useFile = false;	//input z pliku
	bool allowLoops = true;	//czy pętlę mają być tworzone
	int vertices = 7;		//ilość wierzchołków
	double density = 0.5;	//gęstość grafu
	int startNode = 2;		//początkowy wierzchołek dla bellmana

	std::shared_ptr<ActualGraph> graph;

	if (useFile) { //jeśli z pliku
		std::shared_ptr<ActualGraph> tmp = std::make_shared<ActualGraph>();
		graph = tmp;
		try {
			startNode = tmp->readFromFile();
		}
		catch (const char* msg) {
			std::cerr << msg << std::flush;
			return 1;
		}
	}
	else { //jeśli losowy graf
		std::shared_ptr<ActualGraph> tmp = std::make_shared<ActualGraph>(vertices, density);
		graph = tmp;
		tmp->fillGraph(allowLoops); //wypełnij
	}

	graph->printGraph(); 
	try {
		if (!useFile) graph->createInput(startNode); 
	}
	catch(const char* msg) {
		std::cerr << msg << std::flush;
		return 1;
	}
	bellmanFord(std::move(graph), startNode, true); //rozwiązanie bellmanem

	return 0;
}