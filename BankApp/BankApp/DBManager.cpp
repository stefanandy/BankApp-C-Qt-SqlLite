#include "DBManager.h"



DBManager::DBManager(QString* path = &QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"))
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(*path);
	
	db.open();

}


DBManager::~DBManager()
{
}

void DBManager::ErrorMessage(QString* message) {
	
	QMessageBox* m = new QMessageBox();
	m->setText(*message);
	m->show();
}

void DBManager::createUser(QString* user, QString* pass, QString* firstName, QString* lastName, QString* phNumber) {
	
	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("INSERT INTO UsersTable (Username, Password, FirstName, LastName, PhoneNumber) VALUES (?,?,?,?,?)");
	q->addBindValue( *user);
	q->addBindValue( *pass);
	q->addBindValue( *firstName);
	q->addBindValue(*lastName);
	q->addBindValue( *phNumber);
	if (q->exec()) {
		ErrorMessage(&QString("User succesfully created!"));

	}
	else {
		ErrorMessage(&q->lastError().text());
	}

}

void DBManager::closeDatabase() {
	db.close();
}


bool DBManager::checkUserExist(QString* user,QString* pass) {
	
	QSqlQuery* q = new QSqlQuery();
	q->prepare("SELECT * FROM UsersTable WHERE UserName=(:name) ");
	q->bindValue(":name",*user);
	
		if (q->exec() == true ) {
			
			QString password;

			while (q->next()) {
				password = q->value(1).toString();
			}
			if (pass == password) {

				return true;
			
			}else {
				
				return false;
			
			}

			
		}else { 
			ErrorMessage(&getQueryError(q));
			return false; 
		}
}

bool DBManager::checkAdminExist(QString* admin, QString* pass)
{
	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("SELECT AdminPassword FROM AdminsTable WHERE [AdminsTable].AdminName=(:admin_name)");
	q->bindValue(":admin_name", *admin);
	
	if (q->exec()) {
		
		QString password;

		while (q->next()) {
			
			password = q->value(0).toString();

		}

		if (pass == password) {
		
			return true;

		}
		else {
			
			return false;

		}
	
	}
	else {
	
		ErrorMessage(&getQueryError(q));
		return false;

	}

	
}

QString DBManager::getDatabaseError(){

	return this->db.lastError().text();

}

QString DBManager::getQueryError(QSqlQuery* q) {
	
	return q->lastError().text();

}

ClientAccount* DBManager::getAccount(QString* user, QString* pass) {

	QString firstName, lastName, phNumber;
	ClientAccount* cAcc;
	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("SELECT FirstName, LastName, PhoneNumber FROM [UsersTable] WHERE [UsersTable].UserName=(:user) AND [UsersTable].Password=(:pass)");
	q->bindValue(":user", *user);
	q->bindValue(":pass", *pass);
	if (q->exec()) {
		while (q->next()) {
			firstName = q->value(0).toString();
			lastName = q->value(1).toString();
			phNumber = q->value(2).toString();
		}
		cAcc = new ClientAccount(*user, *pass, firstName, lastName, phNumber);
		return cAcc;
	}
	else {
		ErrorMessage(&q->lastError().text());
	}
	
	
	
}

bool DBManager::createBankAccount(QString* username, QString* iban, double* value, QString* currency) {

	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("INSERT INTO BankAccountTable (UserName, IBAN, VALUE, CURRENCY) VALUES (:user, :iban, :value, :currency)");
	q->bindValue(":user", *username);
	q->bindValue(":iban", *iban);
	q->bindValue(":value", *value);
	q->bindValue(":currency", *currency);
	if (q->exec()) {
		return true;
	}
	return false;

}

QSqlTableModel* DBManager::getIBANTable(QString* user) {
	
	QSqlTableModel* model = new QSqlTableModel();
	model->setTable("BankAccountTable");
	model->setFilter("UserName='"+ *user + "'");
	model->select();
	return model;

}

void DBManager::comboBoxData(QComboBox* box,QString* user) {
	
	QList<QString> list;
	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("SELECT IBAN FROM BankAccountTable WHERE [BankAccountTable].UserName=(:user)");
	q->bindValue(":user", *user);
	if (q->exec()) {
		while (q->next()) {
			QString iban = q->value(0).toString();
			list.append(iban);
		}

		box->addItems(list);
		
	}

}


void DBManager::deleteBankAccount(QComboBox* box) {
	
	QString iban = box->currentText();
	int itemIndex = box->currentIndex();

	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("DELETE FROM BankAccountTable WHERE [BankAccountTable].IBAN=(:iban)");
	q->bindValue(":iban", iban);

	if (q->exec()) {
		ErrorMessage(&QString("SUCCESSFULLY DELETED"));
		box->removeItem(itemIndex);
	}
	else { ErrorMessage(&q->lastError().text()); }

}


BankAccount* DBManager::getBankAccountFromDB(QString* iban) {
	
	QString currency;
	double value;

	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("SELECT CURRENCY, VALUE FROM BankAccountTable WHERE [BankAccountTable].IBAN=(:iban)");
	q->bindValue(":iban",*iban);
	if (q->exec()) {
		
		while (q->next()) {
			currency = q->value(0).toString();
			value = q->value(1).toDouble();
		}

		BankAccount* b = new BankAccount(iban, &currency, &value);
		
		return b;

	}
	else { ErrorMessage(&q->lastError().text()); }

}

BankAccount* DBManager::getBankAccountFromCreditTable(QString* iban)
{
	double value_;
	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("SELECT VALUE FROM CreditTable WHERE [CreditTable].IBAN=(:iban)");
	q->bindValue(":iban", *iban);

	if (q->exec()) {
		
		while (q->next()) {
			
			value_ = q->value(0).toDouble();

		}

	}

	BankAccount* b = new BankAccount(iban, value_);
	return b;

}



ClientAccount* DBManager::getAccountFromUserOnly(QString* user) {

	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("SELECT FirstName, LastName, PhoneNumber FROM UsersTable WHERE [UsersTable].UserName=(:user)");
	q->bindValue(":user", *user);
	if (q->exec()) {
		QString firstName, lastName, phoneNumber, password = "default";
		while(q->next()){
			
			firstName = q->value(0).toString();
			lastName = q->value(1).toString();
			phoneNumber = q->value(2).toString();
		}

		ClientAccount* clientAccount = new ClientAccount(*user,password,firstName,lastName,phoneNumber);
		return clientAccount;
	}
	else {
		ErrorMessage(&q->lastError().text());
	}

}

void DBManager::getAllClients(AdminAccount* a)
{
	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("SELECT * FROM UsersTable");

	if (q->exec()) {

		while (q->next()) {
			
			QString user = q->value(0).toString();
			QString pass = q->value(1).toString();
			QString firstName = q->value(2).toString();
			QString lastName = q->value(3).toString();
			QString phoneNumber = q->value(4).toString();
			ClientAccount* c = new ClientAccount(user, pass, firstName, lastName, phoneNumber);

			a->setClients(c);
		
		}

	}
}

QString DBManager::getUserNameFromIban(QString* iban) {

	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("SELECT UserName FROM BankAccountTable WHERE [BankAccountTable].IBAN=(:iban)");
	q->bindValue(":iban", *iban);
	if (q->exec()&&q->next()) {
		QString user = q->value(0).toString();
		return user;
	}
	else { ErrorMessage(&q->lastError().text()); }

}

void DBManager::makeTransaction(QString* sender, QString* receiver, double* value, QString* sender_currency, QString* receiver_currency) {
	
	QSqlQuery* q = new QSqlQuery(db);

	q->prepare("INSERT INTO TransactionsTable (SENDER, RECEIVER, VALUE, SenderCURRENCY, ReceiverCURRENCY) VALUES(:sender, :receiver, :value, :scurrency, :rcurrency) ");
	q->bindValue(":sender", *sender);
	q->bindValue(":receiver", *receiver);
	q->bindValue(":value", *value);
	q->bindValue(":scurrency", *sender_currency);
	q->bindValue(":rcurrency", *receiver_currency);
	
	if (q->exec()) {
		ErrorMessage(&QString("Transaction Inserted INTO DATABASE"));
	}else { ErrorMessage(&q->lastError().text()); }

}


void DBManager::updateBankAccountBalance(BankAccount* b) {
	
	QSqlQuery* q = new QSqlQuery(db);
	q->prepare("UPDATE BankAccountTable SET VALUE=(:value) WHERE IBAN=(:iban)");
	q->bindValue(":value",b->getValue());	
	q->bindValue(":iban", b->getIBAN());
	
	if (q->exec()) {
		
		ErrorMessage(&QString("BALANCE UPDATED IN DATABASE"));

	}else { ErrorMessage(&q->lastError().text()); }

}

QSqlTableModel* DBManager::getTransactionsTable(QString* iban) {

	QSqlTableModel* model = new QSqlTableModel();
	model->setTable("TransactionsTable");
	model->setFilter("SENDER='" + *iban + "' OR RECEIVER='" + *iban + "'");
	model->select();
	return model;
			
}

QSqlTableModel* DBManager::getCreditTable()
{
	QSqlTableModel* model = new QSqlTableModel();
	model->setTable("CreditTable");
	model->select();
	return model;

}

QSqlTableModel * DBManager::getAprovedCreditsTable()
{
	QSqlTableModel* m = new QSqlTableModel();
	m->setTable("CreditTable");
	m->setFilter("STATE='1'");
	m->select();

	return m;
}

void DBManager::getUnaprovedCreditsIBAN(QComboBox* box)
{
	QSqlQuery* q = new QSqlQuery(db);

	q->prepare("SELECT IBAN FROM CreditTable WHERE [CreditTable].STATE=(:false)");
	q->bindValue(":false", false);

	if (q->exec()) {
		
		QList<QString> list;

		while (q->next()) {
			
			QString iban = q->value(0).toString();
			list.append(iban);
		
		}

		box->addItems(list);

	}
	else {
	
		ErrorMessage(&q->lastError().text());

	}

}

void DBManager::updateCreditState(QString* iban)
{

	QSqlQuery* q = new QSqlQuery(db);

	q->prepare("UPDATE CreditTable SET STATE=(:true) WHERE [CreditTable].IBAN=(:iban)");
	q->bindValue(":true", true);
	q->bindValue(":iban", *iban);

	if (q->exec()) {
		
		ErrorMessage(&QString("Credit Approved"));

	}
	else {
		ErrorMessage(&q->lastError().text());
	}


}

void DBManager::updateAddCreditToBalance(QString *iban)
{

	BankAccount* accountFromDb = getBankAccountFromDB(iban);

	BankAccount* credit = getBankAccountFromCreditTable(iban);
	double credit_value = credit->getValue();

	accountFromDb->updateBalance( &credit_value );
	updateBankAccountBalance(accountFromDb);


}

ClientAccount* DBManager::getInfoFromIBAN(QString* iban)
{
	

	return getAccountFromUserOnly(&getUserNameFromIban(iban));


}

void DBManager::creditDatabaseInsert(QString* iban, double* value) {
	
	QSqlQuery* q = new QSqlQuery(db);
	
	q->prepare("INSERT INTO CreditTable (IBAN,VALUE,STATE)  VALUES (:iban,:value,:state) ");
	q->bindValue(":iban",*iban);
	q->bindValue(":value", *value);
	q->bindValue(":state", false);
	
	if (q->exec()) {
		ErrorMessage(&QString("Succesfull"));
	}
	else {
		ErrorMessage( &q->lastError().text() );
	}

}

