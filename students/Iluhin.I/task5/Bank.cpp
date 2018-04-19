#include <iostream> 
#include <vector>

using namespace std;

class User
{
private:
	int cardNumber;
	int pinCode;
	string fullName;
	long money;
public:
	User(int _cardNumber, int _pinCode, string _fullName)
	{
		cardNumber = _cardNumber;
		pinCode = _pinCode;
		fullName = _fullName;
		money = 0;
	}
	int GetCardNumber()
	{
		return cardNumber;
	}
	bool CheckPinCode(int _pinCode)
	{
		return _pinCode == pinCode;
	}
	string GetFullName()
	{
		return fullName;
	}
	bool AddMoney(long newMoney)
	{
		if (newMoney < 0)
		{
			return false;
		}
		money += newMoney;
		return true;
	}
	bool  WithdrawMoney(long oldMoney)
	{
		if ((oldMoney < 0) && (money < oldMoney))
		{
			return false;
		}
		money -= oldMoney;
		return true;
	}
};

class ATM
{
private:
	int bills[6];
public:
	ATM()
	{
		for (int i = 0; i < 6; i++)
		{
			bills[i] = 1600000;
		}
	}
};

class ProcessingCenter
{
private:
	vector<User> users;
	int count;
	int GetRandomPassWord()
	{
		return rand() % 10000;
	}
	int GetNewCardNumber()
	{
		count++;
		return count;
	}
public:
	ProcessingCenter()
	{
		count = -1;
	}
	void AddUser(string fullName)
	{
		int cardNumber = GetNewCardNumber();
		int password = GetRandomPassWord();
		User newUser(cardNumber, password, fullName);
		users.push_back(newUser);
	}
	bool CheckUser(int cardNumber)
	{
		int i = 0; 
		while (users[i].GetCardNumber() != cardNumber && i < users.size())
			i++;
		if (i == users.size())
			return false;
		else 
			return true;
	}
};

void main()
{
	system("pause");
}