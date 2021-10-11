#ifndef MIREA_ALGOS_TEXTPARSER_H
#define MIREA_ALGOS_TEXTPARSER_H

#include <string>
#include <iostream>

class TextParser {
	std::string sentence;

public:
	explicit TextParser(std::string &);
	void set_new(std::string &);
	/*
	 * Дано предложение, состоящее из слов. Найти самое длинное
	 * слово предложения, первая и последняя буквы которого
	 * одинаковы*/
	std::string find_longest_with_same_edges();
	/*
	 * Используя алгоритм Кнута-Мориса-Пратта, найти индекс
	 * последнего вхождения образца в текст.*/
	int find_last();
};


#endif
