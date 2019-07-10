#pragma once

#include <QWidget>
#include "ui_QtGetInfoUI.h"
#include "DBManager.h"

class QtGetInfoUI : public QWidget
{
	Q_OBJECT

public:
	QtGetInfoUI(QWidget *parent = Q_NULLPTR);
	QtGetInfoUI(ClientAccount*,QWidget *parent = Q_NULLPTR);
	
	void loadTableData();
	~QtGetInfoUI();

private:
	Ui::QtGetInfoUI ui;
	DBManager* db;
	ClientAccount* client;
	void getConnection();

};
