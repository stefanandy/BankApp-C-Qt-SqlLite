#pragma once

#include <QWidget>
#include "ui_QtAdminClass.h"
#include "DBManager.h"
#include "QtAdminUnverifiedCreditsUI.h"
#include "QtApprovedCreditsUI.h"

class QtAdminClass : public QWidget 
{
	Q_OBJECT

public:
	QtAdminClass(QWidget *parent = Q_NULLPTR);
	QtAdminClass(AdminAccount*, QWidget *parent = Q_NULLPTR);
	
	void populateTable();
	
	~QtAdminClass();

private slots:
	void unaprovedCreditsButton();
	void approvedCreditsButton();
	void refreshButton();

private:
	Ui::QtAdminClass ui;
	DBManager* db;
	void getDbConnection();
	AdminAccount* admin;
	QtAdminUnverifiedCreditsUI* unverifiedcreditsUI;
	QtApprovedCreditsUI* approvedCreditsUI;
};
