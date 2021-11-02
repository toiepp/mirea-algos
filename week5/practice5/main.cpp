#include <iostream>
#include <vector>

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

std::ostream & operator << (std::ostream& out, Info info) {
	out << "(" << info.begin << ") ==" << info.weight << "==> (" << info.end << ")";
	return out;
}


void euler_cycle(std::vector<Info>& graph) {
	std::vector<int> visited(10);
}

void level_order(std::vector<Info>& graph) {

}

int main() {
	std::cout << "=== Практическая 5 ===" << std::endl;
	std::cout << "===   Вариант 28   ===" << std::endl;
	std::cout << std::endl;
	std::cout << "Граф создан на основе списка ребер." << std::endl;

	std::vector<Info> graph = {
			Info(1, 4, 2),
			Info(1, 2, 3),
			Info(1, 3, 4),
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

	std::cout << "=== Эйлеров цикл ===" << std::endl;

	euler_cycle(graph);

	std::cout << std::endl;

	std::cout << "=== Обход в глубину ===" << std::endl;

	level_order(graph);

	return 0;
}