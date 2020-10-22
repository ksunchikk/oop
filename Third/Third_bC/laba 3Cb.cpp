#include <iostream>
#include "BigInt_b.h"
using namespace Prog3b;

int main() {
	BigInt f, s;
	int id = 1;
	while (id) {
		std::cout << "Enter first big integer" << std::endl;
		std::cout << "First: ";
		std::cin >> f;
		std::cout << std::endl;
		std::cout << "Enter second big integer" << std::endl;
		std::cout << "Second: ";
		std::cin >> s;
		std::cout << std::endl;
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
				int x = 1;
				BigInt f1 = f;
				f1 <<= x;
				std::cout << "Recived number: " << f1 << std::endl;
			}
			catch (const std::exception& msg) {
				std::cout << msg.what() << std::endl;
			}
		}
		else {
			int x = 1;
			BigInt f1 = f;
			f1 >>= x;
			std::cout << "Recived number: " << f1 << std::endl;
		}
		std::cout << "Enter 0 to increase second number or 1 to decrease" << std::endl;
		std::cin >> id;
		if (!id) {
			try {
				int x = 1;
				BigInt s1 = s;
				s1 <<= x;
				std::cout << "Recived number: " << s1 << std::endl;
			}
			catch (const std::exception& msg) {
				std::cout << msg.what() << std::endl;
			}
		}
		else {
			int x = 1;
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