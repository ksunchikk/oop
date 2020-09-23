namespace First {
	struct element {
		double num;
		int k;
		struct element* next;
	};
	struct line {
		int n;
		int k;
		element* num;
		line* next;
	};
	template <class type>
	int getNum(type& a)
	{
		std::cin >> a;
		if (!std::cin.good()) // обнаружена ошибка ввода или конец файла
			return -1;
		return 1;
	}
	int getNut(int&, const char*);
	double getEl(double&);
	line* input(int&, int&); // ввод матрицы
	line* input_element(line*&, int, double);
	line* input_line(line*&, int);
	line* new_line(line*&, int m);
	element* new_element(element*&, int, double);
	line* res_matrix(int m, int c, line* lines);
	element* serch_min(element*, int&, double&, int&, int&);
	void output(const char*, line*);
	void output_with_zero(const char*, line*, int, int, int);// вывод матрицы
	line* erase(line*& a, int m); // освобождение занятой памяти
	void first_zero(element*, int&, double&, int&);
}