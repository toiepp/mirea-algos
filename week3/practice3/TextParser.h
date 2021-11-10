#ifndef MIREA_ALGOS_TEXTPARSER_H
#define MIREA_ALGOS_TEXTPARSER_H

#include <iostream>
#include <vector>
#include <string>

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
	size_t find_last(const std::string&);
};


#endif
