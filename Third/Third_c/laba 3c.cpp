#include <iostream>
#include "BigInt_c.h"
using namespace Prog3c;

int main() {
	BigInt f, s;
	int id = 1;
	while (id) {
		std::cout << "Enter first big integer" << std::endl << "First: ";
		try {
			std::cin>>f;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
		std::cout << std::endl << "Enter second big integer" << std::endl << "Second: ";
		try {
			std::cin >> s;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
		std::cout << std::endl;
		if (f > s) {
			std::cout << "First number is bigger than second" << std::endl;
		}
		if (f < s) {
			std::cout << "First number is smaller than second" << std::endl;
		}
		if (f == s) {
			std::cout << "First number is equal for second" << std::endl;
		}
		try {
			BigInt Sum = f + s;
			std::cout << f << "+(" << s << ")=" << Sum << std::endl;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
		try {
			BigInt Sub = f - s;
			std::cout << f << "-(" << s << ")=" << Sub << std::endl;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
		std::cout << "Enter 0 to increase first number or 1 to decrease" << std::endl;
		std::cin >> id;
		if (!id) {
			try {
				std::cout << "Enter number of digits for increasing" << std::endl;
				int x;
				std::cin >> x;
				BigInt f1 = f;
				f1 <<= x;
				std::cout << "Recived number: " << f1 << std::endl;
			}
			catch (const std::exception& msg) {
				std::cout << msg.what() << std::endl;
			}
		}
		else {
			std::cout << "Enter number of digits for decreasing" << std::endl;
			int x;
			std::cin >> x;
			BigInt f1 = f;
			f1 = f1 >>= x;
			std::cout << "Recived number: " << f1 << std::endl;
		}
		std::cout << "Enter 0 to increase second number or 1 to decrease" << std::endl;
		std::cin >> id;
		if (!id) {
			try {
				std::cout << "Enter number of digits for increasing" << std::endl;
				int x;
				std::cin >> x;
				BigInt s1 = s;
				s1 <<= x;
				std::cout << "Recived number: " << s1 << std::endl;
			}
			catch (const std::exception& msg) {
				std::cout << msg.what() << std::endl;
			}
		}
		else {
			std::cout << "Enter number of digits for decreasing" << std::endl;
			int x;
			std::cin >> x;
			BigInt s1 = s;
			s1 >>= x;
			std::cout << "Recived number: " << s1 << std::endl;
		}
		std::cout << "Enter 0 to exit or 1 to continue: ";
		std::cin >> id;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return 0;
}


