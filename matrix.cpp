#include <fstream>
#include "Matrix.h"

#define SIZE 5

int main()
{
	ifstream A("a.txt"), B("b.txt");
	ofstream C("c.txt");
	Matrix<int, SIZE, SIZE> a, b, c;
	A >> a, B >> b;
	c = a + b;
	C << c;
	A.close(), B.close(), C.close();
	return 0;
}
