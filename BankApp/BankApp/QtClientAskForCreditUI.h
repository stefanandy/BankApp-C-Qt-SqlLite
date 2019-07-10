#pragma once

#include <QWidget>
#include "ui_QtClientAskForCreditUI.h"
#include "DBManager.h"

class QtClientAskForCreditUI : public QWidget
{
	Q_OBJECT

public:

	QtClientAskForCreditUI(QWidget *parent = Q_NULLPTR);
	QtClientAskForCreditUI(QString* , QWidget *parent = Q_NULLPTR);
	
	void GetComboBoxData(QString*);
	~QtClientAskForCreditUI();

private slots:
	void handleSendButton();

private:
	Ui::QtClientAskForCreditUI ui;
	DBManager* db;
	void dbOpen();
};
