#include "TextParser.h"
#include <iostream>

int main() {
	std::string s;
	TextParser tp = TextParser(s);


	std::cout << "Задание 1" << std::endl;

	s = "Lorem ipsum dolor sits amet coetuc adipiscing eli Donec"
		" faucibus lorem in dapibus finibus mestigubibulum susci"
		"pit faucibus metus at cursus turpis molestie sit amet p"
		"raesent efficitur nisl ut risus soltudins egestas";
	tp.set_new(s);
	std::cout << tp.find_longest_with_same_edges() << std::endl;

	s = "abc avc asf gdguu fddfd";
	tp.set_new(s);
	std::cout << tp.find_longest_with_same_edges() << std::endl;

	s = "aaaaaaaaaa aaa aaaa";
	tp.set_new(s);
	std::cout << tp.find_longest_with_same_edges() << std::endl;

	s = "aaaaaaaaaa";
	tp.set_new(s);
	std::cout << tp.find_longest_with_same_edges() << std::endl;

	std::cout << "Задание 2" << std::endl;

	s = "abcabeabcabcabd";
	tp.set_new(s);
	std::cout << tp.find_last("abcabd") << std::endl;

	s = "dsjhfl dskjafhjglskd flfghru jalghfjkg gfualifua jg fguiafgrahdshaalkjgf";
	tp.set_new(s);
	std::cout << tp.find_last("jg") << std::endl;

	s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
		" Quisque at rutrum metus. Mauris nec condimentum velit, "
		"tincidunt pellentesque mollis arcu. In molestie, justo a"
		"c tincidunt landit, dolor felis laoreet risus, sed aucto"
		"r metus erat sed nibh. In in lectus sem. In a laoreet ni"
		"sl. Nam cursus, metus molestie egestas pellentesque, ris"
		"us massa";
	tp.set_new(s);
	std::cout << tp.find_last("pellentesque") << std::endl;

	s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
		" Quisque at rutrum metus. Mauris nec condimentum velit, "
		"tincidunt mollis arcu. In molestie, justo ac tincidunt l"
		"andit, dolor felis laoreet risus, sed auctor metus erat "
		"sed nibh. In in lectus sem. In a laoreet nisl. Nam cursu"
		"s, metus molestie egestas pellentesque, risus massa";
	tp.set_new(s);
	std::cout << tp.find_last("kdfsha") << std::endl;

	s = "abcdefg";
	tp.set_new(s);
	std::cout << tp.find_last("hh") << std::endl;

	s = "abcdefghijklmnoprst";
	tp.set_new(s);
	std::cout << tp.find_last("hhh") << std::endl;
	return 0;
}