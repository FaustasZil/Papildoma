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
	std::regex re("(?:(?:https?|ftp):\\/\\/)?[\\w/\\-?=%.]+\\.[\\w/\\-&?=%.]+"); //https://stackoverflow.com/questions/6038061/regular-expression-to-find-urls-within-a-string?page=1&tab=scoredesc#tab-top
	input = bufferis.str();
	std::sregex_token_iterator first{ input.begin(), input.end(), re}, last;
	std::vector<std::string> tokens{ first, last };
	for (auto& t : tokens) {
		std::for_each(t.begin(), t.end(), [](char& c) {
			c = ::tolower(c);
		});
		cout << t<<std::endl;
	}

	return 0;
}