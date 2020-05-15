#include "macierz_graf.h"

static int NieskonczonoscS = 1000000; //takie samo jak w bellman_algorytm

static int balansinterwaluS = -1;

MatrixGraph::MatrixGraph(int Vt, double DensT)  //konstruktor
	: Graph(Vt, static_cast<int>(DensT* Vt* (Vt - 1)), DensT),
	  matrix(std::make_unique<std::unique_ptr<int[]>[]>(Vt)) {

	//inicjalizacja
	for (int iCell = 0; iCell < Vm; ++iCell) {

		matrix[iCell] = std::make_unique<int[]>(Vt); 
		for (int iColumn = 0; iColumn < Vm; ++iColumn) {
			
			if (iCell == iColumn) matrix[iCell][iColumn] = 0; //zera na przekątnej
			else matrix[iCell][iColumn] = NieskonczonoscS; //nieskonczonosc wszedzie indziej
		}
	}
}


void MatrixGraph::fillGraph(const bool allowLoopsT) const {

	if (DensM == 1) {  //dla pełnego grafu
		for (int iRows = 0; iRows < Vm; ++iRows) { //dla każdergo wersu
			for (int jColumns = 0; jColumns < Vm; ++jColumns) {  //dla każdej kolumny
				if (iRows != jColumns) //nie rób pętli
				{
					int WagaF = rand() % 20  + balansinterwaluS;
					while (WagaF == 0) { 
						WagaF = rand() % 20 + balansinterwaluS;
					}
					matrix[iRows][jColumns] = WagaF;
				}
			}
		}
	}
	else { //inne gęstości

		int EdgesF = Em;

		while (EdgesF) { 
			int rowNode = rand() % Vm; 
			int columnNode = rand() % Vm;
			if (matrix[rowNode][columnNode] == 0|| matrix[rowNode][columnNode]== NieskonczonoscS) { 

				int WagaF = rand() % 20 + balansinterwaluS;
				while (WagaF == 0) { 

					WagaF = rand() % 20 + balansinterwaluS;
				}

				if (rowNode != columnNode) {

					matrix[rowNode][columnNode] = WagaF;
					--EdgesF;
				}
				else if (allowLoopsT) {

					matrix[rowNode][columnNode] = WagaF;
					--EdgesF;
				}
			}
		}
	}
}


void MatrixGraph::printGraph() const {
	std::cout << std::string(33, '-') << "\n  Reprezentacja macierzą sąsiedztwa\n\n ";
	for (int iIter = 0; iIter < Vm; ++iIter) {
		
		if (iIter <= 10) std::cout << "    " << iIter;
		else if (iIter <= 100) std::cout << "   " << iIter;
		else std::cout << "  " << iIter;
	}
	std::cout << "\n\n";

	for (int iRows = 0; iRows < Vm; ++iRows) {	

		if (iRows < 10) std::cout << iRows << "   |";
		else if (iRows < 100) std::cout << iRows << "  |";
		else std::cout << iRows << " |";

		for (int jColumns = 0; jColumns < Vm; ++jColumns) {

			int foo = matrix[iRows][jColumns];

			if (foo == NieskonczonoscS) std::cout << "*"; //jeśli nie ma połączenia
			else std::cout << foo;

			if (abs(foo) < 10 || abs(foo) == NieskonczonoscS) std::cout << "    ";
			else if (abs(foo) < 100) std::cout << "   ";
			else std::cout << "  ";

			if (foo < 0) std::cout << '\b'; 
		}
		std::cout << "|\n";
	}
	std::cout << std::endl;
}


const int MatrixGraph::readFromFile() {

	std::ifstream file("Input.txt"); 
	if (!file.is_open()) {
		throw "INPUT MACIERZ NIE OTWARTY!";
		return 1;
	}

	int start, source, destination, weight;
	file >> Em >> Vm >> start;
	matrix = std::make_unique<std::unique_ptr<int[]>[]>(Vm);

	for (int iRow = 0; iRow < Vm; ++iRow) {

		matrix[iRow] = std::move(std::make_unique<int[]>(Vm));
		for (int iColumn = 0; iColumn < Vm; ++iColumn) {

			if (iRow == iColumn) matrix[iRow][iColumn] = 0;
			else matrix[iRow][iColumn] = NieskonczonoscS;
		}
	}

	for (int iEdge = 0; iEdge < Em; ++iEdge) {

		file >> source >> destination >> weight;
		matrix[source][destination] = weight;;
	}
	file.close();
	return start; 
}

// ilość krawędzi | ilość wierzchołków | wierzchołek startowy
//
// wierzchołek początkowy | wierzchołek końcowy | waga
//...
//

void MatrixGraph::createInput(const int startNodeT) const {
	
	std::ofstream file("CreatedInput.txt");
	if (!file.is_open()) {
		throw  "CREATEDINPUT MACIERZ NIE OTWARTY!";
		return;
	}

	file << Em << " " << Vm << " " << startNodeT << "\n";
	for (int iRow = 0; iRow < Vm; ++iRow) {
		for (int iColumn = 0; iColumn < Vm; ++iColumn) {

			if (matrix[iRow][iColumn] != NieskonczonoscS && matrix[iRow][iColumn] != 0) {

				file << iRow << " ";
				file << iColumn << " ";
				file << matrix[iRow][iColumn] << "\n";
			}
		}
	}
	file.close();
}
