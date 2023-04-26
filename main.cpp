#include "RooksPlay.h"

int main() {

	std::cout << "\t\t\tPlay with rooks\n\n";
	std::cout << "Input count figure(from 4 to 6)\n\n";

	int number_of_rooks;
	std::cin >> number_of_rooks;

	RooksPlay play(number_of_rooks);
}