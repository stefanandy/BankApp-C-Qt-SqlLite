#pragma once

#include <QWidget>
#include "ui_QtAdminUnverifiedCreditsUI.h"
#include "DBManager.h"
#include "QtGetInfoUI.h"

class QtAdminUnverifiedCreditsUI : public QWidget
{
	Q_OBJECT

public:
	QtAdminUnverifiedCreditsUI(QWidget *parent = Q_NULLPTR);
	void populateBox();
	
	~QtAdminUnverifiedCreditsUI();

private slots:
	void getInfoButton();
	void approvedButton();

private:
	Ui::QtAdminUnverifiedCreditsUI ui;
	DBManager* db;
	void getConnection();
	QtGetInfoUI* infoUi;

};
