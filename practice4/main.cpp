#include <iostream>
#include <queue>

/*
	 * Вариант 12
	 * Тип значения узла: Строка - город				+
	 * Тип дерева: Бинарное дерево поиска				+
	 * Вставка элемента									+
	 * Симметричный обход								+
	 * Обход в ширину									+
	 * Найти длину пути от корня до заданного значения	+
	 * Найти высоту дерева								+
	 */

template<typename T>
struct TreeNode {
	T data;
	TreeNode *left = nullptr;
	TreeNode *right = nullptr;

	explicit TreeNode(T data) : data(std::move(data)) {}
};

// Функция добавления элемента
template<typename T>
void add(TreeNode<T> *, const T &);

// Функция симметричного обхода
template<typename T>
void symmetric_print(TreeNode<T> *);

// Функция обхода в ширину
template<typename T>
void breadth_order_traversal(TreeNode<T> *);

// Функция вычисления длины пути от корня до заданного значения
template<typename T>
int get_length(TreeNode<T> *, T);

// Функция вычисления высоты дерева
template<typename T>
int get_height(TreeNode<T> *);

int main() {
	std::cout << "=== Практическая работа №4 ===" << std::endl;
	std::cout << "===       Вариант 12       ===" << std::endl;

	int to_do;
	std::string data;
	TreeNode<std::string> *root = nullptr;

	// Engure Babolsar Watoona Panxi Marugame Chochkan Overkalix Mandala Tilang Takanini
	// Longra Portland Jintan Poitiers Tabatinga Mayma Shibukawa Lebu Miguel Bearna
	// Вставка Kalepasan и Hamburg
	do {
		std::cout << std::endl
				  << "=== === === === === === === === === ===\n"
				  << "=== [1] Создать дерево              ===\n"
				  << "=== [2] Вставить элемен             ===\n"
				  << "=== [3] Симметричный обход          ===\n"
				  << "=== [4] Обход в ширину              ===\n"
				  << "=== [5] Получить длину до элемента  ===\n"
				  << "=== [6] Получить высоту дерева      ===\n"
				  << "=== [0] Выйти                       ===\n"
				  << "=== === === === === === === === === ===\n"
				  << std::endl;
		std::cout << "Команда (1-6): ";
		std::cin >> to_do;
		switch (to_do) {
			case 0: {
				std::cout << "Выход" << std::endl;
				break;
			}
			case 1: {
				size_t n;
				std::cout << "Введите кол-во элементов: ";
				std::cin >> n;
				std::cout << "Введите данный: ";
				std::cin >> data;
				root = new TreeNode<std::string>(data);
				for (int i = 0; i < n - 1; ++i) {
					std::cin >> data;
					add(root, data);
				}
				break;
			}
			case 2: {
				std::cout << "Элемент для вставки: ";
				std::cin >> data;
				add(root, data);
				break;
			}
			case 3: {
				symmetric_print(root);
				std::cout << std::endl;
				break;
			}
			case 4: {
				level_print(root);
				std::cout << std::endl;
				break;
			}
			case 5: {
				std::cout << "Введите элемент: ";
				std::cin >> data;
				int l = get_length(root, data);
				if (l < 0) {
					std::cout << "Узла с таким ключом нет!" << std::endl;
				} else {
					std::cout << "Длина от корня до " << data << ": " << l << std::endl;
				}
				break;
			}
			case 6: {
				std::cout << "Высота дерева: " << get_height(root) << std::endl;
				break;
			}
			default:
				std::cout << "Неверная команда: " << to_do << std::endl;
		}
	} while (to_do);

	/*std::string d1;
	std::string d2;
	while (true) {
		std::cin >> d1 >> d2;
		if (d1 > d2) {
			std::cout << d1 << " > " << d2 << " : " << (d1 > d2) << std::endl;
		} else {
			std::cout << d1 << " <= " << d2 << " : " << (d1 <= d2) << std::endl;
		}
	}*/

	return 0;
}

template<typename T>
void add(TreeNode<T> *node, const T &data) {
	// Если узел уже имеет двух потомков или
	// перейти к правому или левому поддереву
	if ((node->left && node->right) ||
		(data >= node->data && node->right) ||
		(data < node->data && node->left)) {
		if (data < node->data) {
			add(node->left, data);
		} else {
			add(node->right, data);
		}
		return;
	}
	// Добавляю потомка в соотв. сторону
	if (data < node->data) {
		node->left = new TreeNode(data);
	} else {
		node->right = new TreeNode(data);
	}
}

template<typename T>
void symmetric_print(TreeNode<T> *node) {
	if (!node) return;
	symmetric_print(node->left);
	std::cout << node->data << " ";
	symmetric_print(node->right);
}

template<typename T>
void breadth_order_traversal(TreeNode<T> *node) {
	if (node) {
		std::queue<TreeNode<T> *> queue;
		queue.push(node);
		while (!queue.empty()) {
			node = queue.front();
			queue.pop();
			std::cout << node->data << " ";
			if (node->left) queue.push(node->left);
			if (node->right) queue.push(node->right);
		}
	}
}

template<typename T>
int get_length(TreeNode<T> *node, T dest) {
	TreeNode<T> *iter = node;
	size_t length = 0;
	while (iter != nullptr && iter->data != dest) {
		iter = (dest > iter->data) ? iter->right : iter->left;
		length++;
	}
	return (iter != nullptr) ? length : -1;
}

template<typename T>
int get_height(TreeNode<T> *node) {
	int left = 0;
	int right = 0;

	if (node->right != nullptr) {
		right += get_height(node->right);
		right++;
	}

	if (node->left != nullptr) {
		left += get_height(node->left);
		left++;
	}

	return std::max(left, right);
}