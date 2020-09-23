#include <iostream>
#include "First.h"

namespace First
{
	line* erase(line*& lines, int m)
	{
		line** ptr1 = &lines;
		while (*ptr1 != nullptr) {
			element** ptr = &(*ptr1)->num;
			element* tmp = nullptr;
			while (*ptr != nullptr) {
				tmp = *ptr;
				*ptr = (*ptr)->next;
				delete tmp;
			}
			line* tmp1 = nullptr;
			tmp1 = *ptr1;
			(*ptr1) = (*ptr1)->next;
			delete tmp1;
		}
		return nullptr;
	}
	line* input(int& resl, int& resc)
	{
		line* lines = nullptr;
		int m, c, k = 0, lr = 0, cr = 0;
		if (getNut(m, "Enter number of lines: -> ") < 0) { return nullptr; }
		if (getNut(c, "Enter number of columns: -> ") < 0) { return nullptr; }
		do {//заполнение строк
			std::cout << "If you want to add new elements at the line enter 0. If not enter another number ->";
			getNum(k);
			if (k == 0) {//хочет добавить
				double recnum = 0, rec = 0;
				std::cout << "Enter number of matrix line ->";//выбор строки для добавления
				getNum(lr);
				if (lr <= m && lr > 0) {
					line* ptr1 = input_line(lines, lr);
					while (ptr1->n != lr) { ptr1 = ptr1->next; }
					std::cout << "Enter number of matrix column. If you want to end your adding at chosen line enter number <= 0" << std::endl;//ввод элементов в строку в паре столбец/значение
					do {
						std::cout << "Column number->";//номер колонки
						if (getNum(cr) < 0) {
							erase(lines, m);
							return nullptr;
						}
						if (cr <= c && cr > 0) {//если больше нуля - ввод значения, если меньше или равно - выход из ввода в строку, если больше количества столбцов - Incorrect number
							ptr1 = input_element(ptr1, cr, recnum);
						}
					} while (cr > 0);
				}
				else { std::cout << "Incorrect number" << std::endl; }
			}
		} while (k == 0);
		resl = m, resc = c;
		return lines;
	}
	line* res_matrix(int m, int c, line* lines) {
		line* result = new line;
		result->k = 0;
		int min_index = 0, r = 0, k = 0;
		double min = 0;
		line* a = lines, * res = result;
		while (a != nullptr) {
			element* ptr = a->num;
			if (ptr != nullptr) {
				ptr = serch_min(ptr, min_index, min, k, r);
				res->k = k;
				if ((ptr->k < c) && (min > 0)) {
					res->k = c - r - 1;
					res->num = nullptr;
				}
				else {
					element* tmp = a->num;
					while (tmp->k != min_index) { tmp = tmp->next; }
					res->num = tmp;
					res->n = a->n;
				}
				min_index = 0, min = 0;
				res->next = new line;
				res->next->k = 0;
			}
			a = a->next;
			if (a) {
				res = res->next;
			}
			else {
				res->next = nullptr;
			}
		}
		return result;
	}
	element* serch_min(element* ptr, int& min_index, double& min, int& k, int& r) {
		first_zero(ptr, min_index, min, k);
		while (ptr != nullptr && ptr->next != nullptr) {//пробегаем по списку сущ.элементов
			if (ptr->num < min) {//если меньше минимума, новый минимум и индекс
				min_index = ptr->k;
				min = ptr->num;
				k = 0;
			}
			else if ((ptr->next->k - ptr->k) > 1) {//если больше, проверяем на нули. если есть расстояние между индексами, то сравниваем минимум с 0, если больше - переприсваиваем индексы и минимум=0
				if (min > 0) {
					min_index = ptr->next->k;
					min = 0;
					k = ptr->next->k - ptr->k - 1;
				}
			}
			r = ptr->k;//запоминаем номер исследуемого, чтобы для проверки последнего знать, сколько было нулей между последним в цикле и в списке
			ptr = ptr->next;
		}
		if (ptr->num < min) {
			min_index = ptr->k;
			min = ptr->num;
			k = 0;
		}
		return ptr;
	}
	void first_zero(element* ptr, int& min_index, double& min, int& k) {
		if (ptr->k > 1) {
			min_index = ptr->k;
			min = 0;
			k = ptr->k - 1;
		}
		else {
			min = ptr->num;
			min_index = ptr->k;
			k = 0;
		}
	}
	line* input_line(line*& lines, int lr) {
		line* ptr = lines;
		line* tmp = nullptr;
		new_line(tmp, lr);
		if (ptr != NULL) {
			while (ptr != nullptr) {
				if (ptr->k == lr) {
					delete tmp;
					return ptr;}
				else if (ptr->next != nullptr) {//если следующий элемент есть, проверяем больше ли он текущего, и меньше ли следующего. если да, то вставяем, если нет, двигаемся дальше
					if (ptr->n < lr && ptr->next->n>lr) {
						tmp->next = ptr->next;
						ptr->next = tmp;
						break;}
					if (ptr->n > lr) {
						tmp->next = ptr;
						lines = tmp;
						break;}
	                }
				else {//следующего нет
					if (ptr->n < lr) {
						ptr->next = new_line(ptr->next, lr);
						delete tmp;}
					if (ptr->n > lr) {
						tmp->next = ptr;
						lines = tmp;}
					break;}
				ptr = ptr->next;
			}
		}
		else {
			lines = new_line(lines, lr);
			delete tmp;
		}
		return lines;
	}
	line* new_line(line*& a, int lr) {
		a = new line;
		a->num = nullptr;
		a->n = lr;
		a->k = 0;
		a->next = nullptr;
		return a;
	}
	line* input_element(line*& ptr1, int cr, double recnum) {
		element* ptr = ptr1->num, * tmp = nullptr;
		int rec = 0;
		getEl(recnum);
		new_element(tmp, cr, recnum);
		if (ptr != NULL) {
			while (ptr != nullptr) {//проверяем строку на пустоту при первой иттерации, и на конец строки при последующих, пробегаясь по списку элементов
				if (ptr->k == cr) {//нашелся элемент с таким номером. В зависимости от решения пользователя либо заменяем, либо пропускаем
					std::cout << "There's element with another number. Do you want to change it? Enter 0 to change and 1 to continue unchanged" << std::endl;
					getNum(rec);
					if (rec == 0) { ptr->num = recnum; }
					delete tmp;
					break;}
				else if (ptr->next != nullptr) {//если следующий элемент есть, проверяем больше ли он текущего, и меньше ли следующего. если да, то вставяем, если нет, двигаемся дальше
					if (ptr->k < cr && ptr->next->k>cr) {
						tmp->next = ptr->next;
						ptr->next = tmp;
						break;}
					if (ptr->k > cr) {
						tmp->next = ptr;
						ptr1->num = tmp;
						break;}
				}
				else {//следующего нет
					if (ptr->k < cr) {
						ptr->next = new_element(ptr->next, cr, recnum);
						delete tmp;
						break;
					}
					else {
						tmp->next = ptr;
						ptr1->num = tmp;
						break;
					}
				}
				ptr = ptr->next;
			}
		}
		else {//первый элемент в строке
			ptr1->num = new_element(ptr1->num, cr, recnum);
			delete tmp;}
		return ptr1;
	}
	element* new_element(element*& tmp, int cr, double recnum) {
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
		return tmp;
	}
	void output(const char* msg, line* a) {
		int i, j;
		std::cout << msg << ":\n";
		while (a != nullptr) {
			element* ptr = a->num;
			while (ptr != nullptr) {
				std::cout << "[" << a->n << "," << ptr->k << "]" << " " << "{" << ptr->num << "}" << " ";
				ptr = ptr->next;
			}
			std::cout << std::endl;
			a = a->next;
		}
	}
	int getNut(int& a, const char* msg) {
		const char* pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << msg;
			pr = "You are wrong; repeat please!";
			if (getNum(a) < 0) {
				return -1;
			}
		} while (a < 1);
	}
	double getEl(double& a) {
		const char* pr = "";
		do {
			std::cout << pr;
			std::cout << "Element number->";
			pr = "You enter 0. Try again.";
			if (getNum(a) < 0) {
				return -1;
			}
		} while (a == 0);
		std::cout << std::endl;
		return 1;
	}
}
