// CP.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

unsigned int FindFunctionDefn( const char* strFunctionName, const char* strSourceCode )
{
	string fn(strFunctionName);
	string code(strSourceCode);

	int name_len = fn.length();
	int line_num = 1;
	int i=0;
	while(i<code.length())
	{
		int j = code.find(fn, i);

		//count lines from i->j
		for(int k=i;k<j;k++)
		{
			if(code[k]=='\n')
				line_num++;
		}

		//check if valid fn

		//checking the function name
		//int*fn, int&fn, int fn
		char bf = code[j-1];
		if(!(bf == '*' || bf == ' ' || bf == '&' || bf == '\n'  ))
		{
			i = j+1;
			continue;
		}

		char af = code[j+name_len];
		if(!(af == '(' || af == ' ' || af == '\n' ))
		{
			i = j+1;
			continue;
		}

		// checking if actually a function

		//checking if a valid parenthesis follows the name (differentiating it from a variable or a class)
		int k=j+name_len;
		while((code[k]==' ' || code[k]=='\n') && k<code.length())
		{
			k++;
		}
		if(k>=code.length() || code[k]!='(')
		{
			i = j+1;
			continue;
		}
		int cb = code.find(")", k+1)+1;
		while((code[cb] == ' ' || code[cb] == '\n') && cb<code.length() )
		{
			cb++;
		}
		//checking if the function is defined after the parenthesis (differentiating it from a declaration or a prototype )
		if(cb>=code.length() || code[cb]!='{')
		{
			i = j+1;
			continue;
		}

		return line_num;
	}

	return 0;
}

int main()
{
	/*
	 * Implement the following C/C++ function: unsigned int FindFunctionDefn( const char* strFunctionName, const char* strSourceCode ); 
	 * FindFunctionDefn takes two strings as inputs: a function name and a program string; 
	 * it returns as an output the line number that contains the function definition (differentiate this with the function calls) in the program string. 
	 * The program string is a valid C code; it contains a character "\n" indicate the end of a line with the line number starts from one. 
	 * The program string is guaranteed not to contain any C (or C++) comments. 
	 * The function FindFunctionDefn returns 0 if it fails to find the function definition. 
	 * For example, 
	 * char strFunctionName[] = "func2"; 
	 * char strSourceCode[] = "int func1(){ return 0; }\\n int func2(){ return 1; }\\n" 
	 * "int main(int argc, char*argv[]){ return func2(); }\\n"; 
	 * FindFunctionDefn( strFunctionName, strSourceCode ) should return 2. 
	 */

	/*
	 * TLDR;
	 * Find function Definition ( Not Declaration / Prototype )
	 */

	char fn[100];
	cout << "Enter Function Name: ";
	cin >> fn;

	cout << "Enter Code (End with $):" << endl;
	string str;
	getline(cin, str, '$');

	cout << FindFunctionDefn(fn, str.c_str()) << "\n";

	system("pause");
	return 0;
}