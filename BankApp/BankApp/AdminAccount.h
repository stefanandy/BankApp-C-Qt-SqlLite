#pragma once
#include "Account.h"
#include "ClientAccount.h"
#include <vector>

class AdminAccount :public Account
{
	QString admin;
	QString pass;
	vector<ClientAccount*> v;

public:

	AdminAccount(QString*, QString*);
	void setClients(ClientAccount*);
	~AdminAccount();
};

