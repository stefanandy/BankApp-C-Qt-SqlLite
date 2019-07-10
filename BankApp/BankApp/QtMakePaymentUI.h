#pragma once

#include <QWidget>
#include "ui_QtMakePaymentUI.h"
#include "ClientAccount.h"
#include "DBManager.h"


class QtMakePaymentUI : public QWidget
{
	Q_OBJECT

public:
	QtMakePaymentUI(QWidget *parent = Q_NULLPTR);
	QtMakePaymentUI(ClientAccount*, QWidget *parent = Q_NULLPTR);
	void ibanLis(QString*);
	

	~QtMakePaymentUI();

private slots:
	void checkIBAN();
	void sendTransaction();

private:
	Ui::QtMakePaymentUI ui;
	ClientAccount* clientAccount;
	DBManager* db;
	void getConnection();
	void MouseEvent(QMouseEvent*);
};
