#include <iostream>
#include "First.h"

namespace First
{
	line* erase(line*& lines, int m)
	{
		int i;
		for (i = 0; i < m; i++) {
			element** ptr = &lines[i].num;
			element* tmp = nullptr;
			while(*ptr!=nullptr){
				tmp = *ptr;
				*ptr = (*ptr)->next;
				delete tmp;
			}
		}
		delete[] lines;
		return nullptr;
	}
	line* input(int& resl, int& resc)
	{
		const char* pr = "";
		line* lines = nullptr;
		int m, c;
		do {//ввод количества строк
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: -> ";
			pr = "You are wrong; repeat please!";
			if (getNum(m) < 0) {
				return nullptr;
			}
		} while (m < 1);

		pr = "";
		do {//ввод количества столбцов
			std::cout << pr << std::endl;
			std::cout << "Enter number of columns: -> ";
			pr = "You are wrong; repeat please!";
			if (getNum(c) < 0) {
				return nullptr;
			}
		} while (c < 1);
		std::cout << std::endl;

		try {//выделение памяти под массив и его инициализация
			lines = new line[m];
		}
		catch (std::bad_alloc & ba)
		{
			std::cout << "----— too many lines in matrix: " << ba.what() << std::endl;
			return nullptr;
		}
		for (int i = 0; i < m; i++) {
			lines[i].n = c;
			lines[i].num = nullptr;
		}

		int k = 0, lr = 0, cr = 0;
		do {//заполнение строк
			std::cout << "If you want to add new elements at the line enter 0. If not enter another number ->";
			if (getNum(k) < 0) {//решение пользователя добавить новые элементы
				erase(lines, m);
				return nullptr;
			}
			if (k == 0) {//хочет добавить
				double recnum = 0, rec = 0;
				std::cout << "Enter number of matrix line ->";//выбор строки для добавления
				if (getNum(lr) < 0) {
					erase(lines, m);
					return nullptr;
				}
				if (lr <= m && lr > 0) {
					std::cout << "Enter number of matrix column. If you want to end your adding at chosen line enter number <= 0" << std::endl;//ввод элементов в строку в паре столбец/значение
					do {
						std::cout << "Column number->";//номер колонки
						if (getNum(cr) < 0) {
							erase(lines, m);
							return nullptr;
						}
						if (cr <= c && cr > 0) {//если больше нуля - ввод значения, если меньше или равно - выход из ввода в троку, если больше количества столбцов - Incorrect number
							element* ptr = lines[lr - 1].num;
							pr = "";
							do {
								std::cout << pr;
								std::cout << "Element number->";
								pr = "You enter 0. Try again.";
								if (getNum(recnum) < 0) {
									erase(lines, m);
									return nullptr;
								}
							} while (recnum == 0);
							std::cout << std::endl;
							element* tmp = nullptr;
							try {//выделяем память под новый элемент и инициализируем его введенными значениями
								tmp = new element;;
							}
							catch (std::bad_alloc& ba)
							{
								std::cout << "----— too many elements in matrix: " << ba.what() << std::endl;
								delete tmp;
								return nullptr;
							}
							tmp->k = cr;
							tmp->num = recnum;
							tmp->next = nullptr;
							
							if (ptr != NULL) {
								while (ptr != nullptr) {//проверяем строку на пустоту при первой иттерации, и на конец строки при последующих, пробегаясь по списку элементов
									if (ptr->k == cr) {//нашелся элемент с таким номером. В зависимости от решения пользователя либо заменяем, либо пропускаем
										std::cout << "There's element with another number. Do you want to change it? Enter 0 to change and 1 to continue unchanged" << std::endl;
										if (getNum(rec) < 0) {
											erase(lines, m);
											return nullptr;
										}
										if (rec == 0) {
											ptr->num = recnum;
										}
										delete tmp;
										break;
									}
									else if (ptr->next != nullptr) {//если следующий элемент есть, проверяем больше ли он текущего, и меньше ли следующего. если да, то вставяем, если нет, двигаемся дальше
										if (ptr->k < cr && ptr->next->k>cr){
											tmp->next = ptr->next;
											ptr->next = tmp;
											break;
										}
										if (ptr->k > cr) {
											tmp->next = ptr;
											lines[lr - 1].num = tmp;
											break;
										}
									}
									else {//следующего нет
										if (ptr->k < cr) {
											ptr->next = new element;
											ptr->next->k = cr;
											ptr->next->num = recnum;
											ptr->next->next = nullptr;
											delete tmp;
										}
										if (ptr->k > cr) {
											tmp->next = ptr;
											lines[lr - 1].num = tmp;
										}
										break;
									}
									ptr = ptr->next;
								}
							}
							else{//первый элемент в строке
								try {
									lines[lr-1].num = new element;
								}
								catch (std::bad_alloc& ba)
								{
									std::cout << "----— too many elements in matrix: " << ba.what() << std::endl;
									erase(lines, lr-1);
									return nullptr;
								}
								lines[lr - 1].num->num = recnum;
								lines[lr - 1].num->k = cr;
								lines[lr - 1].num->next = nullptr;
								delete tmp;
							}
									
						}
					} while (cr>0);
				}
				else { std::cout << "Incorrect number" << std::endl; }
			}
		} while (k == 0);
		resl = m;
		resc = c;
		return lines;
	}
	line* res_matrix(int m, int c,line* lines) {
		line* result = new line[m];
		int min_index = 0, r=0;
		double min = 0;
		for (int i = 0; i < m; i++) {
			result[i].num = nullptr;
			element* ptr = lines[i].num;
			if (ptr != nullptr) {
				if (ptr->k > 1) {//проверяем на первые нули. если они есть, то min=0, индекс от первого элемента
					min_index = ptr->k;
					min = 0;
					result[i].k = ptr->k - 1;
				}
				else {//если нет, то индекс 1, минимум = значению первого
					min = ptr->num;
					min_index = ptr->k;
					result[i].k = 0;
				}
				while (ptr != nullptr && ptr->next != nullptr) {//пробегаем по списку сущ.элементов
					if (ptr->num < min) {//если меньше минимума, новый минимум и индекс
						min_index = ptr->k;
						min = ptr->num;
						result[i].k = 0;
					}
					else if ((ptr->next->k - ptr->k) > 1) {//если больше, проверяем на нули. если есть расстояние между индексами, то сравниваем минимум с 0, если больше - переприсваиваем индексы и минимум=0
						if (min > 0) {
							min_index = ptr->next->k;
							min = 0;
							result[i].k = ptr->next->k - ptr->k - 1;
						}
					}
				    r = ptr->k;//запоминаем номер исследуемого, чтобы для проверки последнего знать, сколько было нулей между последним в цикле и в списке
					ptr = ptr->next;
				}
				//проверка последнего элемента. если он меньше - минимум переприсваиваем, нет - идем дальше
				if (ptr->num < min) {
				    min_index = ptr->k;
				    min = ptr->num;
					result[i].k = 0;
				}
				if ((ptr->k < lines[i].n) && (min > 0)) {//проверка на нули в конце, если все предыдущие были без дырок. если первый ноль в конце, то в строку не записываем ничего
					result[i].n = 0;
					result[i].k = ptr->k - r - 1;
				}
				else {//первые нули не найдены - пробегаем до элемента с найденным индексом и в строку записываем
					element* tmp = lines[i].num;
					while (tmp->k != min_index) {
						tmp = tmp->next;
					}
					element** ptr1 = &result[i].num;
					*ptr1 = tmp;
				}
				min_index = 0;
				min = 0;
			}
		}
		return result;
	}

	void output(const char* msg, line* a, int m) {
		int i, j;
		std::cout << msg << ":\n";
		for (i = 0; i < m; ++i) {
			element* ptr = a[i].num;
			while (ptr != nullptr) {
				std::cout << "["<< i+1 << "," << ptr->k<<"]" << " "<<"{"<< ptr->num <<"}" << " " ;
				ptr = ptr->next;
			}
			std::cout << std::endl;
		}
	}
}