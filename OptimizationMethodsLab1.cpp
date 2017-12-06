// OptimizationMethodsLab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Functions.h"

int main()
{
	Simplex_Table table;
	table.Create_Simplex_Table();
	table.Print_Problem();
	table.Print_Canonized_Problem();
	table.Print_Simplex_Table();
	table.Opornoe_Solution();
	table.Simplex_Method();
	table.Transform_Into_Twin();
	table.Opornoe_Solution_Twin();
	table.Simplex_Method_Twin();
	system("pause");
	return 0;

}

