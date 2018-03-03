#include <iostream>
#include <cmath>

using namespace std;

class Polynom
{
private:
	double* koef;
	int deg;
public:
	Polynom(int n, double a[]);
	~Polynom();

	int GetDegree();
	double Calculate(double x);
	Polynom Derivative();

	Polynom& operator=(const Polynom& p)
	{
		if (this == &p)
		{
			return *this;
		}
		else
		{
			if (deg != p.deg)
			{
				delete[] koef;
				deg = p.deg;
				koef = new double[p.deg + 1];
			}
			for (int i = 0; i < deg + 1; i++)
			{
				koef[i] = p.koef[i];
			}
			return *this;
		}
	}

	double operator[](int i)
	{
		if (i <= deg)
			return koef[i];
		else
			return numeric_limits<double>::quiet_NaN();
	}

	void ToConsole();
};

Polynom::Polynom(int n, double a[])
{
	n++;
	koef = new double[n];
	deg = n - 1;
	for (int i = 0; i < n; i++)
	{
		koef[i] = a[i];
	}
}

Polynom::~Polynom()
{
	delete[] koef;
}

int Polynom::GetDegree()
{
	return deg;
}

double Polynom::Calculate(double x)
{
	double s = 0;
	for (int i = 0; i < deg+1; i++)
	{
		s += (koef[i] * pow(x, deg - i));
	}

	return s;
}

Polynom Polynom::Derivative()
{
	double* s = new double[deg];

	for (int i = 0; i < deg; i++)
	{
		s[i] = (koef[i] * (deg - i));
	}

	//Тут наверное утечка памяти, но все другие варианты не работают
	Polynom* d = new Polynom(deg-1,s);
	delete[] s;
	return *d;
}

void Polynom::ToConsole()
{
	if (deg > 0)
	{
		cout << koef[0] << "(x^" << deg << ")";
		for (int i = 1; i < deg; i++)
		{
			cout << " + " << koef[i] << "(x^" << deg - i << ")";
		}
		cout << " + ";
	}
	cout << koef[deg];
}

void main()
{
	double a[] = { 1,3,1 };
	Polynom p(2,a);
	cout << p.Calculate(-1);
	cout << "\n";
	p.ToConsole();
	cout << "\n";
	double b[] = { 1,3};
	Polynom p1(1, b);
	p = p1.Derivative();
	p.ToConsole();
	cout << "\n";
	system("pause");
}