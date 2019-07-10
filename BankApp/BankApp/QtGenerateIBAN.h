#pragma once

#include <QWidget>
#include "ui_QtGenerateIBAN.h"
#include "ClientAccount.h"
#include <QtSql>
#include <QSqlQuery>
#include <qmessagebox.h>
#include "DBManager.h"


class QtGenerateIBAN : public QWidget
{
	Q_OBJECT

public:
	QtGenerateIBAN(QWidget *parent = Q_NULLPTR);
	QtGenerateIBAN(ClientAccount* ,QWidget *parent = Q_NULLPTR);
	void ErrorMessage(QString*);
	~QtGenerateIBAN();

private slots:
	void createBankAccount();

private:
	Ui::QtGenerateIBAN ui;
	ClientAccount* clientAccount;
};
