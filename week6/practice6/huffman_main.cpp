#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
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

void print_alphabet() {
	std::vector<Symbol> alphabet = ALPHABET.front();
	std::sort(alphabet.begin(), alphabet.end(), [](Symbol const &left, Symbol const &right) {
		return left.amount > right.amount;
	});
	std::for_each(alphabet.begin(), alphabet.end(), [](const Symbol &symbol) {
		std::cout << symbol.symbol << "(" << symbol.amount << ")[";
		for (size_t i = 0; i < symbol.code.size(); ++i) {
			std::cout << symbol.code.at(i);
		}
		std::cout << "]" << std::endl;
	});
	std::cout << std::endl;
}

Sequence::iterator get_by_code(std::vector<bool> &code) {
	return std::find_if(ALPHABET.front().begin(), ALPHABET.front().end(),
						[&code](const Symbol &symbol) { return code == symbol.code; });
}

double compression(std::string &text, std::vector<bool> &encoded) {
	return ((double) encoded.size() / (double) (text.size() * 8));
}

double average() {
	double S = 0;
	double total_amount = 0;
	std::for_each(ALPHABET.front().begin(), ALPHABET.front().end(),
				  [&total_amount](const Symbol &symbol) {
					  total_amount += symbol.amount;
				  });
	std::for_each(ALPHABET.front().begin(), ALPHABET.front().end(),
				  [&S, &total_amount](const Symbol &symbol) {
					  S += ((double) symbol.amount / total_amount) * (double) symbol.code.size();
				  });
	return S;
}

double dispertion() {
	double d = 0.0;
	double total_amount = 0;
	double l_avg = average();
	std::for_each(ALPHABET.front().begin(), ALPHABET.front().end(),
				  [&total_amount](const Symbol &symbol) {
					  total_amount += symbol.amount;
				  });
	for (size_t i = 0; i < ALPHABET.front().size(); ++i) {
		double p_s = total_amount / (double) ALPHABET.front().at(i).amount;
		double l_s = ALPHABET.front().at(i).code.size();
		d += p_s * std::pow(l_s - l_avg, 2);
	}
	return d;
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

	std::string to_process = default_str_en_long;

	std::cout << to_process << std::endl
			  << std::endl;

	std::vector<bool> encoded = huffman_encode(to_process);

//	print_alphabet();
//	std::cout << std::endl;

	std::cout << "Коэффициент сжатия: " << compression(to_process, encoded) << std::endl;
	std::cout << "Среднее:\t\t\t" << average() << " бит/символ" << std::endl;
	std::cout << "Дисперсия:\t\t\t" << dispertion() << std::endl;

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