#include "QtClientClass.h"
#include <QtSql>
#include <QSqlQuery>
#include <qmessagebox.h>
#include <qsqlquerymodel.h>
#include <qsqltablemodel.h>
#include <qstandarditemmodel.h>



QtClientClass::QtClientClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//QObject::connect(ui.createBankAccountButton, SIGNAL(clicked()), this, SLOT(ErrorMessage(&QString("NOT YET"))));
	connect(ui.creditButton, SIGNAL(clicked()), this, SLOT(loadTableSlot()));

}

QtClientClass::QtClientClass(QString* u,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.creditButton, SIGNAL(clicked()), this, SLOT(loadTableSlot()));
	//connectToDatabaseAndGetUser(u);
	//ui.helloUserLabel->setText(*u);
	//connect(ui.createBankAccountButton,SIGNAL(clicked()),this,SLOT(connectToDatabse()));
	/*user = *u;
	ui.helloUserLabel->setText(QString("MUE"));
	ui.helloUserLabel->repaint();*/
	
}

QtClientClass::QtClientClass(ClientAccount* cAccount, QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	ui.helloUserLabel->setText(QString("<html><i>Hello, "+ cAccount->getFirstName()+"</i><html>"));
	//ErrorMessage(&QString("User is : " + cAccount->getUserName()+" and name is"+cAccount->getFirstName()));
	clientAccount = cAccount;
	getConnection();
	loadTableData();
	connect(ui.createBankAccountButton, SIGNAL(clicked()), this, SLOT(createBankAccountUI()));
	connect(ui.refreshTableButton, SIGNAL(clicked()), this, SLOT(loadTableSlot()));
	connect(ui.deleteBankAccountButton, SIGNAL(clicked()), this, SLOT(deleteUIScreen()));
	connect(ui.paymentButton, SIGNAL(clicked()), this, SLOT(transactionUIButton()));
	connect(ui.transHistoryButton, SIGNAL(clicked()), this, SLOT(transactionHistoryButton()));
	connect(ui.creditButton, SIGNAL(clicked()), this, SLOT(creditUIButton()));

}

QtClientClass::~QtClientClass()
{
}


void QtClientClass::createBankAccountUI() {
		
	generateBankAccountUI = new QtGenerateIBAN(clientAccount);
	generateBankAccountUI->setWindowModality(Qt::ApplicationModal);
	generateBankAccountUI->show();

}

//depreciated
void QtClientClass::connectToDatabaseAndGetUser(QString* u) {

	QString password, firstName, lastName, phoneNumber;
	
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	QString dbname = "UsersDatabase";
	QString servername = "DESKTOP-FTFFKM6";
	db.setConnectOptions();
	QString dsn = QString("DRIVER={SQL Server Native Client 11.0};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(servername).arg(dbname);
	db.setDatabaseName(dsn);
	bool ok = db.open();
	
	if (ok == true) {
		QSqlQuery q;
		q.prepare("SELECT [UserTable].Password, [UserTable].FirstName, [UserTable].LastName, [UserTable].PhoneNumber FROM [UserTable] WHERE [UserTable].UserName = (:username)");
		q.bindValue(":username", *u);
		ok = q.exec();
		if (ok == true ) {
			
			while (q.next()) {
			
				 password = q.value(0).toString();
				 firstName = q.value(1).toString();;
				 lastName = q.value(2).toString();
				 phoneNumber = q.value(3).toString();

			}
			
			clientAccount = new ClientAccount(*u,password, firstName, lastName,phoneNumber);
			
		}else {
			ErrorMessage(&QString("Query Error"));
			
		}
	}
	else { ErrorMessage(&db.lastError().text()); }
	
}
//

void QtClientClass::ErrorMessage(QString* message) {
	QMessageBox* m = new QMessageBox();
	m->setText(*message);
	m->setVisible(true);
	m->show();

}

void QtClientClass::loadTableData() {
	
	

	
	this->ui.bankAccountTableView->setModel(db->getIBANTable(&clientAccount->getUserName()));
	this->ui.bankAccountTableView->hideColumn(0);
	


	/*QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	QString dbname = "UsersDatabase";
	QString servername = "DESKTOP-FTFFKM6";
	db.setConnectOptions();
	QString dsn = QString("DRIVER={SQL Server Native Client 11.0};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(servername).arg(dbname);
	db.setDatabaseName(dsn);
	bool ok = db.open();*/
	//bool ok = true;
	///*if (ok == true) {*/
	//QSqlQueryModel* model = new QSqlQueryModel();
	//
	//
	//	//QSqlQueryModel* model = new QSqlQueryModel();
	//	QSqlQuery* q = new QSqlQuery();
	//	
	//	q->prepare("SELECT IBAN, VALUE, CURRENCY FROM BankAccountTable WHERE [BankAccountTable].UserName = (:username)");
	//	q->bindValue("(:username)", clientAccount->getUserName());
	//	//q->setForwardOnly(true);
	//	ok = q->exec();
	//	
	//	if (ok == true) {
	//		model->setQuery(*q);
	//		//table->setModel(model);
	//		//table->resizeColumnsToContents();
	//		//table->show();
	//		
	//		/*model->setTable("BankAccountTable");
	//		model->setFilter("UserName='" + clientAccount->getUserName()+"'");
	//		model->select();*/
	//		this->ui.bankAccountTableView->setModel(model);
	//		this->ui.bankAccountTableView->update();
	//		//this->ui.bankAccountTableView->resizeColumnsToContents();
	//	
	//	}
	//	else {
	//		ErrorMessage(&QString("MODEL ERROR"));
	//	}


	/*}
	else { ErrorMessage(&db.lastError().text()); }*/
	/*db.close();*/
}

void QtClientClass::getConnection()
{
	 db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));
}

void QtClientClass::loadTableSlot() {

	
	this->ui.bankAccountTableView->setModel(db->getIBANTable(&clientAccount->getUserName()));
	this->ui.bankAccountTableView->hideColumn(0);
	
}


void QtClientClass::deleteUIScreen() {
	
	deleteUI = new QtDeleteBAUI(&clientAccount->getUserName());
	deleteUI->setWindowModality(Qt::ApplicationModal);
	deleteUI->show();


}


void QtClientClass::transactionUIButton() {
	
	makePaymentUI = new QtMakePaymentUI(clientAccount);
	makePaymentUI->setWindowModality(Qt::ApplicationModal);
	makePaymentUI->show();

}

void QtClientClass::transactionHistoryButton() {
	
	tHistoryUI = new QtTransactionsHistoryUI(clientAccount);
	tHistoryUI->setWindowModality(Qt::ApplicationModal);
	tHistoryUI->show();
}


void QtClientClass::creditUIButton() {
	
	creditUI = new QtClientAskForCreditUI(&clientAccount->getUserName());
	creditUI->setWindowModality(Qt::ApplicationModal);
	creditUI->show();
	
}

