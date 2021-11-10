#include <iostream>
#include <queue>
#include <stack>
#include <vector>

struct {
	char sign;
	std::vector<bool> edges;
} typedef Graph;

/*
 * Граф, содержащий Эйлеров цикл
10
a b c d e f g h i j
0 1 1 0 1 1 0 0 0 0
1 0 1 1 1 0 0 0 0 0
1 1 0 1 0 0 0 0 1 0
0 1 1 0 0 0 0 1 1 0
1 1 0 0 0 1 1 0 0 0
1 0 0 0 1 0 1 0 0 1
0 0 0 0 1 1 0 0 0 1
0 0 0 1 0 0 1 0 1 1
0 0 1 1 0 0 0 0 0 1
0 0 0 0 0 1 1 0 1 0
*/

/*
 * 1. Найти и вывести эйлеров цикл в графе.
 *
 * Эйлеров путь (эйлерова цепь) в графе — это путь,
 * проходящий по всем рёбрам графа и притом только
 * по одному разу.
 *
 * Эйлеров путь в графе существует тогда и только тогда,
 * когда граф связный и содержит не более двух вершин
 * нечётной степени.
 *
 * 2. Реализовать обход графа в ширину. +
 * */

// http://graphonline.ru/?graph=HDumlQSPEidmrFMJ

bool deg(std::vector<bool> &vertex) {
	return std::count(vertex.begin(), vertex.end(), true);
}

void euler_path(std::vector<std::vector<bool>> &graph, std::vector<char> &nodes) {
	// Проверяю, является ли граф связным
	for (std::vector<bool> &vertex : graph) {
		if (std::count(vertex.begin(), vertex.end(), 1) == 0) {
			std::cout << "Граф не содержит Эйлеров цикл (граф несвязный)" << std::endl;
			return;
		}
	}

	// Проверяю, содержит ли граф вершины с нечетной степенью
	int count = 0;
	for (std::vector<bool> &vertex : graph) {
		if (std::count(vertex.begin(), vertex.end(), true) % 2 == 1) count++;
		if (count > 2) {
			std::cout << "В графе более 2-х вершин с нечетной степенью ==> граф не содержит эйлеров путь." << std::endl;
			return;
		}
	}

	// Создаю обертку над графом для простоты вывода пути на экран
	std::vector<Graph> g_vec(graph.size());
	for (int i = 0; i < graph.size(); ++i) {
		g_vec[i].sign = nodes.at(i);
		g_vec[i].edges = graph.at(i);
	}

	// Если граф полуэйлеровый, то путь надо
	// начинать с вершины с нечетной степенью
	std::vector<char> result;
	std::stack<Graph *> stack;

	// Кладу первую попавшуюся
	// вершину нечетной степени в стек
	size_t idx_of_start = std::distance(graph.begin(),
										std::find_if(graph.begin(), graph.end(),
													 [](const std::vector<bool> &vertex) {
														 return std::count(vertex.begin(), vertex.end(), true) % 2;
													 }));
	stack.push(&g_vec.at(idx_of_start));

	while (!stack.empty()) {
		Graph *V = stack.top();
		result.push_back(V->sign);
		stack.pop();
		for (int i = 0; i < nodes.size(); ++i) {
			if (V->edges.at(i)) {
				// Удаляю ребро, которое было пройдено
				// WARN неправильно удаляет ребро
				V->edges.at(i) = false;
				g_vec.at(i).edges[i + 1] = false;
				// Кладу другой конец этой вершины в стек
				stack.push(&g_vec.at(i));
				break;
			}
		}
	}


	std::for_each(result.begin(),
				  result.end() - 1,
				  [](const char &vertex) {
					  std::cout << vertex << " --> ";
				  });
	std::cout << *(result.end() - 1) << std::endl;
}

void level_order(/* матрица смежности графа */ std::vector<std::vector<bool>> &graph,
				 /* имена вершин графа */ std::vector<char> &nodes) {
	bool visited[nodes.size()];// массив вершин, которые уже обошли
	std::queue<std::vector<bool>> queue;
	queue.push(graph.at(0));
	visited[0] = true;
	std::cout << nodes.at(0) << " ";

	while (!queue.empty()) {
		std::vector<bool> vertex = queue.front();
		queue.pop();
		for (int i = 0; i < vertex.size(); ++i) {
			// если у вершины есть ребро с i-й вершиной и ее ещё не обошли
			if (vertex.at(i) && !visited[i]) {
				std::cout << nodes.at(i) << " ";// вывожу имя этой вершины
				queue.push(graph.at(i));        // кладу эту вершину в очередь
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
			std::vector<bool> tmp;
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

	std::cout << std::endl;

	std::cout << "=== Эйлеров путь ===" << std::endl;
	euler_path(graph, nodes);
	std::cout << std::endl;

	std::cout << "=== Обход в ширину ===" << std::endl;
	level_order(graph, nodes);
	std::cout << std::endl;

	return 0;
}