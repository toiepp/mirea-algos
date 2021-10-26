#include <iostream>

/*
 * Вариант 12
 * Тип значения узла: Строка - город
 * Тип дерева: Бинарное дерево поиска
 * Вставка элемента
 * Симметричный обход
 * Обход в ширину
 * Найти длину пути от корня до заданного значения
 * Найти высоту дерева
 */

template<typename T>
struct TreeNode {
	TreeNode *parent = nullptr;
	T data;
	TreeNode *left = nullptr;
	TreeNode *right = nullptr;

	explicit TreeNode(T data) : data(std::move(data)) {}
};

// Функция создания бинарного дерева поиска с заданным
// количеством элементов
template<typename T>
void build_binary_tree(TreeNode<T> *, const T &);

// Функция вставки нового элемента
template<typename T>
void insert(TreeNode<T> *, TreeNode<T> *);

// Функция симметричного обхода
template<typename T>
void symmetric_print(TreeNode<T> *);

// Функция обхода в ширину
template<typename T>
void wide_print(TreeNode<T> *);

// Функция вычисления длины пути от корня до заданного значения
template<typename T>
int get_length(TreeNode<T> *, TreeNode<T> *);

// Функция вычисления высоты дерева
template<typename T>
int get_height(TreeNode<T> *);

int main() {
	std::cout << "=== Практическая работа №4 ===" << std::endl;
	std::cout << "===       Вариант 12       ===" << std::endl;

	size_t n;
	int data;
	std::cout << "Введите кол-во городов: ";
	std::cin >> n;

	std::cin >> data;

	auto *root = new TreeNode<int>(data);

	for (int i = 0; i < n - 1; ++i) {
		std::cin >> data;
		build_binary_tree(root, data);
	}

	return 0;
}

// 26 30 32 6 41 2 19 21 4 25 7 44 45 24 17 13 34 35 22 27
// left[data] < this[data] <= right[data]
template<typename T>
void build_binary_tree(TreeNode<T> *root, const T &data) {
	// Если узел уже имеет двух потомков или нужно сменить корневой текущий узел
	if ((root->left && root->right) /*еще одно условие должно быть*/
		|| (data > root->data && root->right)
		|| (data <= root->data && root->left)) {
		if (data < root->data) {
			build_binary_tree(root->left, data);
		} else {
			build_binary_tree(root->right, data);
		}
		return;
	}
	if (data < root->data) {
		root->left = new TreeNode(data);
	} else {
		root->right = new TreeNode(data);
	}
}