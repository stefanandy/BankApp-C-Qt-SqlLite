#include "BankApp.h"
#include "QtAdminClass.h"
#include <QtSql>
#include <QSqlQuery>
#include <qmessagebox.h>


BankApp::BankApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(handleNewLoginButton()));
	//connect(ui.loginButton, &QPushButton::clicked, this, &BankApp::handleLoginButton);
	connect(ui.registerButton, SIGNAL(clicked()), this, SLOT(handleRegisterButton()));
	
}



void BankApp::ShowClientUI() {
	
	
	clientUI = new QtClientClass(clientAccount);
	
	clientUI->setWindowModality(Qt::ApplicationModal);
	//clientUI->setVisible(true);
	
	clientUI->hide(); //When you use setWindowModality, you hide and then show again the UI;
	clientUI->show();
	
	

}





void BankApp::handleRegisterButton() {

	registerUI = new QtGuiClassRegister();
	registerUI->setVisible(true);
	registerUI->show();

}

void BankApp::ErrorMessage(QString* error) {
	
	QMessageBox* m = new QMessageBox();
	m->setText(*error);
	m->show();

}

void BankApp::getQStringfromField(QLineEdit* userField, QLineEdit* passwordField) {

	userName = userField->text();
	password = passwordField->text();

}

bool BankApp::checkLineEditData(QLineEdit* userField, QLineEdit* passwordField) {

	QString message = "Incorrect Username OR passoword!";

	if (userField->text().isEmpty() || passwordField->text().isEmpty()) {
		ErrorMessage(&message);
		return false;
	} else {
		return true;
	}

}

void BankApp::handleNewLoginButton() {

	DBManager* db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));
	if (db->checkUserExist(&this->ui.userField->text(), &this->ui.passwordField->text())== true ) {
		
		clientUI = new QtClientClass(db->getAccount(&this->ui.userField->text(),&this->ui.passwordField->text()));
		clientUI->setWindowModality(Qt::ApplicationModal);
		clientUI->show();
	}
	else if (db->checkAdminExist(&this->ui.userField->text(), &this->ui.passwordField->text()) == true) {

		adminUI = new QtAdminClass(&AdminAccount(&this->ui.userField->text(), &this->ui.passwordField->text()));
		adminUI->setWindowModality(Qt::ApplicationModal);
		adminUI->show();

	}else {
		ErrorMessage(&db->getDatabaseError());
	}
}



