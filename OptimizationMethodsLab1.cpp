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
//	table.Basis_Solution();
	table.Opornoe_Solution();
	table.Simplex_Method();
//	table.Just_In_Case();
	table.Transform_Into_Twin();
	table.Opornoe_Solution();
	table.Simplex_Method();
//	table.Just_In_Case();
	system("pause");
	return 0;

}

