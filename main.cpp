#include <iostream>
#include <cmath>

using namespace std;


class TRational
{
private:
	bool exist; // Существует ли дробь
	int p; //Числитель
	int q; //Знаменатель
	int NOD(int a, int b);
	void MakeFinal()
	{
		int tmp = 0;
		if ((tmp = NOD(abs(p), abs(q))) > 1)
		{
			p = p / tmp;
			q = q / tmp;
		}
	}

	TRational Add(const TRational& t);
	TRational Subtract(const TRational& t);
	TRational Multiply(const TRational& t);
	TRational Devide(const TRational& t);


public:
	TRational(int a, int b);

	bool IsExist();
	void Print();

	TRational& operator=(const TRational& t)
	{
		p = t.p;
		q = t.q;
		return *this;
	}
	TRational& operator+=(const TRational& t)
	{
		Add(t);

		return *this;
	}
	TRational& operator-=(const TRational& t)
	{
		Subtract(t);

		return *this;
	}
	TRational& operator*=(const TRational& t)
	{
		Multiply(t);

		return *this;
	}
	TRational& operator/=(const TRational& t)
	{
		Devide(t);

		return *this;
	}


	TRational operator+(const TRational& t)
	{
		TRational a(p*t.q + q*t.p, q*t.q);
		return a;
	}

	TRational operator-(const TRational& t)
	{
		TRational a(p*t.q - q * t.p, q*q);
		return a;
	}

	TRational operator*(const TRational& t)
	{

		TRational a(p* t.p, q*t.q);
		return a;
	}

	TRational operator/(const TRational& t)
	{
		TRational a(p* t.q, q*t.p);
		return a;
	}
};

TRational::TRational(int a, int b)
{
	p = a;
	if (b != 0)
	{
		exist = true;
		q = b;
		if (q < 0) { q *= (-1); p *= (-1); }
		MakeFinal();
	}
	else
	{
		exist = false;
	}
}

int TRational::NOD(int a, int b)
{
	int nod = 1;
	for (int i = a; i > 0; i--) {
		if (a % i == 0 && b % i == 0) {
			nod = i;
			break;
		}
	}
	return nod;
}

bool TRational::IsExist()
{
	return exist;
}

TRational TRational::Add(const TRational& t)
{
	p = p*t.q + t.p*q;
	q = q*t.q;
	MakeFinal();

	TRational a(p, q);
	return a;
}

TRational TRational::Subtract(const TRational& t)
{
	p = p*t.q - t.p*q;
	q = q*t.q;
	MakeFinal();

	TRational a(p, q);
	return a;
}

TRational TRational::Multiply(const TRational& t)
{
	p = p*t.p;
	q = q*t.q;
	MakeFinal();

	TRational a(p, q);
	return a;
}

TRational TRational::Devide(const TRational& t)
{
	p = p*t.q;
	q = q*t.p;
	MakeFinal();

	TRational a(p, q);
	return a;
}

void TRational::Print()
{
	cout << "(" << p << "/" << q << ")";
}


void main()
{
	TRational a(5, -3);
	TRational b(20, -8);
	if (a.IsExist() && b.IsExist())
	{
		(a + b).Print(); cout << "\n";
		(a - b).Print(); cout << "\n";
		(a * b).Print(); cout << "\n";
		(a / b).Print(); cout << "\n";
	}
	system("pause");
}
