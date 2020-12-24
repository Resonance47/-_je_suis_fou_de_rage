#include <iostream>
#include <conio.h>
#include <windows.h>
//#include <string>
//#include <sstream>
#include <fstream>
#define rusific 1251
#define cls system("cls");

//дополнительные функции для удобства
int compare(const void* a, const void* b)
{
	const double* x = (double*)a;
	const double* y = (double*)b;

	if (*x > * y)
		return 1;
	else if (*x < *y)
		return -1;

	return 0;
}
int bin_poisk(double* arr, int size, double value)
{
	int middle = 0, // переменная для хранения индекса среднего элемента массива
		low = 0, // индекс первого элемента в массиве
		high = size - 1; // индекс последнего элемента в массиве

	while (low < high)
	{
		middle = low + (high - low) / 2; // меняем индекс среднего значения
		value <= arr[middle] ? high = middle : low = middle + 1;    // найден ключевой элемент или нет 
	}


	if (arr[high] == value)
		return high;
	else
		return -1;
}
void double_cin(double& p_double)//функция ввода переменной типа double с защитой
{
	while (!(std::cin >> p_double) || std::cin.get() != '\n')//если ввел не double
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "По-моему вы что-то ввели не так, попробуйте повторить ввод: ";
	}
}
void int_cin(int& p_int)//функция ввода переменной типа int с защитой
{
	while (true)
	{
		while (!(std::cin >> p_int) || std::cin.get() != '\n')//если считали что-то не то
		{
			std::cout << "Упс! Похоже Вы ввели что-то не то" << std::endl;
			//std::cin.sync();
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Попробуйте еще раз: ";
		}
		if (p_int > 0)//тк функция используется для ввода рхамерности массива, нас устраивают только положительные числа
			break;
		else
		{
			std::cout << "Упс! Похоже Вы ввели что-то не то" << std::endl;
			std::cout << "Попробуйте еще раз: ";
		}

	}
}
//

//класс для всех матриц
class Matrix
{
private:
	bool status = 0;//статус инициализации матрицы - изначально создается пустая матрица
	void build()//выделение памяти под матрицу
	{
		matrix = new double* [N];
		for (int i = 0; i < N; i++)
		{
			matrix[i] = new double[N];
		}
	}
	void read()//чтение из файла
	{
		char key;
		std::ifstream in(adress); // окрываем файл для чтения
		if (in)
		{
			in >> key;
			while (key != matrix_name)//ищем матрицу
			{
				in >> key;
			}
			in >> N;//считываем данные о размерности
			build();
			for (int i = 0; i < N; i++)//создаем матрицу
			{
				for (int j = 0; j < N; j++)
				{
					in >> matrix[i][j];
				}
			}
			status = 0;
		}
		else
		{
			std::cout << "Error! File is not found\nPress enter to continue...\n";
			system("pause");
		}
	}
	void cin_m()//ввод матрицы с клавиатуры
	{

		std::cout << "Введите матрицу " << matrix_name << ": " << std::endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				std::cout << "Введите элемент матрицы: " << " " << matrix_name << "[" << i + 1 << "; " << j + 1 << "] = ";
				double_cin(matrix[i][j]);//вводим элемент матрицы, проверяя корректность ввода
			}
		}
		status = 0;
	}
	int N;//размерность матрицы
	char matrix_name;
	std::string adress;//адресс файла для чтения и записи
	double max_value;
	double** matrix;

public:
	Matrix(char matrix_name)
	{
		this->matrix_name = matrix_name;
		status = 1;
		N = 1;
		max_value = 0;
		matrix = NULL;
	}

	void input_matrix()
	{
		std::cout << "Введите резмерность матрицы " << matrix_name << ": ";
		N = 0;
		while (N <= 0)
		{
			std::cin >> N;
		}
		build();
		cin_m();
	}
	void read_matrix(std::string adress)
	{
		this->adress = adress;
		read();
	}
	void output()//вывод матрицы
	{
		if (!status)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					std::cout << matrix[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}
		else
			std::cout << "Matrix doesn't exist\n";
	}
	void red()//редактирование матрицы
	{
		if (!status)
		{
			std::cout << "You wanna red matrix " << matrix_name << ":" << std::endl;
			output();
			std::cout << "Select an item" << std::endl;
			std::cout << "Enter line number: ";
			int line;
			int_cin(line);
			while (line > N || line < 1)//если такого элемента нет
			{
				std::cout << "Wrong! Try again: ";
				int_cin(line);
			}
			std::cout << "Select column number: ";
			int column;
			int_cin(column);
			while (column > N || column < 1)
			{
				std::cout << "Wromg! Try again: ";
				int_cin(column);
			}
			std::cout << "Enter new item [" << line << "; " << column << "]: ";
			double redact;
			double_cin(redact);
			matrix[line - 1][column - 1] = redact;
		}
		else
		{
			std::cout << "\nMatrix doesn't exist\n";
			system("pause");
		}
			

	}
	void recall()//запись в файл
	{
		if (!status)
		{
			std::ofstream outpur_file;
			outpur_file.open(adress, std::ios::app);
			if (outpur_file.is_open())
			{
				outpur_file << "\n" << matrix_name << " " << N << std::endl;
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < N; j++)
					{
						outpur_file << matrix[i][j] << " ";
					}
					outpur_file << '\n';
				}
			}
			outpur_file.close();
		}
		else
		{
			std::cout << "Something went wrong...\n";
			system("pause");
		}
	}

	void q5()
	{
		if (!status)
		{
			max_value = matrix[0][0];
			for (int i = 0; i < N; i++)//поиск максимума
			{
				for (int j = 0; j < N; j++)
				{
					if (max_value < matrix[i][j])
					{
						max_value = matrix[i][j];
					}
				}
			}
			if (max_value!=0)//зашита от деления на ноль
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < N; j++)
					{
						matrix[i][j] /= max_value;
					}
				}
			}
			else
			{
				cls;
				std::cout << "Error matrix " << matrix_name << ": division by zero is imposible\n";
				system("pause");
			}
		}
		else
		{
			std::cout << "Something went wromg...\n";
			system("pause");
		}
	}
	void q15(Matrix& A, Matrix& B)
	{
		if (!status)
		{
			double* max = new double[A.N + B.N];//массив со всеми максимумами
			int k = 0;//счетчик заполненности
			for (int j = 0; j < A.N; j++)//ищем максимумы в столбцах матрицы А
			{
				max[k] = A.matrix[0][j];
				for (int i = 0; i < A.N; i++)
				{
					if (A.matrix[i][j] > max[k])
					{
						max[k] = A.matrix[i][j];
					}
				}
				k++;
			}
			for (int i = 0; i < B.N; i++)//ищем максимумы в строках матрицы B
			{
				max[k] = B.matrix[i][0];
				for (int j = 0; j < A.N; j++)
				{
					if (B.matrix[i][j] > max[k])
					{
						max[k] = B.matrix[i][j];
					}
				}
				k++;
			}
			k;
			qsort(max, k, sizeof(max[0]), compare);//сортировка для дальнейшего бинарного поиска

			for (int i = 0; i < N; i++)//пробегаем по всем элемеентам матрицы С и заменяем необходимые элементы нудями
			{
				for (int j = 0; j < N; j++)
				{
					int index = bin_poisk(max, k, matrix[i][j]);//ищем жлемент в массиве max с помощью бинароного поиска
					if (index != -1)
					{
						matrix[i][j] = 0;
					}
				}
			}
			delete[] max;//не забываем почистить память
		}
		else
		{
			std::cout << "Something went wromg...\n";
			system("pause");
		}
	}

	~Matrix()//деструктор
	{
		if (!status)
		{
			std::cout << matrix_name;
			delete[] matrix;
		}
		std::cout << "_______";
		system("pause");
	}
};
//

//меню
int menu()
{
	int n = 5;
	char choice = 'p';
	while (choice != 13)//пока не нажали enter
	{
		if (choice != 13)//не enter?
		{
			if (n == 5)
			{
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mEnter matrix         \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "  " << "Complete the task №5 " << "  " << std::endl;
				std::cout << "  " << "Complete the task №15" << "  " << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 0;
			}
			else if (n == 0)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mRead matrix          \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "  " << "Complete the task №5 " << "  " << std::endl;
				std::cout << "  " << "Complete the task №15" << "  " << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 1;

			}
			else if (n == 1)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mEdit matrix          \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Complete the task №5 " << "  " << std::endl;
				std::cout << "  " << "Complete the task №15" << "  " << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 2;
			}
			else if (n == 2)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mComplete the task №5 \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Complete the task №15" << "  " << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 3;
			}
			else if (n == 3)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "  " << "Complete the task №5 " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mComplete the task №15\x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 4;
			}
			else if (n == 4)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "  " << "Complete the task №5 " << "  " << std::endl;
				std::cout << "  " << "Complete the task №15" << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mWrite matrix         \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				n = 5;
			}
		}
		std::cout << "\x1b[6A";
		choice = _getch();//считываем
	}

	return n;
}
void inputmenu(Matrix &A, Matrix &B, Matrix &C)
{
	std::cout << "Enter name or any other key to enter all: ";
	char a;
	std::cin >> a;
	if (a == 'A')
	{
		A.input_matrix();
	}
	else if (a == 'B')
	{
		B.input_matrix();
	}
	else if (a == 'C')
	{
		C.input_matrix();
	}
	else
	{
		A.input_matrix();
		B.input_matrix();
		C.input_matrix();
	}
}
void readmenu(Matrix& A, Matrix& B, Matrix& C, std::string addr)
{
	std::cout << "Enter name or any other key to enter all: ";
	char a;
	std::cin >> a;
	if (a == 'A')
	{
		A.read_matrix(addr);
	}
	else if (a == 'B')
	{
		B.read_matrix(addr);
	}
	else if (a == 'C')
	{
		C.read_matrix(addr);
	}
	else
	{
		A.read_matrix(addr);
		B.read_matrix(addr);
		C.read_matrix(addr);
	}
}
void editmenu(Matrix& A, Matrix& B, Matrix& C)
{
	std::cout << "Enter name or any other key to enter all: ";
	char a;
	std::cin >> a;
	if (a == 'A')
	{
		A.red();
	}
	else if (a == 'B')
	{
		B.red();
	}
	else if (a == 'C')
	{
		C.red();
	}
	else
	{
		A.red();
		B.red();
		C.red();
	}
}
void writemenu(Matrix& A, Matrix& B, Matrix& C)
{
	std::cout << "Enter name or any other key to enter all: ";
	char a;
	std::cin >> a;
	if (a == 'A')
	{
		A.recall();
	}
	else if (a == 'B')
	{
		B.recall();
	}
	else if (a == 'C')
	{
		C.recall();
	}
	else
	{
		A.recall();
		B.recall();
		C.recall();
	}
}
//
int main()
{
	SetConsoleCP(rusific);
	SetConsoleOutputCP(rusific);

	std::string adr = "bonjour.txt";
	Matrix A('A');
	Matrix B('B');
	Matrix C('C');
	int ch = 9;
	while (true)
	{
		using std::cout;
		cls;
		cout << "A:\n";
		A.output();
		cout << "B:\n";
		B.output();
		cout << "C:\n";
		C.output();

		ch = menu();
		cls;

		if (ch == 0)
		{
			inputmenu(A, B, C);
		}
		else if (ch == 1)
		{
			readmenu(A, B, C, adr);
		}
		else if (ch == 2)
		{
			editmenu(A, B, C);
		}
		else if (ch == 3)
		{
			A.q5();
			B.q5();
			C.q5();
		}
		else if (ch == 4)
		{
			C.q15(A, B);
		}
		else if (ch == 5)
		{
			writemenu(A, B, C);
		}
	}
	system("pause");
	return 47;
}