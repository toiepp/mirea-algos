#include <iostream>
#include <vector>
#include <queue>

/*
 * 1. Найти и вывести эйлеров цикл в графе.
 * 2. Реализовать обход графа в ширину.
 * */

/*
 * http://graphonline.ru/?graph=iNcyQqXCvUvaRpfI
 * */

struct Info {
	int begin;
	int end;
	int weight;

	Info(int b, int e, int w) : begin(b), end(e), weight(w) {}
};

std::ostream &operator<<(std::ostream &out, const Info& info) {
	out << "(" << info.begin << ") ==" << info.weight << "==> (" << info.end << ")";
	return out;
}
std::istream &operator>>(std::istream &in, Info info) {
	in >> info.begin >> info.end >> info.weight;
	return in;
}

void print_graph(std::vector<Info> &graph) {
	for (auto & el : graph) {
		std::cout << el << std::endl;
	}
}

void euler_cycle(std::vector<Info> &graph) {
	bool visited[10];
}

void level_order(std::vector<Info> &graph, int start) {
	std::queue<int> queue;
	queue.push(start);
	// массив, показывающий была ли соотв.
	// вершина посещена при обходе
	bool visited[10];
	visited[start - 1] = true;

	while (!queue.empty()) {
		int v = queue.front();
		queue.pop();
		if (visited[v - 1]) {
			std::cout << v << " ";
		}
		for (Info &el : graph) {
			if (el.begin == v && !visited[el.end - 1]) {
				queue.push(el.end);
				visited[el.end - 1] = true;
			}
		}
	}
	std::cout << std::endl;
}

int main() {
	std::cout << "=== Практическая 5 ===" << std::endl;
	std::cout << "===   Вариант 28   ===" << std::endl;
	std::cout << "Граф создан на основе списка ребер." << std::endl;
	std::cout << std::endl;

	int option;
	std::cout << "Ввести граф (1) или использовать граф по умолчанию (2): ";
	std::cin >> option;

	std::vector<Info> graph;

	// создание графи на основе ввода с клавиатуры
	if (option == 1) {
		std::cout << "Для завершения введите 0" << std::endl;
		int begin, end, weight;
		do {
			std::cin >> begin;
			if (begin == 0) break;
			std::cin >> end >> weight;
			Info info(begin, end, weight);
			graph.push_back(info);
		} while (true);
	}
	// граф, определнный в варинте
	if (option == 2) {
		graph = {
				Info(1, 2, 3),
				Info(1, 3, 4),
				Info(1, 4, 2),
				Info(2, 6, 3),
				Info(3, 6, 6),
				Info(4, 5, 5),
				Info(4, 6, 2),
				Info(5, 7, 6),
				Info(5, 9, 12),
				Info(6, 5, 1),
				Info(6, 7, 8),
				Info(6, 8, 7),
				Info(7, 10, 4),
				Info(8, 10, 3),
				Info(9, 8, 6),
				Info(9, 10, 11),

		};
	}

	print_graph(graph);
	std::cout << std::endl;

	std::cout << "=== Эйлеров цикл ===" << std::endl;

	euler_cycle(graph);
	std::cout << std::endl;

	std::cout << "=== Обход в ширину ===" << std::endl;

	int start;
	std::cout << "Начало: ";
	std::cin >> start;

	if (start <= 10) {
		level_order(graph, start);
	} else {
		std::cout << "Такой вершины в графе нет: " << start << std::endl;
	}

	return 0;
}