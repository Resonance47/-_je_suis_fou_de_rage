#include <iostream>
#include <conio.h>
#include <windows.h>
//#include <string>
//#include <sstream>
#include <fstream>
#define rusific 1251
#define cls system("cls");

//�������������� ������� ��� ��������
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
	int middle = 0, // ���������� ��� �������� ������� �������� �������� �������
		low = 0, // ������ ������� �������� � �������
		high = size - 1; // ������ ���������� �������� � �������

	while (low < high)
	{
		middle = low + (high - low) / 2; // ������ ������ �������� ��������
		value <= arr[middle] ? high = middle : low = middle + 1;    // ������ �������� ������� ��� ��� 
	}


	if (arr[high] == value)
		return high;
	else
		return -1;
}
void double_cin(double& p_double)//������� ����� ���������� ���� double � �������
{
	while (!(std::cin >> p_double) || std::cin.get() != '\n')//���� ���� �� double
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "��-����� �� ���-�� ����� �� ���, ���������� ��������� ����: ";
	}
}
void int_cin(int& p_int)//������� ����� ���������� ���� int � �������
{
	while (true)
	{
		while (!(std::cin >> p_int) || std::cin.get() != '\n')//���� ������� ���-�� �� ��
		{
			std::cout << "���! ������ �� ����� ���-�� �� ��" << std::endl;
			//std::cin.sync();
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "���������� ��� ���: ";
		}
		if (p_int > 0)//�� ������� ������������ ��� ����� ����������� �������, ��� ���������� ������ ������������� �����
			break;
		else
		{
			std::cout << "���! ������ �� ����� ���-�� �� ��" << std::endl;
			std::cout << "���������� ��� ���: ";
		}

	}
}
//

//����� ��� ���� ������
class Matrix
{
private:
	bool status = 0;//������ ������������� ������� - ���������� ��������� ������ �������
	void build()//��������� ������ ��� �������
	{
		matrix = new double* [N];
		for (int i = 0; i < N; i++)
		{
			matrix[i] = new double[N];
		}
	}
	void read()//������ �� �����
	{
		char key;
		std::ifstream in(adress); // �������� ���� ��� ������
		if (in)
		{
			in >> key;
			while (key != matrix_name)//���� �������
			{
				in >> key;
			}
			in >> N;//��������� ������ � �����������
			build();
			for (int i = 0; i < N; i++)//������� �������
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
	void cin_m()//���� ������� � ����������
	{

		std::cout << "������� ������� " << matrix_name << ": " << std::endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				std::cout << "������� ������� �������: " << " " << matrix_name << "[" << i + 1 << "; " << j + 1 << "] = ";
				double_cin(matrix[i][j]);//������ ������� �������, �������� ������������ �����
			}
		}
		status = 0;
	}
	int N;//����������� �������
	char matrix_name;
	std::string adress;//������ ����� ��� ������ � ������
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
		std::cout << "������� ����������� ������� " << matrix_name << ": ";
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
	void output()//����� �������
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
	void red()//�������������� �������
	{
		if (!status)
		{
			std::cout << "You wanna red matrix " << matrix_name << ":" << std::endl;
			output();
			std::cout << "Select an item" << std::endl;
			std::cout << "Enter line number: ";
			int line;
			int_cin(line);
			while (line > N || line < 1)//���� ������ �������� ���
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
	void recall()//������ � ����
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
			for (int i = 0; i < N; i++)//����� ���������
			{
				for (int j = 0; j < N; j++)
				{
					if (max_value < matrix[i][j])
					{
						max_value = matrix[i][j];
					}
				}
			}
			if (max_value!=0)//������ �� ������� �� ����
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
			double* max = new double[A.N + B.N];//������ �� ����� �����������
			int k = 0;//������� �������������
			for (int j = 0; j < A.N; j++)//���� ��������� � �������� ������� �
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
			for (int i = 0; i < B.N; i++)//���� ��������� � ������� ������� B
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
			qsort(max, k, sizeof(max[0]), compare);//���������� ��� ����������� ��������� ������

			for (int i = 0; i < N; i++)//��������� �� ���� ���������� ������� � � �������� ����������� �������� ������
			{
				for (int j = 0; j < N; j++)
				{
					int index = bin_poisk(max, k, matrix[i][j]);//���� ������� � ������� max � ������� ���������� ������
					if (index != -1)
					{
						matrix[i][j] = 0;
					}
				}
			}
			delete[] max;//�� �������� ��������� ������
		}
		else
		{
			std::cout << "Something went wromg...\n";
			system("pause");
		}
	}

	~Matrix()//����������
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

//����
int menu()
{
	int n = 5;
	char choice = 'p';
	while (choice != 13)//���� �� ������ enter
	{
		if (choice != 13)//�� enter?
		{
			if (n == 5)
			{
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mEnter matrix         \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "  " << "Complete the task �5 " << "  " << std::endl;
				std::cout << "  " << "Complete the task �15" << "  " << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 0;
			}
			else if (n == 0)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mRead matrix          \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "  " << "Complete the task �5 " << "  " << std::endl;
				std::cout << "  " << "Complete the task �15" << "  " << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 1;

			}
			else if (n == 1)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mEdit matrix          \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Complete the task �5 " << "  " << std::endl;
				std::cout << "  " << "Complete the task �15" << "  " << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 2;
			}
			else if (n == 2)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mComplete the task �5 \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Complete the task �15" << "  " << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 3;
			}
			else if (n == 3)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "  " << "Complete the task �5 " << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mComplete the task �15\x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				std::cout << "  " << "Write matrix         " << "  " << std::endl;
				n = 4;
			}
			else if (n == 4)
			{
				std::cout << "  " << "Enter matrix         " << "  " << std::endl;
				std::cout << "  " << "Read matrix          " << "  " << std::endl;
				std::cout << "  " << "Edit matrix          " << "  " << std::endl;
				std::cout << "  " << "Complete the task �5 " << "  " << std::endl;
				std::cout << "  " << "Complete the task �15" << "  " << std::endl;
				std::cout << "\x1b[31m>\x1b[0m " << "\x1b[33mWrite matrix         \x1b[0m" << " \x1b[31m<\x1b[0m" << std::endl;
				n = 5;
			}
		}
		std::cout << "\x1b[6A";
		choice = _getch();//���������
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