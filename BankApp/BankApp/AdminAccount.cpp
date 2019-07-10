#include "AdminAccount.h"



AdminAccount::AdminAccount(QString* admin_, QString* pass_) : Account(*admin_, *pass_)
{
	admin = *admin_;
	pass = *pass_;

}



void AdminAccount::setClients(ClientAccount* c)
{
	v.push_back(c);
}


AdminAccount::~AdminAccount()
{
}
