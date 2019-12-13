// MAIN.CPP

#include "simplex_a.hpp"
#include "simplex_b.hpp"

int main(int argc, char const *argv[]) {
	char char_for_while;
	double c[5] = { -1, -1, -1, -1, -1 };
	double A[4][5] = { { -15, -9, -3, -15, -19 } , { -5, -1, -8, -9, -14 } , { -5, -18, -4, -9, -9 } , { -0, -12, -9, -14, -0 } };
	double b[4] = { -1, -1, -1, -1 };

	int nach[5][4] = { { 15, 9, 3, 15 } , { 19, 5, 1, 8 } , { 9, 14, 5, 18 } , { 4, 9, 9, 0 } , { 12, 9, 14, 0 } };
	int i = 0;
	int j = 0;
	std::cout << "Пусть матрица стратегий имеет вид:\n" << std::endl;
	std::cout.setf(std::ios::left);
	std::cout.width(10);
	std::cout << "Strategy";
	for (int i = 1; i < 5; i++)
	{
		std::string temp = "b_" + std::to_string(i);
		std::cout.width(5);
		std::cout << temp;
	}
	std::cout << std::endl;
	for (i = 0; i < 5; i++)
	{
		std::string temp = "a_" + std::to_string(i+1);
		std::cout.width(10);
		std::cout << temp;
		for (j = 0; j < 4; j++)
		{
			std::cout.width(5);
			std::cout << nach[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "\nИГРОК A >> поиск смешанных стратегий:\n";

	Simplex_A *player1 = new Simplex_A(c, A, b, "u_", "W");
	player1->start();
	delete player1;

	double c1[4] = { 1, 1, 1, 1 };
	double A1[5][4] = { { 15, 9, 3, 15 } , { 19, 5, 1, 8 } , { 9, 14, 5, 18 } , { 4, 9, 9, 0 } , { 12, 9, 14, 0 } };
	double b1[5] = { 1, 1, 1, 1, 1 };

	std::cout << std::endl << "ИГРОК B >> поиск смешанных стратегий:" << std::endl;

	Simplex_B *player2 = new Simplex_B(c1, A1, b1, "v_", "Z");
	player2->start();
	delete player2;

	return 0;
}
