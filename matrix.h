#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>

#define OUT_WIDTH 1

using namespace std;

template <class T, int M, int N = M> 
class Matrix
{
public:
	Matrix()
	{
		p_ = new T*[M];
		for (int i = 0; i < M; i++)
		{
			p_[i] = new T[N];
		}
	}

	Matrix(const Matrix<T, M, N>& copy)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				p_[i][j] = copy.p_[i][j];
			}
		}
	}

	~Matrix()
	{
		for (int i = 0; i < M; i++)
		{
			delete[] p_[i];
		}
		delete[] p_;
	}

	T* operator[](int i)
	{
		return p_[i];
	}

	Matrix<T, M, N> operator- ()
	{
		Matrix<T, M, N> c;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				c[i][j] = -(*this)[i][j];
			}
		}
		return c;
	}

	Matrix<T, M, N>& operator= (Matrix<T, M, N> a)
	{
		if (&a == this)
		{
			return *this;
		}
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				(*this)[i][j] = a[i][j];
			}
		}
		return *this;
	}

	Matrix<T, M, N>& operator+= (Matrix<T, M, N>& a)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				(*this)[i][j] += a[i][j];
			}
		}
		return *this;
	}

	Matrix<T, M, N>& operator-= (Matrix<T, M, N>& a)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				(*this)[i][j] += a[i][j];
			}
		}
		return *this;
	}

	Matrix<T, M, N>& operator*= (Matrix<T, M, N>& a)
	{
		return *this = (operator* (*this, a));
	}

	Matrix<T, M, N>& operator*= (int b)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				(*this)[i][j] *= b;
			}
		}
		return *this;
	}

	template<class T1, int M1, int N1>
	friend ofstream& operator<< (ofstream& os, Matrix<T, M, N>& a);

	template<class T1, int M1, int N1>
	friend ifstream& operator>> (ifstream& is, Matrix<T, M, N>& a);

	template<class T1, int M1, int N1>
	friend Matrix<T, M, N> operator+ (Matrix<T, M, N>& a, Matrix<T, M, N>& b);

	template<class T1, int M1, int N1>
	friend Matrix<T, M, N> operator- (Matrix<T, M, N>& a, Matrix<T, M, N>& b);

	template<class T1, int M1, int N1, int K1>
	friend Matrix<T, M, N> operator* (Matrix<T, M, N>& a, Matrix<T, M, N>& b);

	template<class T1, int M1, int N1>
	friend Matrix<T, M, N> operator* (Matrix<T, M, N>& a, T b);

	template<class T1, int M1, int N1>
	friend Matrix<T, M, N> operator* (T b, Matrix<T, M, N>& a);

	template<class T1, int M1, int N1>
	friend bool operator== (Matrix<T, M, N>& a, Matrix<T, M, N>& b);

	template<class T1, int M1, int N1>
	friend bool operator!= (Matrix<T, M, N>& a, Matrix<T, M, N>& b);

private:
	T** p_;
};

template<class T, int M, int N = M>
ofstream& operator<< (ofstream& os, Matrix<T, M, N>& a)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			os << setw(OUT_WIDTH) << a[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

template <class T, int M, int N = M>
ifstream& operator>> (ifstream &is, Matrix<T, M, N>& a)
{
	string line;
	for (int i = 0; i < M; i++)
	{
		getline(is, line);
		stringstream ss(line);
		for (int j = 0; j < N; j++)
		{
			ss >> a[i][j];
		}
	}
	return is;
}

template<class T, int M, int N = M>
ostream& operator<< (ostream& os, Matrix<T, M, N>& a)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			os << setw(OUT_WIDTH) << a[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

template <class T, int M, int N = M>
istream& operator>> (istream &is, Matrix<T, M, N>& a)
{
	string line;
	for (int i = 0; i < M; i++)
	{
		getline(is, line);
		stringstream ss(line);
		for (int j = 0; j < N; j++)
		{
			ss >> a[i][j];
		}
	}
	return is;
}

template <class T, int M, int N = M>
Matrix<T, M, N> operator+ (Matrix<T, M, N>& a, Matrix<T, M, N>& b)
{
	Matrix<T, M, N> c;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

template <class T, int M, int N = M>
Matrix<T, M, N> operator- (Matrix<T, M, N>& a, Matrix<T, M, N>& b)
{
	Matrix<T, M, N> c;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			c[i][j] = a[i][j] - b[i][j];
		}
	}
	return c;
}

template<class T, int M, int N = M, int K>
Matrix<T, M, K> operator* (Matrix<T, M, N>& a, Matrix<T, N, K>& b)
{
	Matrix<T, M, K> c;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < K; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < N; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

template<class T, int M, int N = M>
Matrix<T, M, N> operator* (Matrix<T, M, N>& a, T b)
{
	Matrix<T, M, N> c;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			c[i][j] = a[i][j] *b;
		}
	}
	return c;
}

template<class T, int M, int N = M>
Matrix<T, M, N> operator* (T b, Matrix<T, M, N>& a)
{
	return a * b;
}

template<class T, int M, int N = M>
bool operator== (Matrix<T, M, N>& a, Matrix<T, M, N>& b)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (a[i][j] != b[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

template<class T, int M, int N = M>
bool operator!= (Matrix<T, M, N>& a, Matrix<T, M, N>& b)
{
	return !(a == b);
}

#endif