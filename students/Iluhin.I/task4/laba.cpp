#include <fstream> 
#include <iostream> 
#include <vector>

using namespace std;

struct Date
{
	int day;
	int month;
	int year;
};

class SingleCount
{
private:
	int steps;
	int startHour;
	int startMinute;
	int endHour;
	int endMinute;
	Date date;
public:
	SingleCount() {}
	SingleCount(Date d, int sm, int sh, int em, int eh, int s)
	{
		startMinute = sm;
		startHour = sh;
		endMinute = em;
		endHour = eh;
		date = d;
		steps = s;
	}
	int getSteps()
	{
		return steps;
	}
	int getStartHour()
	{
		return startHour;
	}
	int getStartMinute()
	{
		return startMinute;
	}
	int getEndHour()
	{
		return endHour;
	}
	int getEndMinute()
	{
		return endMinute;
	}
	Date getDate()
	{
		return date;
	}
};

class Pedometr
{
private:
	SingleCount startCount;
	vector<SingleCount> Counts;
	int GetDayOfWeek(int D, int M, int Y)
	{
		int a, y, m, R;
		a = (14 - M) / 12;
		y = Y - a;
		m = M + 12 * a - 2;
		R = 7000 + (D + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12);
		return R % 7;
	}
public:
	SingleCount operator[](int i)
	{
		return Counts[i];
	}
	void setStartDate(Date d)
	{
		SingleCount k(d, 0, 0, 0, 0, 0);
		if (Counts.size() > 0)
			Counts[0] = k;
		else
			Counts.push_back(k);

	}
	Date getStartDate()
	{
		return startCount.getDate();
	}
	void AddCount(Date d, int sm, int sh, int em, int eh, int c)
	{
		SingleCount sc(d, sm, sh, em, eh, c);
		Counts.push_back(sc);
	}
	int GetAvierageCounts(int month)
	{
		int k;
		int s;
		for (int i = 0; i < Counts.size(); i++)
			if (Counts[i].getDate().month == month)
			{
				k++;
				s += Counts[i].getSteps();
			}
		return (s / k);
	}
	int GetAvierageCounts()
	{
		int k;
		int s;
		for (int i = 0; i < Counts.size(); i++)
		{
			k++;
			s += Counts[i].getSteps();
		}
		return (s / k);
	}
	int GetDayAvierageCounts(int DayOfWeek)
	{
		int k;
		int s;
		for (int i = 0; i < Counts.size(); i++)
		{
			int dow = GetDayOfWeek(Counts[i].getDate().day, Counts[i].getDate().month, Counts[i].getDate().year);
			if (dow == DayOfWeek)
			{
				k++;
				s += Counts[i].getSteps();
			}
		}
		return (s / k);
	}
	int GetMaxStepsForDay(Date& d, int mount = -1)
	{
		int k;
		int max;
		int m[31];
		for (int i = 0; i < 31; i++)
			m[i] = 0;
		for (int i = 0; i < Counts.size(); i++)
			if (mount == -1 || Counts[i].getDate().month == mount)
				m[Counts[i].getDate().day - 1] += Counts[i].getSteps();
		max = m[0];
		for (int i = 1; i < 31; i++)
			if (max < m[i])
			{
				max = m[i];
				k = i;
			}
		for (int i = 0; i < Counts.size(); i++)
			if ((Counts[i].getDate().day == k + 1 && Counts[i].getDate().month == mount) || mount == -1)
				d = Counts[i].getDate();
		return max;
	}
	void saveFile()
	{
		ofstream file("Pedometr.txt");
		for (int i = 0; i < Counts.size(); i++)
		{
			Date t = Counts[i].getDate();
			file << Counts[i].getSteps() << '$' << Counts[i].getStartHour() << '$' << Counts[i].getStartMinute() << '$' << Counts[i].getEndHour() << '$' << Counts[i].getEndMinute() << endl;
		}
	}
	/*void openFile()
	{
		ifstream file("Pedometr.txt");
	}
	*/
	};

	void main()
	{
		Pedometr p;
		Date d;
		d.day = 3;
		d.month = 4;
		d.year = 2010;
		p.AddCount(d, 4, 5, 10, 12, 124);
		p.AddCount(d, 4, 15, 8, 12, 2344);
		for (int i = 0; i < 2; i++)
			cout << p[i].getSteps();
		p.saveFile();
		//p.openFile();
		for (int i = 0; i < 2; i++)
			cout << p[i].getSteps();
		system("pause");
	}