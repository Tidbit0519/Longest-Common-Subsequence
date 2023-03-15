#include <iostream>
#include <fstream>
#include <sstream>
#include "2DArray.cpp"

using namespace std;

TwoDimIntArray* b;
TwoDimIntArray* c;

// Longest Common Subsequence algorithm.
// Calculates the LCS by comparing two different strings.
void lcsLength(string X, string Y) {
	int m = X.length();
	int n = Y.length();
	// let b[1 : m, 1 : n] and c[0 : m, 0 : n] be new tables.
	// array b is to keep track of the "arrows".
	// array c is to keep track of the cumulative common subsequence.
	b = new TwoDimIntArray(m + 1, n + 1);
	c = new TwoDimIntArray(m + 1, n + 1);

	// compute table entries in row-major order
	// initialize the value of each array element as zero.
	for (int i = 0; i <= m; i++)
	{
		c->set(i, 0, 0);
	}
	for (int j = 0; j <= n; j++)
	{
		c->set(0, j, 0);
	}
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// If both characters at the position of the string are the same, 
			// replace the value of that index with the sum of 1 and the value of the diagonal element
			// for array b at the same index, set 1 to indicate “↖”
			if (X[i - 1] == Y[j - 1])
			{
				c->set(i, j, c->get(i - 1, j - 1) + 1);
				b->set(i, j, 1); // “↖”
			}
			// If the value of the element to the top is larger, replace it with that value.
			// for array b at the same index, set 2 to indicate "↑”
			else if (c->get(i - 1, j) >= c->get(i, j - 1))
			{
				c->set(i, j, c->get(i - 1, j));
				b->set(i, j, 2); // “↑”
			}
			// If the value of the element to the left is larger, replace it with that value.
			// for array b at the same index, set 3 to indicate “←”
			else
			{
				c->set(i, j, c->get(i, j - 1));
				b->set(i, j, 3); // “←”
			}
		}
	}
}

// Prints the LCS according to the "arrows" from the LCS table which are the values recorded in array b
void printLcs(string X, int i, int j) {
	if (i == 0 || j == 0)
	{
		return; // the LCS has length 0
	}
	if (b->get(i, j) == 1) 
	{
		printLcs(X, i - 1, j - 1);
		cout << X[i - 1]; // same as y[j-1]
	}
	else if (b->get(i, j) == 2)
	{
		printLcs(X, i - 1, j);
	}
	else
	{
		printLcs(X, i, j - 1);
	}

}

int main(int argc, char** argv) {
	// If the user forgets the command-line parameter, or if the file cannot be found, the program should report an appropriate error message.
	if (argc == 1) {
		cout << "You forgot the command line parameter" << endl;
		exit(0);
	}
	ifstream ifs;
	ifs.open(argv[1], ios::in);
	if (!ifs) {
		cout << "could not find file " << argv[1] << endl;
		exit(0);
	}

	// Gets the first line and second line of string from the txt file and print them out.
	string firstLine, secondLine;
	getline(ifs, firstLine);
	getline(ifs, secondLine);
	cout << "String X: " << firstLine << endl;
	cout << "String Y: " << secondLine << endl;
	lcsLength(firstLine, secondLine);
	cout << "LCS: ";
	printLcs(firstLine, firstLine.length(), secondLine.length());
}
