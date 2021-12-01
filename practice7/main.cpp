#include <iomanip>
#include <iostream>
#include <vector>
#include <limits>

#define INF std::numeric_limits<int>::infinity()
#define TEST

/*
62 95 78 69 87 29
64 84 40 35 40 49
77 32 91 46 60 84
49 61 63 64 69 36
84 40 19 45 64 52
50 18 13 89 74 19
*/

typedef std::vector<std::vector<int>> Field;

struct Edge {
	int u;
	int v;
	int w;

	Edge() : u(INF), v(INF), w(INF) {}

	Edge(int s, int d, int w) : u(s), v(d), w(w) {}
};

std::ostream &operator<<(std::ostream &out, const Edge &e) {
	out << std::setw(5) << std::left << e.u << "-<" << e.w << ">->" << std::setw(5) << std::right << e.v;
	return out;
}

/*
 * Решение задачи с помощью алгоритма Беллмана-Форда,
 * на основе динамеческого программирования.
 * */

class Solution {
public:
	std::vector<Edge> graph;

	// Строит граф на основе вершин
	// Граф представлен как вектор взвешенных
	// ребер между вершинами
	Solution(Field &field) {
		graph = std::vector<Edge>();
		int counter = 1;
		for (size_t i = 0; i < field.size(); ++i) {
			for (size_t j = 0; j < field.at(0).size(); ++j) {
				if (j != field.at(0).size() - 1) {
					Edge right(counter, counter + 1, field.at(i).at(j + 1));
					graph.push_back(right);
				}
				if (i != field.size() - 1) {
					Edge below(counter, counter + field.at(0).size(), field.at(i + 1).at(j));
					graph.push_back(below);
				}
				if (i != field.size() - 1 && j != field.at(0).size() - 1) {
					Edge right_below(counter, counter + field.at(0).size() + 1, field.at(i + 1).at(j + 1));
					graph.push_back(right_below);
				}
				counter++;
			}
		}
		graph.push_back(Edge(field.at(0).size() * field.size(), INF, INF));
		graph.shrink_to_fit();
	}

#ifdef TEST
	void show_graph() {
		std::for_each(graph.begin(), graph.end(),
					  [](const Edge &e) {
						  std::cout << e << std::endl;
					  });
	}
#endif

	int solve() {
		std::vector<int> dist(graph.size(), INF);
		dist[0] = 0;

		for (int i = 0; i < graph.size(); ++i) {

		}

		return 0;
	}
};

Field create();

void print_field(Field field);

int get_shortest(Field &);

#ifndef TEST
int main() {
	std::cout << "=== Практическая работа №7 ===" << std::endl
			  << "===        Вариант 6       ===" << std::endl;

	Field field = create();
	Solution solution(field);

	return 0;
}
#else
int main() {
	Field field = create();
	Solution solution(field);

	solution.show_graph();
}
#endif

Field create() {
	Field field;

	int option;
	std::cout << "Ввести поле (1) или использовать готовое (2): ";
	std::cin >> option;

	switch (option) {
		case 1: {
			// строки и колонок
			size_t n, m;
			std::cout << "Введите размер поля (n x m): ";
			std::cin >> n >> m;

			field = Field(n);
			std::fill(field.begin(), field.end(), std::vector<int>(m));

			int val;
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = 0; j < m; ++j) {
					std::cin >> val;
					field[i][j] = val;
				}
			}

			break;
		}
		case 2: {
			field = {
					{6, 11, 11, 19, 8, 17, 2, 1, 10, 19, 4, 6, 13, 15, 1, 18, 7, 12, 19, 7},
					{7, 1, 16, 11, 4, 8, 8, 10, 15, 14, 9, 16, 6, 1, 14, 4, 2, 5, 9, 19},
					{12, 11, 12, 18, 4, 16, 8, 11, 12, 14, 12, 16, 13, 19, 13, 10, 19, 14, 18, 18},
					{20, 17, 18, 8, 5, 7, 8, 7, 16, 4, 8, 19, 9, 16, 4, 17, 6, 12, 10, 2},
					{11, 13, 19, 11, 13, 18, 19, 10, 9, 9, 3, 7, 9, 19, 13, 18, 8, 5, 1, 13},
					{14, 12, 9, 11, 1, 6, 13, 3, 8, 15, 13, 3, 1, 14, 2, 9, 13, 10, 15, 16},
					{19, 13, 16, 19, 16, 2, 2, 16, 9, 11, 10, 11, 16, 18, 16, 3, 5, 20, 20, 18},
					{17, 5, 15, 13, 14, 6, 12, 4, 5, 14, 2, 17, 2, 3, 5, 9, 13, 3, 12, 17},
					{17, 10, 5, 18, 7, 15, 1, 8, 2, 6, 18, 12, 12, 12, 6, 7, 5, 14, 3, 10},
					{9, 4, 18, 16, 11, 9, 7, 14, 6, 4, 20, 3, 2, 16, 10, 6, 12, 17, 4, 13},
					{18, 9, 2, 13, 16, 13, 2, 12, 2, 15, 18, 17, 4, 20, 7, 6, 20, 3, 9, 8},
					{19, 7, 14, 16, 19, 2, 7, 11, 7, 11, 11, 13, 15, 10, 15, 14, 10, 12, 13, 19},
					{17, 6, 9, 3, 2, 9, 15, 19, 1, 18, 13, 17, 13, 13, 3, 12, 13, 10, 20, 18},
					{8, 7, 5, 8, 8, 6, 19, 19, 4, 7, 10, 15, 5, 18, 3, 13, 19, 18, 7, 11},
					{11, 18, 4, 11, 5, 5, 19, 14, 18, 18, 11, 18, 20, 12, 7, 11, 4, 2, 20, 7},
					{16, 13, 10, 1, 2, 19, 20, 2, 19, 8, 8, 15, 12, 6, 11, 10, 3, 15, 7, 9},
					{17, 14, 15, 1, 13, 4, 14, 14, 18, 14, 19, 4, 14, 3, 3, 5, 16, 16, 13, 10},
					{12, 11, 3, 6, 8, 9, 11, 5, 17, 5, 11, 6, 6, 6, 6, 17, 15, 16, 7, 16},
					{8, 7, 7, 3, 3, 17, 3, 16, 6, 14, 2, 20, 11, 5, 13, 7, 15, 6, 10, 12},
					{18, 11, 12, 10, 2, 5, 2, 16, 16, 7, 1, 7, 20, 1, 16, 3, 5, 4, 6, 8}};
			break;
		}
	}
	return field;
}

void print_field(Field field) {
	for (auto row : field) {
		for (auto column : row) {
			std::cout << std::setw(3) << std::left << column << " ";
		}
		std::cout << std::endl;
	}
}

size_t count_paths(Field &field) {
	if (field.size() == 1 || field.at(0).size() == 1) {
		return 1;
	}
	std::vector<int> counts(field.at(0).size(), 1);
	std::vector<int> prev_state(counts.begin(), counts.end());

	for (size_t i = 1; i < counts.size(); ++i) {
		counts[i] = counts.at(i - 1) + 2;
	}

	for (size_t i = 2; i < field.size(); ++i) {
		prev_state = counts;
		for (size_t j = 1; j < counts.size(); ++j) {
			counts[j] = counts.at(j - 1) + prev_state.at(j) + prev_state.at(j - 1);
		}
	}

	return *counts.rbegin();
}