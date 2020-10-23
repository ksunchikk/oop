
#include <iostream>
#include <stdio.h>
#include "BigInt_a.h"
using namespace Prog3a;
int main() {
	BigInt f, s;
	int id = 1;
	while (id) {
		std::cout << "Enter first big integer" << std::endl << "First: ";
		try {
			f=f.InputStr();
		}
		catch (const std::exception& msg) {
		     std::cout << msg.what() << std::endl;
		}
		std::cout << std::endl<< "Enter second big integer" << std::endl << "Second: ";
		try {
			s=s.InputStr();			
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
		std::cout<< std::endl;
		try {
			BigInt Sum(f.Sum(s));
			f.Print();
			std::cout << "+(";
			s.Print();
			std::cout << ")=";
			Sum.Print();
			std::cout << std::endl;
			}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
		try {
			BigInt Sub(f.Subtraction(s));
				f.Print();
				std::cout << "-(";
				s.Print();
				std::cout << ")=";
				Sub.Print();
				std::cout << std::endl;
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}
		std::cout << "Enter 0 to increase first number or 1 to decrease" << std::endl;
		std::cin >> id;
		if (!id) {
			try {
				BigInt f1=f.Inc();
				std::cout << "Recived number: ";
				f1.Print();
				std::cout << std::endl;
			}
			catch (const std::exception& msg) {
				std::cout << msg.what() << std::endl;
			}
		}
		else {
			BigInt f1 = f.Dec();
			std::cout << "Recived number: ";
			f1.Print();
			std::cout << std::endl;
		}
		std::cout << "Enter 0 to increase second number or 1 to decrease" << std::endl;
		std::cin >> id;
		if (!id) {
			try {
				BigInt s1=s.Inc();
				std::cout << "Recived number: ";
				s1.Print();
				std::cout << std::endl;
			}
			catch (const std::exception& msg) {
				std::cout << msg.what() << std::endl;
			}
		}
		else {
			BigInt s1 = s.Dec();
			std::cout << "Recived number: ";
			s1.Print();
		    std::cout << std::endl;
		}
		std::cout << "Enter 0 to exit or 1 to continue: ";
		std::cin >> id;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return 0;
	}


