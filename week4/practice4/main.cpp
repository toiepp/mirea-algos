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
void insert(TreeNode<T> *, T);

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

	// корневой элемент дерева
	auto *root = new TreeNode<int>(data);

	for (int i = 0; i < n - 1; ++i) {
		std::cin >> data;
		build_binary_tree(root, data);
	}

	// ------------------------------------

	std::cout << "Какой элемент добавить: ";
	std::cin >> data;
	insert(root, data);

	std::cout << "Какой элемент добавить: ";
	std::cin >> data;
	insert(root, data);

	std::cout << "Какой элемент добавить: ";
	std::cin >> data;
	insert(root, data);

	return 0;
}

// Без дубликатов
// 26 30 32 6 41 2 19 21 4 25 7 44 45 24 17 13 34 35 22 27
// С дубликатами
// 26 21 32 2 41 2 19 21
// left[data] < this[data] <= right[data]
template<typename T>
void build_binary_tree(TreeNode<T> *node, const T &data) {
	// Если узел уже имеет двух потомков или нужно сменить корневой текущий узел
	if ((node->left && node->right) /*еще одно условие должно быть*/
		|| (data >= node->data && node->right)
		|| (data < node->data && node->left)) {
		if (data < node->data) {
			build_binary_tree(node->left, data);
		} else {
			build_binary_tree(node->right, data);
		}
		return;
	}
	if (data < node->data) {
		node->left = new TreeNode(data);
		node->left->parent = node;
	} else {
		node->right = new TreeNode(data);
		node->right->parent = node;
	}
}

template<typename T>
void insert(TreeNode<T> *node, T to_insert) {
	build_binary_tree(node, to_insert);
}