#include "BankAccount.h"
#include "Account.h"



BankAccount::BankAccount(QString* iban, QString* _currency, double* _value) {
	
	IBAN = *iban;
	currency = *_currency;
	value = *_value;

}

BankAccount::BankAccount(QString* currency_s, double value_s) 
{
	

	currency = *currency_s;
	value = value_s;
}

BankAccount::BankAccount(QString* currency_s) {
	
	currency = *currency_s;
	IBAN = GenerateIBAN(currency);
}


BankAccount::~BankAccount()
{
}

QString BankAccount::GenerateIBAN(QString _currency_) {
	
	QString generatedIBAN;
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	generatedIBAN = QString("RO" + GetRand(10,90) + _currency_ + /*(10000 + qrand()% 99999)*/ GetRand(10000,99999) + "XXXX");
	return generatedIBAN;

}

double BankAccount::getValue() {

	return value;

}

QString BankAccount::getIBAN() {
	return IBAN;
}

QString BankAccount::GetRand(int low, int high) {
	int i = qrand() % ((high + 1) - low) + low;
	QString s = QString::number(i);
	return s;
}

QString BankAccount::getCurrency() {
	return currency;
}

void BankAccount::updateBalance(double* _value) {
	if (*_value < 0) {
		
		*_value *= -1;
		value -= *_value;
	
	}else if (*_value > 0) {
		
		value += *_value;
	
	}
}