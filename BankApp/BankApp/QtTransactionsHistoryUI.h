#pragma once

#include <QWidget>
#include "ui_QtTransactionsHistoryUI.h"
#include "DBManager.h"
#include "ClientAccount.h"

class QtTransactionsHistoryUI : public QWidget
{
	Q_OBJECT

public:
	QtTransactionsHistoryUI(QWidget *parent = Q_NULLPTR);
	QtTransactionsHistoryUI(ClientAccount* ,QWidget *parent = Q_NULLPTR);
	~QtTransactionsHistoryUI();
	void populateComboBox(QString*);
	

private slots:
	void showData();


private:
	Ui::QtTransactionsHistoryUI ui;
	DBManager* db;
	void getConnection();
};
