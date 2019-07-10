#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BankApp.h"
#include "QtAdminClass.h"
#include "QtGuiClassRegister.h"
#include "QtClientClass.h"
#include "DBManager.h"

class BankApp : public QMainWindow
{
	Q_OBJECT

public:
	BankApp(QWidget *parent = Q_NULLPTR);


	void getQStringfromField(QLineEdit*, QLineEdit*);
	bool checkLineEditData(QLineEdit*, QLineEdit*);
	void ErrorMessage(QString*);
	void ShowClientUI();

signals:
	void emitUserName(QString);

private slots:
	
	void handleRegisterButton();
	void handleNewLoginButton();
	
private:
	Ui::BankAppClass ui;
	QtAdminClass* adminUI;
	QtGuiClassRegister*  registerUI;
	QtClientClass* clientUI;
	//QtGuiClassClient* clientUI;
	QString userName, password;
	ClientAccount* clientAccount;
	
};
