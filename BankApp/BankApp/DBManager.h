#pragma once
#include <QString>
#include <QtSql>
#include <qsqlquery.h>
#include <qsqlquerymodel.h>
#include <qmessagebox.h>
#include "ClientAccount.h"
#include "AdminAccount.h"


class DBManager
{
public:

	DBManager(QString* path);
	void ErrorMessage(QString*);
	void createUser(QString*, QString*,QString*,QString*,QString*);
	void closeDatabase();
	void comboBoxData(QComboBox*,QString*);
	void deleteBankAccount(QComboBox*);
	void makeTransaction(QString*, QString*, double*, QString*, QString*);
	void updateBankAccountBalance(BankAccount*);
	void creditDatabaseInsert(QString*,double*);
	void getAllClients(AdminAccount*);
	void getUnaprovedCreditsIBAN(QComboBox*);
	void updateCreditState(QString*);
	void updateAddCreditToBalance(QString*);
	BankAccount* getBankAccountFromDB(QString*);
	BankAccount* getBankAccountFromCreditTable(QString*);
	bool checkUserExist(QString*,QString*);
	bool checkAdminExist(QString*, QString*);
	bool createBankAccount(QString*, QString*, double*, QString* );
	QString getUserNameFromIban(QString*);
	QString getDatabaseError();
	QString getQueryError(QSqlQuery*);
	ClientAccount* getAccount(QString*, QString*);
	ClientAccount* getAccountFromUserOnly(QString*);
	ClientAccount* getInfoFromIBAN(QString*);
	QSqlTableModel* getIBANTable(QString*);
	QSqlTableModel* getTransactionsTable(QString*);
	QSqlTableModel* getCreditTable();
	QSqlTableModel* getAprovedCreditsTable();
	
	
	

	~DBManager();

private:
	QSqlDatabase db;

};

