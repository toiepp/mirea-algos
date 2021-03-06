#include <cmath>
#include <fstream>
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

	Symbol(std::pair<char, size_t> pair)
		: symbol(pair.first), amount(pair.second) {}
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

size_t total_amount(Sequence sequence) {
	size_t total = 0;
	for (Symbol s : sequence) {
		total += s.amount;
	}
	return total;
}

void print_alphabet() {
	std::vector<Symbol> alphabet = ALPHABET.front();
	std::sort(alphabet.begin(), alphabet.end(),
			  [](Symbol const &left, Symbol const &right) {
				  return left.amount > right.amount;
			  });
	std::for_each(alphabet.begin(), alphabet.end(), [](const Symbol &symbol) {
		std::cout << symbol.symbol << "(" << symbol.amount << ")";
		std::cout << std::setw(5) << std::right << "[";
		for (size_t i = 0; i < symbol.code.size(); ++i) {
			std::cout << std::left << symbol.code.at(i);
		}
		std::cout << "]" << std::endl;
	});
	std::cout << std::endl;
}

Sequence::iterator get_by_code(std::vector<bool> &code) {
	return std::find_if(ALPHABET.front().begin(), ALPHABET.front().end(),
						[&code](const Symbol &symbol) {
							return code == symbol.code;
						});
}

double compression(std::string &text, std::vector<bool> &encoded) {
	return ((double) (text.size() * 8)) / ((double) encoded.size());
}

double average() {
	double S = 0;
	std::for_each(ALPHABET.front().begin(), ALPHABET.front().end(),
				  [&S](const Symbol &symbol) {
					  S += ((double) symbol.amount /
							total_amount(ALPHABET.front())) *
						   (double) symbol.code.size();
				  });
	return S;
}

double dispersion() {
	double dispersion = 0.0;
	double total_amount = 0;
	double l_avg = average();
	std::for_each(ALPHABET.front().begin(), ALPHABET.front().end(),
				  [&total_amount](const Symbol &symbol) {
					  total_amount += symbol.amount;
				  });
	for (size_t i = 0; i < ALPHABET.front().size(); ++i) {
		double p_s = ALPHABET.front().at(i).amount / total_amount;
		double l_s = ALPHABET.front().at(i).code.size();
		dispersion += p_s * std::pow(l_s - l_avg, 2);
	}
	return dispersion;
}

std::vector<bool> huffman_encode(std::string &);

std::string huffman_decode(std::vector<bool> &);


int main() {
	std::cout << "=== ???????????????????????? ???????????? ???6 ===" << std::endl;
	std::cout << "===       ?????????????? 19       ===" << std::endl;
	std::cout << std::endl;

	std::string fio = "Mikholskiy Ivan Olegovich";

	std::ifstream in("/home/mikholskiyivan/main/mirea/mirea-algos/week6/practice6/text.txt");
	std::string long_text;
	std::string buffer;

	while (std::getline(in, buffer)) {
		long_text += buffer;
	}

	std::string to_process = fio;

	std::cout << to_process << std::endl
			  << std::endl;

	std::vector<bool> encoded = huffman_encode(to_process);

	print_alphabet();
	std::cout << std::endl;

	std::cout << "?????????????????? ????????????:\t" << to_process.length() * 8 << " ??????" << std::endl;
	std::cout << "???????????????? ????????????:\t" << encoded.size() << " ??????" << std::endl;
	std::cout << "?????????????????????? ????????????: " << compression(to_process, encoded) << std::endl;
	std::cout << "??????????????:\t\t\t" << average() << " ??????/????????????" << std::endl;
	std::cout << "??????????????????:\t\t\t" << dispersion() << std::endl;

	std::cout << std::endl;

	for (bool b : encoded) {
		std::cout << b;
	}
	std::cout << std::endl
			  << std::endl;

	std::cout << huffman_decode(encoded) << std::endl;

	return 0;
}


std::vector<bool> huffman_encode(std::string &text) {
	Alphabet alphabet = create_alphabet(text);

	while (alphabet.size() != 1) {
		auto p = get_two_min_and_delete(alphabet);
		std::for_each(p.first.begin(), p.first.end(),
					  [](Symbol &s) {
						  s.code.push_back(0);
					  });
		std::for_each(p.second.begin(), p.second.end(),
					  [&p](Symbol &s) {
						  s.code.push_back(1);
						  p.first.push_back(std::move(s));
					  });

		alphabet.push_back(std::move(p.first));
	}

	std::for_each(alphabet.front().begin(), alphabet.front().end(),
				  [](Symbol &symbol) {
					  std::reverse(symbol.code.begin(),
								   symbol.code.end());
				  });

	std::vector<bool> encoded;
	for (char &c : text) {
		std::vector<bool> code =
				std::find_if(alphabet.front().begin(),
							 alphabet.front().end(),
							 [&c](const Symbol &s) {
								 return s.symbol == c;
							 })
						->code;
		encoded.insert(encoded.end(), code.begin(), code.end());
	}
	ALPHABET = std::move(alphabet);

	return encoded;
}

std::string huffman_decode(std::vector<bool> &encoded) {
	std::string result;

	size_t min_buffer_size =
			std::min_element(ALPHABET.front().begin(),
							 ALPHABET.front().end(),
							 [](Symbol const &left, Symbol const &right) {
								 return left.code.size() < right.code.size();
							 })
					->code.size();

	for (size_t i = 0; i < encoded.size();) {
		size_t min = min_buffer_size;
		std::vector<bool> buffer = std::vector<bool>(encoded.begin() + i,
													 encoded.begin() + i + min);
		Sequence::iterator symbol = get_by_code(buffer);
		while (symbol == ALPHABET.front().end()) {
			bool next = *(encoded.begin() + i + min);
			buffer.push_back(next);
			min += 1;
			symbol = get_by_code(buffer);
		}
		result += symbol->symbol;
		i += buffer.size();
	}

	return result;
}

Alphabet create_alphabet(std::string &text) {
	std::map<char, size_t> alphabet;

	std::for_each(text.begin(), text.end(),
				  [&alphabet](const char &c) {
					  alphabet[c] += 1;
				  });

	Alphabet result;

	std::for_each(alphabet.begin(), alphabet.end(),
				  [&result](const std::pair<char, size_t> &p) {
					  Sequence sequence;
					  sequence.push_back(Symbol(std::move(p)));
					  result.push_back(std::move(sequence));
				  });

	return result;
}

std::pair<Sequence, Sequence> get_two_min_and_delete(Alphabet &alphabet) {
	auto comp = [](Sequence const &left, Sequence const &right) {
		return total_amount(left) < total_amount(right);
	};

	Sequence min1 = *std::min_element(alphabet.begin(), alphabet.end(), comp);
	std::erase(alphabet, min1);

	Sequence min2 = *std::min_element(alphabet.begin(), alphabet.end(), comp);
	std::erase(alphabet, min2);

	return std::make_pair(std::move(min2), std::move(min1));
}