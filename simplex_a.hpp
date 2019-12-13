//  SIMPLEX_A.HPP

#include <iostream>
#include <string>
#include <cmath>

class Simplex_A
{
public:
	const static int row = 5, col = 6;
private:
	double Matrix[row][col];
	std::string upstring[col];
	std::string leftstring[row];
	int find_reference_solution();
	int find_optimal_solution();
	int search_good_row_to_swap(int k);
	int search_good_column_to_swap(int r);
	int swap(int r, int k);
public:
	Simplex_A(double c[col - 1], double A[row - 1][col - 1], double b[row - 1], std::string var = "x_", std::string func = "F");
	~Simplex_A();
	int print();
	int start();

};
