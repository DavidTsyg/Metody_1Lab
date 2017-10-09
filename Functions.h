#pragma once
#include <vector>
#include <string>
using namespace std;
class Simplex_Table
{
private:
	bool _min_max;
	int _number_of_equations;
	int _number_of_arguments;
	vector<vector<pair<double,pair<int, int>>>> _simplex_table;
	vector<vector<double>> _equations;
	vector<double> _conditional_values;
	vector<double> _function;
public:
	Simplex_Table();
	Simplex_Table(vector<vector<double>>& equations, vector<double>& conditional_values, vector<double>& function, int& number_of_equations, int& number_of_arguments);
	~Simplex_Table();
	const int& Give_Number_Of_Equations();
	const int& Give_Number_Of_Arguments();
	const vector<vector<pair<double, pair<int, int>>>>& Give_Simplex_Table();
	const vector<vector<double>>& Give_Equations();
	const vector<double>& Give_Conditional_Values();
	const vector<double>& Give_Function();
	void Create_Simplex_Table();
	void Print_Problem();
	void Print_Canonized_Problem();
	void Print_Simplex_Table();
//	bool Basis_Solution();
	void Opornoe_Solution();
	void Jordan_Exclusions(int solve_row, int solve_column, int solve_perem_row, int solve_perem_column);
	void Simplex_Method();
	void Just_In_Case();
	void Transform_Into_Twin();
	void Print_Twin_Problem();
	void Solve_Twin();
};
