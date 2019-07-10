#pragma once

#include <QWidget>
#include "ui_QtApprovedCreditsUI.h"
#include "DBManager.h"
#include "QtGetInfoUI.h"

class QtApprovedCreditsUI : public QWidget
{
	Q_OBJECT

public:
	QtApprovedCreditsUI(QWidget *parent = Q_NULLPTR);
	
	void populateTable();
	~QtApprovedCreditsUI();
private slots:
	void getInfoButton();

private:
	Ui::QtApprovedCreditsUI ui;
	DBManager* db;
	void getConnection();
	QtGetInfoUI* infoUi;
};
