#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <regex>
#include <set>
#include <iterator>

using std::cout;
using std::cin;
using std::string;

struct zodis {
	string vardas;
	std::vector <int> eilutes;
};

int main() {
	std::stringstream bufferis;
	try {
		std::ifstream fd("tekstas.txt");
		if (fd) {
			bufferis << fd.rdbuf();
			fd.close();
		}
		else
			throw 404;
	}
	catch (...) {
		cout << "Pasirinkto duomenu failo nera. Programa uzbaigta";
		return 0;
	}
	std::string input = "";
	int eilute =1;
	zodis temp;
	std::multiset <string> sarasas;
	std::regex re("[.%()\\]\\[$/0123456789\\|\\-,; \"\n :]");
	std::vector<zodis> zodziai;
	while (bufferis) {
		if (!bufferis.eof()) {
			std::getline(bufferis, input);
			std::sregex_token_iterator first{ input.begin(), input.end(), re, -1 }, last;
			std::vector<std::string> tokens{ first, last };
			for (auto &t : tokens) {
				std::for_each(t.begin(), t.end(), [](char& c) {
					c = ::tolower(c);
					});
				for (auto &i : zodziai) {
					if (t == i.vardas) { 
						i.eilutes.push_back(eilute);
						sarasas.insert(t);
						goto loop;
					}
				}
				temp.vardas = t;
				temp.eilutes.push_back(eilute);
				zodziai.push_back(temp);
				temp.eilutes.clear();
				sarasas.insert(t);
	loop:
				continue;
			}
			eilute++;
		}
	}
	std::ofstream fr("rezultatai.txt");
	fr << "| " << std::left << std::setw(15) << "Zodis" << "|" << std::setw(5) << "Kartai" << "| " << std::setw(50) << "Eil.numeris" << std::endl;
	for (auto &i : zodziai) {
		if (i.vardas == "" || sarasas.count(i.vardas)<2) continue;
		fr << "| " <<std::left <<std::setw(15) << i.vardas << "| " << std::setw(5) << sarasas.count(i.vardas) << "| ";
		for (auto y : i.eilutes) {
			fr << y << " ";
		}
		fr << std::endl;
	}
	fr.close();
	return 0;
}