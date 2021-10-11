#include "TextParser.h"
#include <iostream>

int main() {
	std::string s = "Lorem ipsui dolor sit amet consectetuc adipiscing elit "
					"Quisque vel auctor ut nisl venenatis luctus Vivamus dolor libero "
					"ultrices a elit at rhoncus consectetuc sem eros Orci varius natoque "
					"penatibus et magnis dis parturient vel montes nascetur ridiculus mus "
					"Aenean sem lorem quam condimentum et urna viverra dignissim semper sem "
					"Praesent eu lorem ut tellus sollicitudin luctus quis quis nibh Cras "
					"fermentum ante sem eu tincidunt sfhgjkdhlgjdlghsdlgjfhsldfkjgshds sem mauris pulvinar ipsum "
					"sed placerat nulla turpis vel velit Ut sattis nec turpis ac pharetra "
					"Etiam sem venenatis hendrerit mauris sem quis pellentesque metus malesuada eu "
					"Pellentesque vel a mattis vel justo Orci varius natoque penatibus et magnis dis "
					"parturienp montes nascetur ridiculus mus Quisque arcu nibh sem accumsan et "
					"conguehtrlksjgfc";

	TextParser tp = TextParser(s);
	std::cout << tp.find_longest_with_same_edges() << std::endl;
	std::cout << tp.find_last("vel") << std::endl;

	s = "dsjhfl dskjafhlskd flfghru  jalghfjkg gfualifua jg fguiafgrahdshaalkjgf";
	tp.set_new(s);
	std::cout << tp.find_longest_with_same_edges() << std::endl;
	std::cout << tp.find_last("sem") << std::endl;

	return 0;
}