#pragma once

#include <QWidget>
#include "ui_QtClientClass.h"
#include "ClientAccount.h"
#include "QtGenerateIBAN.h"
#include "QtDeleteBAUI.h"
#include "QtMakePaymentUI.h"
#include "QtTransactionsHistoryUI.h"
#include "QtClientAskForCreditUI.h"


class QtClientClass : public QWidget
{
	Q_OBJECT

public:
	QtClientClass(QString* , QWidget *parent = Q_NULLPTR);
	QtClientClass(ClientAccount*, QWidget *parent = Q_NULLPTR);
	QtClientClass(QWidget *parent = Q_NULLPTR);
	~QtClientClass();
	void connectToDatabaseAndGetUser(QString*);
	void ErrorMessage(QString*);
	void loadTableData();
	
	

//public slots:
//	void getUserName(QString);
//
private slots:
	void createBankAccountUI();
	void loadTableSlot();
	void deleteUIScreen();
	void transactionUIButton();
	void transactionHistoryButton();
	void creditUIButton();

private:

	Ui::QtClientClass ui;
	ClientAccount* clientAccount;
	QtGenerateIBAN* generateBankAccountUI;
	QtDeleteBAUI* deleteUI;
	QtMakePaymentUI* makePaymentUI;
	QtTransactionsHistoryUI* tHistoryUI;
	QtClientAskForCreditUI* creditUI;
	DBManager* db;
	void getConnection();
	
};
