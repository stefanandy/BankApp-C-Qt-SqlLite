#pragma once

#include <QWidget>
#include "ui_QtGuiClassRegister.h"
#include "ClientAccount.h"
#include <string>
#include "DBManager.h"

class QtGuiClassRegister : public QWidget
{
	Q_OBJECT

public:
	QtGuiClassRegister(QWidget *parent = Q_NULLPTR);
	~QtGuiClassRegister();
	
	void getQStringFromField(QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*);
	void getStringFromQString(QString*, QString*, QString*, QString*, QString* );
	void clearAllField(QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*);
	bool checkLineEdit(QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*, QLineEdit*);

private slots:
	void handleRegisterAccount();
	void handleNewDatabase();

private:
	Ui::QtGuiClassRegister ui;
	string user, password, firstName, lastName, phoneNumber;
	QString QUser, QPassword, QFirstName, QLastName, QPhoneNumber;
	
};
