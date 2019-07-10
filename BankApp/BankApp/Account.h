#pragma once

#include <QString>

class Account
{
	QString id;
	QString password;
	
public:
	Account(QString, QString);
	Account();
	~Account();
};

