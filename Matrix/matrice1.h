#pragma once
#include <iostream>
#define DEFAULT_ELEMENT 0
#define MIN_MATRIX 1

template<typename T> class matrica
{
private:
	int m;
	int n;
	T element;
	T** mat;

	void dealocirajMatricu()
	{
		for (int i = 0; i < m; i++)
		{
			delete[] mat[i];
		}
		delete[] mat;
	}

	void alocirajMatricu()
	{
		mat = new T * [m];
		for (int i = 0; i < m; i++)
		{
			mat[i] = new T[n];
		}
	}

	void popuniMatricu()
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				mat[i][j] = element;
			}
		}
	}

public:
	matrica()
	{
		m = MIN_MATRIX;
		n = MIN_MATRIX;
		element = DEFAULT_ELEMENT;

		alocirajMatricu();
		popuniMatricu();
	}

	matrica(int b)
	{
		m = b;
		n = b;
		element = DEFAULT_ELEMENT;

		alocirajMatricu();
		popuniMatricu();
	}

	matrica(int b, T x)
	{
		m = b;
		n = b;
		element = x;

		alocirajMatricu();
		popuniMatricu();
	}

	matrica(int b1, int b2, T x)
	{
		m = b1;
		n = b2;
		element = x;

		alocirajMatricu();
		popuniMatricu();
	}

	matrica(matrica& matr)
	{
		this->m = matr.m;
		this->n = matr.n;
		this->element = matr.element;
		
		alocirajMatricu();

		for (int i = 0; i < this->m; i++)
		{
			for (int j = 0; j < this->n; j++)
			{
				this->mat[i][j] = matr.mat[i][j];
			}
		}
	}

	~matrica()
	{
		for (int i = 0; i < m; i++)
		{
			delete[] mat[i];
		}
		delete[] mat;
		std::cout << "Destruktor unistio matricu dimenzija " << m << "x" << n << "\n";
	}

	friend std::ostream& operator<<(std::ostream& os, const matrica<T>& m)
	{
		for (int i = 0; i < m.m; i++)
		{
			for (int j = 0; j < m.n; j++)
			{
				os << m.mat[i][j] << " ";
			}
			os << std::endl;
		}

		return os;
	}

	matrica<T>& operator+=(matrica<T>& matr)
	{
		if (this->m != matr.m || this->n != matr.n)
		{
			std::cout << "Operaciju += nije moguce izvrsiti!\n";
			return *this;
		}

		for (int i = 0; i < this->m; i++)
		{
			for (int j = 0; j < this->n; j++)
			{
				this->mat[i][j] += matr.mat[i][j];
			}
		}
		return *this;
	}

	matrica<T>& operator-=(matrica<T>& matr)
	{
		if (this->m != matr.m || this->n != matr.n)
		{
			std::cout << "Operaciju -= nije moguce izvrsiti!\n";
			return *this;
		}

		for (int i = 0; i < this->m; i++)
		{
			for (int j = 0; j < this->n; j++)
			{
				this->mat[i][j] -= matr.mat[i][j];
			}
		}
		return *this;
	}

	matrica<T>& operator*=(matrica<T>& matr)
	{
		if (!((this->m == this->n) && (matr.m == matr.n) && (this->m == matr.m)))
		{
			std::cout << "Operaciju *= nije moguce izvrsiti!\n";
			return *this;
		}

		matrica<T> matrica(this->m, matr.n, DEFAULT_ELEMENT);

		for (int i = 0; i < this->m; i++)
		{
			for (int j = 0; j < matr.n; j++)
			{
				matrica.mat[i][j] = 0;

				for (int k = 0; k < matr.m; k++)
				{
					matrica.mat[i][j] += this->mat[i][k] * matr.mat[k][j];
				}
			}
		}

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				this->mat[i][j] = matrica.mat[i][j];
			}
		}

		return *this;
	}

	bool operator==(matrica<T>& matr)
	{
		if (this->m != matr.m || this->n != matr.n)
		{
			return false;
		}

		for (int i = 0; i < this->m; i++)
		{
			for (int j = 0; j < this->n; j++)
			{
				if (this->mat[i][j] != matr.mat[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(matrica<T>& matr)
	{
		if (this->m != matr.m || this->n != matr.n)
		{
			return true;
		}

		for (int i = 0; i < this->m; i++)
		{
			for (int j = 0; j < this->n; j++)
			{
				if (this->mat[i][j] != matr.mat[i][j])
				{
					return true;
				}
			}
		}
		return false;
	}

	operator int() const
	{
		int brojac = 0;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (mat[i][j] != 0)
				{
					brojac++;
				}
			}
		}
		return brojac;
	}

	operator double() const
	{
		double trag = 0;
		if (m != n)
		{
			return 0;
		}
		for (int i = 0; i < m; i++)
		{
			trag += mat[i][i];
		}
		return trag;
	}

	T& dohvatiElement(int redIndeks, int stIndeks)
	{
		return mat[redIndeks][stIndeks];
	}

	void ispisDimenzija()
	{
		std::cout << m << " " << n << std::endl;
	}

};

template<typename T> struct ocisti
{
	void operator()(T razina, matrica<T>& matr)
	{
		for (int i = 0; i < matr.m; i++)
		{
			for (int j = 0; j < matr.n; j++)
			{
				if (matr.mat[i][j] < razina)
				{
					matr.mat[i][j] = 0;
				}
			}
		}
	}
};

template<typename T> struct transponiraj
{
	void operator()(matrica<T>& matr)
	{
		matrica<T> temp(matr.n, matr.m, DEFAULT_ELEMENT);

		for (int i = 0; i < matr.m; i++)
		{
			for (int j = 0; j < matr.n; j++)
			{
				temp.mat[j][i] = matr.mat[i][j];
			}
		}

		matr.dealocirajMatricu();
		matr.m = temp.m;
		matr.n = temp.n;
		matr.alocirajMatricu();

		for (int i = 0; i < temp.m; i++)
		{
			for (int j = 0; j < temp.n; j++)
			{
				matr.mat[i][j] = temp.mat[i][j];
			}
		}
	}

};

template<typename Iter, typename Funktor>
void for_each(Iter start, Iter kraj, Funktor f)
{
	for (Iter i = start; i != kraj; ++i)
	{
		f(*i);
	}
}

template<typename Iter, typename Funktor>
void for_each(Iter start, Iter kraj, Funktor f, int razina)
{
	for (Iter i = start; i != kraj; ++i)
	{
		f(razina, **i);
	}
}