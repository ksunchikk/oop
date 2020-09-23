#include <iostream>
#include "First.h"

using namespace First;

// основная функция
int main()
{
	line* arr = nullptr; // исходный и массив
	line* res = nullptr;
	int m, c;
	arr = input(m, c); // ввод матрицы
	if (!arr) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	output("Sourced matrix", arr);
	res = res_matrix(m, c, arr);
	output("Result matrix", res);
	erase(arr, m); // освобождение памяти
	return 0;
}
