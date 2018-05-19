#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class User
{
private:
	int cardNumber;
	int pinCode;
	string fullName;
	long money;
	bool state;
public:
	User()
	{
		
	}
	User(int _cardNumber, int _pinCode, string _fullName)
	{
		cardNumber = _cardNumber;
		pinCode = _pinCode;
		fullName = _fullName;
		money = 0;
		state = true;
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
		if (!state || newMoney < 0)
		{
			return false;
		}
		money += newMoney;
		return true;
	}
	bool  LooseMoney(long oldMoney)
	{
		if (!state || ((oldMoney < 0) && (money < oldMoney)))
		{
			return false;
		}
		money -= oldMoney;
		return true;
	}
	int GetMoney()
	{
		return money;
	}
	void SetState(bool newState)
	{
		state = newState;
	}
	string GetStringState()
	{
		if (state)
		{
			return "Not blocked";
		}
		return "Blocked";
	}
};

class ProcessingCenter
{
private:
	vector<User> users;
	int count;
	string FormatNumber(int value)
	{
		string result = to_string(value);
		if (value < 1000)
		{
			result = "0" + result;
			if (value < 100)
			{
				result = "0" + result;
				if (value < 10)
				{
					result = "0" + result;
				}
			}
			
		}
		return result;
	}
	int GetRandomPinCode()
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
		count = 0;
		users = vector<User>();
		users.resize(1);
	}
	void RegisterUser(string fullName)
	{
		int cardNumber = GetNewCardNumber();
		int pinCode = GetRandomPinCode();
		User newUser;
		newUser = User(cardNumber, pinCode, fullName);
		users.push_back(newUser);
		PrintUserInfo(cardNumber);
		cout << "Your cardNumber: " << FormatNumber(cardNumber) << endl;
		cout << "Your pinCode: " << FormatNumber(pinCode) << endl;
	}
	bool CheckUserExists(int cardNumber)
	{
		return count > cardNumber;
	}
	bool CheckUser(int cardNumber, int pinCode)
	{
		return CheckUserExists(cardNumber) && users[cardNumber].CheckPinCode(pinCode);
	}
	void PrintUserInfo(int cardNumber)
	{
		cout << "Money: " << users[cardNumber].GetMoney() << endl;
		cout << "State: " << users[cardNumber].GetStringState() << endl;
		cout << "Fullname: " << users[cardNumber].GetFullName() << endl;
	}
	bool RequestToLooseMoney(int cardNumber, long value)
	{
		return  users[cardNumber].LooseMoney(value);
	}
	bool RequestToAddMoney(int cardNumber, long value)
	{
		return  users[cardNumber].AddMoney(value);
	}
	void SetState(int cardNumber, bool newState)
	{
		users[cardNumber].SetState(newState);
	}
};

class ATM
{
private:
	ProcessingCenter* PC;
	int cardNumber;
	int bills[6];
	int billsValue[6];
public:
	ATM(ProcessingCenter* pc)
	{
		for (int i = 0; i < 6; i++)
		{
			bills[i] = 1600000;
		}
		PC = pc;
		billsValue[0] = 100;
		billsValue[1] = 200;
		billsValue[2] = 500;
		billsValue[3] = 1000;
		billsValue[4] = 2000;
		billsValue[5] = 5000;
	}
	bool LoadCard(int _cardNumber)
	{
		if (PC->CheckUserExists(_cardNumber))
		{
			cardNumber = _cardNumber;
			return true;
		}
		return false;
	}
	bool FindUser(int _cardNumber)
	{
		return PC->CheckUserExists(_cardNumber);
	}
	bool CheckPinCode(int _pinCode)
	{
		return PC->CheckUser(cardNumber, _pinCode);
	}
	bool PrintState()
	{
		PC->PrintUserInfo(cardNumber);
			return true;
	}
	bool WithDrawMoney(long value)
	{
		if (!PC->RequestToLooseMoney(cardNumber, value))
		{
			return false;
		}
		int billsResult[6];
		long remainder = value;
		for (int i = 0; i < 6; i++)
		{
			billsResult[i] = remainder / billsValue[i];
			int tmpcount = min(billsResult[i], bills[i]);
			remainder = remainder - billsResult[i] * billsValue[i];
		}
		if (remainder != 0)
		{
			PC->RequestToAddMoney(cardNumber, value);
			return false;
		}
		for (int i = 0; i < 6; i++)
		{
			bills[i] -= billsResult[i];
		}
		return true;
	}
	bool LoadMoney(int cash[6])
	{
		long newValue = 0;
		for (int i = 0; i <6; i++)
		{
			newValue += cash[i] * billsValue[i];
		}
		if (!PC->RequestToAddMoney(cardNumber, newValue))
		{
			return false;
		}
		for (int i = 0; i <6; i++)
		{
			bills[i] += cash[i];
		}
		return true;
	}
	bool BlockUser()
	{
		PC->SetState(cardNumber, false);
			return true;
	}
	bool Returncard()
	{
		int cardNumber = -1;
		return true;
	}
};

void HandleCommand(bool state)
{
	if (state)
	{
		cout << "success" << endl;
	}
	else cout << "failed" << endl;
}
	
int main()
{
	ProcessingCenter PC;
	int n;
	cout << "Input count of users: ";
	cin >> n;
	string tmp;
	for (int i = 0; i < n; i++)
	{
		cout << "Input name of new user: ";
		cin >> tmp;
		PC.RegisterUser(tmp);
	}
	ATM atm(&PC);
	system("pause");
	return 0;
}
