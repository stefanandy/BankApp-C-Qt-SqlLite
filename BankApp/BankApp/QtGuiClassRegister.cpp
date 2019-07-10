#include "QtGuiClassRegister.h"
#include <qmessagebox.h>
#include <QtSql>    
#include <QSqlQuery>


QtGuiClassRegister::QtGuiClassRegister(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	connect(ui.registerAccountButton, SIGNAL(clicked()), SLOT(handleNewDatabase()));
}

QtGuiClassRegister::~QtGuiClassRegister()
{
}


void QtGuiClassRegister::handleRegisterAccount() {

	
	getQStringFromField(ui.user_filed, ui.password_field, ui.firstName_field, ui.lastNameField, ui.phoneNumber_field);
	
	
	if (checkLineEdit(ui.user_filed, ui.password_field, ui.firstName_field, ui.lastNameField, ui.phoneNumber_field) == true) {

		QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
		QString dbname = "UsersDatabase";
		QString servername = "DESKTOP-FTFFKM6";
		db.setConnectOptions();
		QString dsn = QString("DRIVER={SQL Server Native Client 11.0};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(servername).arg(dbname);
		db.setDatabaseName(dsn);
		//db.setHostName("DESKTOP-FTFFKM6");
		//db.setDatabaseName("QUsersDatabase");
		//db.setUserName("DESKTOP-FTFFKM6\Lejer");
		//db.setPassword("password");
		//

		bool ok = db.open();

		if (ok == false) {
			QMessageBox* m = new QMessageBox();
			m->setText(db.lastError().text());
			m->show();

		}
		else {
			QSqlQuery q;

			
			q.prepare("SELECT UserName FROM [UserTable] WHERE UserName = (:username)");
			q.bindValue(":username", QUser);
			ok = q.exec();
			if (ok == true && q.next()) {
				QMessageBox* m = new QMessageBox();
				m->setText("Username is taken!");
				m->show();
			}
			else {

				QString sqlCMD = "INSERT INTO [UserTable] (UserName, Password, FirstName, LastName, PhoneNumber) VALUES (?, ?, ?, ?, ?)";

				q.prepare(sqlCMD);
				q.addBindValue(QUser);
				q.addBindValue(QPassword);
				q.addBindValue(QFirstName);
				q.addBindValue(QLastName);
				q.addBindValue(QPhoneNumber);
				if (q.exec()) {
					QMessageBox* m = new QMessageBox();
					m->setText("User Created Succesfully");
					m->show();
					clearAllField(ui.user_filed, ui.password_field, ui.firstName_field, ui.lastNameField, ui.phoneNumber_field);
				}
			}

			db.close();
		}
	}
	

}

void QtGuiClassRegister::getQStringFromField(QLineEdit* userLineEdit, QLineEdit* passwordLineEdit, QLineEdit* firstNameLineEdit, QLineEdit* lastNameLineEdit, QLineEdit* phoneNumberLineEdit) {

	QUser = userLineEdit->text();
	QPassword = passwordLineEdit->text();
	QFirstName = firstNameLineEdit->text();
	QLastName = lastNameLineEdit->text();
	QPhoneNumber = phoneNumberLineEdit->text();

}
 
void QtGuiClassRegister::getStringFromQString(QString* q_user, QString* q_password, QString* q_firstName, QString* q_lastName, QString* q_phoneNumber) {
	
	user = q_user->toUtf8();
	password = q_password->toUtf8();
	firstName = q_firstName->toUtf8();
	lastName = q_lastName->toUtf8();
	phoneNumber = q_phoneNumber->toUtf8();

}

void QtGuiClassRegister::clearAllField(QLineEdit* userLineEdit, QLineEdit* passwordLineEdit, QLineEdit* firstNameLineEdit, QLineEdit* lastNameLineEdit, QLineEdit* phoneNumberLineEdit) {
	
	userLineEdit->clear();
	passwordLineEdit->clear();
	firstNameLineEdit->clear();
	lastNameLineEdit->clear();
	phoneNumberLineEdit->clear();
}


bool QtGuiClassRegister::checkLineEdit(QLineEdit* userLineEdit, QLineEdit* passwordLineEdit, QLineEdit* firstNameLineEdit, QLineEdit* lastNameLineEdit, QLineEdit* phoneNumberLineEdit) {
	
	int count = 0;
	QLineEdit* lineEditAray[5] = {userLineEdit,passwordLineEdit,firstNameLineEdit,lastNameLineEdit,phoneNumberLineEdit};

	for (int i = 0; i < 5; i++) {
		if (lineEditAray[i]->text().isEmpty()) {
				lineEditAray[i]->setStyleSheet("QLineEdit { background: rgb(0, 255, 255); selection-background-color: rgb(233, 99, 0); }");
				count++;
		}else {
			lineEditAray[i]->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(233, 99, 0); }");
		}
	}
	if (count > 0) {
		QMessageBox* m = new QMessageBox();
		m->setText("All fields must be completed!");
		m->show();
		return false;
	}
	else {
		return true;
	}

	/*if (userLineEdit->text().isEmpty()) {
		userLineEdit->setStyleSheet("QLineEdit { background: rgb(0, 255, 255); selection-background-color: rgb(233, 99, 0); }");
	}*/

}


void QtGuiClassRegister::handleNewDatabase() {
	
	
	DBManager* db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));


	if (checkLineEdit(ui.user_filed, ui.password_field, ui.firstName_field, ui.lastNameField, ui.phoneNumber_field) == true) {
		
		db->createUser(&this->ui.user_filed->text(), &this->ui.password_field->text(),
			&this->ui.firstName_field->text(), &this->ui.lastNameField->text(),
			&this->ui.phoneNumber_field->text());
		
		clearAllField(ui.user_filed, ui.password_field, ui.firstName_field, ui.lastNameField, ui.phoneNumber_field);
	}
	

}