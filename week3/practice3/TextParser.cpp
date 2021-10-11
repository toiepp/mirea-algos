#include "TextParser.h"


TextParser::TextParser(std::string &s) : sentence(s) {}

void TextParser::set_new(std::string &s) {
	this->sentence = s;
}

std::string TextParser::find_longest_with_same_edges() {
}

int TextParser::find_last() {
	return 0;
}
