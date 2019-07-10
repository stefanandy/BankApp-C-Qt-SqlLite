#include "QtGenerateIBAN.h"

QtGenerateIBAN::QtGenerateIBAN(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//connect(ui.createAccountButton, SIGNAL(clicked()), this, SLOT(createBankAccount()));
}

QtGenerateIBAN::QtGenerateIBAN(ClientAccount* cAccount , QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	clientAccount = cAccount;
	connect(ui.createAccountButton, SIGNAL(clicked()), this, SLOT(createBankAccount()));
}

QtGenerateIBAN::~QtGenerateIBAN()
{
}

void QtGenerateIBAN::createBankAccount() {
	 
	/*clientAccount->createBankAcount(&this->ui.comboBox_2->currentText());
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	QString dbname = "UsersDatabase";
	QString servername = "DESKTOP-FTFFKM6";
	db.setConnectOptions();
	QString dsn = QString("DRIVER={SQL Server Native Client 11.0};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(servername).arg(dbname);
	db.setDatabaseName(dsn);

	bool ok = db.open();
	if (ok == true) {
		QSqlQuery q;
		q.prepare("INSERT INTO [BankAccountTable] (UserName, IBAN, VALUE, CURRENCY) Values(:username,:iban,:value,:currency)");
		q.bindValue(":username", clientAccount->getUserName());
		q.bindValue(":iban", clientAccount->getBankAccount()->getIBAN());
		q.bindValue(":currency", this->ui.comboBox_2->currentText());
		q.bindValue(":value", 0.00);
		ok = q.exec();
		if (ok == true) {
			ErrorMessage(&QString("Account created, IBAN:" + clientAccount->getBankAccount()->getIBAN()));
		}
		else { ErrorMessage(&q.lastError().text()); }
	}
	else {
		ErrorMessage(&db.lastError().text());
	}*/


	double zero=0.00;
	clientAccount->createBankAcount(&this->ui.comboBox_2->currentText());
	DBManager* db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));
	if (db->createBankAccount(&clientAccount->getUserName(), &clientAccount->getBankAccount()->getIBAN(), &zero, &this->ui.comboBox_2->currentText()) == true) {
		ErrorMessage(&QString("Account created, IBAN:" + clientAccount->getBankAccount()->getIBAN()));
	}else {
		ErrorMessage(&db->getDatabaseError());
	}
	db->closeDatabase();

}

void QtGenerateIBAN::ErrorMessage(QString* qs) {
	
	QMessageBox* m = new QMessageBox();
	m->setText(*qs);
	m->show();

}
