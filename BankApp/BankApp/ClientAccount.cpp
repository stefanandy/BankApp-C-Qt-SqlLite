#include "ClientAccount.h"



ClientAccount::ClientAccount(QString user, QString password, QString firstName, QString lastName, QString phNumber) : Account(user, password)
{
	userName = user;
	Password = password;
	FirstName = firstName;
	LastName = lastName;
	PhoneNumber = phNumber;
	
}


ClientAccount::~ClientAccount()
{
}

void ClientAccount::createBankAcount(QString* currency) {
	bankAccount = new BankAccount(currency);
}

BankAccount* ClientAccount::getBankAccount() {
	return bankAccount;
}


QString ClientAccount::getUserName() {
	return userName;
}


QString ClientAccount::getFirstName() {
	return FirstName;
}


QString ClientAccount::getLastName() {
	return LastName;
}


QString ClientAccount::getPhoneNumber() {
	return PhoneNumber;
}