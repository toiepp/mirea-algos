#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Symbol;

typedef std::vector<Symbol> Sequence;

typedef std::vector<Sequence> Alphabet;

Alphabet ALPHABET;

struct Symbol {
	char symbol;
	size_t amount;
	std::vector<bool> code;

	Symbol(std::pair<char, size_t> pair) : symbol(pair.first), amount(pair.second) {}
};

std::ostream &operator<<(std::ostream &out, const Symbol &symbol) {
	out << symbol.symbol << "(" << symbol.amount << ")=";
	for (size_t i = 0; i < symbol.code.size(); ++i) {
		out << symbol.code.at(i);
	}
	return out;
}

std::ostream &operator<<(std::ostream &out, const Sequence &sequence) {
	out << "{ ";
	for (size_t i = 0; i < sequence.size() - 1; ++i) {
		out << sequence.at(i) << ", ";
	}
	out << sequence.back() << " }";
	return out;
}

bool operator==(const Sequence &left, const Sequence &right) {
	return std::equal(left.begin(), left.end(), right.begin(),
					  [](const Symbol &left, const Symbol &right) {
						  return left.symbol == right.symbol;
					  });
}

Alphabet create_alphabet(std::string &);

std::pair<Sequence, Sequence> get_two_min_and_delete(Alphabet &);

size_t total_sum_of_seq(Sequence sequence) {
	size_t total = 0;
	for (Symbol s : sequence) {
		total += s.amount;
	}
	return total;
}

Sequence::iterator get_by_code(std::vector<bool> &code) {
	return std::find_if(ALPHABET.front().begin(), ALPHABET.front().end(),
						[&code](const Symbol &symbol) { return code == symbol.code; });
}

std::vector<bool> huffman_encode(std::string &);

std::string huffman_decode(std::vector<bool> &);

int main() {
	std::cout << "=== Практическая работа №6 ===" << std::endl;
	std::cout << "===       Вариант 19       ===" << std::endl;
	std::cout << std::endl;

	std::string default_str_ru = "Перводан, другодан,\n"
								 "На колоде барабан;\n"
								 "Свинистель, коростель,\n"
								 "Пятерка, шестерка,\n"
								 "утюг.";

	std::string default_str_en_long = "Do not go gentle into that good night,\n"
									  "Old age should burn and rave at close of day;\n"
									  "Rage, rage against the dying of the light.\n"
									  "Though wise men at their end know dark is right,\n"
									  "Because their words had forked no lightning they\n"
									  "Do not go gentle into that good night.";

	std::string default_str_en_short = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
									   "ddddddddddddddddddddddddddddddddddddddd"
									   "aaaaaaaaaaaaaaaaaaaaaaaaaaa"
									   "eeeeeeeeeeee"
									   "ccccccccc"
									   "fffff";

//	default_str_en_short = "aaabbc";

	std::vector<bool> encoded = huffman_encode(default_str_en_short);

	for (Sequence s : ALPHABET) {
		std::cout << s << std::endl;
	}

	for (bool b : encoded) {
		std::cout << b;
	}
	std::cout << std::endl;

	std::cout << huffman_decode(encoded) << std::endl;

	return 0;
}

std::vector<bool> huffman_encode(std::string &text) {
	Alphabet alphabet = create_alphabet(text);

	while (alphabet.size() != 1) {
		Alphabet new_alphabet;
		while ((alphabet.size() != 1 && alphabet.size() % 2 != 0) || (alphabet.size() != 0 && alphabet.size() % 2 == 0)) {
			auto p = get_two_min_and_delete(alphabet);
			Sequence new_sequence;
			std::for_each(p.first.begin(), p.first.end(),
						  [&new_sequence](Symbol &s) {
							  s.code.insert(s.code.begin(), 1, 0);
							  new_sequence.push_back(s);
						  });
			std::for_each(p.second.begin(), p.second.end(),
						  [&new_sequence](Symbol &s) {
							  s.code.insert(s.code.begin(), 1, 1);
							  new_sequence.push_back(s);
						  });

			new_alphabet.push_back(new_sequence);
		}
		alphabet.insert(alphabet.end(), new_alphabet.begin(), new_alphabet.end());
	}
	std::vector<bool> encoded;
	for (char c : text) {
		std::vector<bool> code = std::find_if(alphabet.front().begin(), alphabet.front().end(),
											  [&c](const Symbol &s) {
												  return s.symbol == c;
											  })
										 ->code;
		encoded.insert(encoded.end(), code.begin(), code.end());
	}
	ALPHABET = alphabet;
	return encoded;
}

std::string huffman_decode(std::vector<bool> &encoded) {
	std::string result;
	std::vector<bool> buffer;

	size_t skip_count = 0;
	for (size_t i = 0; i < encoded.size();) {
		buffer.push_back(encoded.at(i));
		Sequence::iterator seq_iter = get_by_code(buffer);
		if (seq_iter != ALPHABET.front().end()) {
			result += seq_iter->symbol;
			i += buffer.size() - skip_count;
			buffer.clear();
			skip_count = 0;
		} else {
			skip_count++;
			i += 1;
		}
	}

	return result;
}

Alphabet create_alphabet(std::string &text) {
	std::map<char, size_t> alphabet;

	std::for_each(text.begin(), text.end(), [&alphabet](const char &c) {
		alphabet[c] += 1;
	});

	Alphabet result;

	std::for_each(alphabet.begin(), alphabet.end(), [&result](const std::pair<char, size_t> &p) {
		Sequence sequence;
		sequence.push_back(Symbol(p));
		result.push_back(sequence);
	});

	std::sort(result.begin(), result.end(), [](Sequence const &left, Sequence const &right) {
		return left.front().amount >= right.front().amount;
	});

	return result;
}

std::pair<Sequence, Sequence> get_two_min_and_delete(Alphabet &alphabet) {
	auto comp = [](Sequence const &left, Sequence const &right) {
		return total_sum_of_seq(left) < total_sum_of_seq(right);
	};

	Sequence min1 = *std::min_element(alphabet.begin(), alphabet.end(), comp);
	std::erase(alphabet, min1);

	Sequence min2 = *std::min_element(alphabet.begin(), alphabet.end(), comp);
	std::erase(alphabet, min2);

	return std::make_pair(min2, min1);
}