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

struct TreeNode {
	std::string city;
	TreeNode *left = nullptr;
	TreeNode *right = nullptr;

	explicit TreeNode(std::string city) : city(std::move(city)) {}

	TreeNode(std::string city, TreeNode *left, TreeNode *right)
		: city(std::move(city)), left(left), right(right) {}
};

// Функция создания бинарного дерева поиска с заданным
// количеством элементов
void build_binary_tree(TreeNode*, size_t);

// Функция вставки нового элемента
void insert(TreeNode*, TreeNode*);

// Функция симметричного обхода
void symmetric_print(TreeNode*);

// Функция обхода в ширину
void wide_print(TreeNode*);

// Функция вычисления длины пути от корня до заданного значения
int get_length(TreeNode*, TreeNode*);

// Функция вычисления высоты дерева
int get_height(TreeNode*);

int main() {
	std::cout << "=== Практическая работа №4 ===" << std::endl;
	std::cout << "===       Вариант 12       ===" << std::endl;

	size_t n;
	auto *root = new TreeNode("Root City");
	std::cout << "Сколько элементов добавить в дерево: ";
	std::cin >> n;

	// Строю бинарное дерево поиска
	build_binary_tree(root, n);

	return 0;
}
