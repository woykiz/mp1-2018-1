#include <iostream>
#include <cmath>

using namespace std;


class TRational
{
private:
	bool e; // Существует ли дробь
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

public:
	TRational(int a, int b);

	TRational Add(TRational t);
	TRational Subtract(TRational t);
	TRational Multiply(TRational t);
	TRational Devide(TRational t);

	bool Exist();
	void Print();

	int GetP()
	{
		return p;
	}
	int GetQ()
	{
		return q;
	}

	TRational& operator=(TRational& t)
	{
		p = t.GetP();
		q = t.GetQ();

		return *this;
	}
	TRational& operator+=(TRational& t)
	{
		Add(t);

		return *this;
	}
	TRational& operator-=(TRational& t)
	{
		Subtract(t);

		return *this;
	}
	TRational& operator*=(TRational& t)
	{
		Multiply(t);

		return *this;
	}
	TRational& operator/=(TRational& t)
	{
		Devide(t);

		return *this;
	}


	TRational& operator+(TRational& t)
	{
		return *(new TRational(p*t.GetQ() + q*t.GetP(), q*t.GetQ()));
	}

	TRational& operator-(TRational& t)
	{
		return *(new TRational(p*t.GetQ() - q*t.GetP(), q*t.GetQ()));
	}

	TRational& operator*(TRational& t)
	{

		return *(new TRational(p*t.GetP(), q*t.GetQ()));
	}

	TRational& operator/(TRational& t)
	{
		return *(new TRational(p*t.GetQ(), q*t.GetP()));
	}
};

TRational::TRational(int a, int b)
{
	p = a;
	if (b != 0)
	{
		e = true;
		q = b;
		if (q < 0) { q *= (-1); p *= (-1); }
		MakeFinal();
	}
	else
	{
		e = false;
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

bool TRational::Exist()
{
	return e;
}

TRational TRational::Add(TRational t)
{
	p = p*t.GetQ() + t.GetP()*q;
	q = q*t.GetQ();
	MakeFinal();

	TRational a(p, q);
	return a;
}

TRational TRational::Subtract(TRational t)
{
	p = p*t.GetQ() - t.GetP()*q;
	q = q*t.GetQ();
	MakeFinal();

	TRational a(p, q);
	return a;
}

TRational TRational::Multiply(TRational t)
{
	p = p*t.GetP();
	q = q*t.GetQ();
	MakeFinal();

	TRational a(p, q);
	return a;
}

TRational TRational::Devide(TRational t)
{
	p = p*t.GetQ();
	q = q*t.GetP();
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
	TRational a(5, 3);
	TRational b(20, 5);
	if (a.Exist() && b.Exist())
	{
		(a + b).Print(); cout << "\n";
		(a - b).Print(); cout << "\n";
		(a * b).Print(); cout << "\n";
		(a / b).Print(); cout << "\n";
		/*TRational c=a.Add(b);
		a += b;*/
	}
	system("pause");
}
