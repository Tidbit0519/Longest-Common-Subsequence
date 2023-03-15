#include <iostream>
#include <fstream>
#include <sstream>

class TwoDimIntArray {
private:
	int* data;
	int sizeX;

public:
	TwoDimIntArray(int width, int height) {
		sizeX = width;
		data = new int[width * height];
	}

	~TwoDimIntArray() {
		delete[] data;
	}

	int get(int x, int y) {
		return data[y * sizeX + x];
	}

	void set(int x, int y, int val) {
		data[y * sizeX + x] = val;
	}
};

using namespace std;

TwoDimIntArray* b;
TwoDimIntArray* c;

void lcsLength(string X, string Y) {
	int m = X.length();
	int n = Y.length();
	b = new TwoDimIntArray(m + 1, n + 1);
	c = new TwoDimIntArray(m + 1, n + 1);

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
			if (X[i - 1] == Y[j - 1])
			{
				c->set(i, j, c->get(i - 1, j - 1) + 1);
				b->set(i, j, 1);
			}
			else if (c->get(i - 1, j) >= c->get(i, j - 1))
			{
				c->set(i, j, c->get(i - 1, j));
				b->set(i, j, 2);
			}
			else
			{
				c->set(i, j, c->get(i, j - 1));
				b->set(i, j, 3);
			}
		}
	}
}

void printLcs(string X, int i, int j) {
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b->get(i, j) == 1) 
	{
		printLcs(X, i - 1, j - 1);
		cout << X[i - 1];
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
	// handles missing command - line parameters and "file-not-found" errors.
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

	string firstLine, secondLine;
	getline(ifs, firstLine);
	getline(ifs, secondLine);
	cout << "String X: " << firstLine << endl;
	cout << "String Y: " << secondLine << endl;
	lcsLength(firstLine, secondLine);
	cout << "LCS: ";
	printLcs(firstLine, firstLine.length(), secondLine.length());
}
