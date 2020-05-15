#include "lista_graf.h"

static int balansinterwaluS = -1; //taki sam jak w macierz_graf

void ListGraph::addEdge(int guardLiczbaT, int LiczbaT, int WagaT, int FlagaT) const {

	edge[FlagaT].dest = LiczbaT;
	edge[FlagaT].source = guardLiczbaT;
	edge[FlagaT].weight = WagaT;
}


bool ListGraph::detectIfExist(int guardLiczbaT, int LiczbaWierzchT) const {

	for (int iNumber = 0; iNumber < Em; ++iNumber) { //sprawdza liste edgy

		if (edge[iNumber].dest == LiczbaWierzchT && edge[iNumber].source == guardLiczbaT) return true; 
	}
	return false;
}


void ListGraph::fillGraph(const bool allowLoopsT) const {

	if (DensM == 1) {  //dla pełnego grafu

		int FlagaF = 0;
		for (int iSource = 0; iSource < Vm; ++iSource) { //fla każdego źródła
			for (int iDest = 0; iDest < Vm; ++iDest) { //dla każdego celu

				if (iSource!= iDest) { //nie rób pętli

					int WagaF = rand() % 20 + balansinterwaluS;
					while (WagaF == 0) { 

						WagaF = rand() % 20 + balansinterwaluS;
					}
					addEdge(iSource, iDest, WagaF, FlagaF++);
				}
			}
		}
	}
	else { //inne gęstości

		int EdgesF = 0;
		while (EdgesF < Em) {

			int guardNode = rand() % Vm;
			int nodeNode = rand() % Vm;
			if (!detectIfExist(guardNode, nodeNode)) {

				int WagaF = rand() % 20 + balansinterwaluS;
				while (WagaF == 0) {

					WagaF = rand() % 20 + balansinterwaluS;
				}

				if (guardNode != nodeNode) addEdge(guardNode, nodeNode, WagaF, EdgesF++);
				else if (allowLoopsT) addEdge(guardNode, nodeNode, WagaF, EdgesF++);
			}
		}
	}
}


void ListGraph::printGraph() const {

	std::cout << std::string(30, '-') << "\n  Reprezentacja listą sąsiedztwa\n\n";
	for (int iSource = 0; iSource < Vm; ++iSource) {
		
		//numer źródła
		std::cout << iSource;
		for (int iEdge = 0; iEdge < Em; ++iEdge) {

			if (edge[iEdge].source == iSource) 
				std::cout << "->" << "[" << edge[iEdge].dest << "|" << edge[iEdge].weight << "]";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}


const int ListGraph::readFromFile() {

	std::ifstream file("Input.txt");
	if (!file.is_open()) {
		throw "INPUT LISTA NIE OTWARTY";
		return 1;
	}

	//inicjalizacja
	int start, source, destination, weight;
	file >> Em >> Vm >> start;
	edge = new Edge[Em];

	for (int iEdge = 0; iEdge < Em; ++iEdge) {

		file >> source >> destination >> weight;
		addEdge(source, destination, weight, iEdge);
	}
	file.close();
	return start;
}


void ListGraph::createInput(const int startNodeT) const {

	std::ofstream file("CreatedInput.txt");
	if (!file.is_open()) {
		throw  "CREATEDINPUT LISTA NIE OTWARTY";
		return;
	}

	file << Em << " " << Vm << " " << startNodeT << "\n";
	for (int iEdge = 0; iEdge < Em; ++iEdge) {

		file << edge[iEdge].source << " ";
		file << edge[iEdge].dest << " ";
		file << edge[iEdge].weight << "\n";		
	}
	file.close();
}
