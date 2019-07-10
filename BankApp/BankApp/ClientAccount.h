#pragma once

#include "BankAccount.h"
#include "Account.h"


using namespace std;

class ClientAccount : public Account
{
	QString userName;
	QString Password;
	QString FirstName;
	QString LastName;
	QString PhoneNumber;
	BankAccount* bankAccount;

public:
	ClientAccount(QString, QString, QString, QString, QString);
	void createBankAcount(QString*);
	BankAccount* getBankAccount();
	QString getUserName();
	QString getFirstName();
	QString getLastName();
	QString getPhoneNumber();
	~ClientAccount();
};

