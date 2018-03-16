#include <iostream>
#include <math.h>
using namespace std;

enum functions { SIN, COS, EXP, LOG };
enum method { LEFT, MID, RIGHT };

class Integral
{
private:
	double leftBound;
	double rightBound;
	functions func;
	method meth;
	int N;
	double inFunc(double x)
	{
		switch (func) 
		{
		case 0: return sin(x);
		case 1: return cos(x);
		case 2: return exp(x);
		case 3: return log(x);
		}	
	}
	double calcIntegralL()
	{
		int i;
		double result, h;

		result = 0;

		h = (rightBound - leftBound) / N; 

		for (i = 0; i < N; i++)
		{
			result += inFunc(leftBound + h * (i)); 
		}

		result *= h;

		return result;
	}
	double calcIntegralM()
	{
		int i;
		double result, h;

		result = 0;

		h = (rightBound - leftBound) / N; 

		for (i = 0; i < N; i++)
		{
			result += inFunc(leftBound + h * (i + 0.5)); 
		}

		result *= h;

		return result;
	}
	double calcIntegralR()
	{
		int i;
		double result, h;

		result = 0;

		h = (rightBound - leftBound) / N;

		for (i = 1; i <= N; i++)
		{
			result += inFunc(leftBound + h * (i));
		}

		result *= h;

		return result;
	}
public: 
	Integral() {};
	Integral(double a, double b) 
	{
		leftBound = a;
		rightBound = b;
	}
	Integral(const Integral& i)
	{
		leftBound = i.leftBound;
		rightBound = i.rightBound;
		func = i.func;
		meth = i.meth;
	}
	Integral& operator=(const Integral& i)
	{
		leftBound = i.leftBound;
		rightBound = i.rightBound;
		func = i.func;
		meth = i.meth;
		return *this;
	}
	void setBounds(double a, double b)
	{
		leftBound = a;
		rightBound = b;
	}
	void getBounds(double *a, double *b)
	{
		double lb = leftBound;
		a = &lb;
		double rb = rightBound;
		b = &rb;
	}
	void setParams(int _N, functions f = SIN, method m = LEFT)
	{
		N = _N;
		func = f;
		meth = m;
	}
	double calculate(bool toConsole=false) ///если правда, тогда выводим в консоль 
	{
		double res;
		switch (meth)
		{
		case 0: {res = calcIntegralL(); }
		case 1: {res = calcIntegralM(); }
		case 2: {res = calcIntegralR(); }
		}
		if (toConsole) cout << res;
		return res;
	}
};





void main()
{
	Integral i;
	i.setBounds(-10, 10);
	i.setParams(100, COS, MID);
	i.calculate(true);
	cout << '\n';
	system("pause");
}
