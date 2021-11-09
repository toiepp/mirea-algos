#include <iostream>
#include <queue>
#include <vector>

/*
 * Граф, содержащий Эйлеров цикл
0 1 1 0 1 1 0 0 0 0
1 0 1 1 1 0 0 0 0 0
1 1 0 1 0 0 0 0 1 0
0 1 1 0 0 0 0 1 1 0
1 1 0 0 0 1 1 0 0 0
1 0 0 0 1 0 1 0 0 1
0 0 0 0 1 1 0 1 0 1
0 0 0 1 0 0 1 0 1 1
0 0 1 1 0 0 0 1 0 1
0 0 0 0 0 1 1 1 1 0
*/

/*
 * 1. Найти и вывести эйлеров цикл в графе.
 *
 * Эйлеров цикл — эйлеров путь, являющийся циклом,
 * то есть замкнутый путь, проходящий через каждое
 * ребро графа ровно по одному разу.
 *
 * Эйлеров цикл существует тогда и только тогда,
 * когда граф связный или будет являться связным,
 * если удалить из него все изолированные вершины,
 * и в нём отсутствуют вершины нечётной степени.
 *
 *
 * 2. Реализовать обход графа в ширину.
 * */

// http://graphonline.ru/?graph=HDumlQSPEidmrFMJ

bool is_even_deg(std::vector<bool> &vertex) {
	bool result = vertex.at(0);
	for (size_t i = 1; i < vertex.size(); ++i) {
		if (vertex.at(i)) {                // если есть ребро
			result = result ^ vertex.at(i);// XOR
		}
	}
	return !result;
}

void euler_cycle(std::vector<std::vector<bool>> &graph, std::vector<char> &nodes) {
	// Проверяю, является ли граф связным
	for (std::vector<bool> & vertex : graph) {
		std::vector<bool>::iterator found = std::find(vertex.begin(), vertex.end(), true);
		if (found == vertex.end()) {
			std::cout << "Граф не содержит Эйлеров цикл (граф несвязный)" << std::endl;
			return;
		}
	}
	// Проверяю, содержит ли граф вершины с нечетной степенью
	for (std::vector<bool> &vertex : graph) {
		if (!is_even_deg(vertex)) {
			std::cout << "Граф не содержет Эйлеров цикл (содержит вершины нечётной степени)" << std::endl;
			return;
		}
	}

	bool visited[10];
}

/*
  a b c d f g h i j k
a 0 1 1 0 1 1 0 0 0 0
b 1 0 1 1 1 0 0 0 0 0
c 1 1 0 1 0 0 0 0 1 0
d 0 1 1 0 0 0 0 1 1 0
f 1 1 0 0 0 1 1 0 0 0
g 1 0 0 0 1 0 1 0 0 1
h 0 0 0 0 1 1 0 1 0 1
i 0 0 0 1 0 0 1 0 1 1
j 0 0 1 1 0 0 0 1 0 1
k 0 0 0 0 0 1 1 1 1 0
 */

/* обход начинается с первой вершины из матрицы смежности */
void level_order(/* матрица смежности графа */std::vector<std::vector<bool>> &graph,
				 /* имена вершин графа */std::vector<char> &nodes) {
	bool visited[nodes.size()]; // массив вершин, которые я уже обошел
	std::queue<std::vector<bool>> queue;
	queue.push(graph.at(0));
	visited[0] = true;
	std::cout << nodes.at(0) << " ";

	while(!queue.empty()) {
		std::vector<bool> vertex = queue.front();
		queue.pop();
		for (int i = 0; i < vertex.size(); ++i) {
			// если у вершины есть ребро с i-й вершиной и ее ещё не обошли
			if (vertex.at(i) && !visited[i]) {
				std::cout << nodes.at(i) << " "; // вывожу имя этой вершины
				queue.push(graph.at(i)); // кладу эту вершину в очередь
				visited[i] = true;
			}
		}
	}
}

int main() {
	std::cout << "=== Практическая 5 ===" << std::endl;
	std::cout << "===   Вариант 28   ===" << std::endl;
	std::cout << "Граф создан на основе списка ребер." << std::endl;
	std::cout << std::endl;

	int option;
	std::cout << "Ввести граф (1) или использовать граф по умолчанию (2): ";
	std::cin >> option;

	std::vector<char> nodes;
	std::vector<std::vector<bool>> graph;

	// создание графи на основе ввода с клавиатуры
	if (option == 1) {
		int n;
		char name;
		std::cout << "Кол-во вершин в графе: ";
		std::cin >> n;
		std::cout << "Названия вершин: ";
		for (int i = 0; i < n; ++i) {
			std::cin >> name;
			nodes.push_back(name);
		}
		std::cout << "Введите матрицу смежности: " << std::endl;
		for (int i = 0; i < n; ++i) {
			std::vector<bool> tmp(n);
			for (int j = 0; j < n; ++j) {
				int r;
				std::cin >> r;
				tmp.push_back(r);
			}
			graph.push_back(tmp);
			tmp.clear();
		}
	}
	// граф, определнный в варинте
	if (option == 2) {
		nodes = {'a', 'b', 'c', 'd', 'f', 'g', 'h', 'i', 'j', 'k'};
		graph = {
				//     a  b  c  d  f  g  h  i  j  k
				/*a*/ {0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
				/*b*/ {1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
				/*c*/ {0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
				/*d*/ {0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
				/*f*/ {1, 1, 0, 0, 0, 1, 1, 0, 0, 0},
				/*g*/ {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
				/*h*/ {0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
				/*i*/ {0, 0, 0, 1, 0, 0, 1, 0, 1, 1},
				/*j*/ {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
				/*k*/ {0, 0, 0, 0, 0, 0, 1, 1, 0, 0}};
	}

	//	print_graph(graph);
	std::cout << std::endl;

	std::cout << "=== Эйлеров цикл ===" << std::endl;
	euler_cycle(graph, nodes);
	std::cout << std::endl;

	std::cout << "=== Обход в ширину ===" << std::endl;
	level_order(graph, nodes);

	return 0;
}