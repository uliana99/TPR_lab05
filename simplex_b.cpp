//  SIMPLEX_B.CPP

#include "simplex_b.hpp"

Simplex_B::Simplex_B(double c[col - 1], double A[row - 1][col - 1], double b[row - 1], std::string var, std::string func)
{
	int i = 0, j = 0;
	for (i = 0; i < row - 1; i++)
	{
		Matrix[i][0] = b[i];
	}
	for (i = 0; i < row - 1; i++)
	{
		for (j = 1; j < col; j++)
		{
			Matrix[i][j] = A[i][j - 1];
		}
	}
	for (j = 1; j < col; j++)
	{
		Matrix[row - 1][j] = c[j - 1];
	}
	Matrix[row - 1][0] = 0;
	upstring[0] = "S_i0";
	for (j = 1; j < col; j++)
	{
		upstring[j] = var + std::to_string(j);
	}
	for (i = 0; i < row - 1; i++)
	{
		leftstring[i] = var + std::to_string(i + col);
	}
	leftstring[row - 1] = func;
}

Simplex_B::~Simplex_B()
{
}

int Simplex_B::print()
{
	int i = 0, j = 0;
	std::cout << '\t';
	for (j = 0; j < col; j++)
	{
		std::cout.setf(std::ios::left);
		std::cout.width(8);
		std::cout << upstring[j];
	}
	std::cout.setf(std::ios::fixed);
	std::cout.precision(3);
	std::cout << std::endl;
	for (i = 0; i < row; i++)
	{
		std::cout.width(7);
		std::cout << leftstring[i] << ' ';
		for (j = 0; j < col; j++)
		{
			std::cout.width(7);
			std::cout << Matrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return 0;
}


int Simplex_B::start()
{
	std::cout << "На основе первоначальных данных составлена симплекс-таблица:" << std::endl;
	print();
	std::cout << "Ищем опорное решение:" << std::endl;
	if (find_reference_solution()<0)
		std::cout << "Опорное решение не найдено!";
	std::cout << "Так как все элементы столбца S_i0 неотрицательны, имеем опорное решение. \nАнализируем строку " << leftstring[row - 1] << ":" << std::endl;
	if (find_optimal_solution() < 0)
		std::cout << "Опорное решение не найдено!";
	else
	{
		std::cout << "Оптимальное решение: ";
		for (int j = 1; j < col; j++)
		{
			std::cout << upstring[j] << " = ";
		}
		std::cout << "0, ";
		for (int i = 0; i < row - 1; i++)
		{
			std::cout << leftstring[i] << " = " << Matrix[i][0] << ", ";
		}
		std::cout << "\nЦелевая функция " << leftstring[row - 1] << " = " << abs(Matrix[row - 1][0]) << std::endl << std::endl;
	}
	return 0;
}


int Simplex_B::find_reference_solution()
{
	int i = 0, j = 0;
	int r = 0, k = 0;
	int count_for_while = 1;
	while (count_for_while) {
		for (i = 0; i < row - 1; i++) {
			if (Matrix[i][j] < 0) {

				r = i;
				k = search_good_column_to_swap(r);
				if (k < 0) {
					std::cout << "Нет возможных решений!" << std::endl;
					return -1;
				}
				r = search_good_row_to_swap(k);
				if (r < 0) {
					std::cout << "Нет возможных решений!" << std::endl;
					return -1;
				}
				swap(r, k);
				count_for_while = 2;
				i = row;
			}
		}
		if (count_for_while != 1) count_for_while = 1;
		else count_for_while = 0;
	}
	return 0;
}

int Simplex_B::search_good_column_to_swap(int r)
{
	int j = 0;
	for (j = 1; j < col; j++)
	{
		if (Matrix[r][j] < 0)
		{
			std::cout << upstring[j] << " - разрешающий столбец" << std::endl;
			return j;
		}
	}
	return -1;

}

int Simplex_B::find_optimal_solution()
{
	int i = row - 1, j = 0;
	int r = 0, k = 0;
	int count_for_while = 1;
	while (count_for_while)
	{
		for (j = col - 1; j > 0; j--)
		{
			if (Matrix[i][j] >= 0)
			{
				std::cout << upstring[j] << " - разрешающий столбец. Ищем разрешающую строку." << std::endl;

				k = j;
				r = search_good_row_to_swap(k);
				if (r < 0)
				{
					std::cout << "Нет возможных решений!" << std::endl;
					return -1;
				}
				swap(r, k);
				count_for_while = 2;
				j = col;
			}
		}
		if (count_for_while != 1) count_for_while = 1;
		else count_for_while = 0;
	}
	return 0;
}

int Simplex_B::search_good_row_to_swap(int k)
{
	int i = 0, j = 0;
	int imin = 0;
	int count_of_good_rows = 0;
	for (i = 0; i < row - 1; i++)
	{
		if (Matrix[i][k] != 0 && Matrix[i][j] / Matrix[i][k] > 0)
		{
			if (count_of_good_rows == 0) imin = i;
			count_of_good_rows++;
			if (Matrix[i][j] / Matrix[i][k] < Matrix[imin][j] / Matrix[imin][k]) imin = i;
		}
	}
	if (count_of_good_rows == 0) return -1;
	std::cout << leftstring[imin] << " - разрешающая строка." << std::endl;
	return imin;
}

int Simplex_B::swap(int r, int k)
{
	std::cout << "Заменим базисы " << leftstring[r] << " <-> " << upstring[k] << std::endl;

	std::string temp;
	temp = leftstring[r];
	leftstring[r] = upstring[k];
	upstring[k] = temp;

	int i = 0, j = 0;
	Matrix[r][k] = 1 / Matrix[r][k];
	for (j = 0; j < col; j++)
	{
		if (j != k)
		{
			Matrix[r][j] = Matrix[r][j] * Matrix[r][k];
		}
	}
	for (i = 0; i < row; i++)
	{
		if (i != r)
		{
			Matrix[i][k] = -1 * Matrix[i][k] * Matrix[r][k];
		}
	}
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (i != r && j != k)
			{
				Matrix[i][j] = Matrix[i][j] + Matrix[r][j] * Matrix[i][k] / Matrix[r][k];
			}
		}
	}

	std::cout << "Получаем симплекс-таблицу" << std::endl;
	print();

	return 0;
}
