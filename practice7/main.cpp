#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#define INF std::numeric_limits<int>::max()
#define MARK "\033[1m\033[31m"
#define CLOSE "\033[0m"

/*
3 2 5 1 23 7 2 8 1
*/

typedef std::vector<std::vector<int>> Field;

struct Edge {
	int u = INF;
	int v = INF;
	int w = INF;

	Edge() {}

	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

class Solution {
private:
	Field field;
	size_t count_paths() {
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
	// Возвращает стандартное поле или введенное поле
	Field create() {
		Field f;

		int option;
		std::cout << "Ввести поле (1) или использовать готовое (2): ";
		std::cin >> option;

		switch (option) {
			case 1: {
				// строки и колонок
				size_t n, m;
				std::cout << "Введите размер поля (n x m): ";
				std::cin >> n >> m;

				f = Field(n);
				std::fill(f.begin(), f.end(), std::vector<int>(m));

				int val;
				for (size_t i = 0; i < n; ++i) {
					for (size_t j = 0; j < m; ++j) {
						std::cin >> val;
						f[i][j] = val;
					}
				}

				break;
			}
			case 2: {
				f = {
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
		return f;
	}
public:
	// Строит граф на основе поля
	Solution() : field(Solution::create()) {}

	// Находит кратчайший путь  методом Беллмана-Форда
	void solve() {
		std::vector<int> dist(field.front().size() * field.size(), INF);
		dist[0] = 0;

		std::vector<std::vector<int>> paths(dist.size());
		std::fill(paths.begin(), paths.end(), std::vector<int>(1, 0));

		int counter = 0;
		for (int i = 0; i < field.size(); ++i) {
			for (int j = 0; j < field.front().size(); ++j) {
				int u, v, w;
				// Если один путь вправо
				if (i == field.size() - 1 && j == field.front().size() - 1) {
					if (field.size() == 1) break;
					int top = dist.at(counter - field.front().size());
					int left = dist.at(counter - 1);
					int top_left = dist.at(counter - field.front().size() + 1);
					std::vector<int> all = {top, left, top_left};
					dist.rbegin() += *std::min(all.begin(), all.end());
					break;
				}
				if (i == field.size() - 1) {
					u = counter;
					v = counter + 1;
					w = field.at(i).at(j + 1);
					if (dist.at(u) != INF && dist.at(u) + w < dist.at(v)) {
						int save = dist.at(v);
						dist[v] = w + dist.at(u);
						if (save > dist.at(v)) {
							paths.at(v).clear();
							paths.at(v).push_back(0);
						}
						for (int el : paths.at(u)) {
							if (el != 0) paths.at(v).push_back(el);
						}
						paths.at(v).push_back(v);
					}
					counter++;
					continue;
				}
				// Если один путь вниз
				if (j == field.front().size() - 1) {
					u = counter;
					v = counter + field.front().size();
					w = field.at(i + 1).at(j);
					if (dist.at(u) != INF && dist.at(u) + w < dist.at(v)) {
						int save = dist.at(v);
						dist[v] = w + dist.at(u);
						if (save > dist.at(v)) {
							paths.at(v).clear();
							paths.at(v).push_back(0);
						}
						for (int el : paths.at(u)) {
							if (el != 0) paths.at(v).push_back(el);
						}
						paths.at(v).push_back(v);
					}
					counter++;
					continue;
				}
				// Если 3 пути
				if (i < field.size() && j < field.front().size()) {
					Edge right(counter, counter + 1, field.at(i).at(j + 1));
					Edge below(counter, counter + field.front().size(), field.at(i + 1).at(j));
					Edge right_below(counter, counter + field.front().size() + 1, field.at(i + 1).at(j + 1));
					std::vector<Edge> edges{right, below, right_below};

					for (Edge e : edges) {
						if (dist.at(e.u) != INF && dist.at(e.u) + e.w < dist.at(e.v)) {
							int save = dist.at(e.v);
							dist[e.v] = e.w + dist.at(e.u);
							if (save > dist.at(e.v)) {
								paths.at(e.v).clear();
								paths.at(e.v).push_back(0);
							}
							for (int el : paths.at(e.u)) {
								if (el != 0) {
									paths.at(e.v).push_back(el);
								}
							}
							paths.at(e.v).push_back(e.v);
						}
					}
					counter++;
					continue;
				}
			}
		}

		std::cout << "Самый короткий путь: " << std::endl;
		std::vector<int> path = *paths.rbegin();
		int name = 0;
		for (auto row : field) {
			for (auto column : row) {
				if (std::find(path.begin(), path.end(), name) != path.end()) {
					std::cout << MARK;
				}
				std::cout << std::setw(4) << column << CLOSE;
				name++;
			}
			std::cout << std::endl;
		}

		std::cout << "Длина пути: " << *dist.rbegin() << std::endl;
	}

	/*
	 * 1. Полный перебор по ВСЕМ ВОЗМОЖНЫМ путям*/
	void brute_solve() {
		size_t paths_count = count_paths();
	}
};

int main() {
	Solution solution;
	solution.solve();
	solution.brute_solve();
}