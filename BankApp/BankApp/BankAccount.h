#pragma once
#include "Account.h"
#include <qglobal.h>
#include <qdatetime.h>

class BankAccount 
{

	QString IBAN;
	QString currency;
	double value;
	QString GetRand(int, int);

public:
	BankAccount(QString*, QString*, double*);
	BankAccount(QString*, double);
	BankAccount(QString*);
	BankAccount();
	QString GenerateIBAN(QString);
	QString getIBAN();
	QString getCurrency();
	void updateBalance(double*);
	double getValue();
	~BankAccount();
};

