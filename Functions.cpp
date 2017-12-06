#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "Functions.h"
#include <iomanip>

using namespace std;

Simplex_Table::Simplex_Table() {}
Simplex_Table::Simplex_Table(vector<vector<double>>& equations, vector<double>& conditional_values, vector<double>& function, int& number_of_equations, int& number_of_arguments)
{
	_equations = equations;
	_conditional_values = conditional_values;
	_function = function;
	_number_of_equations = number_of_equations;
	_number_of_arguments = number_of_arguments;
	vector<pair<double, pair<int, int>>> buffer_vector;
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		buffer_vector.push_back(make_pair(_conditional_values[i], make_pair(_number_of_arguments + 1 + i, 0)));
		for (auto j = 0; j < _equations[0].size(); ++j)
			buffer_vector.push_back(make_pair(_equations[i][j], make_pair(_number_of_arguments + 1 + i, j + 1)));
		_simplex_table.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _function.size(); ++i)
		buffer_vector.push_back(make_pair((_function[i])*(-1), make_pair(_number_of_arguments + 1 + i, 0)));
	_simplex_table.push_back(buffer_vector);
}
Simplex_Table::~Simplex_Table() {}

const int& Simplex_Table::Give_Number_Of_Equations() { return _number_of_equations; }
const int& Simplex_Table::Give_Number_Of_Arguments() { return _number_of_arguments; }
const vector<vector<pair<double, pair<int, int>>>>& Simplex_Table::Give_Simplex_Table() { return _simplex_table; }
const vector<vector<double>>& Simplex_Table::Give_Equations() { return _equations; }
const vector<double>& Simplex_Table::Give_Conditional_Values() { return _conditional_values; }
const vector<double>& Simplex_Table::Give_Function() { return _function; }

void Simplex_Table::Create_Simplex_Table()
{
	double buffer;
	vector<pair<double, pair<int, int>>> buffer_vector;
	cout << "min or max (for max input 1, for min input 0) : ";
	cin >> _min_max;
	cout << "Input the number of equations ( more than 0 ) : ";
	cin >> _number_of_equations;
	while (_number_of_equations == 0)
	{
		cout << "Input the number of equations ( more than 0 ) : ";
		cin >> _number_of_equations;
	}
	cout << "Input the number of arguments ( more than 0 ) : ";
	cin >> _number_of_arguments;
	while (_number_of_arguments == 0)
	{
		cout << "Input the number of arguments ( more than 0 ) : ";
		cin >> _number_of_arguments;
	}

	if (_number_of_equations > _number_of_arguments)
	{
		cout << "The number of arguments is lesss than the number of equations";
		exit(EXIT_FAILURE);
	}
	cout << "Now filling up equations" << endl;
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		double buffer;
		vector<double> empty;
		_equations.push_back(empty);
		for (auto j = 0; j < _number_of_arguments; ++j)
		{
			cout << "Input the multiplier by the number : ";
			cin >> buffer;
			_equations[i].push_back(buffer);
		}
		cout << "Input the conditional value : ";
		cin >> buffer;
		_conditional_values.push_back(buffer);
	}
	cout << "Creating the function" << endl;
	cout << "Input the free value : ";
	cin >> buffer;
	_function.push_back(buffer);
	cout << "Input the funtion arguments" << endl;
	for (auto i = 0; i < _number_of_arguments; ++i)
	{
		cout << "x" << i + 1 << " : ";
		cin >> buffer;
		_function.push_back(buffer);
	}

	/*	cout << "These are the arguments" << endl;
	for (auto i = 0; i < _number_of_equations; ++i)
	{
	for (auto j = 0; j < _number_of_arguments; ++j)
	{
	cout << _equations[i][j] << " ";
	}
	cout << endl;
	}*/
	/*	cout << "This is the function" << endl;
	for (auto i = 0; i < _number_of_arguments + 1; ++i)
	{
	cout << _function[i] << " + ";
	}
	cout << endl; */
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		buffer_vector.push_back(make_pair(_conditional_values[i], make_pair(_number_of_arguments + 1 + i, 0)));
		for (auto j = 0; j < _equations[0].size(); ++j)
			buffer_vector.push_back(make_pair(_equations[i][j], make_pair(_number_of_arguments + 1 + i, j + 1)));
		_simplex_table.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _function.size(); ++i)
	{
		if (!_min_max)
		{
			if (_function[i] != 0)
				buffer_vector.push_back(make_pair(_function[i], make_pair(_number_of_equations + 1, i)));
			else
				buffer_vector.push_back(make_pair((_function[i]) * (-1), make_pair(_number_of_equations + 1, i)));
		}
		else
		{
			if (_function[i] != 0)
				buffer_vector.push_back(make_pair(_function[i], make_pair(_number_of_equations + 1, i)));
			else
				buffer_vector.push_back(make_pair(_function[i], make_pair(_number_of_equations + 1, i)));
		}
		/*		if (_function[i] != 0)
		buffer_vector.push_back(make_pair((_function[i])*(-1), make_pair(_number_of_equations + 1, i)));
		else
		buffer_vector.push_back(make_pair(_function[i], make_pair(_number_of_equations + 1, i)));*/
	}
	_simplex_table.push_back(buffer_vector);
	/*	cout << "This is the simplex table" << endl;
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
	for (auto j = 0; j < _simplex_table[0].size(); ++j)
	cout << _simplex_table[i][j].first << "  ";
	cout << endl;
	}*/
}

void Simplex_Table::Print_Problem()
{
	// Выводим уравнение F
	vector<pair<double, unsigned int>> buffer_vector;
	for (auto i = 1; i < _function.size(); ++i)
	{
		if (_function[i] != 0)
			buffer_vector.push_back(make_pair(_function[i], i));
	}
	cout << "F = ";
	if (_function[0] != 0)
	{
		if (buffer_vector[0].first > 0)
			cout << buffer_vector[0].first << " + ";
		else
			cout << buffer_vector[0].first << " - ";
	}
	else
	{
		if (buffer_vector[0].first < 0)
			cout << buffer_vector[0].first << " - ";
	}
	for (auto i = 0; i < buffer_vector.size() - 1; ++i)
	{
		if (buffer_vector[i + 1].first > 0)
		{
			cout << buffer_vector[i].first << "*x" << buffer_vector[i].second << " + ";
		}
		else
		{
			cout << abs(buffer_vector[i].first) << "*x" << buffer_vector[i].second << " - ";
		}
	}
	cout << buffer_vector.back().first << "*x" << buffer_vector.back().second << " -> max"<< endl;
	buffer_vector.clear();
	// Выводим неравенства
	for (auto i = 0; i < _equations.size(); ++i)
	{
		for (auto j = 0; j < _equations.size(); ++j)
		{
			if (_equations[i][j] != 0)
				buffer_vector.push_back(make_pair(_equations[i][j], j + 1));
		}
		if (buffer_vector[0].first < 0)
			cout << buffer_vector[0].first << " - ";
		for (auto j = 0; j < buffer_vector.size() - 1; ++j)
		{
			if (buffer_vector[j + 1].first > 0)
			{
				cout << buffer_vector[j].first << "*x" << buffer_vector[j].second << " + ";
			}
			else
			{
				cout << abs(buffer_vector[j].first) << "*x" << buffer_vector[j].second << " - ";
			}
		}
		cout << buffer_vector.back().first << "*x" << buffer_vector.back().second;
		cout << " <= " << _conditional_values[i] << endl;
		buffer_vector.clear();
//		cout << endl;
	}
}

void Simplex_Table::Print_Canonized_Problem()
{
	// Выводим уравнение F
	vector<pair<double, unsigned int>> buffer_vector;
	for (auto i = 1; i < _function.size(); ++i)
	{
		if (_function[i] != 0)
			buffer_vector.push_back(make_pair(_function[i], i));
	}
	cout << "F =  ";
	if (_function[0] != 0)
	{
		if (buffer_vector[0].first > 0)
			cout << _function[0] << " - ";
		else
			cout << _function[0] << " + ";
	}
	if (buffer_vector[0].first > 0)
		cout << "- ";
	for (auto i = 0; i < buffer_vector.size() - 1; ++i)
	{
		if (buffer_vector[i + 1].first > 0)
		{
			cout << buffer_vector[i].first << "*x" << buffer_vector[i].second << " - ";
		}
		else
		{
			cout << abs(buffer_vector[i].first) << "*x" << buffer_vector[i].second << " + ";
		}
	}
	cout << buffer_vector.back().first << "*x" << buffer_vector.back().second << " -> min" << endl;
	buffer_vector.clear();
//	cout << endl;
	// Выводим равенства
	for (auto i = 0; i < _equations.size(); ++i)
	{
		for (auto j = 0; j < _equations.size(); ++j)
		{
			if (_equations[i][j] != 0)
				buffer_vector.push_back(make_pair(_equations[i][j], j + 1));
		}
		if (buffer_vector[0].first < 0)
			cout << buffer_vector[0].first << " - ";
		for (auto j = 0; j < buffer_vector.size() - 1; ++j)
		{
			if (buffer_vector[j + 1].first > 0)
			{
				cout << buffer_vector[j].first << "*x" << buffer_vector[j].second << " + ";
			}
			else
			{
				cout << abs(buffer_vector[j].first) << "*x" << buffer_vector[j].second << " - ";
			}
		}
		cout << buffer_vector.back().first << "*x" << buffer_vector.back().second;
		cout << " + x" << _equations.size() + 1 + i << " = " << _conditional_values[i] << endl;
		buffer_vector.clear();
//		cout << endl;
	}
}

void Simplex_Table::Print_Simplex_Table()
{
	cout << "This is the simplex table" << endl;
	string buffer;
	cout << std::setw(8) << " ";
	cout << std::setw(8) << "Si0";
	for (auto i = 1; i < _simplex_table[0].size(); ++i)
	{
		buffer = "x";
		buffer += to_string(((_simplex_table[0][i]).second).second);
		cout << std::setw(8) << buffer;
	}
	cout << endl;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		buffer = "x";
		buffer += to_string(_simplex_table[i][0].second.first);
		cout << std::setw(8) << buffer;
		for (auto j = 0; j < _simplex_table[i].size(); ++j)
		{
			cout << std::setw(8) << defaultfloat << std::setprecision(3) << _simplex_table[i][j].first;
		}
		cout << endl;
	}
	cout << std::setw(8) << "F";
	for (auto i = 0; i < (_simplex_table.back()).size(); ++i)
	{
		cout << std::setw(8) << defaultfloat << std::setprecision(3) << ((_simplex_table.back())[i]).first;
	}
	cout << endl << endl;
}
void Simplex_Table::Jordan_Exclusions(int solve_row, int solve_column, int solve_perem_column, int solve_perem_row)
{
	vector<vector<double>> buffer_vector_vector;
	vector<double> buffer_vector;
	double solve_value = _simplex_table[solve_row][solve_column].first;
	for (auto i = 0; i < _simplex_table.back().size(); ++i)
	{
		_simplex_table[solve_row][i].second.first = solve_perem_row;
	}
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		_simplex_table[i][solve_column].second.second = solve_perem_column;
	}
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		for (auto j = 0; j < _simplex_table.back().size(); ++j)
		{
			if (j != solve_column)
			{
				if (i == solve_row)
					buffer_vector.push_back(_simplex_table[i][j].first / solve_value);
				else
				{
					buffer_vector.push_back(_simplex_table[i][j].first - ((_simplex_table[solve_row][j].first * _simplex_table[i][solve_column].first) / solve_value));
				}
			}
			else
			{
				if (i == solve_row)
					buffer_vector.push_back(((double)1) / solve_value);
				else
					buffer_vector.push_back(0 - ((((double)1) * _simplex_table[i][solve_column].first) / solve_value));
			}
		}
		buffer_vector_vector.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		for (auto j = 0; j < _simplex_table.back().size(); ++j)
		{
			_simplex_table[i][j].first = buffer_vector_vector[i][j];
		}
	}
	buffer_vector.clear();
}

void  Simplex_Table::Opornoe_Solution()
{
	int solve_perem_column;
	int solve_perem_row;
	int solve_row;
	int solve_column;
	double solve_value;
	double min_value;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].first < 0)
		{
			solve_row = i;
			solve_perem_row = _simplex_table[i][0].second.first;
			for (auto j = 1; j < _simplex_table.back().size(); ++j)
			{
				if (_simplex_table[i][j].first < 0)
				{
					solve_column = j;
					solve_perem_column = _simplex_table[i][j].second.second;
					solve_value = _simplex_table[i][j].first;
					Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
					cout << "Solve element is " << solve_value << " with basis perem x" << solve_perem_row << " and free perem x" << solve_perem_column << endl;
					Print_Simplex_Table();
					break;
				}
			}
		}
	}
	cout << "Basis Solution" << endl;
	Print_Simplex_Table();
}
void Simplex_Table::Simplex_Method()
{
	bool out_of_negatives = 0;
	bool out_of_positives = 0;
	double min_negative;
	double min_positive;
	double min_pos_div;
	int solve_perem_column;
	int solve_perem_row;
	int solve_row;
	int solve_column;
	double solve_value;
	vector<vector<double>> buffer_vector_vector;
	vector<double> buffer_vector;
	while (!out_of_positives)
	{
		min_positive = 0;
		out_of_positives = 1;
		for (auto i = 1; i < _simplex_table.back().size(); ++i)
		{
			if (_simplex_table.back()[i].first > 0)
			{
				out_of_positives = 0;
				min_positive = _simplex_table.back()[i].first;
				solve_column = i;
				solve_perem_column = _simplex_table.back()[i].second.second;
				break;
			}

		}
		for (auto i = 1; i < _simplex_table.back().size(); ++i)
		{
			if ((_simplex_table.back()[i].first > 0) && (_simplex_table.back()[i].first > min_positive))
			{
				out_of_positives = 0;
				min_positive = _simplex_table.back()[i].first;
				solve_column = i;
				solve_perem_column = _simplex_table.back()[i].second.second;
			}
		}
		if (out_of_positives == 1)
			break;
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			if (_simplex_table[i][solve_column].first != 0)
			{
				if ((_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first) > 0)
				{
					min_pos_div = (_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first);
					solve_row = i;
					solve_perem_row = _simplex_table[i][0].second.first;
					break;
				}
			}
			else
				continue;
		}
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			if (_simplex_table[i][solve_column].first != 0)
			{
				if (((_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first) > 0) && ((_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first) < min_pos_div))
				{
					min_pos_div = (_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first);
					solve_row = i;
					solve_perem_row = _simplex_table[i][0].second.first;
				}
			}
			else
				continue;
		}
		solve_value = _simplex_table[solve_row][solve_column].first;
		cout << "Solve element is " << solve_value << " with basis perem x" << solve_perem_row << " and free perem x" << solve_perem_column << endl;
		Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
		Print_Simplex_Table();
	}
}

void Simplex_Table::Just_In_Case()
{
	double solution = 0;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].second.first <= _number_of_arguments)
		{
			solution += (_simplex_table[i][0].first) * (_function[_simplex_table[i][0].second.first]);
		}
	}
	cout << "The solution is " << solution << endl;
}

void Simplex_Table::Transform_Into_Twin()
{
	vector<pair<double, pair<int, int>>> buffer_vector;
	vector<vector<pair<double, pair<int, int>>>> buffer_vector_vector;
	_min_max = !_min_max;
	for (auto i = 0; i < _number_of_arguments; ++i)
	{
		buffer_vector.push_back(make_pair(_function[i + 1] * (-1), make_pair(_number_of_equations + 1 + i, 0))); 
		for (auto j = 0; j < _number_of_equations; ++j)
		{
			buffer_vector.push_back(make_pair(_equations[j][i] * (-1), make_pair(_number_of_equations + 1 + i, j + 1)));
		}
		buffer_vector_vector.push_back(buffer_vector);
		buffer_vector.clear();
	}
	buffer_vector.push_back(make_pair(0, make_pair(_number_of_arguments + 1, 0)));
	for (auto i = 0; i <_conditional_values.size(); ++i)
	{
		buffer_vector.push_back(make_pair(_conditional_values[i] * -1, make_pair(_number_of_arguments + 1, i + 1)));
	}
	buffer_vector_vector.push_back(buffer_vector);
	_simplex_table.clear();
	buffer_vector.clear();
	for (auto i = 0; i < buffer_vector_vector.size(); ++i)
	{
		_simplex_table.push_back(buffer_vector_vector[i]);
	}
	Print_Simplex_Table_Twin();
}

void Simplex_Table::Print_Twin_Problem()
{
	// Выводим уравнение F
	vector<pair<double, unsigned int>> buffer_vector;
	for (auto i = 1; i < _function.size(); ++i)
	{
		if (_function[i] != 0)
			buffer_vector.push_back(make_pair(_function[i], i));
	}
	cout << "F = ";
	if (_function[0] != 0)
	{
		if (buffer_vector[0].first > 0)
			cout << buffer_vector[0].first << " + ";
		else
			cout << buffer_vector[0].first << " - ";
	}
	else
	{
		if (buffer_vector[0].first < 0)
			cout << buffer_vector[0].first << " - ";
	}
	for (auto i = 0; i < buffer_vector.size() - 1; ++i)
	{
		if (buffer_vector[i + 1].first > 0)
		{
			cout << buffer_vector[i].first << "*y" << buffer_vector[i].second << " + ";
		}
		else
		{
			cout << abs(buffer_vector[i].first) << "*y" << buffer_vector[i].second << " - ";
		}
	}
	cout << buffer_vector.back().first << "*y" << buffer_vector.back().second << endl;
	buffer_vector.clear();
	// Выводим неравенства
	for (auto i = 0; i < _equations.size(); ++i)
	{
		for (auto j = 0; j < _equations.size(); ++j)
		{
			if (_equations[i][j] != 0)
				buffer_vector.push_back(make_pair(_equations[i][j], j + 1));
		}
		if (buffer_vector[0].first < 0)
			cout << buffer_vector[0].first << " - ";
		for (auto j = 0; j < buffer_vector.size() - 1; ++j)
		{
			if (buffer_vector[j + 1].first > 0)
			{
				cout << buffer_vector[j].first << "*y" << buffer_vector[j].second << " + ";
			}
			else
			{
				cout << abs(buffer_vector[j].first) << "*y" << buffer_vector[j].second << " - ";
			}
		}
		cout << buffer_vector.back().first << "*y" << buffer_vector.back().second;
		cout << " >= " << _conditional_values[i] << endl;
		buffer_vector.clear();
	}
}

void Simplex_Table::Print_Simplex_Table_Twin()
{
	cout << "This is the simplex table" << endl;
	string buffer;
	cout << std::setw(8) << " ";
	cout << std::setw(8) << "Si0";
	for (auto i = 1; i < _simplex_table[0].size(); ++i)
	{
		buffer = "y";
		buffer += to_string(((_simplex_table[0][i]).second).second);
		cout << std::setw(8) << buffer;
	}
	cout << endl;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		buffer = "y";
		buffer += to_string(_simplex_table[i][0].second.first);
		cout << std::setw(8) << buffer;
		for (auto j = 0; j < _simplex_table[i].size(); ++j)
		{
			cout << std::setw(8) << defaultfloat << std::setprecision(3) << _simplex_table[i][j].first;
		}
		cout << endl;
	}
	cout << std::setw(8) << "F";
	for (auto i = 0; i < (_simplex_table.back()).size(); ++i)
	{
		cout << std::setw(8) << defaultfloat << std::setprecision(3) << ((_simplex_table.back())[i]).first;
	}
	cout << endl;
}

void Simplex_Table::Simplex_Method_Twin()
{
	bool out_of_negatives = 0;
	bool out_of_positives = 0;
	double min_negative;
	double min_positive;
	double min_pos_div;
	int solve_perem_column;
	int solve_perem_row;
	int solve_row;
	int solve_column;
	double solve_value;
	vector<vector<double>> buffer_vector_vector;
	vector<double> buffer_vector;
	while (!out_of_positives)
	{
		min_positive = 0;
		out_of_positives = 1;
		for (auto i = 1; i < _simplex_table.back().size(); ++i)
		{
			if (_simplex_table.back()[i].first > 0)
			{
				out_of_positives = 0;
				min_positive = _simplex_table.back()[i].first;
				solve_column = i;
				solve_perem_column = _simplex_table.back()[i].second.second;
				break;
			}

		}
		for (auto i = 1; i < _simplex_table.back().size(); ++i)
		{
			if ((_simplex_table.back()[i].first > 0) && (_simplex_table.back()[i].first > min_positive))
			{
				out_of_positives = 0;
				min_positive = _simplex_table.back()[i].first;
				solve_column = i;
				solve_perem_column = _simplex_table.back()[i].second.second;
			}
		}
		if (out_of_positives == 1)
			break;
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			if (_simplex_table[i][solve_column].first != 0)
			{
				if ((_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first) > 0)
				{
					min_pos_div = (_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first);
					solve_row = i;
					solve_perem_row = _simplex_table[i][0].second.first;
					break;
				}
			}
			else
				continue;
		}
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			if (_simplex_table[i][solve_column].first != 0)
			{
				if (((_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first) > 0) && ((_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first) < min_pos_div))
				{
					min_pos_div = (_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first);
					solve_row = i;
					solve_perem_row = _simplex_table[i][0].second.first;
				}
			}
			else
				continue;
		}
		solve_value = _simplex_table[solve_row][solve_column].first;
		cout << "Solve element is " << solve_value << " with basis perem y" << solve_perem_row << " and free perem y" << solve_perem_column << endl;
		Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
		Print_Simplex_Table_Twin();
	}
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].first < 0)
		{
			solve_row = i;
			solve_perem_row = _simplex_table[i][0].second.first;
			for (auto j = 1; j < _simplex_table.back().size(); ++j)
			{
				if (_simplex_table[i][j].first < 0)
				{
					solve_column = j;
					solve_perem_column = _simplex_table[i][j].second.second;
					solve_value = _simplex_table[i][j].first;
					Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
					cout << "Solve element is " << solve_value << " with basis perem y" << solve_perem_row << " and free perem y" << solve_perem_column << endl;
					Print_Simplex_Table_Twin();
					break;
				}
			}
		}
	}
	min_positive = 0;
	out_of_positives = 0;
	while (!out_of_positives)
	{
		min_positive = 0;
		out_of_positives = 1;
		for (auto i = 1; i < _simplex_table.back().size(); ++i)
		{
			if (_simplex_table.back()[i].first > 0)
			{
				out_of_positives = 0;
				min_positive = _simplex_table.back()[i].first;
				solve_column = i;
				solve_perem_column = _simplex_table.back()[i].second.second;
				break;
			}

		}
		for (auto i = 1; i < _simplex_table.back().size(); ++i)
		{
			if ((_simplex_table.back()[i].first > 0) && (_simplex_table.back()[i].first > min_positive))
			{
				out_of_positives = 0;
				min_positive = _simplex_table.back()[i].first;
				solve_column = i;
				solve_perem_column = _simplex_table.back()[i].second.second;
			}
		}
		if (out_of_positives == 1)
			break;
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			if (_simplex_table[i][solve_column].first != 0)
			{
				if ((_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first) > 0)
				{
					min_pos_div = (_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first);
					solve_row = i;
					solve_perem_row = _simplex_table[i][0].second.first;
					break;
				}
			}
			else
				continue;
		}
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			if (_simplex_table[i][solve_column].first != 0)
			{
				if (((_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first) > 0) && ((_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first) < min_pos_div))
				{
					min_pos_div = (_simplex_table[i][0].first) / (_simplex_table[i][solve_column].first);
					solve_row = i;
					solve_perem_row = _simplex_table[i][0].second.first;
				}
			}
			else
				continue;
		}
		solve_value = _simplex_table[solve_row][solve_column].first;
		cout << "Solve element is " << solve_value << " with basis perem y" << solve_perem_row << " and free perem y" << solve_perem_column << endl;
		Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
		Print_Simplex_Table_Twin();
	}
}

void  Simplex_Table::Opornoe_Solution_Twin()
{
	int solve_perem_column;
	int solve_perem_row;
	int solve_row;
	int solve_column;
	double solve_value;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].first < 0)
		{
			solve_row = i;
			solve_perem_row = _simplex_table[i][0].second.first;
			for (auto j = 1; j < _simplex_table.back().size(); ++j)
			{
				if (_simplex_table[i][j].first < 0)
				{
					solve_column = j;
					solve_perem_column = _simplex_table[i][j].second.second;
					solve_value = _simplex_table[i][j].first;
					Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
					cout << "Solve element is " << solve_value << " with basis perem y" << solve_perem_row << " and free perem y" << solve_perem_column << endl;
					Print_Simplex_Table_Twin();
					break;
				}
			}
		}
	}
	cout << "Basis Solution" << endl;
	Print_Simplex_Table_Twin();
}
